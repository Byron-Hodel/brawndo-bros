<?php
define('DB_HOST','localhost');
define('DB_USER','root');
define('DB_PASSWORD','password');
define('DB_DATABASE','BrawndoBros');

include_once('Db_conn.php');
$db=new DatabaseConnection;
?>


<?php
// Enter your host name, database username, password, and database name.
// If you have not set database password on localhost then set empty.
/*$con = mysqli_connect("localhost","root","password","BrawndoBros");
// Check connection
if (mysqli_connect_errno()){
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}*/
?>
