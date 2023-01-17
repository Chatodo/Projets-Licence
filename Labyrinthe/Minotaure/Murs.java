package Minotaure;
import java.awt.Graphics;
import java.util.LinkedList;

/**
 * cette classe représente une liste de tous les murs du labyrinthe 
 *  
 * le but est de faire appel à la méthode render ici afin de ne pas avoir plusieurs lignes de code 
 * dans la méthode pricinpale "jeu"
 *  
 */

public class Murs {
	LinkedList <Mur> objet = new LinkedList <Mur>();
	
	/**
	* cette méthode affiche tous les murs créés sur l'écran un par un
	* en appelant la méthode "render" implémentée dans la classe Mur 
	*
	* @param g le graphic à afficher 
	*/
	public void render (Graphics g) {
		for (int i =0; i<objet.size(); i++) {
			Mur temp = objet.get(i);
			
			temp.render(g);
		}
	}
	

	/**
	* ajoute un mur dans la liste des murs 
	* 
	* @param mur : le mur à rajouter dans la liste 
	* @requires mur != NULL
	* @ensures objet.size() > 0
	*/
	public void ajoutermur (Mur mur) {
		this.objet.add(mur);
	}
	
}
