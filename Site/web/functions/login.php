<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); 

require_once 'curl.php';

$url = "http://brawndotest.mattmoose.net/api/login/login.php";

class Login {
	public $email;
	public $password;
	public $url = "http://brawndotest.mattmoose.net/api/login/login.php";
	public $data = "{\"email\":\"put@put.put\",\"password\":\"puty\"}";
	public $results;
		
	private function setEmail() {
		$this->email = empty($_REQUEST["email"]) ? $email ="p" : $email = $_REQUEST["email"];
	}
	
	private function setPassword() {
		$this->password = empty($_REQUEST["password"]) ? $password ="h" : $password = $_REQUEST["password"];
	}
	
	private function genData() {
		$this->data = "{\"email\":\"" . $this->email . "\",\"password\":\"" . $this->password . "\"}";
	}
	
	public function Login() {
		if (!empty($_REQUEST["login"])) {
			$this->setEmail();
			$this->setPassword();
			$this->genData();
			$results = curl("POST", $this->url, $this->data);
		}
		//return curl("POST", $this->url, $this->data);
	}
	

}

?>