
<!DOCTYPE html>
<html lang="en">
<head>
    <title>How to create Contact Us Form With Bootstrap 4</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="../css/contact.css"/>
   
</head>
<body>
   
<div class="container ">
    <div class="form ">
        <div class="contact-info text-center">
            <h3 class="title">Let's get in touch</h3>
            <p class="text"> Contact us with the following details. and fillup the form with the details. </p>
            <div class="info">
                <div class="social-information"> <i class="fa fa-map-marker"></i>
                    <p>NY,USA</p>
                </div>
                <div class="social-information"> <i class="fa fa-envelope-o"></i>
                    <p>contact@brawndobros.com</p>
                </div>
                <div class="social-information"> <i class="fa fa-mobile-phone"></i>
                    <p>+1 734 123 1234 </p>
                </div>
            </div>
            <div class="social-media">
                <p>Connect with us :</p>
                <div class="social-icons"> <a href="#"> <i class="fa fa-facebook-f"></i> </a> <a href="#"> <i class="fa fa-twitter"></i> </a> <a href="#"> <i class="fa fa-instagram"></i> </a> <a href="#"> <i class="fa fa-linkedin"></i> </a> </div>
            </div>
        </div>
        <div class="contact-info-form"> <span class="circle one"></span> <span class="circle two"></span>
            <form action="#" onclick="return false;" autocomplete="off">
                <h3 class="title">Contact us</h3>
                <div class="social-input-containers"> <input type="text" name="name" class="input" placeholder="Name" /> </div>
                <div class="social-input-containers"> <input type="email" name="email" class="input" placeholder="Email" /> </div>
                <div class="social-input-containers"> <input type="tel" name="phone" class="input" placeholder="Phone" /> </div>
                <div class="social-input-containers textarea"> <textarea name="message" class="input" placeholder="Message"></textarea> </div> <input type="submit" value="Send" class="btn" />
            </form>
        </div>
    </div>
</div>

<?php
 //include('includes/script.php');
 include('includes/footer.php'); ?>
