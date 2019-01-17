<?php

class User
{
	public $Usr_Username;
    public $Password;
	public $UsrId;
	public $UsrPhone;


    function saveUser() {
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
		$sql="insert into usr ( Usr_Username, Password, UsrId, UsrPhone) values(?,?,?,?)";
        $result=$con->prepare($sql);
		$result->bind_param('ssss',$this->Usr_Username,$this->Password, $this->UsrId,$this->UsrPhone);
        $result->execute();
        $result->close();
    }



	
	  function getUserById($UsrId) {
        $con =mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
		$sql="select * from usr where UsrId='".$UsrId."'";
        $result=$con->query($sql);
        if($result->num_rows>0) {
            $row = $result->fetch_assoc();
            $u = new User();
            $u->Password=$row['Password'];
            $u->UsrId=$row['UsrId'];
			$u->Usr_Username=$row['Usr_Username'];
			$u->UsrPhone=$row['UsrPhone'];
            return $u;
        } else {
            return null;
        }
    }

}

?>