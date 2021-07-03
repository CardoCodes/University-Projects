<?php

class RandomStrategy extends MoveStrategy{

    //TODO: implement better O^n method for calculating random slot.
    function pickPlace()
    {
        $available = false;
        $x = 0;
        $y = 0;
        while(!$available){
            $x = rand(0,14);
            $y = rand(0,14);
            if($this->board->isEmpty($x,$y)){
                $this->board->placeStone($x,$y);
                $available = true;
            }
        }
        return array($x,$y);
    }
}