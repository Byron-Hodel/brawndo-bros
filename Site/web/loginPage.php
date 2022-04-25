<?php
require_once './functions/login.php';
?>
<html>
	<head>
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
	</head>
	<body>
		<div class="mx-auto" style="width: 400px;"">
			<div class="mb-3">
			<h1>Brawndo Bros</h1>
			<form action="loginPage.php" method="post"">
			  <div class="mb-3">
				<label for="email" class="form-label">Email address</label>
				<input type="email" name="email" class="form-control" id="email">
			  </div>
			  <div class="mb-3">
				<label for="password" class="form-label">Password</label>
				<input type="password" name="password" class="form-control" id="password">
			  </div>
			  <button type="submit" name="login" class="btn btn-primary">Log In</button>
			</form>
		</div>
		<?php 
		print_r($login = new Login());
		?>
	</body>
</html>
