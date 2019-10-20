<?php
show_source(__FILE__);
class CTFer{
    private $key;
    public $param1;
    public $param2;
    function __construct($key){
        $this->key=$key;
        $this->param1=$this->param2=rand(666,7777777);
    }
    function __destruct(){
        $this->GetFlag();
    }
    function GetFlag(){
        $this->param1=rand(666,7777777);
        if($this->param1===$this->param2&&strlen($this->key)<=11){
		include $this->key;
        }else{
            echo "NONONO!";
        }
	}
}
@unserialize($_GET['s']);
?>