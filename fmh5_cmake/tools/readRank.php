<?php
    header("Access-Control-Allow-Origin: *");
    date_default_timezone_set('Asia/Shanghai');
    //判断参数是否存在
	/*
		type:1 等级排行榜
		type:2 繁荣度排行榜
		type:3 累积被点赞排行榜
		type:4 昨日金币收入排行榜
		type:5 近七天金币收入排行榜
		type:6 近三十天金币收入排行榜
	*/
    if (!array_key_exists('type', $_GET))
    {
        throw new Exception("need param type");
    }

    $type = $_GET['type'];
	$filename = "";
	if($type == "1")
		$filename = "level_rank.json";
	else if($type == "2")
		$filename = "prosperity_rank.json";
	else if($type == "3")
		$filename = "accthumbsup_rank.json";
	else if($type == "4")
		$filename = "lastdaycoin_rank.json";
	else if($type == "5")
		$filename = "sevendaycoin_rank.json";
	else if($type == "6")
		$filename = "thirtydaycoin_rank.json";
	else
		throw new Exception("param type error");

	$json_string = file_get_contents($filename); 
	echo($json_string);
