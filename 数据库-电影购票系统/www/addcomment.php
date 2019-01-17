<?php 
include 'User.php';  
session_start();
$comment = $_POST['comment'];

if($comment == null || $comment == ""){
	echo "<script language='javascript' type='text/javascript'> alert('请输入评论!');</script>";
	$url = "single.php";  
	echo "<script language='javascript' type='text/javascript'>";  
	echo "window.location.href='$url';";  
	echo "</script>"; 
	return;
	
	
}


if(isset($_SESSION['user'])){
$u = $_SESSION['user'];
$un = unserialize($u);
$name = $un->Usr_Username;
}
$movieid = $_SESSION['movieid'];


$sql= "select* from comments;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$con->set_charset("utf8");
$result=$con->query($sql);
$commentcount = $result->num_rows;


$commentcount = $commentcount + 1;

$sql= "select * from movie where Movie_No = ".$movieid.";" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$con->set_charset("utf8");
$result=$con->query($sql); 
$row = $result->fetch_assoc();
$moviename = $row['Name'];


$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$con->set_charset("utf8");
$sql = "SELECT UsrId From usr where Usr_Username = '".$name."'";
$result = $con->query($sql);
$row = $result->fetch_assoc();
$id = $row['UsrId'];
$sql="insert into comments (Comment_ID, Movie_Name, Comments, UsrId) values(".$commentcount. ",'".$moviename."', '".$comment."', '".$id."');";
$result=$con->query($sql);
echo $sql;
$sql= "select * from movie where Movie_No = ".$movieid.";" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$con->set_charset("utf8");
$result=$con->query($sql); 
$row = $result->fetch_assoc();
$moviecomments = $row['Comment_of_people'];
$moviecomments = $moviecomments + 1;




echo "<script language='javascript' type='text/javascript'> alert('评论成功!');</script>";
$url = "blog.php";  
echo "<script language='javascript' type='text/javascript'>";  
echo "window.location.href='$url';";  
echo "</script>"; 
return; 


?>