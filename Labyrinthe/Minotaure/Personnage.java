package Minotaure;
import java.awt.Graphics;
import java.awt.Rectangle;
/**
 * cette classe abstraite représente un personnage dans le labyrinthe 
 * 
 * un personnage a deux coordonnées : une horizontale x et une verticale y
 * il a un identifiant : joueur ou ennemi 
 * et deux entiers pour gérer sa vitesse
 */

public abstract class Personnage {
	//position du personnage
	protected int x;
	protected int y;
	//indique si ennemie ou joueur
	protected ID personnage;
	//entier qui va gerer la vitesse du personnage
	protected double valx, valy;

	/**
	 * 
	 * @param x coordonee x horizontale
	 * @param y coordonee y verticale
	 * @param id l'identite du personnage : joueur ou ennemi
	 * @ensures : getX = x
	 * @ensures : getY = y
	 * @requires : id = JOUEUR1 || id = JOUEUR2 || id = ENNEMI
	 */
	public Personnage (int x, int y, ID id) {
		this.x = x;
		this.y = y;
		this.personnage = id;
	}
	
	/**
	* renvoie la coordonnée x du personnage
	* @return la coordonnée x horizontale du personnage 
	* @pure
	*/
	public int getX() {
		return this.x;
	}
	
	/**
	 * renvoie la coordonnée y du personnage
	 * 
	 * @return la coordonnée y verticale du personnage 
	 * 
	 * @pure
	 */
	public int getY() {
		return this.y;
	}
	
	/**
	* retourne la valeur de l'avancement horizontal du personnage 
	*
	* @return valx : la valeur de l'avancement horizontal du personnage 
	*@pure 
	*/
	public double getvalx () {
		return this.valx;
	}
	
	/**
	* retourne la valeur de l'avancement verticale du personnage 
	*
	* @return valy : la valeur de l'avancement verticale du personnage 
	*@pure 
	*/
	public double getvaly () {
		return this.valy;
	}
	
	/**
	* met le personnage à la position qui aura pour coordonnée x
	* 
	*/
	public void setX (int x) {
		this.x = x;
	}
	
	/**
	* met le personnage à la position qui aura pour coordonnée x
	* 
	*/
	public void setY (int y) {
		this.y = y;
	}
	
	/**
	* modifie la valuer de l'avancement horizontal du personnage 
	* 
	*/
	public void setvalx (double valx) {
		this.valx = valx;
	}
	
	/**
	* modifie la valuer de l'avancement vertical du personnage 
	* 
	*/
	public void setvaly (double valy) {
		this.valy = valy;
	}
	
	/**
	* cette méthode gére les mouvements et l'avancement du personnage
	*  
	*/
	public abstract void tick ();
	
	/**
	* crée un personnage et l'affiche sur l'écran
	* si c'est un joueur il sera bleu
	* si c'est un ennemi il sera rouge
	*
	* @param g le graphic à afficher 
	*/
	public abstract void render (Graphics g);

	/**
    * crée et renvoie un rectangle qui aura les memes coordonnées et la meme taille d'un personnage 
	* afin de gérer les collisions
	* @return un rectangle qui entoure le personnage
	* @pure
	*/
	public abstract Rectangle getBounds();

	
}

