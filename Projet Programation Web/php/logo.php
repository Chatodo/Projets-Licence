<?php
//Fichier permettant d'afficher le logo dans toutes les pages
	require 'php/connectDB.php';
	$logo = "SELECT url FROM image WHERE id = 1;";
	$stmt_logo = $pdo->query($logo);
	$requete_logo = $stmt_logo->fetch(PDO::FETCH_ASSOC);
?>
<div class = "fondlogo"> <img class = "logo" src="<?php echo htmlspecialchars($requete_logo['url']); ?>" alt = "logo" > </div>