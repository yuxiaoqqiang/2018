  <?php

class aduser{
	public $Admin_No;
    public $Password;
	public $Admin_Username;
	
    function __construct() {
    }

}

	
	  function getaduserById($UsrId) {
        $sql="select * from administrator where Admin_Username='".$UsrId."'";
        $con =mysqli_connect("localhost","zxrtt", "tongtong", "movie");
        $result=$con->query($sql);
        if($result->num_rows>0) {
            $row = $result->fetch_assoc();
            $u = new aduser();
            $u->Password=$row['Password'];
            $u->Admin_No=$row['Admin_No'];
			$u->Admin_Username=$row['Admin_Username'];
            return $u;
        } else {
            return null;
        }
    }
	



?>