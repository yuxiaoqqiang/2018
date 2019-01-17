<?php 
session_start();

$movieid = $_POST['movieid'];

if($movieid == null  ){
	 echo "<script language='javascript' type='text/javascript'> alert('请检查输入!');</script>";
	 $url = "index.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 
	 return;
	 
		
}


        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
		$sql= "select *  from movie where Movie_No = '".$movieid."';" ;
        $result=$con->query($sql);
	$u= 0;
 if($result->num_rows>0) {
            $row = $result->fetch_assoc();
			$u = $row['Collection_of_people'];
           
 }
  
 $u = $u + 1;
 

         $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
		 $sql= "update movie set Collection_of_people = ".$u." where Movie_No = '".$movieid."';" ;
        $result=$con->query($sql);
		

	 $url = "index.php";  
	 echo "<script language='javascript' type='text/javascript'>";  
	 echo "window.location.href='$url';";  
	 echo "</script>"; 

?>