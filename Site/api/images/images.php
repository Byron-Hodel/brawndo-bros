<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

//header("Content-Type:application/json");
require_once "../../classes/dbconn.php";

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	if ( !empty($_FILES['image']["name"])) {
		$fileLocation = "/var/www/html/files/" . $_FILES['image']["name"];
		if ( $_FILES["image"]["size"] < 100000 ) {
			if ( move_uploaded_file($_FILES["image"]["tmp_name"], $fileLocation) ) { 
				echo "Your file was successfully uploaded.";
				
				$plantId = $_GET['plantId'];
				$eventType = "data";
				$eventSubtype = "image";
				$eventValue = 'http://brawndotest.mattmoose.net/files/' . $_FILES['image']["name"];
				$eventTime = date("H:i:s Y/m/d");
				
				$sql = "INSERT INTO Events (plantId, eventType, eventSubtype, eventValue, eventTime) VALUES ((?), (?), (?), (?), (?));";
				$args = [];
				$args[] = $plantId;
				$args[] = $eventType;
				$args[] = $eventSubtype;
				$args[] = $eventValue;
				$args[] = $eventTime;
				$sqlResults = execute($sql, $args);
				
				$sql = "UPDATE Plants SET plantImage = (?) WHERE plantId =(?);";
				$args = [];
				$args[] = $eventValue;
				$args[] = $plantId;
				$sqlResults = execute($sql, $args);
			} else { 
				echo "There was a problem uploading your file. please try again."; 
			}
		} else { 
			echo "File too big!"; 
		}
	} else { 
		echo "Something went wrong, please try again.";
	} 
}

function response($status,$status_message,$data) {
	header("HTTP/1.1 ".$status);
	
	$response['status']=$status;
	$response['status_message']=$status_message;
	$response['data']=$data;
	
	$json_response = json_encode($response);
	echo $json_response;
}