<?php

define('PID', 'pid');
define('STRATEGY', 'strategy');
define('MOVE', 'move');
define('DATA', '../data/');

include ("Game.php");

/**
 * Class Response
 */

class Response{
    public $response;
    public $ack_move;
    public $move;
    function __construct($response, $ack_move, $move)
    {
        $this->response = $response;
        $this->ack_move = $ack_move;
        $this->move = $move;
    }
}

$index = new Index();
$index->runThis();

/**
 * Class Index
 */

class Index{
    public $x_req;
    public $y_req;
    public $x_res;
    public $y_res;
    public $board;
    public $game;

    function runThis()
    {
        $this->isValidPID();
        $this->isMoveReal();
        $this->isMoveValid();
        $this->isMoveWellFormed();
        $this->isSlotAvailable();

        $this->game = new Game($this->board);
        $this->game->playerMove($this->x_req, $this->y_req);
        $moveCoords = $this->game->enemyMove();

        $this->x_res = $moveCoords[0];
        $this->y_res = $moveCoords[1];
        Index::sendJson();

    }

    function IsValidPID(){
        if(!array_key_exists("pid", $_GET)){
            $data = array('response'=>false, 'reason'=>"Pid not specified");
            echo json_encode($data);
            exit;
        }
        $files = scandir(DATA);
        if (!in_array($_GET[PID] . '.txt', $files)) {
            $data = array('response'=>false, 'reason'=>"Unknown PID");
            echo json_encode($data);
            exit;
        }
    }

    function isMoveReal(){
        if(!array_key_exists("move", $_GET)){
            $data = array('response'=>false, 'reason'=>"Move not specified");
            echo json_encode($data);
            exit;
        }

    }

    function isMoveValid(){
        $coords = explode(",", $_GET["move"]);
        if(intval($coords[0]) > 14 || intval($coords[0]) < 0){
            $data = array('response'=>false, 'reason'=>"Invalid x coordinate, ".intval($coords[0]));
            echo json_encode($data);
            exit;
        }

        if(intval($coords[1]) > 14 || intval($coords[1]) < 0){
            $data = array('response'=>false, 'reason'=>"Invalid y coordinate, ".intval($coords[1]));
            echo json_encode($data);
            exit;
        }

    }

    function isMoveWellFormed(){
        $coords = explode(",", $_GET["move"]);
        if($coords[0] == null || $coords[1] == null || sizeof($coords) > 2){
            $data = array('response'=>false, 'reason'=>"Move not well-formed");
            echo json_encode($data);
            exit;
        }
        $coordinates = Index::getCoords($_GET['move']);
        $this->x_req = intval($coordinates[0]);
        $this->y_req = intval($coordinates[1]);
    }

    function isSlotAvailable(){
        $this->board = Board::getBoard($_GET[PID]);
        if ($this->board->places[$this->x_req][$this->y_req] != 0) {
            $data = array('response'=>false, 'reason'=>"Slot Invalid");
            echo json_encode($data);
            exit;
        }
    }

    function sendJson(){
        $ack_move = new Move(
            $this->x_req,
            $this->y_req,
            $this->board->player_won(1),
            false,
            $this->game->get_player1_returning_row()
        );
        $move = new Move(
            $this->x_res,
            $this->y_res,
            $this->board->player_won(2),
            false,
            $this->game->get_player2_returning_row()
        );
        $response = new Response(true, $ack_move, $move);
        echo json_encode($response);

    }

    function getCoords($moveInfo){
        $coords = explode(",", $moveInfo);
        $this->isMoveValid();
        return $coords;
    }

}







