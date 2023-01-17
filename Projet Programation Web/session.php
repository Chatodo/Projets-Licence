<?php
//Fichier qui gère tout ce qui est session

// On initialise la session de l'utilisateur en vérifiant que personne n'est connecté
// @return true, la session a bien été initalisé
// @return false, erreur --> quelqu'un est connecté
function init_php_session(): bool{
    if (!session_id()) {
        session_start();
        session_regenerate_id();
        return true;
    }
    return false;
}

// On verifie si un utilisateur est connecté
// @return true si quelqu'un est connecté
// @return false si personne est connecté
function is_logged(): bool{
    if (isset($_SESSION['pseudo']))
       return true;
    return false;
}

// On vérifie si l'admin est connecté 
// @return true si l'admin est connecté
// @return false si l'admin n'est pas connecté
function is_admin():bool{
    if (isset($_SESSION['pseudo']) && $_SESSION['pseudo'] == "admin")
        return true;
    return false;
}
?>