#include <msp430.h>
#include "stateMachines.h"

char trackState;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */

  switch(trackState){
  case 1:
    toggle_leds();
    break;
    
  case 2:
    turnOnRed();
    buzzerNoise();
    break;

  case 3:
    dimGreen();
    dimRed();
    break;

  case 4:
    turnOffAll();
    
  default:
    break;

  }
}


