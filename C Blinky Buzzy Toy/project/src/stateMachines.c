#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static int count = 0;

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

//turn on red turn off green
void turnOnRed()
{
  red_on = 1;
  green_on = 0;
  led_update();
}

//turn on green turn off red 
void turnOnGreen()
{
  green_on = 1;
  red_on = 0;
  led_update();
}

//turn on both leds
void turnOnBoth(){
  green_on = 1;
  red_on = 1;
  led_update();
}

//turn off led and buzzer
void turnOffAll()
{
  buzzer_set_period(0);
  red_on = 0;
  green_on = 0;
  led_update();
}
char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

void toggle_leds()
{
  buzzer_set_period(1000);
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    green_on = 0;
    led_update();
    state = 1;
    break;
  case 1:
    green_on = 1;
    red_on = 0;
    led_update();
    state = 0;
    break;
  }
}

void buzzerNoise(){
  //end of count at 2500
  if(count == 2500){
    buzzer_set_period(0);
    count = 0;
  }
  if (count < 200) buzzer_set_period(5000);
  else if (count < 400) buzzer_set_period(0);
  else if (count < 600) buzzer_set_period(2222);
  else if (count < 800) buzzer_set_period(0);
  else if (count < 1000) buzzer_set_period(4444);
  else if (count < 1200) buzzer_set_period(0);
  else if (count < 1400) buzzer_set_period(6666);
  else if (count < 1600) buzzer_set_period(0);
  else if (count < 1800) buzzer_set_period(3333);
  else if (count < 2000) buzzer_set_period(0);
  else if (count < 2200) buzzer_set_period(5555);
  else if (count < 2400) buzzer_set_period(0);
  else if (count < 2450) buzzer_set_period(1000);
  count +=2;
}

void dimGreen()
{
  //reset count at 5000
  if (count == 5000){
    count = 0;
  }
  
  if (count < 1000) {
    green_on = 1;
  }
  else if (count < 2000 && count%2 == 0){
    green_on = 1;
  }
  else if (count < 3000 && count%3 == 0){
    green_on = 1;
  }
  else if (count < 4000 && count%4 == 0){
    green_on = 1;
  }
  else if (count < 5000 && count%5 == 0){
    green_on = 1;
  }
  else green_on = 0;
  count += 1;
}

void dimRed(){
  //reset count at 5000
  if (count == 5000){
    count = 0;
  }
  if (count < 1000) {
    red_on = 1;
  }
  else if (count < 2000 && count%2 == 0){
    red_on = 1;
  }
  else if (count < 3000 && count%3 == 0){
    red_on = 1;
  }
  else if (count < 4000 && count%4 == 0){
    red_on = 1;
  }
  else if (count < 5000 && count%5 == 0){
    red_on = 1;
  }
  else red_on = 0;
  count += 1;
}
  
void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}



