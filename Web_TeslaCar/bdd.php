<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv = "Content-Type" charset="utf-8">
		<title> TeslaCar </title>
		<hr><center> Voici le recap de notre voitre TeslaCar </hr>
		<hr> </hr>
	</head>
	<body>
		<?php
try
{
	// On se connecte à MySQL
	$bdd = new PDO('mysql:host=localhost;dbname=teslacar;charset=utf8', 'root', '');
}
catch(Exception $e)
{
	// En cas d'erreur, on affiche un message et on arrête tout
        die('Erreur : '.$e->getMessage());
}

// Si tout va bien, on peut continuer

// On récupère tout le contenu de la table jeux_video
$reponse = $bdd->query('SELECT * FROM donnee');

// On affiche chaque entrée une à une
while ($donnees = $reponse->fetch())
{
?>
<p>
    La vitesse est de : <?php echo $donnees['vitesse']; ?> <br />
	La position de la voiture est : <?php echo $donnees['position']; ?> </br>
   
   </p>
<?php
}

$reponse->closeCursor(); // Termine le traitement de la requête

?>
	</body> 
</html>