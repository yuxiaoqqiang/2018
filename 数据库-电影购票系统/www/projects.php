<?php 
include 'aduser.php';
session_start();

$sql= "select Arrange_Name, Arrange_Date, Arrange_Time, Arrange_Screen  from arrangement where datediff(Arrange_Date,curdate()) >= 0 order by Arrange_Name asc ,Arrange_Date asc ,Arrange_Time asc;" ;
        $con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
		$con->set_charset("utf8");
        $result=$con->query($sql);
		$ts = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = array();
				$t['Arrange_Name'] = $row['Arrange_Name'];
				$t['Arrange_Date'] = $row['Arrange_Date'];
				$t['Arrange_Time'] = $row['Arrange_Time'];
				$t['Arrange_Screen'] = $row['Arrange_Screen'];
				$ts[] = $t;
			}while($row);
        }
        $result->close();


function page1($ts){
	for($i = 0; $i < count($ts); $i = $i + 1){
		$temp1 = $ts[$i]['Arrange_Name'];
		$temp2 = $ts[$i]['Arrange_Date'];
		$temp3 = $ts[$i]['Arrange_Time'];
		$temp4 = $ts[$i]['Arrange_Screen'];
echo <<< EOF1
	<tr><td>$temp1</td> <td>$temp2</td> <td>$temp3</td> <td>$temp4</td><td><a href="#" class="view-link">View</a></td></tr>
	
EOF1;
				
	}
		
}


$sql= "select* from screen order by Screen_No;" ;
$con=mysqli_connect("localhost","zxrtt", "tongtong", "movie");
$result=$con->query($sql);
$tp = array();
		if($result && $result->num_rows>0) {
			do{
				$row = $result->fetch_assoc();
				if(!$row){
					break;
					
				}
				$t = array();
				$t['Screen_Name'] = $row['Screen_Name'];
				$tp[] = $t;
			}while($row);

        }
		
		
function page2($tp){
	for($i = 0; $i < count($tp); $i = $i + 1){
		$temp1 = $tp[$i]['Screen_Name'];
		echo <<< EOF2
		<option value ="$temp1">$temp1 号</option>
EOF2;
		
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
							<li >
								<a href="admin.php"><i class="icon-white icon-home"></i> 电影</a>
							</li>
							<li class="active">
								<a href="projects.php"><i class="icon-folder-open"></i> 上映</a>
							</li>
						</ul>
					</div>
				</div>
				<div class="span9">
					<h1>
						上映情况
					</h1>
					<table class="table table-bordered table-striped">
						<thead>
							<tr>
								<th>
									电影
								</th>
								<th>
									日期
								</th>
								<th>
									时间
								</th>
								<th>
									影厅
								</th>
								<th>
									详情
								</th>
							</tr>
						</thead>
						<tbody>
							<?php page1($ts); ?>
							
						</tbody>
					</table>
					<a class="toggle-link" href="#new-project"><i class="icon-plus"></i> 安排一场电影</a>
					<form id="new-project" action="arrangeMovie.php" method="post" class="form-horizontal hidden">
						<fieldset>
							<legend>新的场次</legend>
							<div class="control-group">
								<label class="control-label" for="input01">电影</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" name="moviename"/>
								</div>
							</div>
							<div class="control-group">
								<label class="control-label" for="select01">影厅</label>
								<div class="controls">
									<select id="select01" name="screenname"> <option>-- 选择影厅 --</option> <?php page2($tp);?> </select>
								</div>
							</div>
                            <div class="control-group">
								<label class="control-label" for="input01">日期</label>
								<div class="controls">
									<input type="text" class="input-xlarge" id="input01" placeholder="例如 2016-11-20" name="date"/>
								</div>
							</div>
							
							<div class="control-group">
								<label class="control-label" for="select01">场次</label>
								<div class="controls">
									<select id="select01" name="timeid"> <option>-- 选择场次 --</option> <option value = 1>09：00</option> <option value =2>11：30</option> <option value =3>15：00</option> <option value =4>19：30</option> <option value =5>22：00</option> </select>
								</div>
							</div>
							<div class="control-group">
								<label class="control-label" for="textarea">备注</label>
								<div class="controls">
									<textarea class="input-xlarge" id="textarea" rows="3"></textarea>
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
