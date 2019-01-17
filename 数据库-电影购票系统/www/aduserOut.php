<?php
session_start();
session_destroy();
echo "<script language='javascript' type='text/javascript'> alert('退出!');</script>";
$url = "index.php";  
echo "<script language='javascript' type='text/javascript'>";  
echo "window.location.href='$url';";  
echo "</script>"; 
return;


?>