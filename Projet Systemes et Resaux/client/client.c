#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char nom[20];

void annuler_signal(int signal){
	printf(" RAPPEL : Z pour quitter\n");
}

void init_sockaddr_in(struct sockaddr_in* serveur, unsigned short port_serveur, char* ip_serveur){
  	//On précise que c'est une socket réseau
	serveur->sin_family = AF_INET;
  	//On initialise le port
  	serveur->sin_port = htons(port_serveur);
  	//On initialise l'adresse du serveur
  	inet_aton(ip_serveur,(struct in_addr*) &serveur->sin_addr);
}

int initialiser_socket(char * ip_serveur, short port_serveur, struct sockaddr_in* serveur){  
  	int sock;
  	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Erreur lors de la création de socket TCP");
		exit(EXIT_FAILURE);
  	}
  	init_sockaddr_in(serveur, port_serveur, ip_serveur);
  
  	//On établit la connexion avec le serveur
  	if((connect(sock, (struct sockaddr *)serveur, sizeof(struct sockaddr_in))) < 0){
		perror("Erreur lors de la connexion au serveur");
		exit(EXIT_FAILURE);
	}
  	return sock;
}

void envoyer_serveur_nom(int sock){
	char message[100] = "";
	read(sock,message,100);
	printf("%s\n",message);
	scanf("%s",nom);
	write(sock, nom, strlen(nom)+1);
}

size_t taille_fichier(const char* chemin){
	struct stat st; 

	if (stat(chemin, &st) == 0)
		return st.st_size;
	return 0; 
}

int charger_sauvegarde(char nom[], int sock, char chaine[]){
	FILE* f = fopen(nom, "r");
	if (f == NULL )
    	return 0;
	//Chaine aura la chaine présente dans f
	fread(chaine,sizeof(char),taille_fichier(nom),f);
	fclose(f);
	write(sock,chaine,strlen(chaine)+1);
	return 1;
}

int recherche_fin(char *chaine){
	//Permet de vérifier si cette chaîne de caractère contient "FIN"
	if(strstr(chaine,"FIN") != NULL)
		return 0;
	return 1;
}

void jeu_solo(char message[],int sock){
	unsigned int jeu = 1;
	char choix[2];
	read(sock,message,10000);
	printf("%s",message);
	do{
		scanf("%s",choix);
		//Pour éviter que le client demandé des fichiers qui n'existent pas
		while(choix[0] != 'A' && choix[0] != 'B' && choix[0] != 'C' && choix[0] != 'Z'){
			printf("Choix impossible, choix accepté : A B C et Z pour quitter en sauvegardant\n");
			scanf("%s",choix);
		}

		write(sock,choix,2);
		//Interuption par le client
		if(choix[0] == 'Z')
			break;

		read(sock,message,10000);
		system("clear"); //Efface le contenu du terminal (besoin d'un système UNIX)
		printf("%s\n",message);
		//On vérifie que "FIN" n'est pas présent 
		jeu = recherche_fin(message);
		write(sock,&jeu,sizeof(unsigned int));
		} while (jeu); //Tant que FIN n'a pas été lu on continue
}

void jeu_solo_sauvegarde(char message[],int sock, char chemin[]){
	unsigned int jeu = 1;
	char choix[2];
	FILE* f = fopen(chemin,"r");
	fread(message,sizeof(char),taille_fichier(chemin),f);
	printf("%s",message);
	fclose(f);
	do{
		scanf("%s",choix);
		//Pour éviter que le client demandé des fichiers qui n'existent pas
		while(choix[0] != 'A' && choix[0] != 'B' && choix[0] != 'C' && choix[0] != 'Z'){
			printf("Choix impossible, choix accepté : A B C et Z pour quitter en sauvegardant\n");
			scanf("%s",choix);
		}

		write(sock,choix,2);
		//Interuption par le client
		if(choix[0] == 'Z')
			break;

		read(sock,message,10000);
		system("clear"); //Efface le contenu du terminal (besoin d'un système UNIX)
		printf("%s\n",message);
		//On vérifie que "FIN" n'est pas présent 
		jeu = recherche_fin(message);
		write(sock,&jeu,sizeof(unsigned int));
		} while (jeu); //Tant que FIN n'a pas été lu on continue
	unlink(nom);
}

void echange_avec_serveur(int sock){
	int choix_jeu;
	char message[10000];
	struct stat buffer;
	int sauvegarde_presente;
	char chaine[100] = "";
	envoyer_serveur_nom(sock);
	//On regarde s'il y'a un fichier du nom du client
	sauvegarde_presente = stat(nom,&buffer);
	//Le fichier est présent
	if(sauvegarde_presente == 0){
			charger_sauvegarde(nom,sock,chaine);
			jeu_solo_sauvegarde(message,sock,chaine);
			return;
	}
	read(sock,message,10000);
	printf("%s\n",message);
	scanf("%d",&choix_jeu);
	write(sock,&choix_jeu,sizeof(int));

	switch (choix_jeu){
	case 1:
		jeu_solo(message,sock);
		break;
	case 2:
		printf("Bye\n");
		break;
	default:
		printf("C'était pas dur pourtant :(\n Reconnecte toi quand tu veux\n");
		break;
	}
}


int main(int argc, char** argv) {
	struct sockaddr_in serveur;
	//Corrige une erreur sur valgrind 
	bzero(&serveur,sizeof(serveur));
	short port_serveur;
	char* ip_serveur = "localhost";
	int sock;

	signal(SIGINT,annuler_signal);

	if (argc != 2) {
		fprintf(stderr,"usage: %s port_serveur\n", argv[0]);
	  	return EXIT_FAILURE;
	}
	port_serveur = atoi(argv[1]);

	sock = initialiser_socket(ip_serveur, port_serveur, &serveur);
	
	echange_avec_serveur(sock);

	close(sock);
	
	return EXIT_SUCCESS;
}
