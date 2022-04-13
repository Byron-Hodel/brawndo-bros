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
require_once "../../../bbrawndobros/config/dbconn.php";


$plants=[];
$sqlResults="";

if($_SERVER['REQUEST_METHOD'] === 'GET') {
	if(!empty($_GET['plantId'])) {
		$plantId = $_GET['plantId'];	
		
		$sql = "SELECT plantId, userId, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilMoistureCurrent, soilTempThreshold, soilTempDosage, soilTempCurrent, ambientLightThreshold, ambientLightDosage, ambientLightCurrent FROM Plants WHERE plantId = (?);";
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
		
		$sql = "SELECT plantId, userId, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilMoistureCurrent, soilTempThreshold, soilTempDosage, soilTempCurrent, ambientLightThreshold, ambientLightDosage, ambientLightCurrent FROM Plants WHERE userId = (?);";
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

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	
	$data = json_decode(file_get_contents('php://input'));
	$userId = $data->{'userId'};
	$plantName = $data->{'plantName'};
	$plantSpecies = $data->{'plantSpecies'};
	$soilMoistureThreshold = $data->{'soilMoistureThreshold'};
	$soilMoistureDosage = $data->{'soilMoistureDosage'};
	$soilTempThreshold = $data->{'soilTempThreshold'};
	$soilTempDosage = $data->{'soilTempDosage'};
	$ambientLightThreshold = $data->{'ambientLightThreshold'};
	$ambientLightDosage = $data->{'ambientLightDosage'};
	
	$sql = "INSERT INTO Plants (userId, plantName, plantSpecies, soilMoistureThreshold, soilMoistureDosage, soilTempThreshold, soilTempDosage, ambientLightThreshold, ambientLightDosage) VALUES ((?), (?), (?), (?), (?), (?), (?), (?), (?));";
	$args = [];
	$args[] = $userId;
	$args[] = $plantName;
	$args[] = $plantSpecies;
	$args[] = $soilMoistureThreshold;
	$args[] = $soilMoistureDosage;
	$args[] = $soilTempThreshold;
	$args[] = $soilTempDosage;
	$args[] = $ambientLightThreshold;
	$args[] = $ambientLightDosage;
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
	$plantId = $data->{'plantId'};
	$plantName = $data->{'plantName'};
	$plantSpecies = $data->{'plantSpecies'};
	$soilMoistureThreshold = $data->{'soilMoistureThreshold'};
	$soilMoistureDosage = $data->{'soilMoistureDosage'};
	$soilTempThreshold = $data->{'soilTempThreshold'};
	$soilTempDosage = $data->{'soilTempDosage'};
	$ambientLightThreshold = $data->{'ambientLightThreshold'};
	$ambientLightDosage = $data->{'ambientLightDosage'};
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
		if (!empty($ambientLightThreshold)) {
			$sql = "UPDATE Plants SET ambientLightThreshold = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $ambientLightThreshold;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Ambient Light Threshold Updated", $plantId);
		}
		if (!empty($ambientLightDosage)) {
			$sql = "UPDATE Plants SET ambientLightDosage = (?) WHERE plantId =(?);";
			$args = [];
			$args[] = $ambientLightDosage;
			$args[] = $plantId;
			$sqlResults = execute($sql, $args);
			response(200, "Plant Ambient Light Dosage Updated", $plantId);
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