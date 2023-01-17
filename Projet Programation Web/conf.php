<?php
// De quoi je me suis aidé pour ça : https://stackoverflow.com/questions/3807963/how-to-get-longitude-and-latitude-of-any-address
//Mais faut payer pour utiliser celui de google donc j'ai utilisé https://developer.mapquest.com/documentation/open/geocoding-api/
			$address = $_GET['g']; // L'adresse
			$apiKey = '0bb9043582d7408c832fa99db8ea367b'; //Ma clé API !!
			// Get JSON results
			$geo = file_get_contents('https://api.opencagedata.com/geocode/v1/json?q='.urlencode($address).'&key='.$apiKey.'&language=fr&pretty=1');
			$geo = json_decode($geo, true); // Convert the JSON to an array
			if (isset($geo['status'])) {
				$latitude = $geo['results'][0]['geometry']['lat']; // Latitude
				$longitude =  $geo['results'][0]['geometry']['lng']; //Longitude
			}
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
			let togg1 = document.getElementById("date");
			let togg2 = document.getElementById("conferencier");
			let togg3 = document.getElementById("pays");
			let d1 = document.getElementById("a");
			let d2 = document.getElementById("b");
			let d3 = document.getElementById("c");
			
			d1.style.display = "none";
			d2.style.display = "none";
			d3.style.display = "none";
			
			togg1.addEventListener("click", () => {
			  if(getComputedStyle(d1).display != "none"){
			    d1.style.display = "none";
			  } else {
			    d1.style.display = "block";
			  }
			})
			
			togg2.addEventListener("click", () => {
			  if(getComputedStyle(d2).display != "none"){
			    d2.style.display = "none";
			  } else {
			    d2.style.display = "block";
			  }
			})
			
			togg3.addEventListener("click", () => {
			  if(getComputedStyle(d3).display != "none"){
			    d3.style.display = "none";
			  } else {
			    d3.style.display = "block";
			  }
			})

			// Ce que j'ai utilisé pour la map
			//https://stackoverflow.com/questions/925164/openstreetmap-embedding-map-in-webpage-like-google-maps
			var element = document.getElementById('osm-map');

			// Height has to be set. You can do this in CSS too.
			element.style = 'height:300px;';

			// Create Leaflet map on map element.
			var map = L.map(element);

			// Add OSM tile layer to the Leaflet map.
			L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
				attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
			}).addTo(map);

			// Target's GPS coordinates.
			var target = L.latLng("<?php echo $latitude; ?>", "<?php echo $longitude; ?>");

			// Set map's center to target with zoom 5.
			map.setView(target, 5);

			// Place a marker on the same location.
			L.marker(target).addTo(map);
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
				  <button onclick="location.href='./conference.php'"> Retour </button>	
				  <h3> Conférence : <?php echo $_GET['a']?></h3>
				  <p> <u>Titre</u> : <?php echo $_GET['a']?> (<?php echo $_GET['b']?>) <p>
				  
				  <p> <u>Sujet </u>: <?php echo $_GET['c']?> </p>
				  <P> <u>Date de la conférence</u> :  <?php echo $_GET['d']?> </p>
				  
				  <p id = "a"> <font color = "red">Date limite d'inscription : <?php echo $_GET['e']?> </p> </font>
				  <p id = "b"> Conférencier : <b> <?php echo $_GET['f']?> </b></p>
				  <p id = "c"> Pays/Ville : <?php echo $_GET['g']?> </p>
				  					
			</div>
	
			<div class="right">
					<br>
				    	<button id = "date"> Date limite d'inscription de la conférence</button>
				    	<br>
				    	<br>
				    	<button id = "conferencier"> Conférencier </button>
				    	<br>
				    	<br>
				    	<button id = "pays"> Pays/Ville où aura lieu la conférence </button>
				    		
				    
	 		</div>
		</div>
		
		<script src="https://unpkg.com/leaflet@1.6.0/dist/leaflet.js"></script>
		<link href="https://unpkg.com/leaflet@1.6.0/dist/leaflet.css" rel="stylesheet"/>
		<div id="osm-map"></div>

	</body>
	

</html>
