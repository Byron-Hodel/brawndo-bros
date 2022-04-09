<?php

/*
ToDo:
	- get event by plantId
	- check if plant exists before POST
	- error handling for failed sql commands
	- api authentication



*/

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

header("Content-Type:application/json");
require_once "../../classes/dbconn.php";


$plants=[];
$sqlResults="";

if($_SERVER['REQUEST_METHOD'] === 'GET') {
	if(!empty($_GET['eventId'])) {
		$eventId = $_GET['eventId'];	
		
		$sql = "SELECT * FROM Events WHERE eventId = (?);";
		$args = [];
		$args[] = $eventId;
		$sqlResults = execute($sql, $args);
	
		if(empty($sqlResults)) {
			response(200,"Event Not Found", NULL);
		} else {
			foreach ($sqlResults as $sqlResult) {
				$eventInfo[] = $sqlResult;
			}
			response(200,"Event Found", $eventInfo);
		}
	} 
}

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	
	$data = json_decode(file_get_contents('php://input'));
	$plantId = $data->{'plantId'};
	$eventType = $data->{'eventType'};
	$eventSubtype = $data->{'eventSubtype'};
	$eventValue = $data->{'eventValue'};
	$eventTime = $data->{'eventTime'};
	
	
	$sql = "INSERT INTO Events (plantId, eventType, eventSubtype, eventValue, eventTime) VALUES ((?), (?), (?), (?), (?));";
	$args = [];
	$args[] = $plantId;
	$args[] = $eventType;
	$args[] = $eventSubtype;
	$args[] = $eventValue;
	$args[] = $eventTime;
	$sqlResults = execute($sql, $args);
	$sql = "SELECT LAST_INSERT_ID();";
	$sqlResults = execute($sql);
	foreach ($sqlResults as $sqlResult) {
		$eventId[] = $sqlResult["LAST_INSERT_ID()"];
	}
	response(200, "Event Added", $eventId);
}


function response($status,$status_message,$data) {
	header("HTTP/1.1 ".$status);
	
	$response['status']=$status;
	$response['status_message']=$status_message;
	$response['data']=$data;
	
	$json_response = json_encode($response);
	echo $json_response;
}