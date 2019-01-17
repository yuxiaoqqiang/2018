<!DOCTYPE html>
<?php 
include 'User.php';
include 'tickets.php';
session_start();


if(isset($_SESSION['user'])){
	$u = unserialize($_SESSION['user']);
	$username = $u->Usr_Username;
	$userid = $u->UsrId;
	$userphone = $u->UsrPhone;
  
  $ticket1 = getAllTicketByusrid($u->UsrId);
  $ticket2 = getTicketByDate_usrid($u->UsrId);
  $ticket3 = getRefundTicketByusrid($u->UsrId);
  
  $le1 = count($ticket1);
  $le2 = count($ticket2);
  $le3 = count($ticket3);
	
 }
  



$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$con->set_charset('utf8');
$sql= "select* from movie order by Movie_No;" ;
$result=$con->query($sql);

$tq = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = array();
				$t['Name'] = $row['Name'];
				$t['Movie_No'] = $row['Movie_No'];
				$tq[] = $t;
			}while($row);

        }
		

function page2($tq){
	for($i = 0; $i < count($tq); $i = $i + 1){
		
		$temp1 = $tq[$i]['Name'];
		$temp2 = $tq[$i]['Movie_No'];
		
		echo <<< EOF2
		<option  value= $temp2 > $temp1</option>
EOF2;
		
    }
}





















?>
<html>
<head>
<title>Home</title>
<link href="css/bootstrap.css" rel='stylesheet' type='text/css' />
<!-- Custom Theme files -->
<link rel="stylesheet" href="css/menu.css" />
<link href="css/style.css" rel="stylesheet" type="text/css" media="all" />
<!-- Custom Theme files -->
<script src="js/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
<!-- Custom Theme files -->
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="keywords" content="My Show Responsive web template, Bootstrap Web Templates, Flat Web Templates, Andriod Compatible web template, 
Smartphone Compatible web template, free webdesigns for Nokia, Samsung, LG, SonyErricsson, Motorola web design" />
<script type="application/x-javascript"> addEventListener("load", function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>
<!--webfont-->
<link href='http://fonts.useso.com/css?family=Oxygen:400,700,300' rel='stylesheet' type='text/css'>
<link href='http://fonts.useso.com/css?family=Open+Sans:400,300,600,700,800' rel='stylesheet' type='text/css'>
	<!-- start menu -->
<link href="css/megamenu.css" rel="stylesheet" type="text/css" media="all" />
<script type="text/javascript" src="js/megamenu.js"></script>
<script>$(document).ready(function(){$(".megamenu").megamenu();});</script>
<script type="text/javascript" src="js/jquery.leanModal.min.js"></script>
<link rel="stylesheet" href="css/font-awesome.min.css" />
<script src="js/easyResponsiveTabs.js" type="text/javascript"></script>
		    <script type="text/javascript">
			    $(document).ready(function () {
			        $('#horizontalTab').easyResponsiveTabs({
			            type: 'default', //Types: default, vertical, accordion           
			            width: 'auto', //auto or any width like 600px
			            fit: true   // 100% fit in a container
			        });
			    });
</script>

<!---- start-smoth-scrolling---->
<script type="text/javascript" src="js/move-top.js"></script>
<script type="text/javascript" src="js/easing.js"></script>
<script type="text/javascript">
			jQuery(document).ready(function($) {
				$(".scroll").click(function(event){		
					event.preventDefault();
					$('html,body').animate({scrollTop:$(this.hash).offset().top},1200);
				});
			});
		</script>
<!---- start-smoth-scrolling---->

</head>
<body>
	<!-- header-section-starts -->
		<div class="header-top-strip">
			<div class="container">
				<div class="header-top-left">
					<p>当前已注册用户数量: <?php                    
        $sql=" select UsrId from usr;" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
        $result=$con->query($sql);
		$num = $result->num_rows;
		echo $num;?>
			</a> | <a class="play-icon popup-with-zoom-anim" href="#small-dialog" href="#"> 信息管理</a> </p>
				<div id="small-dialog" class="mfp-hide">
						<div class="select-city">
							<h3>管理人员登陆</h3>
							<div class="confirmation">
							<form action = "adlogin.php" method="post">
								<input name="adid" type="text" class="email" placeholder="账号" required="required" pattern="([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?" />
								<input name="password" type="text" class="email" placeholder="密码" required="required"  />
								<input type="submit" value="确定" >
							</form>
						</div>
							<div class="clearfix"></div>
						</div>
					</div>	
				</div>
				<div class="header-top-right">
				<div class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title">Modal title</h4>
      </div>
      <div class="modal-body">
        <p>One fine body&hellip;</p>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary">Save changes</button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->
	<!-- Button trigger modal  -->
	<a  <?php 
   if(isset($_SESSION['user']))
	   echo "href=\"aduserOut.php\"";
   else
		echo "href=\"#small-dialog1\"";
   ?> > <?php 
   if(isset($_SESSION['user']))
		echo "注销";
	else
		echo "忘记密码?";
   ?></a>
	<!---pop-up-box---->  
					<link href="css/popuo-box.css" rel="stylesheet" type="text/css" media="all"/>
					<script src="js/jquery.magnific-popup.js" type="text/javascript"></script>
					<!---//pop-up-box---->
                     <script>
						$(document).ready(function() {
						$('.popup-with-zoom-anim').magnificPopup({
							type: 'inline',
							fixedContentPos: false,
							fixedBgPos: true,
							overflowY: 'auto',
							closeBtnInside: true,
							preloader: false,
							midClick: true,
							removalDelay: 300,
							mainClass: 'my-mfp-zoom-in'
						});
																						
						});
				</script>
				<!-- Large modal -->
<button class="btn btn-primary" id="myloginbtn" data-toggle="modal" data-target=<?php 
   if(isset($_SESSION['user']))
		echo "\"\"";
	else
		echo "\"#myModal\"";
   ?>>
    登录</button>
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel"
    aria-hidden="true">
    <div class="modal-dialog modal-lg">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-hidden="true">
                    &times;</button>
                <h4 class="modal-title" id="myModalLabel">
                    登录到我的影院</h4>
            </div>
            <div class="modal-body">
                <div class="row">
                    <div class="col-md-8" style="border-right: 1px dotted #C2C2C2;padding-right: 30px;">
                        <!-- Nav tabs -->
                        <ul class="nav nav-tabs">
                            <li class="active"><a href="#Login" data-toggle="tab">登录</a></li>
                            <li><a href="#Registration" data-toggle="tab">注册</a></li>
                        </ul>
                        <!-- Tab panes -->
                        <div class="tab-content">
                            <div class="tab-pane active" id="Login">
                                <form role="form" class="form-horizontal" action="login.php" method="post">
                                <div class="form-group">
                                    <label for="email" class="col-sm-2 control-label">
                                        邮箱</label>
                                    <div class="col-sm-10">
                                        <input type="email" class="form-control" id="email1" placeholder="邮箱" name="email"/>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="exampleInputPassword1" class="col-sm-2 control-label">
                                        密码</label>
                                    <div class="col-sm-10">
                                        <input type="password" class="form-control" id="exampleInputPassword1" placeholder="密码" name="password" />
                                    </div>
                                </div>
                                <div class="row">
                                    <div class="col-sm-2">
                                    </div>
                                    <div class="col-sm-10">
                                        <button type="submit" class="btn btn-primary btn-sm">
                                            确定</button>
                                        <a href="javascript:;">忘记密码?</a>
                                    </div>
                                </div>
                                </form>
                            </div>
                            <div class="tab-pane" id="Registration">
                                <form role="form" class="form-horizontal" action="register.php" method="post">
                                <div class="form-group">
                                    <label for="email" class="col-sm-2 control-label">
                                        名字</label>
                                    <div class="col-sm-10">
                                        <div class="row">
                                            <div class="col-md-10">
                                                <input type="text" class="form-control" placeholder="名字" name="rname"/>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="email" class="col-sm-2 control-label">
                                        邮箱</label>
                                    <div class="col-sm-10">
                                        <input type="email" class="form-control" id="email" placeholder="邮箱" name="remail" />
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="mobile" class="col-sm-2 control-label">
                                        电话</label>
                                    <div class="col-sm-10">
                                        <input type="text" class="form-control" id="mobile" placeholder="电话" name="rphone"/>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label for="password" class="col-sm-2 control-label">
                                        密码</label>
                                    <div class="col-sm-10">
                                        <input type="password" class="form-control" id="password" placeholder="密码" name="rpassword"/>
                                    </div>
                                </div>
                                <div class="row">
                                    <div class="col-sm-2">
                                    </div>
                                    <div class="col-sm-10">
                                        <button type="submit" class="btn btn-primary btn-sm">
                                            确定</button>
                                        <button type="button" class="btn btn-default btn-sm">
                                            取消</button>
                                    </div>
                                </div>
                                </form>
                            </div>
                        </div>
                        <div id="OR" class="hidden-xs">
                            OR</div>
                    </div>
                    <div class="col-md-4">
                        <div class="row text-center sign-with">
                            <div class="col-md-12">
                                <h3 class="other-nw">
                                    其它方式</h3>
                            </div>
                            <div class="col-md-12">
                                <div class="btn-group btn-group-justified">
                                    <a href="#" class="btn btn-primary">微信</a> <a href="#" class="btn btn-danger">
                                        微博</a>
                                </div>
                            </div>
                        </div>
                    </div>  
                </div>
            </div>
        </div>
    </div>
</div>
<script>
   var log= <?php 
   if(isset($_SESSION['user']))
		echo "1";
	else
		echo "0";
   ?>;
   
 if(log == 0){
 $('#myModal').modal('show');
 
 }
 if(log == 1){
	 document.getElementById("myloginbtn").innerHTML= "<?php $u = $_SESSION['user'];
	   $un = unserialize($u);
	   $name = $un->Usr_Username;
	   echo $name;
	 ?>";
	
	 
 }
	 
</script>

</div>
				<div class="clearfix"></div>
			</div>
		</div>
		<div class="container">
		  <div class="main-content">
			<div class="header">
				<div class="logo">
					<a href="index.php"><h1>影院售票管理平台</h1></a>
				</div>
				<div class="search">
					<div class="search2">
					  <form>
						<i class="fa fa-search"></i>
						 <input type="text" value="Search for a movie, play, event, sport or more" onfocus="this.value = '';" onblur="if (this.value == '') {this.value = 'Search for a movie, play, event, sport or more';}"/>
					  </form>
					</div>
				</div>
				<div class="clearfix"></div>
			</div>
	<div class="bootstrap_container">
            <nav class="navbar navbar-default w3_megamenu" role="navigation">
                <div class="navbar-header">
          			<button type="button" data-toggle="collapse" data-target="#defaultmenu" class="navbar-toggle"><span class="icon-bar"></span><span class="icon-bar"></span><span class="icon-bar"></span></button><a href="index.php" class="navbar-brand"><i class="fa fa-home"></i></a>
				</div><!-- end navbar-header -->
        
            <div id="defaultmenu" class="navbar-collapse collapse">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="index.php">主页</a></li>	
                    <!-- Mega Menu -->
					<li class="dropdown w3_megamenu-fw"><a href="cinemas.php"  class="dropdown-toggle">电影</b></a>	</li>
                        
					<li class="dropdown w3_megamenu-fw"><a href="trailers-now-showing.php"  class="dropdown-toggle">购票</b></a></li>
					<li class="dropdown w3_megamenu-fw"><a href="blog.php" class="dropdown-toggle">评论</b></a></li>
                </ul><!-- end nav navbar-nav -->
                
				<ul class="nav navbar-nav navbar-right">
					<li class="dropdown"><a href="#" data-toggle="dropdown" class="dropdown-toggle">联系我们<b class="caret"></b></a>
                        <ul class="dropdown-menu">
                            <li>
                                <form id="contact1" action="#" name="contactform" method="post">
                                    <div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">
                                        <input type="text" name="name" id="name1" class="form-control" placeholder="姓名"> 
                                        <input type="text" name="email" id="email1" class="form-control" placeholder="邮箱"> 
                                    </div>
                                    <div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">
                                        <input type="text" name="phone" id="phone1" class="form-control" placeholder="电话">
                                    </div>                 
                                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                                        <textarea class="form-control" name="comments" id="comments1" rows="6" placeholder="写下您的意见 ..."></textarea>
                                    </div>   
                                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                                        <div class="pull-right">
                                            <input type="submit" value="SEND" id="submit1" class="btn btn-primary small">
                                        </div>  
                                    </div>
									<div class="clearfix"></div>  
                                </form>
                            </li>
                        </ul>
					</li>
				</ul><!-- end nav navbar-nav navbar-right -->
			</div><!-- end #navbar-collapse-1 -->
            
			</nav><!-- end navbar navbar-default w3_megamenu -->
		</div><!-- end container -->
    

<!-- AddThis Smart Layers END -->


	<div class="main-banner">
		 <div class="banner col-md-8">
			<section class="slider">
				<div class="flexslider">
						<ul class="slides">
						<li>
							<img src="images/77.jpg" class="img-responsive" alt="" />
						</li>
						<li>
							<img src="images/88.jpg" class="img-responsive" alt="" />
						</li>
						<li>
							<img src="images/99.jpg" class="img-responsive" alt="" />
						</li>
						<li>
							<img src="images/44.jpg" class="img-responsive" alt="" />
						</li>
				  </ul>
				</div>
					</section>
				 <!-- FlexSlider -->
				 <script defer src="js/jquery.flexslider.js"></script>
				 <link rel="stylesheet" href="css/flexslider.css" type="text/css" media="screen" />
					<script type="text/javascript">
				$(function(){
				 SyntaxHighlighter.all();
				});
				$(window).load(function(){
				  $('.flexslider').flexslider({
					animation: "slide",
					start: function(slider){
					  $('body').removeClass('loading');
					}
				 });
				});
			 </script>
         </div>
		 <div class="col-md-4 banner-right">
			<h4>电影信息/我的信息</h4>
			<div class="grid_3 grid_5">
				   <div class="bs-example bs-example-tabs" role="tabpanel" data-example-id="togglable-tabs">
			<ul id="myTab" class="nav nav-tabs" role="tablist">
			  <li role="presentation" class="active"><a href="#home" id="home-tab" role="tab" data-toggle="tab" aria-controls="home" aria-expanded="true">评分</a></li>
			  <li role="presentation"><a href="#profile" role="tab" id="profile-tab" data-toggle="tab" aria-controls="profile" aria-expanded="false">收藏</a></li>
			  <li role="presentation"><a href="#profile2" role="tab" id="profile-tab" data-toggle="tab" aria-controls="profile" aria-expanded="false">我的信息</a></li>
			</ul>
			<div id="myTabContent" class="tab-content">
			  <div role="tabpanel" class="tab-pane fade in active" id="home" aria-labelledby="home-tab">				  
					<form action="score.php" method="post">
					<select class="list_of_movies" name="movieid"> <?php page2($tq); ?></select>
					<select class="list_of_movies" name="points"><option style="padding-left: 10px;" value=1>1分</option><option style="padding-left: 10px;" value=2>2分</option><option style="padding-left: 10px;" value=3>3分</option><option style="padding-left: 10px;" value=4>4分</option><option style="padding-left: 10px;" value=5>5分</option></select>
					<h5 class="pre"><i class="fa fa-heart"></i>Preferred<h5>
					<input class="pre" type="submit" value="评分" />
					</form>
			  </div>
			  <div role="tabpanel" class="tab-pane fade" id="profile" aria-labelledby="profile-tab">
					<form action="collect.php" method="post">
					<select class="list_of_movies" name="movieid"> <?php page2($tq);?></select>
					<h5 class="pre"><i class="fa fa-heart"></i>Preferred<h5>
					<input class="pre" type="submit" value="收藏" />
					</form>
				  
			  </div>
			  <div role="tabpanel" class="tab-pane fade" id="profile2" aria-labelledby="profile-tab">
			       <p>名字：<?php if(isset($_SESSION['user'])) echo $username; ?></p>
				   <p>账号：<?php if(isset($_SESSION['user'])) echo $userid; ?></p>
				   <p>电话：<?php if(isset($_SESSION['user'])) echo $userphone; ?></p>
				   <p>还未观看的：<?php if(isset($_SESSION['user'])) echo $le2;?></p>
				   <p>所有订单：<?php if(isset($_SESSION['user'])) echo $le1; ?></p>
				   <p>已退订单：<?php if(isset($_SESSION['user'])) echo $le3;?></p>
				   <p><?php if(isset($_SESSION['user'])) echo <<<EF
				   <a href="about.php"> 详细</a>
EF;
				   ?></p>			  
				  
			  </div>
			</div>
		   </div>
		  </div>
		 </div>
		 <div class="clearfix"></div>
	</div>
				<div class="review-slider">
			 <ul id="flexiselDemo1">
			 
			 <?php
$NAME1 = ""; $NAME2 = ""; $NAME3 = ""; $NAME4 = ""; $NAME5 = "";
$Director1 = "" ;$Director2 = "" ;$Director3 = "" ;$Director4 = "" ;$Director5 = "" ;
$Main_perf1 = "";$Main_perf2 = "";$Main_perf3= "";$Main_perf4 = "";$Main_perf5 = "";
$img1 = ""; $img2 = ""; $img3 = ""; $img4 = ""; $img5 = "";

function get(){
	$servername = "localhost";
	$username = "zxrtt";
	$password = "tongtong";
	$database = "movie";

	// 创建连接
	$conn = new mysqli($servername, $username, $password, $database);
	// 检测连接
	if ($conn->connect_error) {
		die("连接失败: " . $conn->connect_error);
	}
	$conn->set_charset("utf8");
	
	$sql1 = "SELECT Name FROM Movie";
	$result1 = $conn->query($sql1);
	$sql2 = "SELECT Director FROM Movie";
	$result2 = $conn->query($sql2);
	$sql3 = "SELECT Main_performer FROM Movie";
	$result3 = $conn->query($sql3);
	$sql4 = "SELECT Movie_No FROM Movie";
	$result4 = $conn->query($sql4);
	
	if ($result1->num_rows > 0) {
			$row = $result1->fetch_assoc();
			$GLOBALS['NAME1'] =  $row["Name"];
			$row = $result1->fetch_assoc();
			$GLOBALS['NAME2'] =  $row["Name"];
			$row = $result1->fetch_assoc();
			$GLOBALS['NAME3'] =  $row["Name"];
			$row = $result1->fetch_assoc();
			$GLOBALS['NAME4'] =  $row["Name"];
			$row = $result1->fetch_assoc();
			$GLOBALS['NAME5'] =  $row["Name"];			
	} else {
		echo "当前数据库内没有电影";
	}
	
		if ($result2->num_rows > 0) {
			$row = $result2->fetch_assoc();
			$GLOBALS['Director1'] =  $row["Director"];
			$row = $result2->fetch_assoc();
			$GLOBALS['Director2'] =  $row["Director"];
			$row = $result2->fetch_assoc();
			$GLOBALS['Director3'] =  $row["Director"];
			$row = $result2->fetch_assoc();
			$GLOBALS['Director4'] =  $row["Director"];
			$row = $result2->fetch_assoc();
			$GLOBALS['Director5'] =  $row["Director"];			
	} else {
		echo "当前数据库内没有电影";
	}
	
		if ($result3->num_rows > 0) {
			$row = $result3->fetch_assoc();
			$GLOBALS['Main_perf1'] =  $row["Main_performer"];
			$row = $result3->fetch_assoc();
			$GLOBALS['Main_perf2'] =  $row["Main_performer"];
			$row = $result3->fetch_assoc();
			$GLOBALS['Main_perf3'] =  $row["Main_performer"];
			$row = $result3->fetch_assoc();
			$GLOBALS['Main_perf4'] =  $row["Main_performer"];
			$row = $result3->fetch_assoc();
			$GLOBALS['Main_perf5'] =  $row["Main_performer"];			
	} else {
		echo "当前数据库内没有电影";
	}
	
		if ($result4->num_rows > 0) {
			$row = $result4->fetch_assoc();
			$GLOBALS['img1'] =  $row["Movie_No"];
			$row = $result4->fetch_assoc();
			$GLOBALS['img2'] =  $row["Movie_No"];
			$row = $result4->fetch_assoc();
			$GLOBALS['img3'] =  $row["Movie_No"];
			$row = $result4->fetch_assoc();
			$GLOBALS['img4'] =  $row["Movie_No"];
			$row = $result4->fetch_assoc();
			$GLOBALS['img5'] =  $row["Movie_No"];			
	} else {
		echo "当前数据库内没有电影";
	}
	
	
	$conn->close();

}

function outputHtml(){
	get();
$a0 = $GLOBALS['NAME1'];
$a1 = $GLOBALS['Director1'];
$a2 = $GLOBALS['Main_perf1'];
$a3 = $GLOBALS['NAME2'];
$a4 = $GLOBALS['Director2'];
$a5 = $GLOBALS['Main_perf2'];
$a6 = $GLOBALS['NAME3'];
$a7 = $GLOBALS['Director3'];
$a8 = $GLOBALS['Main_perf3'];
$a9 = $GLOBALS['NAME4'];
$a10 = $GLOBALS['Director4'];
$a11 = $GLOBALS['Main_perf4'];
$a12 = $GLOBALS['NAME5'];
$a13 = $GLOBALS['Director5'];
$a14 = $GLOBALS['Main_perf5'];
$a15 = $GLOBALS['img1'];
$a16 = $GLOBALS['img2'];
$a17 = $GLOBALS['img3'];
$a18 = $GLOBALS['img4'];
$a19 = $GLOBALS['img5'];

$output =<<<EOT
	<li>
	<a href="single.php?new=$a0"><img src="images/$a15.jpg" alt=""/></a>
	<div class="slide-title"><h4>$a0 </div>
		<div class="date-city">
			<h5>导演：$a1</h5>
			<h6>主演：$a2</h6>
			<div class="buy-tickets">
				<a href="single.php?new=$a0 ">点击查看详情</a>
			</div>
		</div>
</li>
	<li>
	<a href="single.php?new=$a3"><img src="images/$a16.jpg" alt=""/></a>
	<div class="slide-title"><h4>$a3 </div>
		<div class="date-city">
			<h5>导演：$a4</h5>
			<h6>主演：$a5</h6>
			<div class="buy-tickets">
				<a href="single.php?new=$a3 ">点击查看详情</a>
			</div>
		</div>
</li>
	<li>
	<a href="single.php?new=$a6"><img src="images/$a17.jpg" alt=""/></a>
	<div class="slide-title"><h4>$a6 </div>
		<div class="date-city">
			<h5>导演：$a7</h5>
			<h6>主演：$a8</h6>
			<div class="buy-tickets">
				<a href="single.php?new=$a6 ">点击查看详情</a>
			</div>
		</div>
</li>
	<li>
	<a href="single.php?new=$a9"><img src="images/$a18.jpg" alt=""/></a>
	<div class="slide-title"><h4>$a9 </div>
		<div class="date-city">
			<h5>导演：$a10</h5>
			<h6>主演：$a11</h6>
			<div class="buy-tickets">
				<a href="single.php?new=$a9 ">点击查看详情</a>
			</div>
		</div>
</li>
	<li>
	<a href="single.php?new=$a12"><img src="images/$a19.jpg" alt=""/></a>
	<div class="slide-title"><h4>$a12	</div>
		<div class="date-city">
			<h5>导演：$a13</h5>
			<h6>主演：$a14</h6>
			<div class="buy-tickets">
				<a href="single.php?new=$a12 ">点击查看详情</a>
			</div>
		</div>
</li>
EOT;

echo $output;
}

outputHtml();

?>	 
		</ul>
			<script type="text/javascript">
		$(window).load(function() {
			
		  $("#flexiselDemo1").flexisel({
				visibleItems: 5,
				animationSpeed: 1000,
				autoPlay: true,
				autoPlaySpeed: 3000,    		
				pauseOnHover: false,
				enableResponsiveBreakpoints: true,
				responsiveBreakpoints: { 
					portrait: { 
						changePoint:480,
						visibleItems: 2
					}, 
					landscape: { 
						changePoint:640,
						visibleItems: 3
					},
					tablet: { 
						changePoint:800,
						visibleItems: 4
					}
				}
			});
			});
		</script>
		<script type="text/javascript" src="js/jquery.flexisel.js"></script>	
		</div>
		<div class="footer-top-grid">
		<div class="list-of-movies col-md-8">
			<div class="tabs">
				<div class="sap_tabs">	
						 <div id="horizontalTab" style="display: block; width: 100%; margin: 0px;">
						  <ul class="resp-tabs-list">
						  	  <li class="resp-tab-item" aria-controls="tab_item-2" role="tab"><span>今日热映</span></li>
							  <li class="resp-tab-item" aria-controls="tab_item-1" role="tab"><span>历史播映</span></li>
							  <li class="resp-tab-item" aria-controls="tab_item-0" role="tab"><span>即将上映</span></li>
							  <div class="clearfix"></div>
						  </ul>				  	 
							<div class="resp-tabs-container">
							    <div class="tab-1 resp-tab-content" aria-labelledby="tab_item-0">
									<ul class="tab_img">
									 
									 <?php
$img1 = ""; $img2 = ""; $img3 = ""; $img4 = ""; $img5 = ""; $img6 = ""; 
$img7 = ""; $img8 = ""; $img9 = ""; 

$name4 = ""; $name5 = ""; $name6 = "";

$wanna_see1 = ""; $wanna_see2 = ""; $wanna_see3 = ""; $wanna_see4 = ""; 
$wanna_see5 = ""; $wanna_see6 = ""; $wanna_see7 = ""; $wanna_see8 = ""; 
$wanna_see9 = ""; 

$all_people1 = "";$all_people2 = "";$all_people3 = "";$all_people4 = "";
$all_people5 = "";$all_people6 = "";$all_people7 = "";$all_people8 = "";
$all_people9 = "";

function getwannasee(){
	$servername = "localhost";
	$username = "zxrtt";
	$password = "tongtong";
	$database = "movie";
	


	// 创建连接
	$conn = new mysqli($servername, $username, $password, $database);
	$conn->set_charset("utf-8");
	// 检测连接
	if ($conn->connect_error) {
		die("连接失败: " . $conn->connect_error);
	}

	$sql = "SELECT distinct a.Movie_No,a.Collection_of_people,a.Score_of_people FROM Movie a ,Arrangement b WHERE a.Name = b.Arrange_Name AND datediff(b.Arrange_Date,curdate()) = 0";
	$result = $conn->query($sql);
	
	if ($result->num_rows > 0) {
		$row = $result->fetch_assoc();
		$GLOBALS['img1'] =  $row["Movie_No"];
		$GLOBALS['wanna_see1'] = $row["Score_of_people"];
		$GLOBALS['all_people1'] = $row["Collection_of_people"];
		$row = $result->fetch_assoc();
		$GLOBALS['img2'] =  $row["Movie_No"];
		$GLOBALS['wanna_see2'] = $row["Score_of_people"];
		$GLOBALS['all_people2'] = $row["Collection_of_people"]	;	
		$row = $result->fetch_assoc();
		$GLOBALS['img3'] =  $row["Movie_No"];
		$GLOBALS['wanna_see3'] = $row["Score_of_people"];
		$GLOBALS['all_people3'] = $row["Collection_of_people"]	;	
	}
	
	$sql = "SELECT distinct b.Arrange_Name,a.Movie_No,a.Collection_of_people,a.Score_of_people FROM Movie a ,Arrangement b WHERE a.Name = b.Arrange_Name AND datediff(b.Arrange_Date,curdate()) < 0";
	$result = $conn->query($sql);
	
	if ($result->num_rows > 0) {
		$row = $result->fetch_assoc();
		$GLOBALS['img4'] =  $row["Movie_No"];
		$GLOBALS['wanna_see4'] = $row["Score_of_people"];
		$GLOBALS['all_people4'] = $row["Collection_of_people"];
		$row = $result->fetch_assoc();
		$GLOBALS['img5'] =  $row["Movie_No"];
		$GLOBALS['wanna_see5'] = $row["Score_of_people"];
		$GLOBALS['all_people5'] = $row["Collection_of_people"];
		$row = $result->fetch_assoc();
		$GLOBALS['img6'] =  $row["Movie_No"];
		$GLOBALS['wanna_see6'] = $row["Score_of_people"];
		$GLOBALS['all_people6'] = $row["Collection_of_people"];
	}

	
	$sql = "SELECT distinct a.Movie_No,a.Collection_of_people,a.Score_of_people FROM Movie a ,Arrangement b WHERE a.Name = b.Arrange_Name AND datediff(b.Arrange_Date,curdate()) > 0";
	$result = $conn->query($sql);
	if ($result->num_rows > 0) {
		$row = $result->fetch_assoc();
		$GLOBALS['img7'] =  $row["Movie_No"];
		$GLOBALS['wanna_see7'] = $row["Score_of_people"];
		$GLOBALS['all_people7'] = $row["Collection_of_people"];
		$row = $result->fetch_assoc();
		$GLOBALS['img8'] =  $row["Movie_No"];
		$GLOBALS['wanna_see8'] = $row["Score_of_people"];
		$GLOBALS['all_people8'] = $row["Collection_of_people"];
		$row = $result->fetch_assoc();
		$GLOBALS['img9'] =  $row["Movie_No"];
		$GLOBALS['wanna_see9'] = $row["Score_of_people"];
		$GLOBALS['all_people9'] = $row["Collection_of_people"];
	}

}

function outputWannnaSee(){
	
	getwannasee();
	
	$a1 = $GLOBALS['img1'];
	$a2 = $GLOBALS['img2'];
	$a3 = $GLOBALS['img3'];
	$a4 = $GLOBALS['img4'];
	$a5 = $GLOBALS['img5'];
	$a6 = $GLOBALS['img6'];
	$a7 = $GLOBALS['img7'];
	$a8 = $GLOBALS['img8'];
	$a9 = $GLOBALS['img9'];

	$b1 = $GLOBALS['wanna_see1'];
	$b2 = $GLOBALS['wanna_see2'];
	$b3 = $GLOBALS['wanna_see3'];
	$b4 = $GLOBALS['wanna_see4'];
	$b5 = $GLOBALS['wanna_see5'];
	$b6 = $GLOBALS['wanna_see6'];
	$b7 = $GLOBALS['wanna_see7'];
	$b8 = $GLOBALS['wanna_see8'];
	$b9 = $GLOBALS['wanna_see9'];
	
	$c1 = $GLOBALS['all_people1'];
	$c2 = $GLOBALS['all_people2'];
	$c3 = $GLOBALS['all_people3'];
	$c4 = $GLOBALS['all_people4'];
	$c5 = $GLOBALS['all_people5'];
	$c6 = $GLOBALS['all_people6'];
	$c7 = $GLOBALS['all_people7'];
	$c8 = $GLOBALS['all_people8'];
	$c9 = $GLOBALS['all_people9'];
	
	$d1 = 0;
	$d2 = 0;
	$d3 = 0;
	$d4 = 0;
	$d5 = 0;
	$d6 = 0;
	$d7 = 0;
	$d8 = 0;
	$d9 = 0;
							
	if($c1 != 0)
		$d1 = round($b1/$c1*100);
	if($c2 != 0)
		$d2 = round($b2/$c2*100);
	if($c3 != 0)
		$d3 = round($b3/$c3*100);
	if($c4 != 0)
		$d4 = round($b4/$c4*100);
	if($c5 != 0)
		$d5 = round($b5/$c5*100);
	if($c6 != 0)
		$d6 = round($b6/$c6*100);
	if($c7 != 0)
		$d7 = round($b7/$c7*100);
	if($c8 != 0)
		$d8 = round($b8/$c8*100);
	if($c9 != 0)
		$d9 = round($b9/$c9*100);

	$output =<<<EOT

									<li>
										<div class="view view-first">
					   		  			  <a href="single.php?new=$a1"> <img src="images/$a1.jpg" class="img-responsive" alt=""/></a>
										   <div class="info1"> </div>
											 <div class="mask">
						                     </div>
								              <div class="tab_desc">
													<a href="movie-select-show.php?new=$a1">点击购票</a>
													<div class="percentage-w-t-s">
														<h5>$d1</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
									  <li>
										<div class="view view-first">
					   		  			   <a href="single.php?new=$a2"><img src="images/$a2.jpg" class="img-responsive" alt=""/></a>
										   <div class="info1"> </div>
											 <div class="mask">
						                     </div>
								              <div class="tab_desc">
													<a href="movie-select-show.php?new=$a2">点击购票</a>
													<div class="percentage-w-t-s">
														<h5>$d2</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
									  <li>
										<div class="view view-first">
					   		  			   <a href="single.php?new=$a3"><img src="images/$a3.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php?new=$a3">点击购票</a>
													<div class="percentage-w-t-s">
														<h5>$d3</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<div class="clearfix"></div>
									</ul>
							     </div>	
							     <div class="tab-1 resp-tab-content" aria-labelledby="tab_item-1">
									<ul class="tab_img">
									  <li>
										<div class="view view-first">
					   		  			   <a href="single.php?new=$a4"><img src="images/$a4.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="single.php?new=$a4">查看详情</a>
													<div class="percentage-w-t-s">
														<h5>$d4</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
									  <li>
										<div class="view view-first">
					   		  			  <a href="single.php?new=$a5"> <img src="images/$a5.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="single.php?new=$a5">查看详情</a>
													<div class="percentage-w-t-s">
														<h5>$d5</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<li class="last">
										  <div class="view view-first">
					   		  			   <a href="single.php?new=$a6"><img src="images/$a6.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								               <div class="tab_desc">
													<a href="single.php?new=$a6">查看详情</a>
													<div class="percentage-w-t-s">
														<h5>$d6</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<div class="clearfix"></div>
									</ul>
							     </div>	
							     <div class="tab-1 resp-tab-content" aria-labelledby="tab_item-2">
									<ul class="tab_img">
										<li>
										  <div class="view view-first">
					   		  			  <a href="single.php?new=$a7"> <img src="images/$a7.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php?new=$a7">点击预订</a>
													<div class="percentage-w-t-s">
														<h5>$d7</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<li>
										  <div class="view view-first">
					   		  			  <a href="single.php?new=$a8"> <img src="images/$a8.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php?new=$a8">点击预订</a>
													<div class="percentage-w-t-s">
														<h5>$d8</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<li class="last">
										  <div class="view view-first">
					   		  			   <a href="single.php?new=$a9"><img src="images/$a9.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php?new=$a9">点击预订</a>
													<div class="percentage-w-t-s">
														<h5>$d9</h5>
														<p>% <br> Want to see</p>
														<div class="clearfix"></div>
													</div>
											  </div>
										  </div>
										</li>
										<div class="clearfix"></div>
									</ul>
							     </div>	
EOT;

echo $output;
}

outputWannnaSee();

?>		 
							     <div class="tab-1 resp-tab-content" aria-labelledby="tab_item-3">
									<ul class="tab_img">
									  <li>
										<div class="view view-first">
					   		  			  <a href="movie-select-show.php"> <img src="images/pic-6.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php">Book Now</a>
											  </div>
										  </div>
										</li>
										<li>
										  <div class="view view-first">
					   		  			  <a href="movie-select-show.php"> <img src="images/pic-1.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php">Book Now</a>
											  </div>
										  </div>
										</li>
										<li>
										  <div class="view view-first">
					   		  			  <a href="movie-select-show.php"> <img src="images/pic-9.jpg" class="img-responsive" alt=""/></a>
											 <div class="mask">
						                        <div class="info1"> </div>
								              </div>
								                <div class="tab_desc">
													<a href="movie-select-show.php">Book Now</a>
											  </div>
										  </div>
										</li>
										<div class="clearfix"></div>
									</ul>
						    	</div>		        					 	        					 
			     		    </div>	
                        </div>
					</div>
				</div>	
				<div class="clearfix"></div>
				<div class="featured">
					<h4>未来上映</h4>
					<ul>
						
						<?php

$NAME = "";		$Director = "";		$Main_perf = "";	$img = "" ;

$servername = "localhost";
	$username = "zxrtt";
	$password = "tongtong";
	$database = "movie";

	// 创建连接
	$conn = new mysqli($servername, $username, $password, $database);
	// 检测连接
	if ($conn->connect_error) {
		die("连接失败: " . $conn->connect_error);
	}
	$conn->set_charset("utf8");
	
	$sql = "SELECT a.Name,b.Arrange_Date,b.Arrange_Screen,a.Movie_No FROM Movie a ,Arrangement b WHERE a.Name = b.Arrange_Name AND datediff(b.Arrange_Date,curdate()) >= 0 order by b.Arrange_Date";
	$result = $conn->query($sql);
	
function getMirai(){
	
		$row = $GLOBALS['result']->fetch_assoc();
		$GLOBALS['NAME'] =  $row["Name"];
		$GLOBALS['Director'] =  $row["Arrange_Date"];
		$GLOBALS['Main_perf'] =  $row["Arrange_Screen"];
		$GLOBALS['img'] =  $row["Movie_No"];
	
}

function outputMirai()
{
	$a = $GLOBALS['NAME'] ;
	$b = $GLOBALS['Director'];
	$c = $GLOBALS['Main_perf'];
	$d = $GLOBALS['img'];
	
	$output =<<<EOT
	<li>
		<div class="f-movie">
			<div class="f-movie-img">
				<a href="single.php?new=$d"><img src="images/$d.jpg" alt="" /></a>
			</div>
			<div class="f-movie-name">
				<a href="single.php?new=$a">$a </a>
				<p>日期：$b</p>
				<p>影厅：$c </p>
			</div>
			<div class="f-buy-tickets">
					<a href="single.php?new=$d">查看详情</a>
			</div>
		</div>
	</li>

EOT;

echo $output;

}

do{
	getMirai();
	if($GLOBALS['NAME']=="")
		break;
	outputMirai();
}while(1)

?>	
						<div class="clearfix"></div>
					</ul>
				</div>
			</div>
			<div class="right-side-bar">
				<div class="top-movies-in-india">
					<h4>好评排行</h4> 
				<?php
$NAME1 = ""; $NAME2 = ""; $NAME3 = ""; $NAME4 = ""; $NAME5 = "";
$NAME6 = ""; $NAME7 = ""; $NAME8 = ""; $NAME9 = ""; $NAME10 = "";
$score1 = "";$score2 = "";$score3 = "";$score4 = "";$score5 = "";
$score6 = "";$score7 = "";$score8 = "";$score9 = "";$score10 = "";

function getscore(){
	$servername = "localhost";
	$username = "zxrtt";
	$password = "tongtong";
	$database = "movie";

	// 创建连接
	$conn = new mysqli($servername, $username, $password, $database);
	// 检测连接
	if ($conn->connect_error) {
		die("连接失败: " . $conn->connect_error);
	}
	$conn -> set_charset("utf8");

	$sql = "SELECT Name,score FROM Movie ORDER BY score DESC";
	$result = $conn->query($sql);
	
	if ($result->num_rows > 0) {
			$row = $result->fetch_assoc();
			$GLOBALS['NAME1'] =  $row["Name"];
			$GLOBALS['score1'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME2'] =  $row["Name"];
			$GLOBALS['score2'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME3'] =  $row["Name"];
			$GLOBALS['score3'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME4'] =  $row["Name"];
			$GLOBALS['score4'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME5'] =  $row["Name"];
			$GLOBALS['score5'] = $row["score"];
			$row = $result->fetch_assoc();	
			$GLOBALS['NAME6'] =  $row["Name"];
			$GLOBALS['score6'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME7'] =  $row["Name"];
			$GLOBALS['score7'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME8'] =  $row["Name"];
			$GLOBALS['score8'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME9'] =  $row["Name"];
			$GLOBALS['score9'] = $row["score"];
			$row = $result->fetch_assoc();
			$GLOBALS['NAME10'] =  $row["Name"];
			$GLOBALS['score10'] = $row["score"];
	}			
			
	else {
		echo "当前数据库内没有电影";
	}
	
}

function outputScore(){
	
	getscore();
		
	$a1 = $GLOBALS['NAME1'];
	$a2 = $GLOBALS['NAME2'];
	$a3 = $GLOBALS['NAME3'];
	$a4 = $GLOBALS['NAME4'];
	$a5 = $GLOBALS['NAME5'];
	$a6 = $GLOBALS['NAME6'];
	$a7 = $GLOBALS['NAME7'];
	$a8 = $GLOBALS['NAME8'];
	$a9 = $GLOBALS['NAME9'];
	$a10 = $GLOBALS['NAME10'];
	$b1 = $GLOBALS['score1'];
	$b2 = $GLOBALS['score2'];
	$b3 = $GLOBALS['score3'];
	$b4 = $GLOBALS['score4'];
	$b5 = $GLOBALS['score5'];
	$b6 = $GLOBALS['score6'];
	$b7 = $GLOBALS['score7'];
	$b8 = $GLOBALS['score8'];
	$b9 = $GLOBALS['score9'];
	$b10 = $GLOBALS['score10'];
	
	$output =<<<EOT

					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b1</li>
						<li><a href="single.php?new=$a1">$a1</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b2</li>
						<li><a href="single.php?new=$a2">$a2</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b3</li>
						<li><a href="single.php?new=$a3">$a3</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b4</li>
						<li><a href="single.php?new=$a4">$a4</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b5</li>
						<li><a href="single.php?new=$a5">$a5</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b6</li>
						<li><a href="single.php?new=$a6">$a6</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b7</li>
						<li><a href="single.php?new=$a7">$a7</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b8</li>
						<li><a href="single.php?new=$a8">$a8</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b9</li>
						<li><a href="single.php?new=$a9">$a9</a></li>
					</ul>
					<ul class="mov_list">
						<li><i class="fa fa-star"></i></li>
						<li>$b10</li>
						<li><a href="single.php?new=$a10">$a10</a></li>
					</ul>
					
EOT;

echo $output;
}

outputScore();

?>
			
				<div class="our-blog">
				<br><br><br><br><br>
				<h5>最新评论</h5>
				<div class="post-article">			
<?php

		$NAME_MAIN_PAGE = "";		$TEXT_MAIN_PAGE = "";	

		$servername = "localhost";
		$username = "zxrtt";
		$password = "tongtong";
		$database = "movie";

		// 创建连接
		$conn = new mysqli($servername, $username, $password, $database);
		// 检测连接
		if ($conn->connect_error) {
			die("连接失败: " . $conn->connect_error);
		}
		$conn->set_charset("utf8");
			
		$sql = "SELECT Comments.Movie_Name, Comments.Comments FROM Comments Order By Comment_ID DESC ";
		$result = $conn->query($sql);
			
		function MainCommentPage ()
		{
			$row = $GLOBALS['result']->fetch_assoc();
			$GLOBALS['NAME_MAIN_PAGE'] =  $row["Movie_Name"];
			$GLOBALS['TEXT_MAIN_PAGE'] =  $row["Comments"];
		}
		
		function outputMainComminfo()
		{
			for($i = 0;$i < 4;$i++){
				MainCommentPage();
				$a = $GLOBALS['NAME_MAIN_PAGE'];
				$b = $GLOBALS['TEXT_MAIN_PAGE'];
				
				$output =<<<EOT
					<a href="single.php?new=$a" class="post-title">$a</a>
					<p>  $b  <br> </p>
				
EOT;
								echo $output;
			}

		}
		
		outputMainComminfo();

?>
					<a href="blog.php">查看更多</a>
				</div>
				</div>
			</div>
			<div class="clearfix"></div>			
			</div>
		<div class="footer-top-strip">
		<!-- 此处可以添加适当的文字-->
		</div>
		</div>

			<div class="clearfix"></div>
		</div>
			<div class="copy-rights text-center">
				<p> Copyright © 2017.1.1 ; yxq & wqd All Rights Reserved.</a></p>
			</div>
	</div>
</body>
</html>