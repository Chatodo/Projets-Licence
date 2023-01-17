<?php
//Fichier de l'utilisateur admin
	require './session.php';
	require 'php/connectDB.php';
	init_php_session();
	//On vérifie que l'admin est bien connecté
	if(!is_admin()){
		http_response_code(403);
		die('Réservé UNIQUEMENT a l\'admin désolé');
	}

	// Fonction qui créer le lien de l'image posté pour pouvoir l'inserer dans la BD
	// @return $img_nv si les conditions sont satisfaites
	// sinon @return NULL
	// @require $_POST[$nom_post], $_FILES[$nom_input]['name'] != NULL
	function creation_lien_image($nom_post,$nom_input):?string{
		if(isset($_POST[$nom_post])){
			if(!empty($_FILES[$nom_input]['name'])){
				$chemin = "images/";
				$img_nv =  $chemin .$_FILES[$nom_input]['name'];
				return $img_nv;
			}
		}
		return NULL;
	}

	// On ajout le nouveau a la base de donné s'il y'a eu un changement
	if(!empty($logo_nv = creation_lien_image("envoi","logo"))){
		$logo = "UPDATE image SET url = '$logo_nv'  WHERE id = 1;";
		$stmt_logo = $pdo->prepare($logo);
		$stmt_logo->execute();
	}

	//On ajoute la nouvelle image ainsi que son titre et sa description
	if(!empty($diapo_nv = creation_lien_image("envoi","diapo"))){
		$img = "INSERT INTO image(url) VALUES ('$diapo_nv');";
		$stmt_ajoutimg = $pdo->prepare($img);
		$stmt_ajoutimg->execute();
		$txt = "INSERT INTO info(titre,sujet) VALUES('$_POST[text_titre]','$_POST[text_desc]');";
		$stmt_ajout_txt= $pdo->prepare($txt);
		$stmt_ajout_txt->execute();
	}

	//On ajoute l'evenement
	if(isset($_POST['envement'])){
		$sql_evenment = "INSERT INTO  conference (titre_conference,abreviation,sujet,date_conference,date_limite_inscription,conferencier,pays)
		VALUES('$_POST[text_eve]','$_POST[text_abr]','$_POST[text_suj]','$_POST[tdate]','$_POST[tdatelim]','$_POST[text_conf]','$_POST[text_pays]') ";
		$stmt_ajoutconf = $pdo->prepare($sql_evenment);
		$stmt_ajoutconf->execute();
	}

	//On change la couleur si l'admin a décidé de la changer
	if(isset($_POST['couleur'])){
		$couleur = '<style> .fondlogo{background-color:'.$_POST['text_couleur'].';}</style>';
		$logo_couleur = "UPDATE image SET url = '$couleur'  WHERE id = 2;";
		$stmt_changercouleur = $pdo->prepare($logo_couleur);
		$stmt_changercouleur->execute();
	}
	//On ajoute le journal
	if(isset($_POST['journal'])){
		$sql_journ = "INSERT INTO  journaux (titre,isbn,editeur,theme)
		VALUES('$_POST[jr]','$_POST[isbn]','$_POST[edit]','$_POST[theme]')";
		$stmt_ajoutjour = $pdo->prepare($sql_journ);
		$stmt_ajoutjour->execute();
	}
	//On ajoute la publication
	if(isset($_POST['publication'])){
		$sql_public = "INSERT INTO  publications (titre,auteur,date_de_publication,sujet)
		VALUES('$_POST[titre]','$_POST[auteur]','$_POST[datep]','$_POST[sujet]')";
		$stmt_ajoutpublic = $pdo->prepare($sql_public);
		$stmt_ajoutpublic->execute();
	}

?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css">
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<style>
			.splitscreen {
				flex-direction: column;
			}
			h1{
				text-align: center;
			}
		</style>
		<script src="https://code.jquery.com/jquery-latest.js"></script>		
		<title> Admin </title>
		<script>
			$(document).ready(function(){
				$('.login').hide();
				$('.logout').show();
				//Si l'utilisateur a ajouté une image il faut qu'il mette un titre ainsi qu'une description
				$("#diapo_image").change(function(){
					var image_upload = $("#diapo_image")[0].files.length;
					if(image_upload > 0){
						document.getElementById('text_titre').required = true; 
						document.getElementById('text_desc').required = true;
					}
					else{
						document.getElementById('text_titre').required = false; 
						document.getElementById('text_desc').required = false;
					}
				});
				//On cache par défaut les formulaires d'ajouts
				$('.conf').hide();
				$('.journal').hide();
				$('.publication').hide();
				//On affiche ce que l'utilisateur a coché pour décider de ce qu'il veut remplir
				$('input[type="checkbox"]').click(function() {
                    var inputValue = $(this).attr("value");
                    $("." + inputValue).toggle();
                });
			
			});



		</script>
	</head>
	<body>
		<!-- Pour afficher le logo -->
		<?php
			require 'php/logo.php';
		?>

		<!-- menu haut -->
		<?php 
			$file = 'admin.php'; 
			require 'php/navbar.php' 
		?>
		
		<!-- On met tout les formulaires possibles par l'admin -->
		<div class="splitscreen">
			<form action ="./admin.php" method="POST" enctype="multipart/form-data">
			<h2> Changer la couleur de fond du logo </h2>
			<input type="text"  name="text_couleur" id="text_couleur">
			<input type="submit" value="Envoyer les changements" name="couleur">
			</form>
		</div>

		<br>
			
		<div class="splitscreen">
			<h1>Administration des images</h1>
			<form action ="./admin.php" method="POST" enctype="multipart/form-data">
				<h2> Changer le logo: </h2>
				<input type="file"  name="logo" id="image">
				<br>
				<br>
				<h2> Ajouter une image pour le diaporama: </h2>
				<input type="file"  name="diapo" id="diapo_image">
				<h2> Le titre de l'image </h2>
				<input type="text"  name="text_titre" id="text_titre">
				<h2> La description </h2>
				<input type="text"  name="text_desc" id="text_desc">
				<br>
				<input type="submit" value="Envoyer les changements" name="envoi">
			</form>
		</div>
		<br>
		<div class="splitscreen">
			<h1> Ajouter une information </h1>
			<label>
				<input type="checkbox"value="conf">Conférence
			</label>
			<label>
				<input type="checkbox" value="journal">Journal
			</label>
			<label>
				<input type="checkbox"value="publication">Publication
			</label>
		</div>
		
		<div class="splitscreen">
			<div class = "conf">
				<h1> Ajouter une conférence </h1>
				<form action ="./admin.php" method="POST" enctype="multipart/form-data">
					<h2> Nom de la conférence </h2>
					<input type="text"  name="text_eve" id="text_eve" required>
					<h2> Date de l'évenement</h2>
					<input type="date"  name="tdate" id="tdate" required>
					<h2> Abrevation</h2>
					<input type="text"  name="text_abr" id="text_abr" required>
					<h2> Sujet</h2>
					<input type="text"  name="text_suj" id="text_suj" required>
					<h2> Date limite d'inscription</h2>
					<input type="date"  name="tdatelim" id="tdatelim" required>
					<h2> Conferencier</h2>
					<input type="text"  name="text_conf" id="text_conf" required>
					<h2> Pays/Ville</h2>
					<input type="text"  name="text_pays" id="text_pays" required>
					<input type="submit" value="Envoyer l'ajout de l'evenement" name="envement">
				</form>
			</div>
		</div>
		<div class="splitscreen">
			<div class = "journal">
				<h1> Ajouter un journal </h1>
				<form action ="./admin.php" method="POST" enctype="multipart/form-data">
					<h2> Titre du journal </h2>
					<input type="text"  name="jr" id="jr" required>
					<h2>Chiffre ISBN</h2>
					<input type="number"  name="isbn" id="isbn" required>
					<h2> Editeur</h2>
					<input type="text"  name="edit" id="edit" required>
					<h2> Theme</h2>
					<input type="text"  name="theme" id="theme" required>
					<input type="submit" value="Envoyer l'ajout du journal" name="journal">
				</form>
			</div>
		</div>
		<div class="splitscreen">
			<div class = "publication">
				<h1> Ajouter une publication </h1>
				<form action ="./admin.php" method="POST" enctype="multipart/form-data">
					<h2> Titre</h2>
					<input type="text"  name="titre" id="titre" required>
					<h2> Auteur</h2>
					<input type="text"  name="auteur" id="auteur" required>
					<h2> Date de publication </h2>
					<input type="date"  name="datep" id="datep" required>
					<h2> Sujet</h2>
					<input type="text"  name="sujet" id="sujet" required>
					<input type="submit" value="Envoyer l'ajout de la publication" name="publication">
				</form>
			</div>
		</div>

		<?php 
			require 'php/footer.php' 
		?>
	</body>
	

</html>


