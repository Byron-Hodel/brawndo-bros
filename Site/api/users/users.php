<?php

/*
ToDo:
	- check for duplicate email before insert
	- check if plant exists before update or delete
	- error handling for failed sql commands
	- hash password on insert
	- api authentication



*/

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

header("Content-Type:application/json");
require_once "../../classes/dbconn.php";

$httpHeaders = getallheaders();
// $accessToken = $httpHeaders['Authorization'];


$users=[];
$sqlResults="";

if($_SERVER['REQUEST_METHOD'] === 'GET') {
	if(!empty($_GET['userId'])) {
		$userId = $_GET['userId'];	
		
		//$sql = "SELECT userId, email, lastLogin FROM Users WHERE userId = (?) and accessToken = (?);";
		$sql = "SELECT userId, email, lastLogin FROM Users WHERE userId = (?);";
		$args = [];
		$args[] = $userId;
		// $args[] = $accessToken;
		$sqlResults = execute($sql, $args);
		
		if(empty($sqlResults)) {
			response(401,"Unautorized Access", NULL);
		} else {
			$userInfo = $sqlResults[0];
			response(200,"User Found", $userInfo);
		}
	} else {
		
		$sql = "SELECT userId, email FROM Users;";
		$sqlResults = execute($sql);
		// print_r($sqlResults);
		if (empty($sqlResults)) {
			response(200, "No Users Found", NULL);
		} else {
			foreach ($sqlResults as $sqlResult) {
				// $users[] = $sqlResult['userId'] . ", " . $sqlResult['email'];
				$users[] = $sqlResult;
			}
			
			response(200, "User(s) Found", $users);
		}
	}
}

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	
	$data = json_decode(file_get_contents('php://input'));
	$email = $data->{'email'};
	$password = $data->{'password'};
	$sql = "INSERT INTO Users (email, password) VALUES ((?), (?));";
	$args = [];
	$args[] = $email;
	$args[] = $password;
	$sqlResults = execute($sql, $args);
	$sql = "SELECT userId, email FROM Users WHERE email = (?);";
	$args = [];
	$args[] = $email;
	$sqlResults = execute($sql, $args);
	foreach ($sqlResults as $sqlResult) {
		$userInfo[] = $sqlResult;
	}
	response(200, "User Added", $userInfo);
	//response(400, "Failed to Add User", NULL);
}

if($_SERVER['REQUEST_METHOD'] === 'PUT') {
	$data = json_decode(file_get_contents('php://input'));
	$userId = $_GET['userId'];	
	$email = $data->{'email'};
	$password = $data->{'password'};
	if (!empty($userId)) {
		if (!empty($email)) {
			$sql = "UPDATE Users SET email = (?) WHERE userId =(?);";
			$args = [];
			$args[] = $email;
			$args[] = $userId;
			$sqlResults = execute($sql, $args);
			response(200, "User Email Updated", $userId);
		}
		if (!empty($password)) {
			$sql = "UPDATE Users SET password = (?) WHERE userId =(?);";
			$args = [];
			$args[] = $password;
			$args[] = $userId;
			$sqlResults = execute($sql, $args);
			response(200, "User Password Updated", $userId);
		}
	}
}

if($_SERVER['REQUEST_METHOD'] === 'DELETE') {
	if(!empty($_REQUEST['userId'])) {
		$userId = $_REQUEST['userId'];	
		$sql = "DELETE FROM Users WHERE userId = (?);";
		$args = [];
		$args[] = $userId;
		$sqlResults = execute($sql, $args);
		response(200,"User Deleted", $userId);
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