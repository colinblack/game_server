<?php
	header("Access-Control-Allow-Origin: *");

function getDbConnection($conf="./conf/db.conf")
{
    $c = file_get_contents($conf);
    if(!$c)
	{
        throw new Exception("get conf failed:" . $conf);
    }

    $dbconf = json_decode($c,true);

    if($dbconf["type"] != "mysql")
    {
        throw new Exception("db type " . $dbconf["type"] . " not support yet",-1);
    }

    $port = $dbconf['port'];
    
    if(!$port)
    {
        $port = '3306';
    }

    //$db = mysqli_connect($dbconf['host'], $dbconf['username'], "1234", "sg17_mapping", $port);
    //$db = mysqli_connect("localhost", "root", "1234", "sg17_mappi");
    $db = mysql_connect($dbconf['host'] . ':' . $port, $dbconf['username'], $dbconf['password']);

    if(!$db)
    {
        throw new Exception(mysql_error());
    }

    return $db;
}

function FuzzyQuery()
{
	//判断参数是否存在
	if (!array_key_exists('name', $_GET))
	{
		throw new Exception("need param name");			
	}

  	$db = getDbConnection();
  	$partname = mysql_real_escape_string($_GET['name']);

  	$sql = 'select alliance_id from sg17_mapping.alliance_mapping where alliance_name like "%'.$partname.'%" limit 50';

    $rlt = mysql_query($sql) ;
     
     if(!$rlt)
     {
        $ret = array("code"=>-1,"msg"=>mysql_error());
        return json_encode($ret);
    }
       
    $rows = array();
    while($row = mysql_fetch_array($rlt, MYSQL_NUM))
    {
         array_push($rows, $row);
    }
    
    mysql_free_result($rlt);

    $ret = array("code"=>0,"msg"=>"success","data"=>$rows);
     //echo $ret["data"];
    //strtr($ret["data"],"\"","");
     
    return json_encode($ret);
    mysql_close(); 
}

try{
    echo FuzzyQuery();
}
catch(Exception $e){
        $ret = array("code"=>-1,"msg"=>$e->getMessage());
        echo json_encode($ret);
}

?>
