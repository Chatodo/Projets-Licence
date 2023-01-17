<?php
	
	require './session.php';
	init_php_session();
	require("php/connectDB.php");
	
	
	$sql = "SELECT * FROM info ;";

	$stmt = $pdo->query($sql);
	
	
	
?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css">
		<script src="https://code.jquery.com/jquery-latest.js"></script>		
		<title> Science&Colab </title>
		
		
	</head>
	<body>
	
		<?php
			require 'php/logo.php';
			$file = 'index.php'; 
			require 'php/navbar.php'
		?>
		
		



		<div class="splitscreen">
			<div class="left">
				  	
				  <h3> Titre de l'info : <?php echo $_GET['nom']?></h3>
				  <?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
				  
		    			<p><?php if($row['titre'] == $_GET['nom']  ){echo htmlspecialchars($row['sujet']);}?></p>
		    		
		    		<?php endwhile; ?>
			<br><br><br>
			<button onclick="location.href='./index.php'"> Retour a la page principal </button>
				  					
			</div>
	
		</div>
			
		


	</body>
	

</html>
