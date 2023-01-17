<?php
//Ce fichier sert a avoir le boutton "Se Connecter" et "Se deconnecter" en fonction du type de l'utilisateur
//Il sera utilisé dans la plupart des fichiers.
echo <<<HEADER
var modal = document.getElementById('login');

		// Si on clique en dehors du cadre de connexion, on ferme celui--ci
		window.onclick = function(event) {
			if (event.target == modal) {
				modal.style.display = "none";
			}
		}
		//On cache par défaut le cadre pour créer un compte
		$('.creer').hide();

		$('#creer').click(function () {
			$('.log').hide();
			$('.creer').show();
		});
		$('#creer_arriere').click(function () {
			$('.creer').hide();
			$('.log').show();
		});
HEADER;
?>