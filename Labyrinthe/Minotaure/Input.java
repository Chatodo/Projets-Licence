package Minotaure;


import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 * cette classe gère les touches qui vont faire bouger les 2 joueurs
 *  
 * selon la touche pressée par l'utilisateur sur son clavier, il fera bouger son joueur vers une certaine direction
 * 
 * pour le joueur1 il faudra utiliser les touches E : haut S : à gauche D : bas F : à droite
 * pour le joueur2 il faudra utiliser les touches O : haut K : à gauche L : bas M : à droite
 */

public class Input extends KeyAdapter{
	
	private ObjetJeu liste;
	
	/**
	* Initialise une entrée de touches dont la liste de joueurs est liste 
	* 
	* @param liste : la liste des joueurs
	* @requires liste != NULL
	*/
	public Input (ObjetJeu liste) {
		this.liste = liste;
	}
	
	/**
	* cette méthode s'occuppe des touches pressées 
	*
	* @param e : la touche pressée par l'utilisateur sur son clavier
	*/
	public void keyPressed (KeyEvent e) {
		int key = e.getKeyCode();
		for (int i =0; i<liste.objet.size(); i++) {
			Personnage tmp = liste.objet.get(i);
			
			if (tmp.personnage == ID.JOUEUR1) {
				if (key == KeyEvent.VK_E) tmp.setvaly (-5) ;
				else if (key == KeyEvent.VK_D) tmp.setvaly (5) ;
				else if (key == KeyEvent.VK_S) tmp.setvalx (-5) ;
				else if (key == KeyEvent.VK_F) tmp.setvalx (5) ;
			}
			
			if (tmp.personnage == ID.JOUEUR2) {
				if (key == KeyEvent.VK_O) tmp.setvaly (-5) ;
				if (key == KeyEvent.VK_L) tmp.setvaly (5) ;
				if (key == KeyEvent.VK_K) tmp.setvalx (-5) ;
				if (key == KeyEvent.VK_M) tmp.setvalx (5) ;
					
			}
			
		}
	}
	
	/**
	* cette méthode s'occuppe des touches libérées
	*
	* @param e : la touche libérée par l'utilisateur sur son clavier
	*/
	public void keyReleased (KeyEvent e) {
		int key = e.getKeyCode();
		for (int i =0; i<liste.objet.size(); i++) {
			Personnage tmp = liste.objet.get(i);
		
			if (tmp.personnage == ID.JOUEUR1) {
				if (key == KeyEvent.VK_E) tmp.setvaly (0) ;
				else if (key == KeyEvent.VK_D) tmp.setvaly (0) ;
				else if (key == KeyEvent.VK_S) tmp.setvalx (0) ;
				else if (key == KeyEvent.VK_F) tmp.setvalx (0) ;
					
			}
			if (tmp.personnage == ID.JOUEUR2) {
				if (key == KeyEvent.VK_O) tmp.setvaly (0) ;
				if (key == KeyEvent.VK_L) tmp.setvaly (0) ;
				if (key == KeyEvent.VK_K) tmp.setvalx (0) ;
				if (key == KeyEvent.VK_M) tmp.setvalx (0) ;
			}
		}
		
	}
}
