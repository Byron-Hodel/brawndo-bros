<?php
/*include('config/dbconn.php');

if(isset($_POST['register']))
{
 $username= mysqli_real_escape_string($con, $_POST['username']);
 $email=mysqli_real_escape_string($con, $_POST['email']);
 $password=mysqli_real_escape_string($con, $_POST['password']);
 //$username=$_POST['username'];
 $confirm_pass=mysqli_real_escape_string($con,$_POST['cpassword']);


if($password==$confirm_pass)
{
//check email
$checkemail="SELECT email FROM users WHERE email='$email'";
$checkemail_run= mysqli_query ($con, $checkemail); 
if(mysqli_num_rows($checkemail_run)> 0)
{
	$_SESSION['message']=" Already email exists";
	header("location: includes/registration.php");
	exit();
}
else{
	$user_query="INSERT INTO users(username, email, password) VALUES('$username', '$email', '$password')";
	$user_query_run=mysqli_query($con,$user_query);

	if($user_query_run)
	{
		$_SESSION['message']=" registered sucessfully";
	header("location: includes/login.php");
	exit();
}
	else{
		$_SESSION['message']=" Something went wrong";
	header("location: includes/registration.php");
	exit();
}
	}
}
}
}

else{
	$_SESSION['message']="Password & confirm password doesn't match";
	header("location: includes/registration.php");
	exit();
}
*/

    include('config/db_conn.php');
    // When form submitted, insert values into the database.
    if (isset($_REQUEST['username'])) {
        // removes backslashes
        $username = stripslashes($_REQUEST['username']);
        //escapes special characters in a string
        $username = mysqli_real_escape_string($con, $username);
        $email    = stripslashes($_REQUEST['email']);
        $email    = mysqli_real_escape_string($con, $email);
        $password = stripslashes($_REQUEST['password']);
        $password = mysqli_real_escape_string($con, $password);
        $create_datetime = date("Y-m-d H:i:s");
        $query    = "INSERT into `users` (username, password, email, create_datetime)
                     VALUES ('$username', '" . md5($password) . "', '$email', '$create_datetime')";
        $result   = mysqli_query($con, $query);
        if ($result) {
            echo "<div class='form'>
                  <h3>You are registered successfully.</h3><br/>
                  <p class='link'>Click here to <a href='login.php'>Login</a></p>
                  </div>";
        } else {
            echo "<div class='form'>
                  <h3>Required fields are missing.</h3><br/>
                  <p class='link'>Click here to <a href='registration.php'>registration</a> again.</p>
                  </div>";
        }
    } else {
		echo "<div class='form'>
		<h3>Something went worng.</h3><br/>
		<p class='link'>Click here to <a href='registration.php'>registration</a> again.</p>
		</div>";
	}
?>