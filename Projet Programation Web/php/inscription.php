<?php
//Fichier permetant d'inserer un utilisateur dans la base de donnée utilisateur
	require("./connectDB.php");
	//On a reçu un envoi
	if(isset($_POST['creer'])){
		$req = $pdo->prepare('INSERT INTO utilisateur (nom, prenom, pseudo, email, password, domaine_recherche,bio,these,pays,cv) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)');
		
		try{
			$req->execute(array($_POST['nom'], $_POST['prenom'], $_POST['pseudo'], $_POST['email'], $_POST['password'], $_POST['domaine_recherche'], $_POST['bio'], $_POST['these'], $_POST['pays'], $_POST['cv']));
		}catch(Exception $e){
			die('Erreur : ' . $e->getMessage());
		}
	}
	//On se redigire vers l'index
	header('Location: ../index.php');
?>