<?php
	require './session.php';
	require 'php/connectDB.php';
	init_php_session();
	$sql = "SELECT * FROM utilisateur where utilisateur.pseudo <> \"admin\" ;";
	$stmt = $stmt2 = $stmt3 = $pdo->query($sql);
	$stmt2 = $pdo->query($sql);
	$i=0;
	$stmt3 = $pdo->query($sql);
	$j=0;
?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css" >
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<script src="https://code.jquery.com/jquery-latest.js"></script>
		<title> Nos Chercheurs </title>
	</head>
	
	<script>
	$(document).ready(function(){
		<?php
			require 'php/navbar_connexion.php';
			require 'php/tri_tableau.php';
		?>
		let var_1 = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"];
	    let var_2 = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"];
	       
	    let a=0;
	    <?php if(is_logged()){?>
		
			<?php while($row3 = $stmt3->fetch(PDO::FETCH_ASSOC)) : ?>
		        
				// cache les paragraphes
				var_2[<?php echo $j;?>]= document.getElementById("<?php echo $j;?>");			
				var_2[<?php echo $j;?>].style.display = "none";
				
				// 
				var_1[<?php echo $j;?>] = document.getElementById("<?php echo htmlspecialchars($row3['nom']);?>");
				
				var_1[<?php echo $j;?>].addEventListener('click', function(event){
						a++;
						if(a%2 != 0){
							var_2[<?php echo $j?>].style.display = "block";
							
						}else{ 
							var_2[<?php echo $j?>].style.display = "none";
							 a =0;
						}
					});
				
				
				<?php $j++;endwhile; ?>
			<?php };?>
			
				 
				 
	
		
		});
		
	
	</script>
	
	<body>
		<?php
			require 'php/logo.php';
		?>
		<!-- menu haut -->
		<?php
		$file = 'chercheurs.php'; 
		require 'php/navbar.php' 
		?>
		
		<div class ="boite">
		<h3>
        		Liste des chercheurs :
		</h3>

		<table>
		    

		    <thead>
			<tr>
			    <th class="sort-by"> Nom </th>
			    <th class="sort-by"> Prénom </th>
			    <th class="sort-by"> Domaine de recherche </th>
			    <th class="sort-by"> Thèse </th>
			    <th class="sort-by"> Pays </th>
			</tr>
		    </thead>
			<?php if(!is_logged()){?>
			<tbody>
			<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC) ) : ?>
		    	<tr>
		       	<td><?php echo htmlspecialchars($row['nom']); ?></td>
		       	<td><?php echo htmlspecialchars($row['prenom']); ?></td>
		       	<td><?php echo htmlspecialchars($row['domaine_recherche']); ?></td>
		       	<td><?php echo htmlspecialchars($row['these']); ?></td>
		       	<td><?php echo htmlspecialchars($row['pays']); ?></td>
		    	</tr>
		    	<?php endwhile; ?>
		    </tbody>
		    <?php }else{ ?>
		    <tbody>
			<?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
		    	<tr>
		       	<td  id= "<?php echo htmlspecialchars($row['nom']);?>" > <?php echo htmlspecialchars($row['nom']); ?></td>
		       	<td><?php echo htmlspecialchars($row['prenom']); ?></td>
		       	<td><?php echo htmlspecialchars($row['domaine_recherche']); ?></td>
		       	<td><?php echo htmlspecialchars($row['these']); ?></td>
		       	<td><?php echo htmlspecialchars($row['pays']); ?></td>
		    	</tr>
		    	<?php endwhile; ?>
		    </tbody>
			<?php };?>			
			
		</table>
		
		<?php if(is_logged()){?>
		
		<?php while($row2 = $stmt2->fetch(PDO::FETCH_ASSOC)) : ?>
			<p id= "<?php echo $i;?>"> <?php echo htmlspecialchars($row2['bio']); ?> </p>
			
		<?php $i++;endwhile; ?>
	<?php };?>
		
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