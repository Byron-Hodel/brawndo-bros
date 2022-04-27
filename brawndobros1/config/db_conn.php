<?php

$host="localhost";
$username="root";
$password="password";
$database="BrawndoBros";
	
$con=mysqli_connect("$host","$username","$password", "$database");

if(!$con)
{
	header("Location:error/dberror.php");
	die();
}
?>