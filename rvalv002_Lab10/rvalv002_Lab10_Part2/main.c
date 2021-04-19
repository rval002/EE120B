/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 10  Exercise 2
*
objective -
Modify the above example so the threeLEDs light for 300 ms, while blinkingLEDÅfs LED still blinks 1 second on and 1 second off.



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
	unsigned long T_elapsedTime = 0;
	unsigned long B_elapsedTime = 0;
	unsigned long C_elapsedTime = 0;
	const unsigned long period = 100;

	DDRB = 0xFF;
	PORTB = 0x00; //B is set to output
	states1 = Start;
	states2	=Start1;
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
		
		
		
		// Wait 1 sec
		while (!TimerFlag);
		TimerFlag = 0;
		T_elapsedTime += period;
		B_elapsedTime += period;
		C_elapsedTime += period;
		
	}
}


