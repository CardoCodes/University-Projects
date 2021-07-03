<?php

class Board{
    public $places;
    public $size;
    public $pid;
    public $strategy;

    //construct a board to play on
    function __construct($size=15, $strategy=''){
        $this->size = $size;
        $this->places = array_fill(0, $size, array_fill(0, $size, 0));
        $this->pid = uniqid();
        $this->strategy = $strategy;
    }

    //toJson and fromJson
    function toJson(){
        return json_encode($this);
    }
    static function fromJson($json){
        $obj = json_decode($json);
        $board = new Board();
        $board->size = $obj->size;
        $board->places = $obj->places;
        $board->pid = $obj->pid;
        $board->strategy = $obj->strategy;
        return $board;
    }

    //check to see if slot is empty
    function isEmpty($x, $y): bool
    {
        return $this->places[$x][$y] == 0;
    }

    //get stone location
    function getStone($x, $y){
        if ($x < 0 || $x > 15 || $y < 0 || $y > 15) {
            return null;
        } else {
            return isset($this->boardPositions[$x][$y]);
        }
    }

    //place stone location
    function placeStone( $x, $y){
        $this->places[$x][$y];
        $this->updateFile();
    }

    function getRow($x, $y, $dx, $dy){
        $row = array();
        for($i = -2; $i < 3; $i++){
            array_push($row, $this->places[$x + $dx * $i][$y + $dy * $i]);
        }
        return $row;
    }

    //update file for pid
    function updateFile(){
        $path = "../data/" . $this->pid . ".txt";
        $file = fopen($path, "w") or die("Error: Unable to open file");
        fwrite($file, $this->toJson());
        fclose($file);
    }

    //get board info with pid (.txt)
    static function getBoard($pid){
        $path = "../data/" . $pid . ".txt";
        $file = fopen($path, "r") or die("Error: Unable to open file");
        $json = fread($file, filesize($path));
        fclose($file);
        return self::fromJson($json);
    }








}