<?php 
include 'aduser.php';
session_start();

$sql= "select Name, addDate, count(Ticket_ID), Collection_of_people  from movie left join ticket on Movie_Name = Name group by Name;" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset('utf8');
        $result=$con->query($sql);
		$ts = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = array();
				$t['Name'] = $row['Name'];
				$t['addDate'] = $row['addDate'];
				$t['count(Ticket_ID)'] = $row['count(Ticket_ID)'];
				$t['Collection_of_people'] = $row['Collection_of_people'];
				$ts[] = $t;
			}while($row);
        }

$sql= "select* from movie;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$moviecount = $result->num_rows;

$sql= "select* from screen;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$screencount = $result->num_rows;

$sql= "select* from usr;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$usrcount = $result->num_rows;

$sql= "select* from ticket;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$ticketcount = $result->num_rows;

function page1($ts){
	for($i = 0; $i < count($ts); $i = $i + 1){
		$temp1 = $ts[$i]['Name'];
		$temp2 = $ts[$i]['addDate'];
		$temp3 = $ts[$i]['count(Ticket_ID)'];
		$temp4 = $ts[$i]['Collection_of_people'];
echo <<< EOF1
	<tr><td>$temp1</td> <td>$temp2</td> <td>$temp3</td> <td>$temp4</td><td><a onclick="return confirm('是否删除此电影？');" href="removemovie.php?moviename=$temp1 " class="view-link">删除</a></td></tr>
	
EOF1;
				
	}
		
}





?>
<html lang="en"><!--<![endif]--> 
	<head>
		<meta charset="utf-8">
		<title>Manangement</title>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link href="css/bootstrap.min.css" rel="stylesheet">
		<link href="css/bootstrap-responsive.min.css" rel="stylesheet">
		<link href="css/site.css" rel="stylesheet">
		<!--[if lt IE 9]><script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
	</head>
	<body>
		<div class="container">
			<div class="navbar">
				<div class="navbar-inner">
					<div class="container">
						<a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse"> <span class="icon-bar"></span> <span class="icon-bar"></span> <span class="icon-bar"></span> </a> <a class="brand" href="#">影票管理系统</a>
						<div class="nav-collapse">
								
							<ul class="nav pull-right">
								<li>
									<a href="aduserOut.php">Logout</a>
								</li>
							</ul>
						</div>
					</div>
				</div>
			</div>
			<div class="row">
				<div class="span3">
					<div class="well" style="padding: 8px 0;">
						<ul class="nav nav-list">
							<li class="nav-header">
								管理
							</li>
							<li class="active">
								<a href="admin.php"><i class="icon-white icon-home"></i> 电影</a>
							</li>
							<li>
								<a href="projects.php"><i class="icon-folder-open"></i> 上映</a>
							</li>
						</ul>
					</div>
				</div>
				
				
				
				
				
				
				
				
				<div class="span9">
					<h1>
						欢迎使用！
					</h1>
					<div class="well summary">
						<ul>
							<li>
								<a href="#"><span class="count"><?php echo $screencount;?></span> 影厅</a>
							</li>
							<li>
								<a href="#"><span class="count"><?php echo $moviecount;?></span>电影</a>
							</li>
							<li>
								<a href="#"><span class="count"><?php echo $usrcount;?></span> 用户</a>
							</li>
							<li class="last">
								<a href="#"><span class="count"><?php echo $ticketcount;?></span> 销售票数</a>
							</li>
						</ul>
					</div>
					<h2>
						电影
					</h2>
					<table class="table table-bordered table-striped">
						<thead>
							<tr>
								<th>
									名字
								</th>
								<th>
									添加时间
								</th>
								<th>
									销售票数
								</th>
								<th>
									收藏人数
								</th>
								<th>
									详情
								</th>
							</tr>
						</thead>
						<tbody>
							<?php   page1($ts);   ?>
						</tbody>
					</table>
					<a class="toggle-link" href="#new-project"><i class="icon-plus"></i> 添加电影</a>
					<form id="new-project" action="addmovie.php" method="post" class="form-horizontal hidden">
						<fieldset>
							<legend>新的电影</legend>
							<div class="control-group">
								<label class="control-label" for="input01">电影</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" name="moviename"/>
								</div>
							</div>
							<div class="control-group">
								<label class="control-label" for="input01">类型</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" name="movietype"/>
								</div>
							</div>
							
							<div class="control-group">
								<label class="control-label" for="input01">导演</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" name="direct"/>
								</div>
							</div>
							<div class="control-group">
								<label class="control-label" for="input01">主演</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" name="mainper"/>
								</div>
							</div>
							
                            
							<div class="control-group">
								<label class="control-label" for="textarea">简介</label>
								<div class="controls">
									<textarea class="input-xlarge" id="textarea" rows="3" name = "short"></textarea>
								</div>
							</div>
							<div class="control-group">
								<label class="control-label" for="textarea">详细</label>
								<div class="controls">
									<textarea class="input-xlarge" id="textarea" rows="3" name = "long"></textarea>
								</div>
							</div>
							
							<div class="form-actions">
								<button type="submit" class="btn btn-primary">确定</button> <button class="btn">取消</button>
							</div>
						</fieldset>
					</form>
					
                    
				</div>
				
				
			</div>
		</div>
		<script src="js/jquery.min.js"></script>
		<script src="js/bootstrap.min.js"></script>
		<script src="js/site.js"></script> 
	</body>
</html>