<!DOCTYPE html>
<?php //Verbindung zur Datenbank
require_once ('config.php'); //Zugangsdaten laden
$led = [];

$db_link = mysqli_connect( //verbinden
		Host,
		Benutzer,
		Passwort,
		Datenbank
		);
if ($db_link){ //wenn Verbindung besteht
    $sql = 'select id, status from Scheinwerfer'; //Statement vorbereiten: zeige alle IDs und dessen Status 
    $result = mysqli_query($db_link, $sql) // Abfrage starten
	or die('Fehlgeschlagen' . mysql_error());
    
    if ($result){ //wenn die Abfrage erfolgreich war
	while ($zeile = mysqli_fetch_array( $result, MYSQLI_ASSOC)){
	    $led[$zeile['id']] = $zeile['status']; //in Datenfeld "led" uebertragen; Index des Datenfeldes = ID des Scheinwerfers
	}
	mysqli_free_result($result);
	
    }
}

else{ //Abbruch, falls keine Verbindung zur DB hergestellt werden kann
    die('keine verbindung: ' . mysqli_error());
}
$db_link->close(); //Verbindung schließen
?>
<script><!-- AJAX möglich -->
    var state_front = "<?php echo $led[1]; ?>";
    var state_rear = "<?php echo $led[2]; ?>";
</script>


<html lang="de">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="script.js"></script>
    <noscript>
      JavaScript deaktiviert
    </noscript>
    <title>Garten Beleuchtung</title>
    <link rel="icon" type="image/jpg" href="favicon.jpg">
  </head>

  <body>
  <div class="flex-container">
	<section class="flex-item">
		<p>vorderer Scheinwerfer</p>
		<label class="switch">
			<input id="front" type="checkbox">
			<span class="slider round"></span>
		</label>
	</section>
	
	<section class="flex-item">
		<p>hinterer Scheinwerfer</p>
		<label class="switch">
			<input id="rear" type="checkbox">
			<span class="slider round"></span>
		</label>
	</section>
  </div>
  </body>
</html>

