 <?php
    include 'User.php';
    session_start();
    $userid = $_POST['email'];

    $password = $_POST['password'];
	//验证用户名和密码
	
	$u = new User();
	$u = $u->getUserById($userid);
	
	if($u == null){
	  echo "<script language='javascript' type='text/javascript'> alert('没有该账户!');</script>";
		
	}else if($u->Password == $password){
		$_SESSION['user'] = serialize($u);
		echo "<script language='javascript' type='text/javascript'> alert('登陆成功!');</script>";
	}else{
		echo "<script language='javascript' type='text/javascript'> alert('密码错误!');</script>";
		
	}
	
    $url = "index.php";  
    echo "<script language='javascript' type='text/javascript'>";  
    echo "window.location.href='$url';";  
    echo "</script>";  
?>
