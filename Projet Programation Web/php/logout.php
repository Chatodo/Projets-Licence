<?php
//Fichier permettant de se déconnecter
	session_start();
	session_unset();
    session_destroy();
	header('Location: ../index.php');
?>