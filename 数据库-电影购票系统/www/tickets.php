 <?php

class tickets
{
    public $moviename;
	public $movietime;
	public $price;
	public $screen;
	public $seat;
	public $buytime;
	public $ticketid;
	
	
}




    function getTicketByDate_usrid($usrid) {   //查询没有过期的票
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
		$sql=" select Ticket_ID, Movie_Name, Movie_Time, Price, Screen, Seat, Purchase_DATE_TIME from ticket, purchase where Purchase_usr_id = '".$usrid."' and Purchase_Ticket_ID = Ticket_ID and datediff(Movie_Time , now()) >=0" ;
        $result=$con->query($sql);
		$ts = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = new tickets();
				$t->ticketid = $row['Ticket_ID'];
				$t->moviename = $row['Movie_Name'];
				$t->movietime = $row['Movie_Time'];
				$t->price = $row['Price'];
				$t->screen = $row['Screen'];
				$t->seat = $row['Seat'];
				$t->buytime = $row['Purchase_DATE_TIME'];
				$ts[] = $t;
			}while($row);
            
			//echo $ts[1]->moviename;
            return $ts;
        } else {
            return null;
        }
        $result->close();
    }



	
	  function getAllTicketByusrid($usrid) {   //查询所有历史订单
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
		$sql=" select Ticket_ID, Movie_Name, Movie_Time, Price, Screen, Seat, Purchase_DATE_TIME from ticket, purchase where Purchase_Ticket_ID = Ticket_ID union select Ticket_ID, Movie_Name, Movie_Time, Price, Screen, Seat, Refund_DATE_TIME from ticket, refund where Refund_Ticket_ID = Ticket_ID;" ;
        $result=$con->query($sql);
		$ts = array();
		
		if($result && $result->num_rows>0) {
			do{
				
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = new tickets();
				$t->ticketid = $row['Ticket_ID'];
				$t->moviename = $row['Movie_Name'];
				$t->movietime = $row['Movie_Time'];
				$t->price = $row['Price'];
				$t->screen = $row['Screen'];
				$t->seat = $row['Seat'];
				$t->buytime = $row['Purchase_DATE_TIME'];
				$ts[] = $t;
			}while($row);
			
            return $ts;
        } else {
		
            return null;
        }
		
        $result->close();
    }
	
	function getRefundTicketByusrid($usrid) {   //查询已退的票
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
		$sql=" select Ticket_ID, Movie_Name, Movie_Time, Price, Screen, Seat, Refund_DATE_TIME from ticket, refund where Refund_Ticket_ID = Ticket_ID;" ;
        $result=$con->query($sql);
		$ts = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = new tickets();
				$t->ticketid = $row['Ticket_ID'];
				$t->moviename = $row['Movie_Name'];
				$t->movietime = $row['Movie_Time'];
				$t->price = $row['Price'];
				$t->screen = $row['Screen'];
				$t->seat = $row['Seat'];
				$t->buytime = $row['Refund_DATE_TIME'];
				$ts[] = $t;
			}while($row);
            return $ts;
        } else {
            return null;
        }
        $result->close();
    }



?>