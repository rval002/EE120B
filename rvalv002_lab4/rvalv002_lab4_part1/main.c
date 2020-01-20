/*    Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab 4  Exercise 1 
 *    
	objective -
	PB0 and PB1 each connect to an LED, and PB0's LED is initially on.
	Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED,
	staying that way after button release. Pressing the button again turns off PB1's LED 
	and turns on PB0's LED.



 *    I acknowledge all content contained herein, excluding template 
 *     or example code, is my own original work.
 *
 */

#include <avr/io.h>

//Global Variables
unsigned char tempA =0x00; // Temp Variable holding A value
unsigned char B =0x00; // Temp Variable holding B value

//Bit Access functions
inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}
inline unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


enum B_States {B_Start,B_PressOn,B_PressOff,B_ReleaseOn,B_ReleaseOff} B_State ;

int Tick(void){
	switch(B_State) { //Transition States
		case B_Start:
		if(1){
		B_State=B_PressOn;
		}
		break;
		case B_PressOn:
		if(tempA == 0x01){ // If Button Pressed while B0 on
			B_State = B_ReleaseOn; // Enter ReleaseOn State
		}
			else {
			B_State = B_PressOn; //If Button Not pressed stay here until button pressed
		}
		break;
		case B_PressOff:
		if(tempA == 0x01){ // If Pressed while B0 is off
			B_State = B_ReleaseOff; //Enter ReleaseOfff State
		}
			else {
			B_State = B_PressOff; // if button not pressed Stay Here
		}
		break;
		case B_ReleaseOn:
		if(tempA == 0x01){ // If button is not being held
			B_State = B_ReleaseOn;  // stay here
		}
			else{
			B_State = B_PressOff; // Enter Press off State
		}
		break;
		case B_ReleaseOff:
		if(tempA == 0x01){ // If button is not being held
			B_State = B_ReleaseOff;  // stay here
		}
		else{
			B_State = B_PressOn; // Enter Press off State
		}
		break;
		default:
		B_State = B_Start;
		break;
}
	switch(B_State) {//Actions
		case B_Start:
		break;
		case B_PressOn:
		 B = 0x02; //Turns off B0 and turns on B1
		break;
		case B_PressOff:
		 B = 0x01; //Turns off B0 and turns on B1
		break;
		case B_ReleaseOn:
		break;
		case B_ReleaseOff:
		break;
	}
	tempA = PINA & 0xFF; // Reads from A
	PORTB = B;
	return 0;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as Outputs, initializes to 0
	tempA = PINA & 0xFF; // Reads from A
	PORTB = 0x01; // Initializes B0 to on
	B= 0x01;
	B_State=B_Start;


    
    while (1) 
    {
	
	Tick();
	
    }
	
}

