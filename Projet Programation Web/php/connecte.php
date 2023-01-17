<?php
//Fichier permetant de cacher le bouton connecter/se déconecter en fonction du statut de l'utilisateur

	//Si un utilisateur est connecté, on cache le bouton login et on montre le bouton pour se déconnecter
	if (is_logged()) :
		?>
		<script language="javascript">
			$('.login').hide();
			$('.logout').show();
		</script>
	<?php

	//On fait le contraire --> utilisateur déconnecte, on affiche le bouton pour se connecter
	else :
	?>
		<script language="javascript">
			$('.login').show();
		</script>
	<?php
	endif;
?>