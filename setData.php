<?php
 
// Achtung Sicherheitsrisiko - Input-Werte validieren!
// Daten empfangen
$id = $_POST['id'];
$status= $_POST['status'];
 


// Inhalt in DB schreiben
//DB Informationen einlesen
require_once ('config.php');

//Verbindung herstellen
$db_link = mysqli_connect(
		Host,
		Benutzer,
		Passwort,
		Datenbank
		);
// wenn verbindung besteht:
if ($db_link){
    $sql = 'update Scheinwerfer set status = '.$status." where id = ".$id.";"; //Statement vorbereiten -- Status in DB updaten

    if($db_link->query($sql) === TRUE){ //Statement ausfuehren
	echo "successfully";
    }
    else
    {
	echo "error: " . $db_link->error;
    }
}

else{ //Abbruch, falls keine Verbindung zur DB hergestellt werden kann.
    die("Connection failed: " . $db_link->connect_error);
}

$db_link->close();
?>
