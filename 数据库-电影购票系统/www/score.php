<?php
session_start();

$movieid = $_POST['movieid'];
$points = $_POST['points'];

echo $movieid;
if($movieid == null ){
	 echo "<script language='javascript' type='text/javascript'> alert('请检查输入!');</script>";
	 $url = "index.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	// echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;
		
}

$sql= "select *  from movie where Movie_No = '".$movieid."';" ;

        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);
	$u= 0;
	$r = 0;
 if($result->num_rows>0) {
            $row = $result->fetch_assoc();
			$u = $row['score'];
			$r = $row['Score_of_people'];
           
 }

 $all = $u * $r;
 $all = $all + $points;
 
 $u = round($all / ($r + 1), 1);
 $r = $r + 1;
 
  $sql= "update movie set Score_of_people = ".$r." ,score = ".$u." where Movie_No = ".$movieid.";" ;
  
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);
		


	 echo "<script language='javascript' type='text/javascript'> alert('成功!');</script>";
	 $url = "index.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;
	 
?>