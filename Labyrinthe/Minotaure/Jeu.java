package Minotaure;


import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferStrategy;

import javax.swing.JOptionPane;

/**
* cette  classe est la classe principale dont laquelle on va lancer le jeu
* 
* le labyrinthe est un jeu de confrontation entre deux joueur qui jouent sur une meme machine 
* le but est d'arriver à la sortie du labyrinthe en premier 
* le joueur doit esquiver les ennemis présents dans le labyrinthe et ne doit pas se cogner contre un mur
* sinon il reviendra à son point de départ ce qui lui fera perdre du temps 
*/
public class Jeu extends Canvas implements Runnable{

	private static final long serialVersionUID = -7827192176388913994L;
	
	//rafraichissement de la fenetre on fait un jeu unithreader (deconseiller il faudrait faire multithreader)
	private Thread thread;
	
	//si le jeu est en marche
	private boolean lancer=false;
	
	
	private ObjetJeu liste= new ObjetJeu();
	private Ennemis listeE=new Ennemis();
	private Murs mur = new Murs();
	private Arrives listeA = new Arrives();
	//On cree une nouvelle fenetre pour interagir avec le constructeur
	Fenetre fenetre = new Fenetre(this);
	int arrive_a,arrive_b;

	public Jeu() {
		
		this.addKeyListener(new Input(liste));

		//On ajoute les murs qui consitue le labyrinthe
		mur.ajoutermur(new Mur(510, 0, 10, 570));//vertical
		mur.ajoutermur(new Mur(620, 0, 10, 570));
		
		mur.ajoutermur(new Mur (620, 570, 60, 10));//horizontal coté droit
		mur.ajoutermur(new Mur (460, 570, 60, 10));//horizontal coté gauche
		
		mur.ajoutermur(new Mur (0, 70,370 ,10));//horizontal
		mur.ajoutermur(new Mur (770, 70,370 ,10));
		mur.ajoutermur(new Mur (435, 70,10 ,140));
		mur.ajoutermur(new Mur (695, 70,10 ,140));
		
		mur.ajoutermur(new Mur (0, 400, 60,10));
		mur.ajoutermur(new Mur (1080, 400, 60,10));
		
		mur.ajoutermur(new Mur (60, 140, 10,200));
		mur.ajoutermur(new Mur (1080, 140, 10,200));
		
		mur.ajoutermur(new Mur (60, 500, 10,80));
		mur.ajoutermur(new Mur (1080, 500, 10,80));
		
		mur.ajoutermur(new Mur (70, 500, 50,10));
		mur.ajoutermur(new Mur (1030, 500, 50,10));
		
		mur.ajoutermur(new Mur (70, 140, 50,10));
		mur.ajoutermur(new Mur (1030, 140, 50,10));
		
		mur.ajoutermur(new Mur (120, 140, 10,430));
		mur.ajoutermur(new Mur (1020, 140, 10,430));
		
		mur.ajoutermur(new Mur (120, 570, 140,10));
		mur.ajoutermur(new Mur (890, 570, 140,10));
		
		mur.ajoutermur(new Mur (315, 570, 95,10));
		mur.ajoutermur(new Mur (735, 570, 105,10));
		
		mur.ajoutermur(new Mur (315, 570, 10,80));
		mur.ajoutermur(new Mur (830, 570, 10,80));
		
		mur.ajoutermur(new Mur (170, 500, 50,10));
		mur.ajoutermur(new Mur (940, 500, 40,10));
		
		mur.ajoutermur(new Mur (260, 500, 100,10));
		mur.ajoutermur(new Mur (770, 500, 120,10));
		
		mur.ajoutermur(new Mur (260, 500, 10,80));
		mur.ajoutermur(new Mur (880, 500, 10,80));
		
		mur.ajoutermur(new Mur(410, 500, 50, 10));
		mur.ajoutermur(new Mur(680, 500, 50, 10));
		
		mur.ajoutermur(new Mur (170, 140, 10,270));
		mur.ajoutermur(new Mur (970, 140, 10,270));
		
		mur.ajoutermur(new Mur(180, 400, 40, 10));
		mur.ajoutermur(new Mur(930, 400, 50, 10));
		
		mur.ajoutermur(new Mur(260, 400, 60, 10));
		mur.ajoutermur(new Mur(830, 400, 50, 10));
		
		mur.ajoutermur(new Mur(370, 400, 90, 10));
		mur.ajoutermur(new Mur(670, 400, 110, 10));
		
		mur.ajoutermur(new Mur (460, 500, 10,80));
		mur.ajoutermur(new Mur (670, 500, 10,80));
		
		mur.ajoutermur(new Mur (210, 400, 10,110));
		mur.ajoutermur(new Mur (930, 400, 10,110));
		
		mur.ajoutermur(new Mur(360, 400, 10, 110));
		mur.ajoutermur(new Mur(770, 400, 10, 100));
		
		mur.ajoutermur(new Mur(400, 400, 10, 110));
		mur.ajoutermur(new Mur(730, 400, 10, 110));
		
		mur.ajoutermur(new Mur (460, 340, 10,70));
		mur.ajoutermur(new Mur (670, 350, 10,50));
		
		mur.ajoutermur(new Mur(320, 340, 140, 10));
		mur.ajoutermur(new Mur(670, 340, 150, 10));
		
		mur.ajoutermur(new Mur (320, 350, 10,60));
		mur.ajoutermur(new Mur (820, 340, 10,70));
		
		mur.ajoutermur(new Mur (370, 70, 10,80));
		mur.ajoutermur(new Mur (760, 70, 10,80));
		
		mur.ajoutermur(new Mur(325, 140, 45,10));
		mur.ajoutermur(new Mur(760, 140, 60, 10));
		
		mur.ajoutermur(new Mur(225, 140, 55, 10));
		mur.ajoutermur(new Mur(870, 140, 60, 10));
		
		mur.ajoutermur(new Mur(225, 140, 10, 200));
		mur.ajoutermur(new Mur(920, 140, 10, 200));
		
		mur.ajoutermur(new Mur(270, 140, 10,70));
		mur.ajoutermur(new Mur(870, 140, 10, 70));
		
		mur.ajoutermur(new Mur(225, 340, 50, 10));
		mur.ajoutermur(new Mur(880, 340, 50, 10));
		
		mur.ajoutermur(new Mur(270, 260, 10, 90));
		mur.ajoutermur(new Mur(880, 260, 10, 90));
		
		mur.ajoutermur(new Mur(270, 200, 170, 10));
		mur.ajoutermur(new Mur(700, 200, 170, 10));
		mur.ajoutermur(new Mur(0, 650, 1152, 10));
		
		//on crée nos deux joueurs
		liste.ajouterperso(new Joueur(1050,23,ID.JOUEUR2, liste,listeE,listeA, mur));
		liste.ajouterperso(new Joueur(50,23,ID.JOUEUR1,liste,listeE,listeA, mur ));
		
		//on crée nos ennemis 
		listeA.ajouterperso(new Arrive(530,0,ID.ENNEMI,0,0));
		listeE.ajouterperso(new Ennemi(460,0,ID.ENNEMI,false,300,0));
        listeE.ajouterperso(new Ennemi(650,0,ID.ENNEMI,false,300,0));
        
        listeE.ajouterperso(new Ennemi(280,300,ID.ENNEMI,true,200,280));
        listeE.ajouterperso(new Ennemi(650,300,ID.ENNEMI,true,200,650));
        
        listeE.ajouterperso(new Ennemi(0,90,ID.ENNEMI,true,330,0));
        listeE.ajouterperso(new Ennemi(780,90,ID.ENNEMI,true,330,780));
        
        listeE.ajouterperso(new Ennemi(90,170,ID.ENNEMI,false,300,170));
        listeE.ajouterperso(new Ennemi(1040,170,ID.ENNEMI,false,300,170));
        
        listeE.ajouterperso(new Ennemi(140,90,ID.ENNEMI,false,450,90));
        listeE.ajouterperso(new Ennemi(990,90,ID.ENNEMI,false,450,90));
        
        listeE.ajouterperso(new Ennemi(0,610,ID.ENNEMI,true,290,0));
        listeE.ajouterperso(new Ennemi(870,610,ID.ENNEMI,true,290,870));
        
        listeE.ajouterperso(new Ennemi(340,610,ID.ENNEMI,true,450,340));
	}

	/*
    * fonction va lancer le thread du jeu (jeu mono threader)
    */
	public synchronized void start() {
		//on cree un thread
		thread=new Thread(this);
		thread.start();	
		//le jeu est lance
		lancer=true;
	}
	/*
    * fonction qui permet de tuer le thread
    */
	public synchronized void stop() {
		//si on peut le faire on le fait sinon on fait ce qu'il y'a dans le catch
		try {
			//tue le thread
			thread.join();
			//le jeu est eteint donc le jeux n'est pas lance
			lancer=false;
		}catch(Exception e) {
			//met un bug dans la console
			e.printStackTrace();
		}
	}

	/*
    * fontion qui permet au joueur de ne pas pouvoir allé en dehors des bords de la fenetre
    * @return la position maximum où le joueur peut aller
    */
	public static int clamp(int var,int min,int max) {
		
		if(var>=max) 
			return var=max;
		else if(var<=min)
			return var=min;
		return var;
	}

	/*
    * Une fonction qui nous permet de rafraichir la fenetre d'afficher les fps en console , c'est le coeur du jeu qui permet de mettre a jour le jeu a chaque fps
    * C'est une fonction connu utilisé dans plein de jeu comme minecraft
    *
    */
	public void run() {
		//this.requestFocus ();
		long lastTime = System.nanoTime(); //nous permet de calculer delta
		double amountOfTicks=60.0; //nombre de tick par seconde
		double ns = 1000000000/amountOfTicks; //nous permet de calculer delta c'est le nombre de nanoseconds/tick
		double delta =0;
		long timer = System.currentTimeMillis();
		int frames =0;
		while(lancer){
			long now = System.nanoTime();
			delta += (now - lastTime)/ns;
			lastTime=now;
			while(delta >=1) {
				tick();
				delta--;
			}
			if(lancer) {
				render();
			}
			frames++;
			
			if(System.currentTimeMillis() - timer >1000) {
				timer +=1000;
				System.out.println("FPS: " + frames);
				frames = 0;
			}
			
		}
		
		stop();
	}

	/*
    * Fonction qui nous permet de faire a chaque image des actions , on va verifié nottament quel joueur a gagner 
    * Mais aussi le comportement entre le joueur les enemis le murs et la ligne d'arrivé
    */
	private void tick() {
		liste.tick();
		listeE.tick();
		listeA.tick();
		for(Joueur joueur:liste.objet) {
			arrive_a=joueur.gagner1();
			arrive_b=joueur.gagner2();
		}
		if(arrive_a == 1){
			JOptionPane.showMessageDialog(null, "Le joueur 1 a gagné !","Fin", JOptionPane.INFORMATION_MESSAGE);
			System.exit(0);
		}
		if(arrive_b == 2){
			JOptionPane.showMessageDialog(null, "Le joueur 2 a gagné !","Fin", JOptionPane.INFORMATION_MESSAGE);
			System.exit(0);
		}
	}

	/*
    * Fonction qui permet d'afficher/dessiner les personnages (joueur ennemies, ligne d'arrivé)
    */
	private void render() {
		BufferStrategy bs = this.getBufferStrategy();
		if(bs == null) {
			//Cree 3 buffer pour notre jeux
			this.createBufferStrategy(3);
			return;
		}
		Graphics g =  bs.getDrawGraphics();
		
		//ecran vide
		g.setColor(Color.blue);
		g.clearRect(0, 0, Fenetre.hauteur,  Fenetre.largeur);
		liste.render(g);
		mur.render(g);
		listeE.render(g);
		listeA.render(g);
		
		//paint(g);
		g.dispose();
		bs.show();
		
	}

	//Trace pour crée une map aléatoire
	// public void generation_map_aleatoire(Murs mur, Ennemis listeE,Arrives listeA ){
	// 	liste.ajouterperso(new Joueur(1050,23,ID.JOUEUR2, liste,listeE,listeA, mur));
	// 	liste.ajouterperso(new Joueur(50,23,ID.JOUEUR1,liste,listeE,listeA, mur ));
	//  listeA.ajouterperso(new Arrive(530,350,ID.ENNEMI,0,0));
	// 	int min_x = 0;
    //   	int max_x = Fenetre.hauteur;
	// 		int min_y = 0;
    //   	int max_y = Fenetre.largeur;
	// 	for(int ajout = 0; ajout <20 ;ajout++){
	// 		int random_x = (int)Math.floor(Math.random()*(max_x-min_x+1)+min_x);
	// 		int random_y = (int)Math.floor(Math.random()*(max_y-min_y+1)+min_y);
	// 		mur.ajoutermur(new Mur(random_x, random_y, 40, 200));
	// 		mur.ajoutermur(new Mur(random_x+530, random_y, 40, 200));
	// 	}	

	// }
	
	

}
