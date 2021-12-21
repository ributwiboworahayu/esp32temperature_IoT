<?php 

require 'koneksi.php';

ini_set('date.timezone', 'Asia/Jakarta');

$now = new DateTime();

$datenow = $now->format("Y-m-d H:i:s");

		$kelembaban = $_POST['kelembaban'];
		$suhuc = $_POST['suhuc'];
		$suhuf = $_POST['suhuf'];
		$heatc = $_POST['heatc'];
		$heatf = $_POST['heatf'];

	    $sql = "INSERT INTO data VALUES ('','$datenow', '$kelembaban', '$suhuc', '$suhuf', '$heatc','$heatf')";

		if ($conn->query($sql) === TRUE) {
		    echo json_encode("Ok");
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	


	$conn->close();
 ?>