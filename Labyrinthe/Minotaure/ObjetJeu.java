package Minotaure;
import java.awt.Graphics;
import java.util.LinkedList;

/**
 * cette classe représente une liste des joueurs du labyrinthe 
 *  
 * le but est de faire appel aux méthodes tick et render ici afin de ne pas avoir plusieurs lignes de code 
 * dans la méthode pricinpal "jeu"
 * 
 * @invariant objet.size() = 2
 *  
 */

public class ObjetJeu {
	LinkedList <Joueur> objet = new LinkedList <Joueur>();
	
	/**
	* cette méthode gére la vitesse et l'avancement des deux joueurs 
	* en appelant la méthode "tick" implémentée dans la classe joueur 
	*/
	public void tick () {
		for (int i =0; i<objet.size(); i++) {
			Joueur temp = objet.get(i);
			
			temp.tick();
		}
	}
	
	/**
	* cette méthode affiche les deux joueurs sur l'écran
	* en appelant la méthode "render" implémentée dans la classe joueur 
	*
	* @param g le graphic à afficher 
	*/
	public void render (Graphics g) {
		for (int i =0; i<objet.size(); i++) {
			Joueur temp = objet.get(i);
			
			temp.render(g);
		}
	}
	
	/**
	* ajoute un joueur dans la liste des joueurs 
	* 
	* @param perso : le joueur à rajouter dans la liste 
	* @requires perso != NULL
	* @ensures objet.size() > 0
	*/
	public void ajouterperso (Joueur perso) {
		this.objet.add(perso);
	}
	
}
