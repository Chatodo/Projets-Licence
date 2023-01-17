#define _GNU_SOURCE //pour utiliser asprintf
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>   
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "serveur.h"

#define MAX 10
joueur_t joueur[MAX];
unsigned int nb_client = 0;
int interuption = 1;
int socket_s;

void set_interuption(int signal){
	interuption = 0;
	close(socket_s);
}

void init_sockaddr_in(struct sockaddr_in * serveur, short mon_port){
  	//On précise que c'est une socket réseau
  	serveur->sin_family = AF_INET;
  	//On initialise le port
  	serveur->sin_port = htons(mon_port);
  	//On accepte une connexion de toutes les IPs possibles.
  	serveur->sin_addr.s_addr = htonl(INADDR_ANY);
}

int initialiser_socket(struct sockaddr_in * serveur, short mon_port){
	int sock;
	init_sockaddr_in(serveur, mon_port);

  	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Erreur lors de la création de socket TCP\n");
		exit(EXIT_FAILURE);
	}

  	if(bind(sock, (struct sockaddr *) serveur, sizeof(struct sockaddr_in)) < 0){
		printf("Erreur lors de l'appel à la fonction bind\n");
		exit(EXIT_FAILURE);
	}

  	listen(sock, MAX);
  	return sock;
}

int recherche_joueur(int sock){
	for(int i = 0; i< MAX; i++){
		if(joueur[i].sock == sock)
			return i;
	}
	return -1;
}

int creer_client(int sock){
	if(nb_client < MAX){
		char *message = "Bienvenue sur le jeu, entrer votre nom d'utilisateur";
		send(sock , message , strlen(message)+1,0);

		//On écrit dans le tableau le nom du client 
		if(read(sock, joueur[nb_client].nom, 20) > 0){
			//On lui donne son numéro de socket pour le trouver plus facilement et intéragir avec lui
			joueur[nb_client].sock = sock;
			nb_client++;
			return 1;
		}
	}
	else{
		printf("La charge maximale a été ateinte\n");
		close(sock);
	}
	return 0;
}

size_t taille_fichier(const char* chemin){
	struct stat st; 

	if (stat(chemin, &st) == 0)
		return st.st_size;
	return 0; 
}

int chargement_texte(const char* chemin, char* chaine, size_t taille){
	FILE* f = fopen(chemin,"r");

	if(f == NULL)
		return 0;
	else{
		fread(chaine,sizeof(char),taille,f);
		fclose(f);
		return 1;
	}
}

void sauvegarde(char* nom, char* chemin){
	//On créer le fichier s'il n'existe pas
	FILE *f = fopen(nom,"w+");
	if(f == NULL)
		return;
	fwrite(chemin,sizeof(char), strlen(chemin),f);
	fclose(f);
}


int envoyer_texte(int sock, char* chemin){
	char* chaine;
	chaine = malloc(taille_fichier(chemin)+1*sizeof(char));
	if(chaine == NULL)
		return 0;
	//Corrige une erreur de valgrind
	memset(chaine, 0 , taille_fichier(chemin)+1);
	//Si le fichier existe alors on affecte ce qu'il a dans chaine
	if(chargement_texte(chemin,chaine,taille_fichier(chemin)+1)){
		send(sock , chaine , strlen(chaine)+1,0);
		free(chaine);
		return 1;
	}
	return 0;
}

void menu_jeu(int sock){
	joueur_t client_j = joueur[recherche_joueur(sock)];
	int choix;
	struct stat buffer;
	int sauvegarde_presente;
	//On regarde s'il y'a un fichier du nom du client
	sauvegarde_presente = stat(client_j.nom,&buffer);
	//Le fichier est présent
	if(sauvegarde_presente == 0){
		printf("Il y'a une sauvegarde pour lui\n");
		jeu_solo_sauvegarde(sock);
		return;
	}

	envoyer_texte(sock,"commun/Intro");
	recv(sock, &choix, sizeof(int), 0);

	switch (choix){
	case 1:
		printf("Le joueur %s fait du solo\n",client_j.nom);
		jeu_solo(sock);
		break;
	case 2:
		printf("Le joueur %s a quitté\n",client_j.nom);
		break;
	}
}

void jeu_solo(int sock){
	unsigned int jeu = 1;
	joueur_t client_j = joueur[recherche_joueur(sock)];
	int i = 1;
	char *num;
	char chemin[100] ="commun/";
	char tmp[4] ="";

	envoyer_texte(sock,"commun/Jeu");
		do{
			//Le serveur procède au gracefull shutdown
			if(interuption == 0){
				sauvegarde(client_j.nom, chemin);
				char* fin = "Désolé le serveur doit fermer.. FIN du jeu.\nMais vous pouvez reprendre où vous étiez (même nom svp)";
				send(sock , fin , strlen(fin)+1, 0);
				break;
			}

			//On recoit le choix du client
			if(recv(sock, tmp, 4, 0) > 0){
				if(tmp[0] == 'Z'){
					sauvegarde(client_j.nom, chemin);
					break;
				}
				//Permet de concatener un char et un int car celui-ci va s'allouer
				asprintf(&num, "%d", i);
				//On concatene la variable i avec le choix de l'utilisateur
				strcat(tmp, num);
				free(num); //asprintf alloue de la memoire
				//On concatener tout la chaine, c-a-d le chemin avec le choix
				strcat(chemin, tmp);
				printf("Le joueur %s a demandé le fichier %s\n",client_j.nom,chemin);

				//On verifie bien que ce fichier existe et on envoie
				if(envoyer_texte(sock,chemin)){
					//Le client va envoyer s'il a recu la chaine de caractère FIN pour mettre fin a la boucle
					recv(sock, &jeu, sizeof(unsigned int), 0);
					i++;
				}
				else{
					char* fin = "Fichier pas trouvé, ERREUR FIN\n";
					send(sock , fin , strlen(fin)+1, 0);
					break;
				}
			}
		} while(jeu);
}

void jeu_solo_sauvegarde(int sock){
	char chemin[100] = "";
	recv(sock, chemin, 100, 0);
	unsigned int jeu = 1;
	joueur_t client_j = joueur[recherche_joueur(sock)];
	//On recupere le dernier chiffre de la sauvegarde
	int i = chemin[strlen(chemin) -1 ] - '0';
	i++;
	char *num;
	char tmp[4] = "";
	do{
		if(interuption == 0){
			sauvegarde(client_j.nom, chemin);
			char* fin = "Désolé le serveur doit fermer.. FIN du jeu.\nMais vous pouvez reprendre où vous étiez (même nom svp)";
			send(sock , fin , strlen(fin)+1, 0);
			break;
		}

		if(recv(sock, tmp, 4, 0) > 0){
			if(tmp[0] == 'Z'){
				sauvegarde(client_j.nom, chemin);
				break;
			}

			asprintf(&num, "%d", i);
			strcat(tmp, num);
			free(num);
			strcat(chemin, tmp);
			printf("Le joueur %s a demandé le fichier %s\n",client_j.nom,chemin);

			if(envoyer_texte(sock,chemin)){
				recv(sock, &jeu, sizeof(unsigned int), 0);
				i++;
			}
			else{
				char* fin = "Fichier pas trouvé, ERREUR FIN\n";
				send(sock , fin , strlen(fin)+1, 0);
				break;
			}
		}
	}while(jeu);
}

void* fonction_serveur(void *arg){
	joueur_t client_j = joueur[recherche_joueur(*(int*)arg)];
	printf("%s est connecté au serveur\n",client_j.nom);
	menu_jeu(*(int*)arg);
	//On ferme le socket
	printf("Je ferme le socket de %s\n",client_j.nom);
	close(*(int*)arg);
	return NULL;
} 

int main(int argc , char *argv[]){
	int client_sock;
	struct sockaddr_in serveur , client;
	int len = sizeof(client);
	short port;
	
	if (argc!=2){
		fprintf(stderr,"usage: %s port\n", argv[0]);
		return EXIT_FAILURE;
  	}
  	port = atoi(argv[1]);
	socket_s = initialiser_socket(&serveur, port);
	pthread_t thread[MAX];
	signal(SIGINT,set_interuption);
	signal(SIGPIPE, SIG_IGN); //il arrive que le client lorsque il déconnecte "tue" le tube de communication donc il femre le serveur, on décide de l'ignorer
	while(interuption){	
		client_sock = accept(socket_s, (struct sockaddr *)&client, (socklen_t *) &len);
			
		if(interuption == 0)
			close(client_sock);

		if(creer_client(client_sock)){
				
			if(pthread_create(&thread[nb_client], NULL, fonction_serveur, (void*) &client_sock) < 0){
				perror("Erreur de thread");
				return 1;
			}
		}
	}

	printf("Fermeture des threads\n");
	for(int i = 1;i <= nb_client;i++)
		pthread_join(thread[i],NULL);

	return EXIT_SUCCESS;
}
