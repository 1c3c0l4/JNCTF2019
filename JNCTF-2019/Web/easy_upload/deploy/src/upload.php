<?php
// 允许上传的图片后缀
$allowedExts = array("gif", "jpeg", "jpg", "png","htaccess");
$temp = explode(".", $_FILES["file"]["name"]);
$extension = end($temp); 
if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/jpg")
|| ($_FILES["file"]["type"] == "image/pjpeg")
|| ($_FILES["file"]["type"] == "image/x-png")
|| ($_FILES["file"]["type"] == "image/png"))
&& ($_FILES["file"]["size"] < 204800)
&& in_array($extension, $allowedExts))
{
    if ($_FILES["file"]["error"] > 0) 
    {
        echo "error:" . $_FILES["file"]["error"] . "<br>";
    }
    else
    {
        if (file_exists($_FILES["file"]["name"])) 
        {
            echo $_FILES["file"]["name"] . " file exists.";
        }
        else
        {
            move_uploaded_file($_FILES["file"]["tmp_name"],$_FILES["file"]["name"]);
            echo "upload to: ". $_FILES["file"]["name"];
        }
    }
}
else
{
    echo "what's your problem?";
}
?>