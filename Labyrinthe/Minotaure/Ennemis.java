package Minotaure;


import java.awt.Graphics;
import java.util.LinkedList;

/**
 * 
 * Dans cette classe il y'aura une liste de tous les enemies qu'on va creer dans notre jeu :
 * A chaque fois qu'on veut rajouter un enemi dans notre jeu on le mettra d'abord dans la liste de type objet 
 * et on manipulera directement la liste
 *
 */

public class Ennemis {
	LinkedList <Ennemi> objet = new LinkedList <Ennemi>();
	
	public void tick () {
		//on va faire une boucle sur tout les objets
		for (int i =0; i<objet.size(); i++) {
			//notre objet temporaire est egale a l'ID de l'objet i 
			Ennemi temp = objet.get(i);
			
			temp.tick();
		}
	}
	/*
    * affiche la liste d'enemies
    * 
    * @param g : la structure graphiquequi permet de l'afficher 
    *
    */
	public void render (Graphics g) {
		//tout nos objet seront afficher grace a cette methode
		for (int i =0; i<objet.size(); i++) {
			Ennemi temp = objet.get(i);
			
			temp.render(g);
		}
	}
	
	/*
    * ajoute le personnage a la liste
    * 
    */
	public void ajouterperso (Ennemi perso) {
		this.objet.add(perso);
	}

	/*
	* supprimer les personnages de la liste
	*
	*/
	public void supprimerperso (Ennemi perso) {
		this.objet.remove(perso);
	}
	
}
