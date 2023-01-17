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
		<link rel="stylesheet" href= "css/style.css" >
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<script src="https://code.jquery.com/jquery-latest.js"></script>
		<title> Nos journaux </title>
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
			$file = 'journaux.php'; 
			require 'php/navbar.php' 
		?>
		  
		<div class ="boite">
			
			<h3>Nos Journaux</h3>
			
			<table>
				<?php if(!is_logged()){?>
						<thead>
							<tbody>
								<tr>
									<th class="sort-by"> Titre  </th>
									<th class="sort-by"> Thème </th>
								</tr>
							</tbody>
						</thead>
				<?php }else{ ?>
					<thead>
						<tr>
							<th class="sort-by"> Titre</th>
							<th class="sort-by"> Isbn </th>
							<th class="sort-by"> Editeur</th>
							<th class="sort-by"> Thème</th>
						
						</tr>
					</thead>
				<?php };?>
					
				<?php if(!is_logged()){?>
					<tbody>
						<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
							<tr>
								<td><?php $val1 = htmlspecialchars($row['titre']); echo $val1; ?></td>
								<td><?php $val2 = htmlspecialchars($row['theme']); echo $val2; ?></td>
							</tr>
						<?php endwhile; ?>
					</tbody>
				<?php }else{ ?>
					<tbody>
						<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
							<tr>
								<td><?php $val1 = htmlspecialchars($row['titre']); echo $val1; ?></td>
								<td><?php $val2 = htmlspecialchars($row['isbn']); echo $val2; ?></td>
								<td><?php $val3 = htmlspecialchars($row['editeur']); echo $val3; ?></td>
								<td><?php $val4 = htmlspecialchars($row['theme']); echo $val4; ?></td>
								<td> <a href = "./journal.php?
								a=<?php echo $val1; ?>&amp;
								b=<?php echo $val2; ?>&amp;
								c=<?php echo $val3; ?>&amp;
								d=<?php echo $val4; ?>&amp;
								"> Plus d'info </td>
							</tr>
						<?php endwhile; ?>
					</tbody>
				<?php };?>
			</table>
		</div>
		<br>

		<?php 
			require 'php/footer.php' 
		?> 
	</body>	
</html>

<?php 
	require 'php/connecte.php' 
?>