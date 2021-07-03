<?php

include ("Board.php");
include ("MoveStrategy.php");
include ("Move.php");


class Game{

    var $gameBoard;
    var $moveStrategy;
    var $strategies;

    //construct strategy and board
    public function __construct($gameBoard)
    {
        $this->gameBoard = $gameBoard;
        $this->strategies = array(
            'Smart' => 'SmartStrategy',
            'Random' => 'RandomStrategy'
        );
    }

    //make player move(pickPlace) rand or smart
    function playerMove($x, $y){
        $this->gameBoard->places[$x][$y] = 1;
        $this->gameBoard->updateFile();
    }

    //make enemy move(pickPlace) rand or smart
    function enemyMove(){
        $strategy = new $this->strategies[$this->gameBoard->strategy]($this->gameBoard);
        return $strategy->pickPlace();
    }

    //fromJsonString function used to updateBoard
    public static function fromJsonString($json): Game
    {
        $content = explode("\r\n", $json);
        $strategy =  $content[0];
        $game = new Game($strategy);
        $game->updateBoard(json_decode($content[1]));
        return $game;

    }
    
    //update the game board
    public function updateBoard($board){
        $this->gameBoard = $board;
    }




}
