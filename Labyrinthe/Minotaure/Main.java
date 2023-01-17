package Minotaure;
import javax.swing.*;
import java.awt.event.*;

/**
 * Menu principal du jeu
 * Permet de lancer le jeu, quitter ou avoir les options
 */
public class Main extends Fenetre {
	
	public Fenetre fenetre;

	public Main() {
		//Créer une fenêtre ou le menu sera affiché
		fenetre = new Fenetre();
		//On créer les boutons
		JButton bouton = new JButton("START");
		JButton bouton2 = new JButton("INSTRUCTION");
		JButton bouton3 = new JButton("EXIT");
		
		//L'imgage de fond 
		ImageIcon img = new ImageIcon(".//Ressource//Image//menu.png");
		JLabel background=new JLabel("",img,JLabel.CENTER);
		background.setBounds(0,0,Fenetre.hauteur,Fenetre.largeur);
		fenetre.add(background);

		//On définit la taille des boutons
		bouton.setBounds(520,270,110,30);
		bouton2.setBounds(520,320,115,30);
		bouton3.setBounds(520,370,110,30);

		background.add(bouton);
		background.add(bouton2);
		background.add(bouton3);
		//On affiche la fenêtre
		fenetre.setVisible(true);

		//On affecte a chaque bouton son action
		bouton.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				//On ferme la fenetre
				fenetre.dispose();
				new Jeu();				
			}
		});
		
		bouton2.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(null, "Mouvement:\nJoueur 1 : E D S F\nJoueur 2 : O K L M","Instruction", JOptionPane.INFORMATION_MESSAGE);
			}
		});

		bouton3.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
	}
	public static void main(String[] args) {
		//Pour Linux, active l'accéleration video qui n'est pas activé par défaut (contrairement a Windows)
		System.setProperty("sun.java2d.opengl", "true");
		new Main();
	}

}

