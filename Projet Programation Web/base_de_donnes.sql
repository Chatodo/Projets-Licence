-- L'ensemble des tables nécésaire pour php

-- Table utilisateur

CREATE TABLE utilisateur(
	nom VARCHAR(200) NOT NULL,
	prenom VARCHAR(200) NOT NULL,
	pseudo VARCHAR(100) NOT NULL,
	email VARCHAR(200) NOT NULL,
	password VARCHAR(100) NOT NULL,
	domaine_recherche TEXT,
	bio TEXT,
	cv TEXT,
	these TEXT,
	pays VARCHAR(200) NOT NULL,
	PRIMARY KEY(pseudo)
);

INSERT INTO utilisateur(nom,prenom,pseudo,email,password,domaine_recherche,bio,cv,these,pays) VALUES
("","","admin","","admin","","","","" ,"");
INSERT INTO utilisateur(nom,prenom,pseudo,email,password,domaine_recherche,bio,cv,these,pays) VALUES
("Tesla","Nikola","tesla","tesla@science.rs","aidemo","Moteur asynchrone","ingé",""," Le Courant alternatif pour le transport et la distribution de l'électricité." ,"Serbie");
INSERT INTO utilisateur(nom,prenom,pseudo,email,password,domaine_recherche,bio,cv,these,pays) VALUES
("Einstein","Albert","einstein","","123","Physicien,theoricien","Albert Einstein né le 14 mars 1879 à Ulm, dans le Wurtemberg (Empire allemand), et mort le 18 avril 1955 à Princeton, dans le New Jersey (États-Unis), est un physicien théoricien. Il fut successivement allemand, apatride (entre 1896 et 1901), suisse (1901) et de double nationalité helvético-américaine (1940)N 1. Il épousa Mileva Marić, puis sa cousine Elsa Einstein.

Il publie sa théorie de la relativité restreinte en 1905 et sa théorie de la gravitation, dite relativité générale, en 1915. Il contribue largement au développement de la mécanique quantique et de la cosmologie, et reçoit le prix Nobel de physique de 1921 pour son explication de l’effet photoélectriqueN deux. Son travail est notamment connu du grand public pour l’équation E=mc2, qui établit une équivalence entre la masse et l’énergie d’un système.

Il est aujourd hui considéré comme l un des plus grands scientifiques de l histoire, et sa renommée dépasse largement le milieu scientifique. Il est la personnalité du XXe siècle selon l hebdomadaire Time. Dans la culture populaire, son nom et sa personne sont directement liés aux notions d intelligence, de savoir et de génie. ","images/galaxie.png","relativite restreinte","Allemange" );

INSERT INTO utilisateur(nom,prenom,pseudo,email,password,domaine_recherche,bio,cv,these,pays) VALUES
("Turing","Alan","talan","email@email.com","oui","Mathematicien, Cryptologue","La Machine de Turing","Très grand CV","La machine de Turing pour du PHP, ça tourne mal !" ,"Royaume-Uni");


-- Table conference

CREATE TABLE conference (
	titre_conference VARCHAR(200) NOT NULL,
	abreviation VARCHAR(200) NOT NULL,
	sujet VARCHAR(200) NOT NULL,
	date_conference DATE not NULL,
	date_limite_inscription DATE NOT NULL,
	conferencier VARCHAR(200) NOT NULL,
	pays VARCHAR(200) NOT NULL,
	PRIMARY KEY(sujet,date_conference,pays)
);

INSERT INTO conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays) VALUES ("International conference knowledge","K-CAP","capture de connaissance","2023-12-01","2022-06-15","Jose Manuel Gomez-Perez","US");
INSERT INTO conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays) VALUES ("International conference conceptual structure","ICCS","intelligence aritificielle,cognition humain","2022-09-12","2022-03-25","Tanya Braun","Royaume-Uni");
INSERT INTO conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays) VALUES ("Societe astronomique de France","SAF","Les debrix spatiaux","2022-04-13","2022-04-10","Christophe Bonnal","France");
INSERT INTO conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays) VALUES ("Algebraic Methods in Coding Theory and Communication","CMO","Mathematiques","2022-05-24","2022-06-18","Casa Matemática Oaxaca","Oaxaca");
INSERT INTO conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays) VALUES ("Ecole de printemps d'informatique théorique","CIRM ","Machine Learning","2022-05-24","2022-06-18","Centre International de Rencontres Mathématiques","Marseille");


-- Table journaux

CREATE TABLE journaux (
	titre VARCHAR(200) NOT NULL,
	isbn BIGINT NOT NULL,
	editeur VARCHAR(200) NOT NULL,
	theme VARCHAR(200) NOT NULL,
    PRIMARY KEY(isbn)
);

INSERT INTO journaux(titre,isbn,editeur,theme) VALUES ("Knowledge-Based Systems",9780763776473,"Jie Lu","intelligence artifiecielle");
INSERT INTO journaux(titre,isbn,editeur,theme) VALUES ("Mathématique",129233490499,"Kim jungun","théorie mathématique");
INSERT INTO journaux(titre,isbn,editeur,theme) VALUES ("Les arbres binaires",1411111111111,"Zicheng Fang","Informatique théorique");

-- Table publications

CREATE TABLE publications (
	titre VARCHAR(500),
	auteur VARCHAR(200) NOT NULL,
	date_de_publication DATE not NULL,
	sujet TEXT NOT NULL,
    PRIMARY KEY(auteur,titre)
);

INSERT INTO publications(titre,auteur,date_de_publication,sujet) VALUES ("Computing Machinery and Intelligence","Alan Turing", "1950-01-20","Cet article suggère le test de Turing comme méthode pour faire la différenciation entre machine et humain.");
INSERT INTO publications(titre,auteur,date_de_publication,sujet) VALUES ("A relational model for large shared data banks"," Edgar Frank Codd", "1970-06-01","Ce document présente le modèle relationnel des bases de données.");

-- Table des images, on considère la 1er clé est le logo, la 2ème est la couleur du CSS que l'admin peut changer et le reste sont les images du diapo
CREATE TABLE image(
	id INT NOT NULL AUTO_INCREMENT,
	url TEXT NOT NULL,
	PRIMARY KEY(id)
);
INSERT INTO image(url) VALUES ("images/logo.png");
INSERT INTO image(url) VALUES ("<style> .fondlogo{background-color:#b6f287;}</style>");
INSERT INTO image(url) VALUES ("images/galaxie.jpg");
INSERT INTO image(url) VALUES ("images/journaux.jpg");
INSERT INTO image(url) VALUES ("images/lune.jpg");
INSERT INTO image(url) VALUES ("images/mars.jpg");

-- Table pour les informations d'une photo 
CREATE TABLE info (
	id INT NOT NULL AUTO_INCREMENT,
	titre VARCHAR(500),
	sujet TEXT NOT NULL,
    PRIMARY KEY(id,titre)
);

INSERT INTO info(titre,sujet) VALUES ("Galaxie","Une galaxie est un assemblage d étoiles, de gaz, de poussières, de vide et peut-être essentiellement de matière noire, contenant parfois un trou noir supermassif en son centre.");

INSERT INTO info(titre,sujet) VALUES ("IA","L intelligence artificielle est « l ensemble des théories et des techniques mises en œuvre en vue de réaliser des machines capables de simuler l intelligence humaine ». Elle englobe donc un ensemble de concepts et de technologies, plus qu une discipline autonome constituée.");

INSERT INTO info(titre,sujet) VALUES ("Lune","La Lune, dite aussi Terre I, est le seul satellite naturel permanent de la planète Terre. Il est le cinquième plus grand satellite naturel du Système solaire, et du plus grand des satellites planétaires par rapport à la taille de la planète autour de laquelle il orbite.");

INSERT INTO info(titre,sujet) VALUES ("Mars","Mars est la quatrième planète du Système solaire par ordre croissant de la distance au Soleil et la deuxième par ordre croissant de la taille et de la masse. Son éloignement au Soleil est compris entre 1,381 et 1,666 UA, avec une période orbitale de 669,58 jours martiens.");
