#include "BinarySearchTree.h"
#include "intersect.h"
#include "LinkedList.h"
#include <stdlib.h>

/* Retourne l'intersection de deux listes chainées dans une nouvelle liste chainée.
 */

LinkedList* intersect(const LinkedList* listA, const LinkedList* listB, int comparison_fn_t(const void *, const void *)){
    LinkedList* res = newLinkedList(); // initialise une liste vide qui sera ensuite retourner
    //Erreur de l'allocation
    if ( res == NULL ) {
        return NULL;  
    }   

    LLNode* A = listA->head; // A prend la tete de la liste listeA
    LLNode* B;

    //Comparaison de chaque élément, on compare la value de listA avec toutes les valeurs de la listB en parcourant les listes
    for ( size_t i=0; i < sizeOfLinkedList(listA); i++ ) { 
        B = listB->head; // B prend la tete de la liste listeB
        for ( size_t j=0; j < sizeOfLinkedList(listB); j++ ) {
            if ( comparison_fn_t(A->value, B->value) == 0 ) {
                insertInLinkedList(res, A->value);
            }
            B = B->next;
        }
        A = A->next;    
    }
    return res;
}
