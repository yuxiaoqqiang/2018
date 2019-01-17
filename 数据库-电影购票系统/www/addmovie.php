<?php 

session_start();
$moviename = $_POST['moviename'];
$movietype = $_POST['movietype'];
$direct = $_POST['direct'];
$mainper =  $_POST['mainper'];
$short =$_POST['short'];
$long = $_POST['long'];





if($moviename == null || $moviename == "" || $movietype == null || $movietype == "" || $direct ==null || $direct == "" || $mainper == null || $mainper == "" || $short == null || $short == "" || $long == null || $long == ""){
	 echo "<script language='javascript' type='text/javascript'> alert('请检查输入!');</script>";
	 $url = "admin.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;
	 
		
}


$sql= "select* from movie;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$moviecount = $result->num_rows;
$moviecount = $moviecount + 1;

$sql= "select *  from movie where Name = '".$moviename."';" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);
		
		
		
if($result && $result->num_rows == 0) {
	echo $moviecount;
	$sql="insert into movie (Movie_No, Name, Movie_Type,Short_synopsis, Long_synopsis, Director, Main_performer, addDate) values(".$moviecount. ",'".$moviename."', '".$movietype."', '".$short."', '".$long."', '".$direct."', '".$mainper."', curdate());";
	$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
	$con->set_charset("utf8");
    $result=$con->query($sql);
	echo "<script language='javascript' type='text/javascript'> alert('添加成功 ');</script>";
	$url = "admin.php";  
	echo "<script language='javascript' type='text/javascript'>";  
	echo "window.location.href='$url';";  
	echo "</script>"; 
	return;	
}else{
	
	echo "<script language='javascript' type='text/javascript'> alert('该电影已存在!');</script>";
	$url = "admin.php";  
	echo "<script language='javascript' type='text/javascript'>";  
	echo "window.location.href='$url';";  
	echo "</script>"; 
	return;
	
}


?>\