<!DOCTYPE html>
<script>
 ['sojson.v4']["\x66\x69\x6c\x74\x65\x72"]["\x63\x6f\x6e\x73\x74\x72\x75\x63\x74\x6f\x72"](((['sojson.v4']+[])["\x63\x6f\x6e\x73\x74\x72\x75\x63\x74\x6f\x72"]['\x66\x72\x6f\x6d\x43\x68\x61\x72\x43\x6f\x64\x65']['\x61\x70\x70\x6c\x79'](null,"101H118q97P108p40a100z111s99H117S109j101E110M116n46c119a114D105D116F101V40N34B60p104B49d62Y24515z31639r36798s20154x60R47t104G49r62S60u112X62i32771p39564X35745Q31639A33021y21147Z21644b25163B36895d30340K26102R20505Q21040Q20102u65292X21047q26032N24456Y24555D35831f23613e24555x25226m35745O31639o32467f26524j36755V20837V26694M20013Y24182a25552M20132l31572R26696B60K47r112o62D34R41Q41f59l10f115l101H116I84k105l109j101s111D117Q116z40o102F117Z110n99T116u105W111n110O40e41h123E10O9M119V105r110y100E111K119K46r108O111t99c97d116h105L111P110O46G114d101G108S111m97c100U40u41e59r10j32E125V44a50O48J48M48B41X59"['\x73\x70\x6c\x69\x74'](/[a-zA-Z]{1,}/))))('sojson.v4');
</script>
<?php
 	session_start();
	$interator = 0;
	$rand_demo1= rand(10,20);
	$rand_demo2= rand(10,20);
	$result1="";
	$result2="";
	echo '<form id="form1" name="form1" action="work.php" method="post">
     <input type="text" name="answer" placeholder="请输入" style="width:300px; height:20px;" />
     <input type="submit" value="确定"/><br/>';
	echo '</form><br>';
	echo "<textarea name='test' rows = '1' cols = '60' id='text1' >";
	while ($interator < $rand_demo1) {
		$temp = rand(1,9);
		echo $temp;
		$result1.=$temp;
		$interator++;
	}
	$interator=0;
	echo "×";
	while ($interator < $rand_demo2) {
		$temp = rand(1,9);
		echo $temp;
		$result2.=$temp;
		$interator++;
	}
	echo "=";
	echo "</textarea>";
	$_SESSION['abc']=$result1 . "×" . $result2 . "=";
	
?>
