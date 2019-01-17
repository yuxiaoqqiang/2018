<?php
	session_start();
	include 'user.php';	 
	$servername = "localhost";
	$username = "zxrtt";
	$password = "tongtong";
	$database = "movie";
		
	// 创建连接
	$conn = new mysqli($servername, $username, $password, $database);
	$conn->set_charset('utf8');
	// 检测连接
	if ($conn->connect_error) {
		die("连接失败: " . $conn->connect_error);
	}
	
	$DATE_PAY_PAGE = $_GET['date'];
	$TIME_PAY_PAGE = $_GET['timer'];
	$NAME_PAY_PAGE = $_GET['moviename'];
	$u = $_SESSION['user'];
	$un = unserialize($u);
	$URID_PAY_PAGE = $un->UsrId;
	
	$sql3 = "SELECT Price From Movie Where Name = '".$NAME_PAY_PAGE."'";
	$result = $conn->query($sql3);
	$row = $result->fetch_assoc();
	$Price = $row["Price"];

	$sql4 = "SELECT Arrange_Screen , Selled_Num From arrangement Where Arrange_Name = '".$NAME_PAY_PAGE."'  AND   Arrange_Time = '".$TIME_PAY_PAGE."'  AND  Arrange_Date = '".$DATE_PAY_PAGE."'";
	$result = $conn->query($sql4);
	$row = $result->fetch_assoc();
	$Screen = $row["Arrange_Screen"];
	$Seat = $row["Selled_Num"] + 1;
	
	$Movie_Time = $DATE_PAY_PAGE." ".$TIME_PAY_PAGE;
	
	$sql5 = "SELECT COUNT(*) FROM Ticket";
	$result = $conn->query($sql5);
	$row = $result->fetch_assoc();
	$TicketID = $row["COUNT(*)"] + 1;
	
	$sql6 = "SELECT Seat_Number FROM screen WHERE Screen_No = $Screen";
	$result = $conn->query($sql6);
	$row = $result->fetch_assoc();
	$SeatNum = $row["Seat_Number"];

	$sql7 = "update arrangement set Selled_Num = $Seat WHERE Arrange_Name = '".$NAME_PAY_PAGE."'  AND Arrange_Time = '".$TIME_PAY_PAGE."' AND Arrange_Date = '".$DATE_PAY_PAGE."'";
	$result = $conn->query($sql7);
	
	if($SeatNum<$Seat){
		echo "<script language='javascript' type='text/javascript'> alert('已无余票，购票失败!');</script>";
		$url = "trailers-now-showing.php"; 
		echo "<script language='javascript' type='text/javascript'>";  
		echo "window.location.href='$url';";  
		echo "</script>"; 
	}
	else{
		$sql8 = "insert into ticket (Ticket_ID,Movie_Name,Movie_Time,Price,Screen,Seat) VALUES ($TicketID,'".$NAME_PAY_PAGE."','".$Movie_Time."',$Price,$Screen,$Seat)";
		$result = $conn->query($sql8);
		echo "<script language='javascript' type='text/javascript'> alert(' successed !');</script>";
		$url = "about.php";  
		echo "<script language='javascript' type='text/javascript'>";  
		echo "window.location.href='$url';";  
		echo "</script>"; 
	}
	
	$sql = "insert into purchase (Purchase_Ticket_ID,Purchase_usr_id,Purchase_DATE_TIME) VALUES($TicketID,'".$URID_PAY_PAGE."',CURRENT_TIME)";
	$result = $conn->query($sql);
	
	?>