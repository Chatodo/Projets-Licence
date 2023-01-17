package Minotaure;

//handler
import java.awt.Graphics;
import java.util.LinkedList;

/**
 * 
 * Dans cette classe il y'aura une liste de tous les ligne d'arrivé qu'on va creer dans notre jeu
 * A chaque fois qu'on veut rajouter une ligne d'arrivé notre jeu on le mettra d'abord dans la liste de type objet 
 * et on manipulera directement la liste
 *
 */

public class Arrives {
	LinkedList <Arrive> objet = new LinkedList <Arrive>();
	
	public void tick () {
		//on va faire une boucle sur tout les objets
		for (int i =0; i<objet.size(); i++) {
			//notre objet temporaire est egale a l'ID de l'objet i 
			Arrive temp = objet.get(i);
			
			temp.tick();
		}
	}
	
	/*
    * affiche la liste des lignes d'arrivé
    * 
    * @param g : la structure graphiquequi permet de l'afficher 
    *
    */
	public void render (Graphics g) {
		//tout nos objet seront afficher grace a cette methode
		for (int i =0; i<objet.size(); i++) {
			Arrive temp = objet.get(i);
			
			temp.render(g);
		}
	}

	/*
    * ajoute la ligne d'arrivé
    */
	public void ajouterperso (Arrive perso) {
		this.objet.add(perso);
	}
	
	/*
    *ajoute la ligne d'arrivé
    */
	public void supprimerperso (Arrive perso) {
		this.objet.remove(perso);
	}
	
}
