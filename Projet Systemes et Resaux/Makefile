all : serveur_tcp client_tcp

serveur_tcp: serveur.o
	gcc -g serveur.o -o serveur_tcp -lpthread

serveur.o: serveur/serveur.c serveur/serveur.h
	gcc -c serveur/serveur.c -Wall -lpthread

client_tcp: client.o
	gcc -g client.o -o client_tcp

client.o: client/client.c client/client.h
	gcc -c client/client.c -Wall

clean:
	rm *.o

clean_all:
	rm *.o serveur_tcp client_tcp