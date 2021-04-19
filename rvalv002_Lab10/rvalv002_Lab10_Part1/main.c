/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 10  Exercise 1
*
objective -
Connect LEDs to PB0, PB1, PB2, and PB3.
In one state machine (ThreeLEDsSM), output to a shared variable (threeLEDs) the following behavior: set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each.
In a second state machine (BlinkingLEDSM), output to a shared variable (blinkingLED) the following behavior: set bit 3 to 1 for 1 second, then 0 for 1 second.
In a third state machine (CombineLEDsSM), combine both shared variables and output to the PORTB.




*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/


#include <avr/io.h>
#include "Timer.h"

//Global Variable
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x01;
unsigned char out = 0x00;

//Static
unsigned char cnt = 0x00;
unsigned char count = 0x00;

enum State1{Start, On}states1;
enum State2{Start1, On1}states2;
enum Stateo{Starto, Ono}stateso;

void ThreeLEDsSm(){
	
	switch(states1){ // Transitions
	case Start:
	states1=On;
	break;

	case On:
	states1 = On;
	break;

	default:
	break;
	}
	switch(states1){
	case Start:
	break;

	case On:
	if(cnt == 0x00){
	threeLEDs = 0x01;
	cnt++;
	}else if(cnt == 0x01){
	threeLEDs = 0x02;
	cnt++;
	}else if (cnt == 0x02){
	threeLEDs = 0x04;
	cnt = 0;
	}
	break;


	}
}


void BlinkingLEDSM(){
	
	switch (states2){
		case Start1:
		states2 = On1;
		break;

		case On1:
		states2 = On1;
		break;

		default:
		break;
	} 

	switch (states2){
		case Start1:
		break;

		case On1:
		if(count == 0x00){
			blinkingLED = 0x00;
			count++;
		}else if (count == 0x01){
			blinkingLED = 0x08;
			count = 0x00;
		}
		break;
}
}

void CombineLEDsSM(){
	
	switch(stateso){
		case Starto:
		stateso = Ono;
		break;

		case Ono:
		stateso = Ono;
		break;

		default:
		break;
	}
	switch(stateso){
		case Starto:
		break;

		case Ono:
		out = threeLEDs|(blinkingLED & 0x08);


		break;
	}
	PORTB = out;
}


int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00; //B is set to output
	states1 = Start;
	states2	=Start1;
	stateso =Starto;
	TimerSet(1000);
	TimerOn();
	

	
	while(1) {
		
		ThreeLEDsSm();
		BlinkingLEDSM();
		CombineLEDsSM();
		
		// Wait 1 sec
		while (!TimerFlag);
		TimerFlag = 0;
		
	}
}


