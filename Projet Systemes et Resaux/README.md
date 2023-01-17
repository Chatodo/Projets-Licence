# Projet finale dans l'UE Système et Réseaux (codé en C )

## Description du projet
**Les fichiers de l'histoire ne sont pas fournis, il faut les créer soi-même ou me les demander :)**

L'objectif de notre projet est un jeu qui fera voyager le joueur à travers un personnage et décidera de ses choix.

Selon ses choix, le personnage aura différentes aventures. Écrit par deux scénaristes géniaux. 
~~L'histoire sera fun et divertissante (normalement).~~ (pas fourni désolé :))

Le principe du code est un échange serveur/client de caractères (textes), on le fait en TCP car ce sont des échanges donc le serveur attend une réponse du client (et vice versa).

~~Les fichiers de textes sont présents dans le dossier commun~~.

<u>Pour créer les fichiers de textes :</u> Un fichier est du type nomduchoixNUMERO (les choix se suivent). Par exemple on peut avoir A1B2A3C4 --> C'est a dire on a pris le choix A comme premier choix, puis le choix B, puis le choix A, puis le choix C.

Lorsque que le client se connectera au serveur, il indiquera son nom d'utilisateur et décide s'il veut jouer. 

Alors le client recevra par le serveur un texte avec des choix à faire (soit d'entrer A, B ou C), et selon les choix que le client choisira, le serveur recevra la réponse et lui enverra la suite du texte correspondant au choix sélectionné (grâce à l'ouverture du fichier correspondant à son choix).

Un maximum de 10 clients est accepté si ce chiffre est dépassé alors le serveur ne les prend pas en compte, néanmoins on peut augmenter cette valeur si on le souhaite.
<b>Tant que le client ne reçoit pas la chaîne "FIN"</b> celui-ci continue de jouer (car recevoir FIN met fin au jeu)

Le serveur possède un gracefull shutdown, c'est à dire que si celui-ci reçoit le signal CTRL-c alors le client recevra un message lui disant que sa partie sera sauvegardé et il pourra reprendre la suite après. Si le client se connecte au même nom d'utilisateur pourra reprendre sa sauvegarde (si un fichier avec son nom a bien été créé)

Le client lorsqu’il est dans le jeu, peut décider de quitter en entrant écrivant Z, sa partie sera sauvegardé.

## Comment lancer le projet
On compile tout les fichiers avec make

Ensuite on ouvre le serveur en faisant ./serveur_tcp port

Pour ouvrir un client on fait ./client_tcp port (le même que celui du serveur)

### Note obentu : 19/20 
### Auteurs : KRIVOKUCA Ivan SI ALI Aghiles