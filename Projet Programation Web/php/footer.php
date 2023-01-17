<?php
//Fichier permetant d'afficher le menu d'en bas (footer)
	$info = pathinfo($file);
	$file_name =  basename($file,'.'.$info['extension']);
?>

<footer>
	<div class = "bbas">
	<ul class = "bas">
		<?php
			//Si l'admin est connecté on lui affiche son onglet unique
			if (is_admin()):
				echo '<li> <a class = "admin" href = "./admin.php"> Admin </a> </li>';
			endif;
		?>
		<li> <a <?php if($file_name=='index') echo "class = active2"; ?> href = "./index.php"> Accueil </a> </li>
		<li> <a <?php if($file_name=='chercheurs') echo "class = active2"; ?> href = "./chercheurs.php"> Nos chercheurs </a> </li>
		<li> <a <?php if($file_name=='publication') echo "class = active2"; ?> href = "./publication.php"> Publications </a> </li>
		<li> <a <?php if($file_name=='conference') echo "class = active2"; ?> href = "./conference.php"> Conférences </a> </li>
		<li> <a <?php if($file_name=='journaux') echo "class = active2"; ?> href = "./journaux.php"> Journaux </a> </li>	
	</ul>
	</div>
</footer>