<?php
// Fichier permettant de vérifier si l'utilisateur est présent dans la base de donnée et ainsi le connecter
	// Initialiser la session
	session_start();
	require("./connectDB.php");
	if(isset($_POST['connexion'])){
		$nom = $_POST['pseudo'];
		$mdp = $_POST['password'];
		$sql = "SELECT * FROM utilisateur WHERE pseudo =? AND password =?";
		// Vérifiez si l'utilisateur est connecté, ---sinon demande de réesaye--- ==> A Faire
		try{
			$requete = $pdo->prepare($sql);
			$requete->execute(array($nom,$mdp));
			$count = $requete->rowCount();
			if($count){
				$_SESSION["pseudo"] = $nom;			
			}
		}
		catch (PDOException $e) {
			echo utf8_encode("Echec de select : " . $e->getMessage() . "\n");
			die(); // On arrête tout.
		}

	}
	//Pour l'admin
	if($_SESSION["pseudo"] == "admin")
		header('Location: ../admin.php');
	//Autre
	else
		header('Location: ../index.php');
?>