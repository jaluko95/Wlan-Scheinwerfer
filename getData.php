<?php
$id = $_GET['id']; //Statusabfrage für bestimmte ID

require_once ('config.php'); //Zugangsdaten für die Datenbank laden

$db_link = mysqli_connect( 
		Host,
		Benutzer,
		Passwort,
		Datenbank
		);
		
if ($db_link){
    $sql = 'select status from Scheinwerfer where id = ' . $id; // Statement vorbereiten -- Abfrage des Status von $id
    $result = mysqli_query($db_link, $sql)
	or die('Fehlgeschlagen' . mysql_error());
    
    if ($result){
		$status = mysqli_fetch_array( $result, MYSQLI_ASSOC);
		$status = $status['status'];
	}
	mysqli_free_result($result);
}

else{ //Abbruch, falls keine Verbindung zur DB hergestellt werden kann
    die('keine verbindung: ' . mysqli_error());
}
$db_link->close(); //Verbindung schließen

echo $status; //Antwort senden -- 0 für aus; 1 für an
?>
