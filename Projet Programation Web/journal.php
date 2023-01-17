<?php
	require './session.php';
	init_php_session();
	require("php/connectDB.php");
	$sql = "SELECT * FROM journaux;";
	$stmt = $pdo->query($sql);
?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css">
		<script src="https://code.jquery.com/jquery-latest.js"></script>		
		<title> Nos journaux </title>
		<script>
			
		$(document).ready(function(){
		

			
	
		});
		
		
		</script>
	</head>
	<body>
	
		<?php
			require 'php/logo.php';
		?>
		<!-- menu haut -->
		
		



		<div class="splitscreen">
			<div class="left">
			<button onclick="location.href='./journaux.php'"> Retour </button>
				  	
				  <h3> Journal : <?php echo $_GET['a']?></h3>
				  <p> <u>Titre</u> : <?php echo $_GET['a']?>  <p>
				  <p> <u>Isbn</u> : <?php echo $_GET['b']?> <p>
				  <p> <u>Editeur</u> : <?php echo $_GET['c']?> </p>
				  <P> <u>thème</u> :  <?php echo $_GET['d']?> </p>
				  
				  
				  					
			</div>
	
		</div>
			
		


	</body>
	

</html>
