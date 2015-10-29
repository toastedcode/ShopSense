<?php
$servername = "localhost";
$username = "root";
$password = "mysqlt0st";
$dbname = "shop_sense";

handleCommand($_GET["command"]);

function mysqlConnect()
{
   global $servername, $username, $password, $dbname;

   // Create connection
   $conn = new mysqli($servername, $username, $password, $dbname);

   // Check connection
   if ($conn->connect_error)
   {
      die("Connection failed: " . $conn->connect_error);
   }

   return ($conn);
}

function getSensorReading($sensorId)
{
	$reading = 0;
	
	// Connect to database.
	$conn = mysqlConnect();
	
	// Construct the query.
	$sql = "SELECT sensor_reading FROM data ORDER BY index DESC LIMIT 1");
	
	// Retrieve from database.
	$result = $conn->query($sql);
	
	if ($result->num_rows > 0)
	{
		$row = $result->fetch_assoc();
      $reading = $row['sensor_reading'];
	}
	
   // Close the connection.
   $conn->close();
	
	return ($reading);
}

echo "<meta http-equiv=\"refresh\" content=\"1\">";
echo "Washing machine status";
echo "<p/>";

if (getSensorReading("vibration_01") == 1)
{
	echo "<img src=\"green_light.png\"/>";
}
else
{
	echo "<img src=\"red_light.png\"/>";
}

?>