#ifndef _SERVEUR_H_
#define _SERVEUR_H_
#include <sys/socket.h>
#include <netinet/in.h>
//KRIVOKUCA Ivan 11807642 SI ALI Aghiles 11806989

/**
 * Structure d'un joueur qui se connecte sur le serveur
 * Celle-ci est composé d'un nom (20 caractères max)
 * Un socket qui lui est propre et qui va servir a communiquer avec lui
*/
struct joueur_s{
	char nom[20];
	int sock;
};
typedef struct joueur_s joueur_t;

/**
 * Permet de changer la variable global interuption a 1 et ferme le socket principal
 * @param signal le signal du PID 
 * @author Ivan KRIVOKUCA
*/
void set_interuption(int);

/**
 * Initialise la structure sockaddr_in pour que la socket qui y sera liée
 * puisse communiquer avec toutes les adresses ips possibles, sur le port 'port_serveur'
 * @param serveur est un pointeur vers la structure que l'on souhaite initialiser
 * @param port_serveur est le port auquel la socket sera liée.
 * @require serveur != NULL
*/
void init_sockaddr_in(struct sockaddr_in*, short);

/**
 * Initialise une socket permettant d'accepter des connexions en TCP depuis n'importe
 * qu'elle adresse IP.
 * @param serveur est un pointeur vers la structure que l'on souhaite initialiser
 * @param port_serveur est le port auquel la socket sera liée.
 * @require serveur != NULL
 * @return une socket pouvant accepter des connexions si aucune erreur de survient,
 * quitte le programme sinon.
*/
int initialiser_socket(struct sockaddr_in*, short);

/**
 * Recherche dans un tableau de joueur son socket qui lui est associé
 * Retourne sa position s'il se trouve 
 * @param sock le socket associé au joueur qui sera comparé a la liste de joueur
 * @return la position du joueur s'il est présent sinon retourne -1
 * @author Ivan KRIVOKUCA
 * @require joueur_t[] != NULL
*/ 
int recherche_joueur(int);

/**
 * Dès que le client se connecte, le serveur recevra le nom du joueur
 * et écrira dans a la position nb_client dans le tableau joueur_t[] le nom et le socket
 * @param sock la socket du client
 * @return 1 si la création a pu se faire sinon 0
 * @requires nb_client < MAX
 * @author Ivan KRIVOKUCA SI ALI Aghiles 
*/
int creer_client(int);

/**
 * Renvoie la taille du fichier donné en chemin
 * @param chemin le chemin du fichier
 * @return taille du fichier sinon 0
 * @ensures st.st_size > 0 si le fichier != NULL
 */
size_t taille_fichier(const char*);

/**
 * Charge le contenu du fichier "chemin" de taille "taille" dans la chaine de caractère "chaine"
 * @param chemin le chemin du fichier
 * @param chaine la chaine de caractère qui contiendra
 * @param taille la taille du fichier
 * @return 1 si le chargement du contenu a bien été fait sinon 0
 * @require chemin,chaine,taille != NULL
 * @require taille = "sizeof(chemin)" 
 * @author Ivan KRIVOKUCA 
 */
int chargement_texte(const char*, char*, size_t);

/**
 * Ecrit dans un fichier intitulé "nom" (le nom du client) le chemin du dernier texte ouvert ou le client s'est arrêté
 * Dans le but de reprendre ou l'utilsateur s'est arrêté
 * @param nom, le nom du client
 * @param chemin, le chemin du du dernier texte recu par l'utilisateur
 * @require nom != NULL && chemin != NULL
 * @author Ivan KRIVOKUCA
 */
void sauvegarde(char*, char*);

/**
 * Alloue une chaîne de caractère de la taille du fichier
 * Charge le contenu de cette chaine avec la fonction chargement_texte
 * Si celle-ci a bien chargé on envoie au client
 * @param sock le socket du client
 * @param chemin le chemin du fichier qu'on veut envoyé
 * @return 1 si on a bien envoyé sinon 0  
 * @author Ivan KRIVOKUCA
 */
int envoyer_texte(int, char*);

/**
 * Menu du jeu pour le serveur, tout d'abord celui-ci va voir s'il n'y a pas
 * de fichier sauvegarde associé au client (grace au nom) s'il y'en a un alors il va appeler la fonction jeu_solo_sauvegarde
 * S'il n'y a pas de sauvegarde alors celui-ci va envoyer l'intro du jeu
 * Et va recevoir le choix du joueur -> si 1 alors on appelle jeu_solo
 * Sinon il quitte
 * Il sera affiché le choix du joueur sur le terminal
 * @param sock la socket du client
 * @author SI ALI Aghiles 
 */
void menu_jeu(int);

/**
 * Fonction principale du jeu, permet d'envoyer les chaines de caractères a l'utilisateur
 * Le serveur recoit lequel des fichiers il va envoyer la chaine de caractère
 * S'il celui-ci doit se fermer alors il met fin au jeu
 * Tant qu'il n'a pas reçu du client que celui-ci a fini le jeu alors il envoie les fichiers correspondant
 * @param sock le socket du client
 * @requires commun/ != NULL
 * @author Ivan KRIVOKUCA
 */
void jeu_solo(int);

/**
 * Même procédé que menu_jeu sauf qu'on reprend ou l'utilisateur s'est arrêté
 * @param sock le socket du client
 * @requires la sauvegarde du nom du client est présente 
 */
void jeu_solo_sauvegarde(int);
/**
 * Fonction qui sera executé pour chaque thread et que chaque client exectura
 * Servira ensentilement de comunication entre lui et le client
 * @param arg le socket du client
 * @require thread != NULL --> thread a été crée
 * @author Ivan KRIVOKUCA
*/
void* fonction_serveur(void *);


#endif