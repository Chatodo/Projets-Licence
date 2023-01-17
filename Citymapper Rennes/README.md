## Description
Citymapper Rennes est un projet de licence 3 (2020-2021) de l'Université Sorbonne Paris Nord. Il a pour but de créer une application (non complète) de cartographie de la ville de Rennes. 

L'application est codée en Python avec PyQt5 et utilise une base de données PostgreSQL.

## Fonctionnalités
Lorsque l’utilisateur choisit un départ et un arrivé, un marqueur apparaît sur l’endroit de 
départ et d’arrivée. Il peut choisir aussi de cliquer n’importe où sur la carte et la station la plus 
proche sera affichée.

## Utilisation
Tout d'abord il faut changer la fonction connect_DB() dans le fichier citymapper.py pour qu'elle corresponde à votre base de données.

Crée une base de données PostgreSQL et lancez les fichiers sql dans /source/database pour créer les tables et les remplir.

Lancement : ```python3 citymapper.py```
## Description des fichiers

```citymapper.py``` : Programe principal qui lance l’application.

```horaire.py``` : Code qui récupère les données de network_temporal_day.csv dans 
/source/rennes et les écrit dans un fichier SQL sous forme d’injection de données pour la table horaire dans /source/database

```nodes.py``` : Code qui récupère les données de network_nodes.csv dans
horaire dans /source/database et les écrit dans un fichier SQL sous forme d’injection de données pour la table nodes dans /source/database)

```transport.py``` : Code qui récupère les données de network_combined.csv dans 
/source/rennes et les écrit dans un fichier sql sous forme d’injection de données pour la table transport dans /source/database

```walk.py``` : Code qui récupère les données de network_walk.csv dans /source/rennes et les écrit dans un fichier sql sous forme d’injection de données pour la table walk dans /source/database

/source/database/ : contient les fichiers sql pour créer les tables et mettre les données

/source/rennes/ : contient les fichiers csv récupérés sur https://zenodo.org/record/1186215

## Auteurs
- Ivan KRIVOKUCA
- Aghiles SI ALI
- Raven GALURA

### Notes obtenue : 20/20