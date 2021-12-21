<?php 


$servername = "localhost";
$username = "root";
$password = "";
$database = "iot-esp32";

$conn = mysqli_connect($servername, $username, $password, $database);
$kon = new mysqli($servername, $username, $password, $database);

function query($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
}


function hapus($id){
	global $conn;
	mysqli_query($conn, "DELETE FROM data WHERE id = $id");

return mysqli_affected_rows($conn);
}

function registrasi($data){
	global $conn;

	$username = strtolower(stripslashes( $data["username"]));
	$password = mysqli_real_escape_string($conn, $data["password"]);
	$password2 = mysqli_real_escape_string($conn, $data["password2"]);

 	$result = mysqli_query ($conn, "SELECT username FROM user WHERE username = '$username' ");
 	
 	if (mysqli_fetch_assoc ($result) ){
 		echo "
 		<script>
 			alert('Username sudah Terdaftar');
 		</script>
 		";
 		return false;
 	}

	if ( $password !== $password2){
		echo "
		<script>
		alert('Konfirmasi Password Tidak Sesuai')
		</script>
		";

		return false;
	} 

	$password = password_hash($password, PASSWORD_DEFAULT);
	mysqli_query($conn, "INSERT INTO user VALUES('', '$username', '$password')");

	return mysqli_affected_rows($conn);
}


?>