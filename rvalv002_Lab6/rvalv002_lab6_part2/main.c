/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 6  Exercise 2
*
objective -
Create a simple light game that requires pressing a button on PA0 while the middle of three LEDs on PB0, PB1, and PB2 is lit.
 The LEDs light for 300 ms each in sequence. When the button is pressed, the currently lit LED stays lit.
  Pressing the button again restarts the game.



*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() Setes this to 1. C programer should clear to 0

// Internal variables for mapping AVR's ISE to our cleaner TimerISR Model
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. default 1 ms
unsigned long _avr_timer_cntcurr = 0; //Current internal count of 1ms ticks


//Global Variables
unsigned char tempA =0x00; // Temp Variable holding A value
unsigned char tempB =0x00; // Temp Variable holding B value
unsigned char cnt=0x00;


//Bit Access functions
inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}
inline unsigned char GetBit(unsigned char x, unsigned char k) {
return ((x & (0x01 << k)) != 0);
}

//Timer functions

void TimerOn(){
// AVR timer/counter controller register TCCR1
TCCR1B = 0x0B;   // Bit3 = 0: CTC mode (clear timer on compare)
				// 00001011: 0x0B
				// So, 8 mhz clock or 8mill /64 = 125k ticks /s
				// Thus, TCNT1 register will count at 125k ticks /s

// Avr output compares register OCR1A

OCR1A= 125;

TIMSK1 =0x02;

TCNT1 = 0;

_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;

}

void Timeroff(){
TCCR1B = 0x00;
}

void TimerISR(){
TimerFlag = 1;


}

ISR(TIMER1_CAPT_vect){
_avr_timer_cntcurr--;
if(_avr_timer_cntcurr==0){


TimerISR();
_avr_timer_cntcurr = _avr_timer_M;
}
}

void TimerSet(unsigned long M){

_avr_timer_M=M;

_avr_timer_cntcurr = _avr_timer_M;

}
enum States {Start ,Init ,Light,Stay} State;


int Tick(void){
switch(State){ //Transition States

case Start:
State = Init;
break;

case Init:
State = Light;
break;

case Light:
if(tempA == 0x00){ // If not pressed stay in the Light State
State = Light;
}
else if(tempA == 0x01) // If pressed Go to the Stay state
{
State = Stay;
}

break;

case Stay:
if(tempA == 0x00){ // if button not pressed
State = Stay;
}else if (tempA == 0x01){

State = Light;
}
default:
State = Start;
break;

}

switch(State){//Actions

case Start:
break;

case Init:
tempB = 0x00; // Sets all lights off.
cnt = 0x00;
break;

case Light:

if (cnt == 0x00){ 

tempB = 0x01; // Light 1 on

cnt++;

} else if(cnt == 0x01){

tempB = 0x02; // Light 2 on

cnt++;

} else if(cnt == 0x02){

tempB = 0x04; // Light 3 on

cnt = 0x00;

} else {cnt = 0x00;}

break;

case Stay: 
break;
}


PORTB = tempB;
tempA = PINA & 0x01;
tempA = ~tempA;

return 0;


}






int main(void){

DDRA = 0x00; PORTB = 0xFF; // Sets Port B to input
DDRB = 0xFF; PORTB = 0x00; //Sets Port B to output and init's B to 0
unsigned short Period = 300; // .3 Seconds

tempA = PINA & 0x01;
tempA = ~tempA;

tempB = 0x00;

TimerSet(Period);
TimerOn();

while(1){



while (!TimerFlag); // Wait 1 Second
TimerFlag = 0;
Tick();

}

}
