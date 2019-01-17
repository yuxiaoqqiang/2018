 <?php
 
     include 'User.php';
     session_start();
	 $username = $_POST['rname'];
	 $userId=$_POST['remail'];
	 $userPhone=$_POST['rphone'];
	 $password=$_POST['rpassword'];

	 
	 
	 $u = new User();
	 $u = $u->getUserById($userId);
	 
	 if($u == null){
		 $u = new User();
		 $u->Usr_Username = $username;
		 $u->Password = $password;
		 $u->UsrPhone= $userPhone;
		 $u->UsrId = $userId;
		 $u->saveUser();
		
		$_SESSION['user'] = serialize($u);
		

		 
	 }else{
		 
		 echo "<script language='javascript' type='text/javascript'> alert('邮箱已被注册!');</script>";
		 	 
	 }
	
	$url = "index.php";  
    echo "<script language='javascript' type='text/javascript'>";  
    echo "window.location.href='$url';";  
    echo "</script>"; 

 
 
 ?>