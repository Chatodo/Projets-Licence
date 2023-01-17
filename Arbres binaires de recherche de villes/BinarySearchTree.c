#include "BinarySearchTree.h"
#include <stdlib.h>
#include "LinkedList.h"
#include <stdio.h>

// structure d'un noeud d'un arbre
typedef struct node_t 
{
	const void* clef; // latitude ou longitude (voir zscore pour plus tard)
	const void*  valeur; //ville 
	struct node_t* fg; //fils gauche de l'arbre
	struct node_t* fd;	//fils droit de l'arbre
}node_t;

/*structure de l'arbre*/
struct tree_t { 
	struct node_t * racine; //racine de l'arbre correspondant à un noeud
	int (*comparison_fn_t)(const void*,const void*); //pour savoir si on utilise la fonction int (*compare_doubles)(const void*,const void*) et pas celle des "int"
};


/* ------------------------------------------------------------------------- *
 * Retourne la taille du noeud entré en argumnent
 *
 * PARAMETERS
 * n          pointeur vers un noeud
 *
 * RETURN
 * size_t 		la taille du noeud
 * ------------------------------------------------------------------------- */
size_t sizeOfNode(node_t * n);

/* ------------------------------------------------------------------------- *
 * Si la clef de l'arbre est égale à la clef de l'argument return la valeur du noeud sinon on verifie dans les fils du noeud
 *
 * PARAMETERS
 * n         Un pointeur vers un noeud
 * key       une clef avec un type volatile 
 *
 * RETURN
 * n->valeur           return l'élément correspondant à la clef et null si le noeud est vide
 * ------------------------------------------------------------------------- */
const void* searchnode(node_t* n, const void* key);

/* ------------------------------------------------------------------------- *
 * Libere la mémoire du noeud en fontion si le boolean en argument est vrai ou faux
 *
 * PARAMETERS
 * n          pointeur vers un noeud
 * boolean    nous dit si on free ou non  
 * ------------------------------------------------------------------------- */
void freeN(node_t* n, bool freeContent);

/* ------------------------------------------------------------------------- *
 * Crée un nouveau noeud avec les arguments x en clef et y valeur
 *
 * PARAMETERS
 * x        un éléments correspondant à la clef
 * y		un éléments correspondant à la valeur
 *
 * RETURN
 * p           un node_t*
 * ------------------------------------------------------------------------- */
node_t* new_node(const void* x, const void* y);

/* ------------------------------------------------------------------------- *
 * Met dans une liste dans l'ordre les valeurs en fonction des clefs dans l'arbre binaire de recherche dans l'intervalle keymin keymax
 * 
 *
 * PARAMETERS
 * listevaleur         une pointeur de liste chainé
 * A                   un pointeur vers un noeud
 * keyMin              une valeur correspondant au keymin
 * keyMax              une valeur correspondant au keymax
 * int compare_doubles(const void*a, const void*b)	la fonction permettant de comparer les éléments (par forcement compare_doubles c'est juste le nom)
 * 
 * 
 * ------------------------------------------------------------------------- */
void fonctionA(LinkedList* listevaleur, node_t* A, void* keyMin, void* keyMax, int compare_doubles(const void*a, const void*b) );



BinarySearchTree* newBST(int comparison_fn_t(const void *, const void *)){
	BinarySearchTree *arbre1= malloc(sizeof(BinarySearchTree)); //alloue de la memoire

	//si l'allocation à fonctionné on initialise les paramètres de arbre1
	if (arbre1 != NULL) {
		arbre1->racine=NULL;
		arbre1->comparison_fn_t = comparison_fn_t;
		return arbre1;
	}
	else {
		return NULL;//return NULL si l'allocation a échoué
	}
}

void freeN(node_t* n, bool freeContent){
	//Si noeud est null on return directement
    if ( n == NULL ) {
        return;
    }
    freeN(n->fd,freeContent);//on libère le fils droit
    freeN(n->fg,freeContent);//puis le gauche
    free(n);//puis la racine
}

void freeBST(BinarySearchTree* bst, bool freeContent){
		freeN(bst->racine,freeContent); //on libère le noeud
		free(bst); //puis l'arbre
}

size_t sizeOfNode(node_t * n){
	//Si noeud null taille = 0
    if (n == NULL) {
        return 0;
    }
    //sinon on fait par recursion la taille du fils droit + taille fils gauche +1
    else {
        return 1 + sizeOfNode(n->fd) + sizeOfNode(n->fg);
    }
}

size_t sizeOfBST(const BinarySearchTree* bst){
	//la taille de l'arbre == la taille du noeud de la racine
      return sizeOfNode(bst->racine);
} 

node_t* new_node(const void* x, const void* y){
    node_t *p;
    p = malloc(sizeof(struct node_t));
    p->clef = x;
    p->valeur = y;
    p->fg= NULL;
    p->fd = NULL;
    return p;
} 

bool insertInBST(BinarySearchTree * bst, const void* key, const void* value){ 
    node_t *node1;
    node_t *node2;
    //cellule que l'on ajoute dans l'arbre
    node_t* nodePremier = new_node(key,value);
    if ( nodePremier == NULL) {
        return false;
    }

    node1 = NULL;
    node2 = bst->racine;

    //on parcours l'arbre,on met node1 au bonne endroit selon la cléf.
    while ( node2 != NULL ) {
        node1 = node2;
        //On compare key et la cléf de node2 si key est plus petite que le noeud2, il est égale au fils gauche 
        if ( bst->comparison_fn_t(key,node2->clef) < 0 ) {
            node2 = node2->fg;
        }
        //sinon le noeud2 est égale au fils droit
        else {
            node2 = node2->fd;
        }
    }
    
    //Si le noeud1 est null il est égale à nodePremier
    if ( node1 == NULL){
        bst->racine = nodePremier;
    }
    else {
    	//sinon si la cléf est inferieur à node1, la clef on la met à gauche
        if ( bst->comparison_fn_t(key,node1->clef) < 0 ) {
            node1->fg = nodePremier;
        }
        //sinon à droite
        else {
            node1->fd = nodePremier;
        }
    }
//si tout c'est bien passé on return true
    return true;   
}



const void* searchnode(node_t* n, const void* key){
	if ( n == NULL ) {
    	return NULL;
    }
    else if ( n->clef == key ) {
    	return n->valeur;
    }
    //si la cléf est inferieur on fait un appel recursive sur le fils gauche du noeud
    else if ( key < n->clef ) {
    	return searchnode(n->fg,key);
    }
    //sinon sur le fils droit
    return searchnode(n->fd,key);
    
}

const void* searchBST(BinarySearchTree* bst, const void* key){
    return searchnode(bst->racine, key);
}



void fonctionA(LinkedList* listevaleur, node_t* A, void* keyMin, void* keyMax, int comparison_fn_t(const void *, const void *) ){
	if ( A == NULL ) { // si l'arbre est vide on ne fais rien
		return;
	}

	if (( comparison_fn_t(keyMin, A->clef) < 0 ) || (comparison_fn_t(keyMin, A->clef) == 0)) {
		if (( comparison_fn_t(keyMax, A->clef) > 0 ) || ( comparison_fn_t(keyMax, A->clef) == 0 )) {
			insertInLinkedList(listevaleur, A->valeur);  // si la clef est entre le keymin et keymax on insert sa valeur
		}
	}

	if ( comparison_fn_t(keyMin, A->clef) < 0) {   // si la clef est superieur a keymin on utilise la recursivité et on vas a gauche
		fonctionA(listevaleur, A->fg, keyMin, keyMax, comparison_fn_t);
	}

	if ( comparison_fn_t(keyMax, A->clef) > 0) {  // si la clef est inferieur a keymax on utilise la recursivité et on vas a droite
		fonctionA(listevaleur, A->fd, keyMin, keyMax, comparison_fn_t);
	}
}

LinkedList* getInRange(const BinarySearchTree* bst, void* keyMin, void* keyMax){
	LinkedList* liste2= newLinkedList(); // on cree une nouvelle liste
	if (!liste2) {
		return NULL;
	}
	fonctionA(liste2,bst->racine,keyMin,keyMax,bst->comparison_fn_t); // on utilise la fonction Auxiliaire (fonctionA)
	return liste2; // on retourne la liste avec les valeurs entre keymin et keymax 
}    