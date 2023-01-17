<?php
	require './session.php';
	require 'php/connectDB.php';
	init_php_session();
	$sql = "SELECT * FROM conference;";
	$stmt = $pdo->query($sql);
?>

<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css" >
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<script src="https://code.jquery.com/jquery-latest.js"></script>
		<title> Nos conférences </title>
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
			$file = 'conference.php'; 
			require 'php/navbar.php' 
		?>
		
		<div class ="boite">
		
		<h3>
        		Liste des conférences
		</h3>

		<table>
		    
		<?php if(!is_logged()){?>
			<thead>
			<tr>
			    <th class="sort-by"> Titre de la conférence </th>
			    <th class="sort-by"> Abreviation </th>
			    <th class="sort-by"> Sujet </th>
			    <th class="sort-by"> Date </th>
			   
			</tr>
		    </thead>
		    
		    <?php }else{ ?>
		    <thead>
				<tr>
					<th class="sort-by"> Titre de la conférence </th>
					<th class="sort-by"> Abreviation </th>
					<th class="sort-by"> Sujet </th>
					<th class="sort-by"> Date </th>
					<th class="sort-by"> Date limite d'inscription </th>
					<th class="sort-by"> Conferencier principal </th>
					<th class="sort-by"> Pays/Ville </th>
				</tr>
		    </thead>
			<?php };?>
			
			<?php if(!is_logged()){?>
				<tbody>
					<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
						<tr>
							<td><?php $val1 = htmlspecialchars($row['titre_conference']); echo $val1; ?></td>
							<td><?php $val2 = htmlspecialchars($row['abreviation']); echo $val2; ?></td>
							<td><?php $val3 = htmlspecialchars($row['sujet']); echo $val3; ?></td>
							<td><?php $val4 = htmlspecialchars($row['date_conference']); echo $val4; ?></td>
						</tr>
					<?php endwhile; ?>
				</tbody>
		    <?php }else{ ?>
				<tbody>
					<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
						<tr>
							<td><?php $val1 = htmlspecialchars($row['titre_conference']); echo $val1; ?></td>
							<td><?php $val2 = htmlspecialchars($row['abreviation']); echo $val2; ?></td>
							<td><?php $val3 = htmlspecialchars($row['sujet']); echo $val3; ?></td>
							<td><?php $val4 = htmlspecialchars($row['date_conference']); echo $val4; ?></td>
							<td><?php $val5 = htmlspecialchars($row['date_limite_inscription']); echo $val5; ?></td>
							<td><?php $val6 = htmlspecialchars($row['conferencier']); echo $val6; ?></td>
							<td><?php $val7 = htmlspecialchars($row['pays']); echo $val7; ?></td>
							<td> <a href = "./conf.php?
									a=<?php echo $val1; ?>&amp;
									b=<?php echo $val2; ?>&amp;
									c=<?php echo $val3; ?>&amp;
									d=<?php echo $val4; ?>&amp;
									e=<?php echo $val5; ?>&amp;
									f=<?php echo $val6; ?>&amp;
									g=<?php echo $val7; ?>&amp;
								"> 
							Plus d'info </a> </td>
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
	require 'php/connecte.php';
?>