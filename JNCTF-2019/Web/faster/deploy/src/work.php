<?php
	session_start();
	function mul($a, $b)
{
    $lenA = strlen($a);
    $lenB = strlen($b);

    $result = '0';
    for ($inxA = $lenA - 1; $inxA >= 0; --$inxA) {
        $re = '';
        for ($i = $inxA + 1; $i < $lenA; ++$i) {
            $re = "0" . $re;
        }
        $j = 0;
        for ($inxB = $lenB - 1; $inxB >= 0; --$inxB) {
            $mul = (int)$a[$inxA] * (int)$b[$inxB] + $j;
            if ($mul >= 10) {
                $j = floor($mul / 10);
                $mul = $mul - $j * 10;
            } else {
                $j = 0;
            }
            $re = (string)$mul . $re;
        }
        if ($j > 0) $re = (string)$j . $re;
        $result = add($result, $re);
    }

    return $result;
}
function add($a, $b)
{
    $lenA = strlen($a);
    $lenB = strlen($b);

    $j = 0;
    $re = '';
    for ($inxA = $lenA - 1, $inxB = $lenB - 1; ($inxA >= 0 || $inxB >= 0); --$inxA, --$inxB) {
        $itemA = ($inxA >= 0) ? (int)$a[$inxA] : 0;
        $itemB = ($inxB >= 0) ? (int)$b[$inxB] : 0;
        $sum = $itemA + $itemB + $j;
        if ($sum > 9) {
            $j = 1;
            $sum = $sum - 10;
        } else {
            $j = 0;
        }
        $re = (string)$sum . $re;
    }
    if ($j > 0) $re = (string)$j . $re;

    return $re;
}
	$answer = $_POST['answer'];
 	$str = $_SESSION['abc'];
	
	$temp=array('1','2','3','4','5','6','7','8','9','0'); 
    $result_left=''; 
	$result_right=''; 
	$resultall='';
    for($i=0;$i<strlen($str);$i++){ 
        if(in_array($str[$i],$temp)){ 
            $result_left.=$str[$i]; 
        } 
		else
			break;
    } 

	for($i=$i;$i<strlen($str);$i++){ 
        if(in_array($str[$i],$temp)){ 
            $result_right.=$str[$i]; 
        } 
    }

	$resultall=mul($result_left,$result_right);
 	 if($resultall==$answer){
		echo "<script language='javascript'>alert('flag{zheshiflag}');window.location='index.php'</script>";
	}else{
		echo "<script language='javascript'>alert('Error!!!');window.location='index.php'</script>";
	}  
	session_unset();
	session_destroy();
 ?>

 