<?php

class SmartStrategy extends MoveStrategy {


    //pick place return for index
    //not fully functioning and buggy
    //TODO: Fix smart strategy algo and implementation
    public function pickPlace()
    {
        for ($i = 2; $i < 13; $i++) {
            for ($j = 2; $j < 13; $j++) {
                $hRow = $this->board->getRow($i, $j, 1, 0);
                $vRow = $this->board->getRow($i, $j, 0, 1);
                $dRow = $this->board->getRow($i, $j, 1, 1);
                $ndRow = $this->board->getRow($i, $j, 1, -1);

                $this->calculate($hRow, $i, $j);
                $this->calculate($vRow, $i, $j);
                $this->calculate($dRow, $i, $j);
                $this->calculate($ndRow, $i, $j);


            }
        }

        $smart = new SmartStrategy($this->board);
        return $smart->pickPlace();

    }

    //calculates slot
    function calculate($rowType, $i, $j){
        if($this->rowWin($rowType)){
            for($k = 0; $k < 3; $k++){
                if($rowType[2 + $k] === 0){
                    $this->board->places[$i][ $j + $k] = 2;
                    $this->board->updateFile();
                    return [$i, $j + $k];
                }

                if($rowType[2 - $k] === 0){
                    $this->board->places[$i][ $j - $k] = 2;
                    $this->board->updateFile();
                    return [$i, $j - $k];
                }
            }
        }

    }


    //calculate if the row will be a winning row
    function rowWin($row){
        $x = 0; //track 1
        $y = 0; //track 2
        foreach($row as $num){
            if($num === 1){
                $x++;
            }
            if($num === 2){
                $y++;
            }
        }
        return $y == 0 && $x > 2;


    }




}
