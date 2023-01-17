package Minotaure;


import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;

/**
* cette classe représente les murs du labyrinthe 
* un mur a deux coordonnées x horizontale et y verticale 
* il a une largeur et une longueur
* 
* @invariant largeur > 0
* @invariant longueur > 0
*/
public class Mur {
	
	protected int x;
	protected int y;
	protected int largeur;
	protected int longueur;
	
	/**
	* initialise un mur qui aura pour coordonnées x et y et une largeur "largeur" et une longueur "longueur" 
	* 
	* @requires largeur > 0
	* @requires longueur > 0
	*/
	public Mur (int x, int y, int largeur, int longueur) {
		this.x = x;
		this.y = y;
		this.largeur = largeur;
		this.longueur = longueur;

	}
	
	/**
	* crée et renvoie un rectangle qui aura les memes coordonnées et la meme taille d'un mur
	* afin de gérer les collisions
	*
	* @return un rectangle qui entoure le mur
	* @pure
	*/
	public Rectangle getBounds () {
		return new Rectangle (x,y, largeur, longueur);
	}
	
	
	/**
	* crée un mur et l'affiche sur l'écran
	* 
	* @param g le graphic à afficher 
	*/
	public void render(Graphics g) {
		g.setColor(Color.black);
		g.fillRect(x, y, largeur, longueur);
	}
}
