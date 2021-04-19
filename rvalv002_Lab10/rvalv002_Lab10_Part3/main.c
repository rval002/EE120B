/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 10  Exercise 3
*
objective -
/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 10  Exercise 2
*
objective -
To the previous exercise's implementation, connect your speaker's red wire to PB4 and black wire to ground. 
Add a third task that toggles PB4 on for 2 ms and off for 2 ms as long as a switch on PA2 is in the on position.

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
unsigned char button = 0x00;
unsigned char pwm = 0x00;
//Static
unsigned char cnt = 0x00;
unsigned char count = 0x00;

enum State1{Start, On}states1;
enum State2{Start1, On1}states2;
enum State3{Start3, Off , Pulse} states3;
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

void PulseTick(){
	button = ~PINA & 0x01;

	switch(states3){
		case Start3:
		states3 = Off;
		break;

		case Off:
		if(button){
		states3 = Pulse;
		}else{
		states3 = Off;
		}
		break;
		
		case Pulse:
		if(button){
			states3 = Off;
			}else{
			states3 = Pulse;
		}
		break;

		default:
		break
	}

	switch(states3){
		case Start3:
		break;
		
		case Off:
		pwm = 0x00;
		break;

		case Pulse:
		pwm = 0x10;

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
	unsigned long T_elapsedTime = 0;
	unsigned long B_elapsedTime = 0;
	unsigned long C_elapsedTime = 0;
	const unsigned long period = 2;
	const long P_elapsedTime = 0;

	DDRB = 0xFF;
	PORTB = 0x00; //B is set to output

	button = ~PINA & 0x01;

	states1 = Start;
	states2	=Start1;
	states3 = Start3;
	stateso =Starto;
	
	TimerSet(period);
	TimerOn();
	

	
	while(1) {
		if( T_elapsedTime >= 300){
		ThreeLEDsSm();
		T_elapsedTime =0;
		}
		if( B_elapsedTime >=1000){
		BlinkingLEDSM();
		B_elapsedTime = 0;
		}
		if (C_elapsedTime >=100)
		{
		CombineLEDsSM();
		C_elapsedTime = 0;
		}
		if (P_elapsedTime >= 2){
			PulseTick();
			P_elapsedTime=0;
		}
		
		
		
		// Wait 1 sec
		while (!TimerFlag);
		TimerFlag = 0;
		T_elapsedTime += period;
		B_elapsedTime += period;
		C_elapsedTime += period;
		P_elapsedTime += period;
		
	}
}



