#include "BinarySearchTree.h"
#include <stdlib.h>
#include "LinkedList.h"
#include "City.h"
#include "findCities.h"
#include <stdbool.h>
#include <stddef.h>


LinkedList* findCities2(LinkedList* cities,double longitudeMin,double longitudeMax);
LinkedList* findCities (LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax);
int compare_doubles(const void* a, const void* b);

/* Ici nous avons la fonction qui compare deux variables de type double */
int compare_doubles(const void* a, const void* b) { 
	const double* a_ = (const double*)a;
	const double* b_ = (const double*)b;
	return (*a_ > *b_) - (*a_ < *b_);
}

LinkedList* findCities (LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax) {
    
    BinarySearchTree* bst = newBST(&compare_doubles); /* on cree un nouvel arbre */

    /* nous avons pris l'exemple de findCitiesList.c en changeant et en rajoutant quelque ligne : */

    LLNode* curr = cities->head;
    bool error = false;
    const City* city;

    while ( !error && curr != NULL) {
        city = (const City*)curr->value;

        /* on insert la latitude des villes dans l'arbre
            si on n'insert pas on libere la memoire et on sort de la boucle
        */
        if ( !(insertInBST( bst, &(city)->latitude, city)) ) {
            freeBST(bst,false);
            error = true;
            return NULL;
        }
        /* tant que l'element suivant n'est pas nul on insert dans l'arbre */
        curr = curr->next; 
    }

    /* On recherche Sφ, l’ensemble des villes comprises entre deux latitudes. */ 
    LinkedList* b = getInRange(bst,&(latitudeMin),&(latitudeMax));
    if (!b) { // On pose une condition si rien n'est inserer dans la liste b 
        freeBST(bst,false);
        freeLinkedList(b,false);
        return NULL;
    }
    
    /* On filtre Sφ pour ne garder que les villes comprises entre deux longitudes S. */
    LinkedList* l = findCities2(b,longitudeMin,longitudeMax);
    if (!l) { // On pose une condition si rien n'est inserer dans la liste l
        freeBST(bst,false);
        freeLinkedList(b,false);
        freeLinkedList(l,false);
        return NULL;
    }

    /* On libere la memoire */
    freeBST(bst,false);
    freeLinkedList(b,false);

    /* On renvoie la liste avec les villes qui sont  comprises entre les longitudes et latitudes (Min et Max) 
        donné par l'utilisateur.
    */
    return l; 
}

/* Nous avons repris la notion de filtrage de findCitiesList.c en ne prenant que la longitude(Min et Max) : */

LinkedList* findCities2(LinkedList* cities,double longitudeMin,double longitudeMax)
{
    // Create return object
    LinkedList* filtered = newLinkedList();
    if (!filtered)
        return NULL;

    // Filter the cities
    LLNode* curr = cities->head;
    bool error = false;
    const City* city;

    while (!error && curr != NULL) {

        city = (const City*)curr->value;

        if ( ( longitudeMin <= city->longitude ) && ( city->longitude <= longitudeMax ) ){
            error = error  || !insertInLinkedList(filtered, curr->value);
        }
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


