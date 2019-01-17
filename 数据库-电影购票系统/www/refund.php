<?php 
session_start();
include 'tickets.php';
include 'User.php';

$ticketid = $_GET['ticketid'];
if(isset($_SESSION['user'])){


$u = $_SESSION['user'];
$un = unserialize($u);
$usrid = $un->UsrId;;
$ticks = getTicketByDate_usrid($usrid);
$temp = "";
$t = "";
for($i = 0; $i < count($ticks); $i = $i + 1){
	$t = $ticks[$i];
	$temp = $t->ticketid;
	if($temp == $ticketid){
		break;
	}
	
}

$sql= "delete from purchase where Purchase_Ticket_ID = $temp;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);

$sql= "insert into refund (Refund_Ticket_ID,Refund_usr_id, Refund_DATE_TIME) values($temp, '".$usrid."',CURRENT_TIME);" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);

}

echo "<script language='javascript' type='text/javascript'> alert('退票成功!');</script>";
$url = "about.php";  
echo "<script language='javascript' type='text/javascript'>";  
echo "window.location.href='$url';";  
echo "</script>"; 




?>