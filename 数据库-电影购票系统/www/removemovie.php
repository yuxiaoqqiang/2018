<?php
session_start();

$moviename = $_GET['moviename'];
    $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
	$con->set_charset("utf8");
	$sql="delete from movie where Name = '".$moviename."';";
    $result=$con->query($sql);
	echo "<script language='javascript' type='text/javascript'> alert('删除成功！');</script>";
	$url = "admin.php";  
	echo "<script language='javascript' type='text/javascript'>";  
	echo "window.location.href='$url';";  
	echo "</script>"; 
	return;
	
	
	

?>