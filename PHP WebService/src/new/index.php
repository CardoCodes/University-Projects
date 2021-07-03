<?php

    require_once("../play/Board.php");
    define('STRATEGY', 'strategy');

    isStrategy();
    isValidStrategy();
    $board = new Board(15, $_GET[STRATEGY]);
    toFile($board->pid, $board->toJson());
    echo "{\"response\":true, \"pid\":\"" . $board->pid . "\"}";

    //check to see if strategy is specified.
    //if not echo {"response": false, "reason": "Strategy not specified"}
    function isStrategy(){
        if (!array_key_exists(STRATEGY, $_GET)) {
            $data = array('response'=>false, 'reason'=>"Strategy not specified");
            echo json_encode($data);
            exit;
        }
    }
    //check to see if strategy is programmed
    //if not echo {"response": false, "reason": "Unknown strategy"}
    function isValidStrategy(){
        $strategy = $_GET[STRATEGY];
        if (!($strategy==="Smart" || $strategy==="Random")) {
            $data = array('response'=>false, 'reason'=>"Unknown Strategy");
            echo json_encode($data);
            exit;
        }
    }

    //create and write new file with PID from board
    function toFile($pid, $txt){
        $file = fopen("../data/" . $pid . ".txt", "w") or die("Error Unknown,  file not written");
        fwrite($file, $txt);
        fclose($file);
    }