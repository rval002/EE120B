/*  Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 4  Exercise 4
*
objective -
(Challenge) Extend the above door so that it can also be locked by entering the earlier code. 




*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>

//Global Variables
unsigned char tempA =0x00; // Temp Variable holding A value
unsigned char tempAH =0x00; // Temp Variable holding A value High nibble

unsigned char tempB =0x00; // Temp Variable holding B value

//Bit Access functions
inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}
inline unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}





//State Machine enum
enum States {Start, Wait, Press, Check, Unlock, wait2, press2 } State;

int Tick(void){
	switch(State){ //Transition States
		case Start:
		if(1){ // Always goes to way state on initialization
			State = Wait;
		}
		break;

		case Wait:
		if(tempA == 0x04){ // If # pressed move on to press state
			State = Press;
		}else
		State = Wait;
		break;

		case Press:
		if(tempA == 0x00){ // If all buttons released code can be entered
			State = Check;
			}else if(tempA == 0x04){ // if # is Being held wait till released
			State = Press;
		}
		else{ //If any other multi combination, got back to wait
			State = Wait;
		}
		break;

		case Check:
		if(tempA == 0x02){ //  if Y is pressed Move on to Unlock State
			State = Unlock;
			} else if( tempA == 0x00){ // If no buttons are pressed Stay in check
			State = Check;
		}
		else{ // If any other multiple combination Go back to the Wait state
			State = Wait;
		}
		break;

		case Unlock:
		if (tempAH == 0x80){ // If Button from inside is pressed go to wait state
			State = Wait;
		}
		else if(tempA == 0x04){
			State = wait2;
		}
		else{ // Stay in Unlocked state until inside button is pressed
			State = Unlock;
		}


		break;
		case  wait2:
		if (tempA == 0x02)
		{
			State = press2;
		}
		else if(tempAH == 0x80)
		{
			State = Wait;
		}
		else if (tempA == 0x00 ){
			State = wait2;
		}
		else{
			State = Unlock;
		}
		break;

		case press2:
		if((tempA == (0x04)) || (tempAH == (0x80))){
			State = Wait;
		}
		else if(tempA == 0x00){
			State = press2;
		}
		else{
			State = Unlock;
		}

		default:
		State = Start;
		break;
	}

	switch(State){//Actions
		case Start:
		break;
		case Wait:
		tempB = 0x00; //Door Locked
		break;

		case Press:

		break;
		case Check:

		break;
		case Unlock:


		tempB = 0x01; //Door Unlocked


		break;

		case press2:
		break;
		case  wait2:



		break;
	}

	tempA = PINA & 0X0F;
	tempAH = PINA & 0XF0;
	PORTB = tempB;
	return 0;
}
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; //Configure port B's 8 pins as outputs, init to 0

	tempA = PINA & 0x0F; // Reads low input A
	tempAH = PINA & 0xF0; // Reads high input A
	tempB = 0x00; // Initialize To locked


	
	while (1)
	{
		Tick();
		PORTB = tempB;
	}
}

