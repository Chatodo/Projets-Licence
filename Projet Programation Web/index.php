<!-- https://validator.w3.org/ -->

<!-- Page web par défaut -->
<!-- NOTE : On a préfére regrouper pas mal de choses, comme le header, le logo dans des fichiers php séparé (en général présent dans php/)
	 ce qui explique le nombre de require -->
<?php
	require './session.php';
	require 'php/connectDB.php';
	init_php_session();

?>
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href= "css/style.css">
		<link rel = "icon" href = "images/img_header.png" type = "image/x-icon">
		<script src="https://code.jquery.com/jquery-latest.js"></script>		
		<title> Science&Colab </title>
		<script>
			$(document).ready(function(){
				<?php
					require 'php/navbar_connexion.php';
				?>

				//On cache tout sauf la 1er image
				$('.diapo img:gt(0)').hide();
				$('.corps p:gt(0)').hide();
				//On créer l'interval
				var interval;
				//La fonction qui permet d'avoir un diapo automatique
				var diapo_img = function(){
					interval = setInterval(function(){
							$('.diapo :first-child').fadeOut(100).next().fadeIn(50).end().appendTo('.diapo');
							$('.corps :first-child').fadeOut(100).next().fadeIn(50).end().appendTo('.corps');
							}, 
						2000);
				};
				//Quand la souris est sur l'image on stop le diapo
				// Quand la souris est enlevé de l'image, on rapelle la fonction diapo_img
				$('.diapo').hover(function(){
						$('.diapo :first-child').stop();
						$('.corps :first-child').stop();
						//On stop le temps
						clearInterval(interval); 
				},diapo_img);
			});


		</script>
	</head>
	<body>
		<!-- Ajout du logo ainsi que du navbar -->
		<?php
			require 'php/logo.php';
			$file = 'index.php'; 
			require 'php/navbar.php'
		?>


		<!-- partie droite affichage evenement -->
			
			<!-- diaporama & evenement -->
			
			<div class="splitscreen">
				  <div class="left">
				  	
					<div class = "diapo">
						<?php
							$sql_img = "SELECT url FROM image ORDER BY id DESC LIMIT 4;";
							$stmt_img = $pdo->query($sql_img);
						?>
						<?php while($row_img = $stmt_img->fetch(PDO::FETCH_ASSOC)) : ?>
							<img class = "img_d" src = <?php $val = htmlspecialchars($row_img['url']); echo $val; ?> alt = "img">
						<?php endwhile; ?>
					</div>
				    <div class = "corps">
						<?php
							$sql_info = "SELECT titre FROM info ORDER BY id DESC LIMIT 4;";
							$stmt_info = $pdo->query($sql_info);
						?>
						<?php while($row_text = $stmt_info->fetch(PDO::FETCH_ASSOC)) : ?>
							<p style="text-decoration:underline;" onclick = "location.href='./info.php?nom=<?php $t_val = htmlspecialchars($row_text['titre']); echo $t_val; ?>'"> <?php echo $t_val;?> </p>
						<?php endwhile; ?>
				    </div>
				    	
				  </div>

				  <div class="right">
				  	<br>
				    Science&Colab offre une plateforme de collaboration entre chercheurs du monde entier. 
					<br>
					<br>
					Il partage des travaux de recherche dans des domaines différents (Sciences de données, 
					Sciences humaine, Astronomie, Economie, etc.).
					<br>
					<br> 
					Il présente aussi les différentes conférences 
					et journaux dans le but de diffuser les informations liées à chaque conférence et de chaque 
					domaine de recherche. 
					Ainsi on vous invite a vous balader entre les onglets !
					<br>
					<u>N'hésitez pas à cliquer sur le texte souligné des images qui défilent si vous voulez en savoir plus. </u>

				    
				</div>
			</div>

		<?php 
			require 'php/footer.php' 
		?>
	</body>
	

</html>

<!-- On regarde si un utilisateur est connecté -->
<?php 
	require 'php/connecte.php' 
?>