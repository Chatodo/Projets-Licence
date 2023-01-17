#include "BinarySearchTree.h"
#include <stdlib.h>
#include "LinkedList.h"
#include "City.h"
#include "findCities.h"
#include "intersect.h"
#include <stdbool.h>
#include <stddef.h>


LinkedList* findCities (LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax);
int compare_doubles(const void* a, const void* b);

/* Ici nous avons la fonction qui compare deux variables de type double */
int compare_doubles(const void* a, const void* b) { 
	const double* a_ = (const double*)a;
	const double* b_ = (const double*)b;
	return (*a_ > *b_) - (*a_ < *b_);
}

LinkedList* findCities (LinkedList* cities,double latitudeMin,double latitudeMax,double longitudeMin,double longitudeMax) {
    /* On initialise 2 arbres */
    BinarySearchTree* bst = newBST(&compare_doubles);
    BinarySearchTree* bst2 = newBST(&compare_doubles);

    /* nous avons pris l'exemple de findCitiesList.c en changeant et en rajoutant quelque ligne : */

    LLNode* curr = cities->head;
    bool error = false;
    const City* city;

    while ( !error && curr != NULL) {
        city = (const City*)curr->value;

        /*  On Stocke les villes dans deux arbres binaires de recherche. 
            Le premier admet comme clé les latitudes des villes 
            Et le second leurs longitudes.
            Nous verifions aussi si les valeurs on bien etait inserer 
            sinon on libere la memoire et on sort de la boucle
         */
        if ( !(insertInBST(bst, &(city)->latitude, city)) ) {
            freeBST(bst,false);
            error = true;
            return NULL;
        }

        if ( !(insertInBST(bst2,&(city)->longitude, city)) ) {
            freeBST(bst2,false);
            error = true;
            return NULL;
        }

        curr = curr->next;
    }

    /* On recherche Sφ, toutes les villes qui sont comprises entre deux latitudes */
    LinkedList* b = getInRange(bst,&(latitudeMin),&(latitudeMax));
    if (!b) {
        freeBST(bst,false);
        freeLinkedList(b,false);
        return NULL;
    }

    /* On recherche Sλ, toutes les villes qui sont comprises entre deux longitudes */
    LinkedList* c = getInRange(bst2,&(longitudeMin),&(longitudeMax));
    if (!c) {
        freeBST(bst2,false);
        freeLinkedList(c,false);
        return NULL;
    }

    /* Et enfin on calcule l’intersection de ces deux ensembles : S = Sφ ∩ Sλ.
        On utilise la fonction intersect 
    */
    LinkedList* l = intersect(b, c, &compare_doubles);
    if (!l) {
        freeBST(bst,false);
        freeBST(bst2,false);
        freeLinkedList(b,false);
        freeLinkedList(c,false);
        return NULL;
    }

    /* On libere la memoire */
    freeBST(bst,false);
    freeBST(bst2,false);
    freeLinkedList(b,false);
    freeLinkedList(c,false);

    /* On renvoie la liste avec les villes qui sont comprises entre les longitudes et latitudes (Min et Max) 
        donné par l'utilisateur
    */
    return l;
}


