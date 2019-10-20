<?php
echo "PHP is the best language,and you can input the ?file1=index.php</br>";
error_reporting(0);
$file=$_GET['file1'];
if(strpos($file,"flag")){
	die("You can't read flag by file1");
}
include($file);
$num=$_POST['num'];
$key=$_POST['key'];
if(isset($num)&&!is_numeric($num)&&!is_array($num)){
		if(!is_numeric($key)){
			include($_GET['file2']);
		}
	}
?>