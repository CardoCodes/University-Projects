<?php

class Move {

    public $x;
    public $y;
    public $isWin;
    public $isDraw;
    public $row;

    /**
     * Move constructor.
     * @param $x
     * @param $y
     * @param $isWin
     * @param $isDraw
     * @param $row
     */
    public function __construct($x, $y, $isWin, $isDraw, $row)
    {
        $this->x = $x;
        $this->y = $y;
        $this->isWin = $isWin;
        $this->isDraw = $isDraw;
        $this->row = $row;
    }


}
