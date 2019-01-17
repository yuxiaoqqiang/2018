<?php 

session_start();
$moviename = $_POST['moviename'];
$screenname = $_POST['screenname'];
$timeid = $_POST['timeid'];
$date =  $_POST['date'];

if($timeid == 1){
	$time = "09:00:00";
}else if($timeid == 2){
	$time = "11:30:00";
}else if($timeid == 3){
	$time = "15:00:00";
}else if($timeid == 4){
	$time = "19:30:00";
}else if($timeid == 1){
	$time = "22:00:00";
	
}





$pattern = "\d{4}-\d{1,2}-\d{1,2}"; //!preg_match($pattern,$date)

if($moviename == null || $moviename == "" || $screenname == null || $screenname == "" || $timeid ==null || $timeid == "" ){
	 echo "<script language='javascript' type='text/javascript'> alert('请检查输入!');</script>";
	 $url = "projects.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;
	
	
}

$sql= "select Arrange_Date, Arrange_Time, Arrange_Screen  from arrangement where Arrange_Date = '".$date."' and Arrange_Time = '".$time."' and Arrange_Screen=".$screenname.";" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);
		
if($result && $result->num_rows>0) {
     echo "<script language='javascript' type='text/javascript'> alert('该影厅的该场次已有一场电影!');</script>";
	 $url = "projects.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;


}


$sql= "select *  from movie where Name = '".$moviename."';" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);

if($result && $result->num_rows>0) {
	$sql="insert into arrangement (Arrange_Name, Arrange_Screen, Arrange_Time, Arrange_Date) values('".$moviename."', ".$screenname.", '".$time."', '".$date."');";
	$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
	$con->set_charset("utf8");
    $result=$con->query($sql);
	echo "<script language='javascript' type='text/javascript'> alert('添加成功 ');</script>";
	 $url = "projects.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;	
}else{
	
	echo "<script language='javascript' type='text/javascript'> alert('未检索到电影，请先添加该电影!');</script>";
	$url = "projects.php";  
	echo "<script language='javascript' type='text/javascript'>";  
	echo "window.location.href='$url';";  
	echo "</script>"; 
	return;
	
}


?>