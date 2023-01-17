#include "BinarySearchTree.h"
#include <stdlib.h>
#include "LinkedList.h"
#include "City.h"
#include "findCities.h"
#include <stdbool.h>
#include <stddef.h>
#include "zscore.h"

LinkedList* findCities(LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax);
LinkedList* findCitiesZ(LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax);
int compare_unit64(const void* a, const void* b);

/* Ici nous avons la fonction compare d'entier en 64 bits */
int compare_unit64(const void* a, const void* b) { 
    uint64_t* a_ = (uint64_t*)a;
    uint64_t* b_ = (uint64_t*)b;
    return (*a_ > *b_) - (*a_ < *b_);
}


LinkedList* findCitiesZ(LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax) {
    BinarySearchTree* bst = newBST(&compare_unit64);  // on cree un nouvel arbre

    LLNode* curr = cities->head;
    size_t i;
    const City* city;

    /* On alloue de la memoire pour creer un tableau d'apres le code de morton : 
        https://en.wikipedia.org/wiki/Z-order_curve  
    */
    uint64_t* zscore = malloc(sizeof(uint64_t)*cities->size); 


    /* Nous parcourons le tableau, on transforme la latitude et la longitude en Z-Score
        et on insere dans l'arbre binaire de recherche 
    */
    for ( i=0; i < cities->size; i++ ) {
        city = (const City*)curr->value; 
        zscore[i] = zEncode(city->latitude,city->longitude); 
        insertInBST(bst,&(zscore[i]),city);
        curr = curr->next;
    }

    /* On cree un zscore min et max : Z(φm, λm) et Z(φM, λM) */
    uint64_t min = zEncode(latitudeMin,longitudeMin);
    uint64_t max = zEncode(latitudeMax,longitudeMax);


    /* On recherche SZ, toutes les villes dont les clés sont comprises entre Z(φm, λm) et Z(φM, λM) 
       où φm = min{φ1, φ2}, λm = min{λ1, λ2}, φM = max{φ1, φ2} et λM = max{λ1, λ2}. 
    */
    LinkedList* b = getInRange(bst,&(min),&(max));
    if (!b) {
        free(zscore);
        freeBST(bst,false);
        freeLinkedList(b,false);
        return NULL;
    }

    /* On filtre SZ pour ne garder que l’ensemble S des bonnes villes */
    LinkedList* l = findCities(b,latitudeMin,latitudeMax,longitudeMin,longitudeMax);
    if (!l) { // On procede a une verification 
        free(zscore);
        freeBST(bst,false);
        freeLinkedList(b,false);
        freeLinkedList(l,false);
        return NULL;
    }

    /* On libere de la memoire */
    free(zscore);
    freeBST(bst,false);
    freeLinkedList(b,false);
    freeLinkedList(l,false);

    /* On retourne la liste avec les bonnes villes comprises entre les Zscore min et max */
    return l; 
}


/* nous avons repris la notion de filtrage de findCitiesList.c : */

LinkedList* findCities(LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax) {
    // Create return object
    LinkedList* filtered = newLinkedList();
    if (!filtered)
        return NULL;

    // Filter the cities
    LLNode* curr = cities->head;
    bool error = false;
    const City* city;
    while(!error && curr != NULL)
    {
        city = (const City*)curr->value;
        if(latitudeMin <= city->latitude && city->latitude <= latitudeMax &&
           longitudeMin <= city->longitude && city->longitude <= longitudeMax)
            error = error  || !insertInLinkedList(filtered, curr->value);
        curr = curr->next;
    }
    // Free in case of error
    if(error)
    {
        freeLinkedList(filtered, false);
        return NULL;
    }
    return filtered;
}