<?php
	require './session.php';
	init_php_session();
	require("php/connectDB.php");
	$sql = "SELECT * FROM publications;";
	$stmt = $pdo->query($sql);
?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css" >
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<script src="https://code.jquery.com/jquery-latest.js"></script>
		<title> Publications </title>
	</head>
	<script>
	$(document).ready(function(){
		<?php
			require 'php/navbar_connexion.php';
			require 'php/tri_tableau.php';
		?>
	});
	
	</script>
	
	<body>
		<?php
			require 'php/logo.php';
		?>
		<!-- menu haut -->
		<?php
		$file = 'publication.php'; 
		require 'php/navbar.php' 
		?>
		
		<div class ="boite">
			
		<h3>
        		Liste des publications
		</h3>

		<table>
		    

		    <thead>
			<tr>
			    <th class="sort-by"> Titre </th>
			    <th class="sort-by"> Auteur </th>
			    <th class="sort-by"> Date </th>
			    <th class="sort-by"> Sujet </th>
			
			</tr>
		    </thead>

		    <tbody>
			<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
		    	<tr>
		       	<td><?php echo htmlspecialchars($row['titre']); ?></td>
		       	<td><?php echo htmlspecialchars($row['auteur']); ?></td>
		       	<td><?php echo htmlspecialchars($row['date_de_publication']); ?></td>
		       	<td><?php echo htmlspecialchars($row['sujet']); ?></td>
		    	</tr>
		    	<?php endwhile; ?>
		    </tbody>
			
			
		</table>
		</div>
		<br>
		
		<?php 
			require 'php/footer.php' 
		?>
		
		
	</body>
	
	
</html>
<?php require 'php/connecte.php' ?>