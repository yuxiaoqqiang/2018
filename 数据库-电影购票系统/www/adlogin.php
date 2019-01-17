  <?php
    include 'aduser.php';
    session_start();
    $userid = $_POST['adid'];
    $password = $_POST['password'];
	echo $userid;
	echo $password;
	
	//验证用户名和密码
	if($userid == null || $userid == "" || $password == null || $password == ""){
		echo "<script language='javascript' type='text/javascript'> alert('输入不能为空!');</script>";
		$url = "index.php";  
		echo "<script language='javascript' type='text/javascript'>";  
		echo "window.location.href='$url';";  
		echo "</script>"; 
		return;
	
	}
	
	
	
	
	$u = new aduser();
	$u = getaduserById($userid);
	
	
	
	if($u == null){
	  echo "<script language='javascript' type='text/javascript'> alert('没有该账户!');</script>";
		
	}else if($u->Password == $password){
		$_SESSION['aduser'] = serialize($u);
		echo "<script language='javascript' type='text/javascript'> alert('登陆成功!');</script>";
	}else{
		echo "<script language='javascript' type='text/javascript'> alert('密码错误!');</script>";
	}
	
    $url = "admin.php";  
    echo "<script language='javascript' type='text/javascript'>";  
    echo "window.location.href='$url';";  
    echo "</script>";  
?>
