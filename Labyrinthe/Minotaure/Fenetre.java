package Minotaure;

import javax.swing.*;
/**
 * Permet d'avoir une fenêtre qui sera unifié, d'une taille qui sera statique
 */
public class Fenetre extends JFrame {

	public static int hauteur = 1152;
	public static int largeur = 768;

	/**
	 * La fenêtre aura les caractéristiques donnés par les variables hauteur et largeur
	 * Permet de quitter en cliquant sur la croix, ne permet pas de changé la taille de la fenêtre
	 * Met la fenêtre au milieu de l'écran
	 */
	public Fenetre(){
		super();
		this.setTitle("Le Minotaure");
		this.setSize(hauteur, largeur);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	/**
	 * Ce constructeur permet d'affecter une fenêtre a l'objet Jeu
	 * En effet tout ce qui sera crée dans Jeu (murs,ennemis etc.) sera ajouté dans la fênetre Jframe a l'aide de add
	 * Du coup on met la fenetre visible et on lance le jeu
	 * @param jeu l'objet Jeu qui sera ajouté a la fenêtre
	 * @require jeu != NULL
	 */
	public Fenetre(Jeu jeu){
		super();
		this.setTitle("Le Minotaure");
		this.setSize(hauteur, largeur);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.add(jeu);
		this.setVisible(true);
		jeu.start();
	}
	
}
