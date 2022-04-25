<?php
//* Database Connection Function
$db = null;

function getPDO($selectedDatabase) {
	global $db;
	if ($db != null) {
		return $db;
	}
	try {
		$db = new PDO('mysql:host=localhost;port=3306;dbname=' . $selectedDatabase,'root','password');
		$db->setAttribute(PDO::ATTR_EMULATE_PREPARES,false); 
		$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE,PDO::FETCH_ASSOC); 
		return $db;
	}
	catch (Exception $e2) {
		echo('DB Connection Error - ' . $e2->getMessage());
		exit();
	}
}

function execute($sql,$bindingValues=null,$selectedDatabase = 'BrawndoBros') {
// Uncomment the following when debugging your sql
//echo($sql . '<br>');    
//if ($bindingValues != null) {
//    var_dump($bindingValues);
//}
	$db = getPDO($selectedDatabase);
	try {
		$statement = $db->prepare($sql);
		if (!$statement) {
			echo('DB Prepare Error - ' . $sql);
			exit();
		}
		if ($statement===false) {
			echo('DB Prepare Error - ' . $sql);
			exit();
		}
		if ($bindingValues != null) {
			for ($counter=0; $counter < sizeof($bindingValues); $counter++) {
				$statement->bindParam($counter + 1, $bindingValues[$counter]);
			}
		}
		$statement->execute();
		$results = array();
		if (stripos($sql,'select') === 0) {
			$results = $statement->fetchAll();
		}
		$statement->closeCursor();
		return $results;
	}
	catch (Throwable $e2) {
		echo('DB Error - ' . $sql);
		echo('<br>' . $e2->getMessage());
		exit();
	}
}