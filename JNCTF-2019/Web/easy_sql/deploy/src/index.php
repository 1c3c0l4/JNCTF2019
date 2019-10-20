<html>
<head>
</head>
<body>
<a> Input the id and I will tell you the query result.</a>
<form action="index.php" method="GET">
<input type="text" name="id">
<input type="submit">
<?php
    session_start();
    include_once "config.php";
    $id=$_GET['id'];
	if(strpos($id,' ')||strpos($id,'select')||strpos("$id",'SLEEP')){
		exit("waf!");
	}
	if(strlen($id)>250){
		exit("payload is too long!");
	}
    $con=mysqli_connect("localhost",$datauser,$datapass,$dataName);
    $sql="select * from member where id='".$id."'";
    $result=mysqli_query($con,$sql);
    $row=mysqli_fetch_array($result); 
    if($row){
        echo "</br>"."Yes";
    }
    else{
        echo "</br>"."No";
    }
    ?>
</form>
</body>
</html>


