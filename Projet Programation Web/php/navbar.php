<?php
//Fichier permetant d'afficher le menu d'en haut (navbar)
	$info = pathinfo($file);
	$file_name =  basename($file,'.'.$info['extension']);
?>

<header>
	<!-- Si l'admin a changé la couleur, on la met à jour en forçant l'écriture du style sans toucher au fichier css -->
	<?php
		require 'php/connectDB.php';
		$couleur_fond = "SELECT url FROM image WHERE id = 2;";
		$stmt_couleur = $pdo->query($couleur_fond);
		$requete_couleur = $stmt_couleur->fetch(PDO::FETCH_ASSOC);
		echo $requete_couleur['url'];
	?>
	<ul class = "haut">
		<?php
		//Si l'admin est connecté on lui affiche son onglet unique
		if (is_admin()):
			echo '<li class = "haut"> <a class = "admin" href = "./admin.php"> Admin </a> </li>';
		endif;
		?>
		<!-- Pour vérifier dans quel endroit on se situe pour mettre la class active -->
		<li class = "haut"> <a <?php if($file_name=='index') echo "class = active1"; ?> href = "./index.php"> Accueil </a> </li>
		<li class = "haut"> <a <?php if($file_name=='chercheurs') echo "class = active1"; ?> href = "./chercheurs.php"> Nos chercheurs </a> </li>
		<li class = "haut"> <a <?php if($file_name=='publication') echo "class = active1"; ?> href = "./publication.php"> Publications </a> </li>
		<li class = "haut"> <a <?php if($file_name=='conference') echo "class = active1"; ?> href = "./conference.php"> Conférences </a> </li>
		<li class = "haut"> <a <?php if($file_name=='journaux') echo "class = active1"; ?> href = "./journaux.php"> Journaux </a> </li>	
		<li class = "droite"> <button class ="login" onclick="document.getElementById('login').style.display='block'"> Connexion </button> </li>
		<li class = "droite"> <button class ="logout" onclick="location.href='php/logout.php'"> Se deconnecter </button> </li>	
	</ul>
</header>

<!-- Login -->
<div id="login" class="modal">
	<span onclick="document.getElementById('login').style.display='none'" class="close" title="Fermer le formulaire">&times;</span>
	<div class = "log">
		<form class="modal-content" action ="php/login.php" method="POST">
			<input type="text"  name="pseudo" placeholder="Nom d'utilisateur" required>
			<input type="password" name="password" placeholder="Mot de passe" required>
			<input type="submit" name = "connexion" value="Connexion">
			<br>
			<input type="button" name ="bleubouton" value="Pas de compte ?" id="creer">
			<br>
		</form>
	</div>
	<div class = "creer">
		<form class="modal-content" action ="php/inscription.php" method="POST">
			<h1>Créer un compte</h1>
			<input type="text"  name="nom" placeholder="Nom" required>
			<input type="text"  name="prenom" placeholder="Prenom" required>
			<input type="text"  name="pseudo" placeholder="Pseudo" required>
			<input type="text"  name="email" placeholder="exemple@exemple.com" required>
			<input type="password" name="password" placeholder="Mot de passe" required>
			<input type="text"  name="domaine_recherche" placeholder="Domaine de recherche">
			<input type="text"  name="bio" placeholder="Votre biographie">
			<input type="text"  name="these" placeholder="Titre du thèse">
			<input type="text"  name="pays" placeholder="Pays">
			<label> Chosissez votre CV:</label>
			<br>
			<input type="file"  name="cv">
			<br>
			<input type="submit" name = "creer" value="Envoyer">
			<br>
			<input type="button" name ="bleubouton" value="J'ai déjà un compte" id="creer_arriere">
		</form>
	</div>

	</div>