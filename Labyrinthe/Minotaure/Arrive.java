package Minotaure;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Color;

/* cette classe représente la ligne d'arrivé dans le labyrinthe 
* 
* une ligne d'arrivé est un rectangle jaune qui si il touche le joueur qui l'as touché a gagner
* on a repris le code de l'ennemie , 2 int pour les coordonnée x et y , l'id du la ligne d'arrivé, et les 2 autres int ne servent pas car pas de deplacement
*
* cette classe hérite de la classe personnage
*/
public class Arrive extends Personnage {
	
	int limiteDeplacement,debut;
	public Arrive(int x, int y, ID id,int limiteDeplacement,int debut) {
		super(x, y, id);
		this.limiteDeplacement=limiteDeplacement;
		this.debut=debut;
		valx=5;
		valy=5;
	}
	/*
    * affiche la ligne d'arrivé
    * 
    * @param g : la structure graphique qui permet de l'afficher 
    *
    */
	public void render(Graphics g) {
		g.setColor(Color.yellow);
		g.fillRect(x, y, 75, 50);
	}

	@Override
	public Rectangle getBounds() {
		return new Rectangle (x,y, 75, 50);
	}

	@Override
	public void tick() {
		//Pas besoin :)		
	}


	

}
