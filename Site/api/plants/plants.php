<?php

/*
ToDo:
	- check for duplicate plantName before insert
	- get plant by userId
	- check if plant exists before update or delete
	- replace PUT if statements with switch.
	- combine responses in put request
	- error handling for failed sql commands
	- api authentication



*/

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

header("Content-Type:application/json");
require_once "../../classes/dbconn.php";

$httpHeaders = getallheaders();
// $accessToken = $httpHeaders['Authorization'];


$plants=[];
$sqlResults="";

if($_SERVER['REQUEST_METHOD'] === 'GET') {
	if(!empty($_GET['plantId'])) {
		$plantId = $_GET['plantId'];	
		
		// $sql = "SELECT plantId, userId, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilMoistureCurrent, soilTempThreshold, soilTempDosage FROM Plants WHERE plantId = (?);";
		$sql = "SELECT plantId, userId, plantImage, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilMoistureCurrent, soilTempThreshold, soilTempDosage FROM Plants WHERE plantId = (?);";
		$args = [];
		$args[] = $plantId;
		$sqlResults = execute($sql, $args);
	
		if(empty($sqlResults)) {
			response(200,"Plant Not Found", NULL);
		} else {
			foreach ($sqlResults as $sqlResult) {
				$plantInfo[] = $sqlResult;
			}
			response(200,"Plant Found", $plantInfo);
		}
	} 
	if(!empty($_GET['userId'])) {
		$userId = $_GET['userId'];	
		// $sql = "SELECT userId FROM Users WHERE userId = (?) and accessToken = (?);";
		$sql = "SELECT userId FROM Users WHERE userId = (?);";
		$args = [];
		$args[] = $userId;
		// $args[] = $accessToken;
		$sqlResults = execute($sql, $args);
		if(empty($sqlResults)) {
			response(401,"Unauthorized Access", NULL);
		} else {
			$sql = "SELECT plantId, userId, plantName, plantImage, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilMoistureCurrent, soilTempThreshold, soilTempDosage, soilTempCurrent FROM Plants WHERE userId = (?);";
			$args = [];
			$args[] = $userId;
			$sqlResults = execute($sql, $args);
		
			if(empty($sqlResults)) {
				response(200,"Plant Not Found", NULL);
			} else {
				foreach ($sqlResults as $sqlResult) {
					$plantList[] = $sqlResult;
				}
				response(200,"Plant Found", $plantList);
			}
		}
	}
}

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	
	$data = json_decode(file_get_contents('php://input'));
	$userId = $_GET['userId'];
	$plantName = $data->{'plantName'};
	$plantSpecies = $data->{'plantSpecies'};
	$soilMoistureThreshold = $data->{'soilMoistureThreshold'};
	$soilMoistureDosage = $data->{'soilMoistureDosage'};
	$soilTempThreshold = $data->{'soilTempThreshold'};
	$soilTempDosage = $data->{'soilTempDosage'};
	
	$sql = "INSERT INTO Plants (userId, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilTempThreshold, soilTempDosage) VALUES ((?), (?), (?), (?), (?), (?), (?));";
	$args = [];
	$args[] = $userId;
	$args[] = $plantName;
	$args[] = $plantSpecies;
	$args[] = $soilMoistureThreshold;
	$args[] = $soilMoistureDosage;
	$args[] = $soilTempThreshold;
	$args[] = $soilTempDosage;
	$sqlResults = execute($sql, $args);
	$sql = "SELECT plantId, plantName FROM Plants WHERE plantName = (?);";
	$args = [];
	$args[] = $plantName;
	$sqlResults = execute($sql, $args);
	foreach ($sqlResults as $sqlResult) {
		$plantInfo[] = $sqlResult;
	}
	response(200, "Plant Added", $plantInfo);
	//response(400, "Failed to Add User", NULL);
}

if($_SERVER['REQUEST_METHOD'] === 'PUT') {
	$data = json_decode(file_get_contents('php://input'));
	$plantId = $_GET['plantId'];

	$plantName = $data->{'plantName'};
	$plantSpecies = $data->{'plantSpecies'};
	$soilMoistureThreshold = $data->{'soilMoistureThreshold'};
	$soilMoistureDosage = $data->{'soilMoistureDosage'};
	$soilTempThreshold = $data->{'soilTempThreshold'};
	$soilTempDosage = $data->{'soilTempDosage'};
	if (!empty($plantId)) {
		if (!empty($plantName)) {
			$sql = "UPDATE Plants SET plantName = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $plantName;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Name Updated", $plantId);
		}
		if (!empty($plantSpecies)) {
			$sql = "UPDATE Plants SET plantSpecies = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $plantSpecies;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Species Updated", $plantId);
		}
		if (!empty($soilMoistureThreshold)) {
			$sql = "UPDATE Plants SET soilMoistureThreshold = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $soilMoistureThreshold;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Soil Moisture Threshold Updated", $plantId);
		}
		if (!empty($soilMoistureDosage)) {
			$sql = "UPDATE Plants SET soilMoistureDosage = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $soilMoistureDosage;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Soil Moisture Dosage Updated", $plantId);
		}
		if (!empty($soilTempThreshold)) {
			$sql = "UPDATE Plants SET soilTempThreshold = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $soilTempThreshold;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Soil Temp Threshold Updated", $plantId);
		}
		if (!empty($soilTempDosage)) {
			$sql = "UPDATE Plants SET soilTempDosage = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $soilTempDosage;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Soil Temp Dosage Updated", $plantId);
		}
	}
}

if($_SERVER['REQUEST_METHOD'] === 'DELETE') {
	if(!empty($_REQUEST['plantId'])) {
		$plantId = $_REQUEST['plantId'];	
		$sql = "DELETE FROM Plants WHERE plantId = (?);";
		$args = [];
		$args[] = $plantId;
		$sqlResults = execute($sql, $args);
		response(200,"Plant Deleted", $plantId);
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