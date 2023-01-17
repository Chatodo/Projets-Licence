#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <sys/socket.h>
#include <netinet/in.h>
//KRIVOKUCA Ivan 11807642 SI ALI Aghiles 11806989

/**
 * Annule le signal CTRL-C de l'utilisateur
 * @param signal qui est le PID
 * @author KRIVOKUCA Ivan SI ALI Aghiles 
*/
void annuler_signal(int);

/**
   Initialise la structure sockaddr_in pour que la socket qui y sera liée
   puisse communiquer avec le serveur d'adresse 'ip_serveur', sur le port 'port_serveur'
   @param serveur est un pointeur vers la structure que l'on souhaite initialiser
   @param port_serveur est le port sur serveur avec lequel on souhaite communiquer
   @param ip_serveur est l'adresse du serveur avec lequel on souhaite communiquer
   @require serveur != NULL && ip_serveur != NULL
*/
void init_sockaddr_in(struct sockaddr_in *, unsigned short, char *);

/**
   Etablit une connexion TCP avec le serveur d'adresse 'ip_serveur' sur le port 'port_serveur'.
   Initialise les structures `serveur` et `moi`,
   qui contienne des informations sur l'ip et le port utilisés par les deux points d'accès.
   @param ip_serveur est l'adresse du serveur auquel on se souhaite se connecter
   @param port_serveur est le port sur serveur auquel on se souhaite se connecter
   @param serveur est un pointeur vers la structure représentant les informations du serveur
   @param moi est un pointeur vers la structure représentant les informations du client
   @require serveur != NULL && client != NULL && ip_serveur != NULL
   @return la socket conectée au serveur, quitte le programme en cas d'échec.
*/
int initialiser_socket(char *, short, struct sockaddr_in *, struct sockaddr_in *);

/**
 * Envoie un message au client venant du serveur pour demander a l'utilisateur
 * d'entrer un nom qui sera ensuite envoyé au serveur
 * @require strlen(nom) < 20
 * @require client connecté au serveur
 * @author SI ALI Aghiles 
 */
void envoyer_serveur_nom(int);

/**
 * Renvoie la taille du fichier donné en chemin
 * @param chemin le chemin du fichier
 * @return taille du fichier sinon 0
 * @ensures st.st_size > 0 si le fichier != NULL
 */
size_t taille_fichier(const char*);

/**
 * Ouvre le fichier qui a pour nom le client dont il a une sauvegarde
 * Charge le contenue de cette chaine dans la variable chaine
 * Envoie cette chaine au serveur qui va comprendre a l'endroit ou il s'est arreté
 * @param nom, le nom du fichier
 * @param sock le socket du client
 * @param chaine la chaine de caractètre ou sera stocker ce qu'il a dans le fichier
 * @return 1 si ça s'est bien passé sinon 0
 * @requires nom != NULL
 * @author SI ALI Aghiles KRIVOKUCA Ivan
 */
int charger_sauvegarde(char[], int, char[]);


/**
 * Vérifie dans une chaîne de caractère si la chaîne "FIN" est présent
 * @return 0 si elle est présente sinon 1
 * @param chaine la chaine de caractère qui sera comparé pour voir si "FIN" est présent
 * @author KRIVOKUCA Ivan
 */
int recherche_fin(char *);

/**
 * Fonction servant a l'alégé "echange_avec_serveur" 
 * Lit tout les messages du serveur et les affiches tant qu'il n'y a pas la chaine "FIN"
 * @param message la chaîne de caractère transmise au client
 * @param sock le socket du client
 * @author KRIVOKUCA Ivan SI ALI Aghiles 
 * @require client connecté <==> sock est bien valide
 * @require message != NULL
 * @ensure char = ...."FIN".... sort du jeu 
 */
void jeu_solo(char[],int);
/**
 * Le même fonctionement que jeu_solo a la différence que celui-ci
 * est appelle s'il y'a un fichier de sauvegarde présent
 * On ouvre le fichier et puis on fait le même fonctionement que jeu_solo
 * Supprime le fichier si il arrive a la fin
 * @require chemin != NULL
 * @require message bien alloué
 * @author KRIVOKUCA Ivan SI ALI Aghiles
 */
void jeu_solo_sauvegarde(char message[],int sock, char chemin[]);

/**
 * Fonction principal, initialise une chaîne de caractère qui sera la recepetion des messages du serveur
 * demande le nom a l'utilisateur puis lui l'introduction qui est donné par le serveur
 * Demande a l'utisateur s'il veut jouer ou quitter
 * Appelle jeu_solo s'il a décidé de rentrer 1
 * Sinon quitte
 * @param sock, le socket du client 
 * @ensure client.nom défini
 * @author KRIVOKUCA Ivan SI ALI Aghiles 
 */
void echange_avec_serveur(int);



#endif