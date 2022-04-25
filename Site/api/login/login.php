<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

header("Content-Type:application/json");
require_once "../../classes/dbconn.php";



$sqlResults="";

if($_SERVER['REQUEST_METHOD'] === 'POST') {
	$data = json_decode(file_get_contents('php://input'));
	$email = $data->{'email'};
	$password = $data->{'password'};
	if($email) {
		if($password) {
			$sql = "SELECT userId FROM Users WHERE email = (?) and password = (?);";
			$args = [];
			$args[] = $email;
			$args[] = $password;
			$sqlResults = execute($sql, $args);
			if($sqlResults) {
				$userId = $sqlResults[0];
				$lastLogin = (string)date("YmdHis");
				$accessToken = miniGUID();
				$sql = "UPDATE Users SET lastLogin = (?), accessToken = (?) WHERE userId = (?);";
				$args = [];
				$args[] = $lastLogin;
				$args[] = $accessToken;
				$args[] = $userId['userId'];
				$sqlResults = execute($sql, $args);
				$msg = [];
				$msg['userId'] = $userId['userId'];
				$msg['accessToken'] = $accessToken;
				response(200, "Login Successful", $msg);
			} else { response(200, "Login Unsuccessful", null); }
			
		}
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

function miniGUID()
{
	if (function_exists('com_create_guid') === true)
	{
		return trim(com_create_guid(), '{}');
	}

	return sprintf('%04X%04X', mt_rand(0, 65535), mt_rand(0, 65535));
}