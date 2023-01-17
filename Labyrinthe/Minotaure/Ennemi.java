package Minotaure;


import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Color;

/* cette classe représente un ennemi dans le labyrinthe 
* 
* un ennemie est un personnage qui si il touche le joueur le ramene a son point de départ
* l'enemi as deux coordonnées x horizontale et y verticale , un identifiant ID, un boolean pour savoir si il se deplace en vertical ou horizontal
* un int limiteDeplacement qui correspond au nombre de pixel sur lequel il fait un allez retour, et un int debut pour placer le point d'aller retour
*
* cette classe hérite de la classe personnage
*/
public class Ennemi extends Personnage {
	
	private boolean vertical;
	int limiteDeplacement,debut;
	public Ennemi(int x, int y, ID id,boolean vertical, int limiteDeplacement,int debut) {
		super(x, y, id);
		this.vertical=vertical;
		this.limiteDeplacement=limiteDeplacement;
		this.debut=debut;
		//vitesse de deplacement
		valx=5;
		valy=5;
	}

/*
    * a chaque tick l'ennemie va avancer et si il atteint la limite de là ou il doit aller on lui dit d'aller dans l'autre sens (en multipliant par -1)
    *
    */
	public void tick() {
		//l'IA correspond à un chemin que prend les ennemies 
		
		//les ennemies font des allez retour
		
		if(vertical) {
			
			x += valx;
			if(x <=debut|| x >= debut+limiteDeplacement) valx *=-1;
		}
		else {
			y += valy;
			if(y <=debut|| y >= debut+limiteDeplacement) valy *=-1;
		}

			
		
	}

	/*
    * affiche l'ennemi
    * 
    * @param g : la structure graphique qui permet de l'afficher 
    *
    */
	public void render(Graphics g) {
		g.setColor(Color.red);
		g.fillRect(x, y, 25, 25);
	}

	@Override
	public Rectangle getBounds() {
		return new Rectangle (x,y, 25, 25);
	}


	

}
