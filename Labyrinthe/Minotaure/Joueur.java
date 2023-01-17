package Minotaure;


import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;

/** Cette classe représente un joueur dans le labyrinthe 
 * 
 * un joueur est un personnage qui essaye de trouver la sortie du labyrinthe en esquivant les ennemis 
 * et sans se cogner contre un mur.
 * le joueur aura deux coordonnées x horizontale et y verticale , un identifiant ID et deux 
 * valeurs pour gérer sa vitesse valx (horizontal) et valy (vertical)
 *
 * cette classe hérite de la classe personnage
 */


public class Joueur extends Personnage {
	
	protected ObjetJeu liste;
	protected Ennemis listeE;
	protected Arrives listeA;
	protected Murs mur;
	public int gagner1;
	public int gagner2;

	/**
	* Initialise un joueur qui aura pour coordonnées les coordonnées x et y passées en argument et pour 
	* identifiant id
	* 
	* @param x : la coordonnée horizontale 
	* @param y : la coordonnée verticale
	* @param id : l'identifiant du joueur JOUEUR1 ou JOUEUR2 
	* les param suivants vont nous servir à gérer les collisions
	* @param liste : la liste des joueurs 
	* @param listes : la liste des ennemis 
	* @param jaune : la ligne d'arrivée 
	* @param mur : la liste des murs 
	*
	* @ensures : getX = x
	* @ensures : getY = y
	* @requires : id = JOUEUR1 || id = JOUEUR2
	*/
	public Joueur (int x, int y, ID id, ObjetJeu liste, Ennemis listes,Arrives jaune,Murs mur) {
		super(x, y, id);
		this.liste = liste;
		this.listeE=listes;
		this.listeA=jaune;
		gagner1=0;
		gagner2=0;
		this.mur = mur;
	}
	
	@Override
	public void tick() {
		collision ();
		
		x += valx;
		y += valy;
		
		//pas sortir de l'ecran
		x=Jeu.clamp(x, 0, Fenetre.hauteur-37);
		y=Jeu.clamp(y, 0, Fenetre.largeur-60);
	}
	
	@Override
	public Rectangle getBounds () {
		return new Rectangle (x,y, 30, 30);
	}
	
	/**
	* cette méthode gére les collisions entre un joueur et les murs, les ennemis et la ligne d'arrivée
	* si un joueur se cogne contre un mur ou un ennemi il sera retourné à son point de départ 
	* si un joueur atteint le rectangle jaune qui désigne la ligne d'arrivée le joueur aura gagné et 
	* un message sera affiché à l'écran 
	*
	* @requires : liste n'est pas vide
	* @requires : listeE n'est pas vide
	* @requires : mur n'est pas vide
	*/
	public void collision (){
		for (Joueur joueur : liste.objet ) {
			if(joueur.personnage==ID.JOUEUR1 ) {
				for (Mur mur : mur.objet) {
					if (joueur.getBounds().intersects(mur.getBounds()) ) {
						joueur.setX(50);
						joueur.setY(23);
					}
					
				}
				//si joueur1 touche un ennemi il reviens au debut
				for (Ennemi ennemi: listeE.objet) {
					if (joueur.getBounds().intersects(ennemi.getBounds()) ) {
						joueur.setX(50);
						joueur.setY(23);
					}
					
				}
				//Si joueur1 touche l'arrive alors il gagne
				for (Arrive fin: listeA.objet) {
					if (joueur.getBounds().intersects(fin.getBounds()) ) {
						this.gagner1=1;	
					}
					
				}
			}
			
			//si joueur2 touche un mur il revient au debut
			if(joueur.personnage==ID.JOUEUR2 ) {
				for (Mur mur : mur.objet) {
					if (joueur.getBounds().intersects(mur.getBounds()) ) {
						joueur.setX(1050);
						joueur.setY(23);
					}
					
				}
				//si joueur2 touche un ennemi il revient au debut
				for (Ennemi ennemi: listeE.objet) {
					if (joueur.getBounds().intersects(ennemi.getBounds()) ) {
						joueur.setX(1050);
						joueur.setY(23);
					}
					
				}
				//Si joueur2 touche l'arrive alors il gagne
				for (Arrive fin: listeA.objet) {
					if (joueur.getBounds().intersects(fin.getBounds()) ) {
						this.gagner2=2;	
					}
					
				}
				
			}
			
			
		}
		
	}

	/**
	* renvoie la valeur de la variable gagner1 
	* @return gagner1 : la variable qui indique si le joueur1 a touché le rectangle jaune càd 
	* qu'il est arrivée à la sortie du labyrinthe
	* 
	* @pure
	*/
	public int gagner1() {
		return gagner1;
	}

	/**
	* renvoie la valeur de la variable gagner2 
	* @return gagner2 : la variable qui indique si le joueur2 a touché le rectangle jaune càd 
	* qu'il est arrivée à la sortie du labyrinthe
	* 
	* @pure
	*/
	public int gagner2() {
		return gagner2;
	}

	@Override	
	public void render(Graphics g) {
		
		if (this.personnage != ID.ENNEMI) g.setColor(Color.blue);
		else g.setColor(Color.RED);
		
		g.fillRect(x, y, 30, 30);
	}
}
