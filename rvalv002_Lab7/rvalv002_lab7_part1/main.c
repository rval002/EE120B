/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 7 Exercise 1
*
objective -
Buttons are connected to PA0 and PA1. Output PORTC and PORTD drive the LCD display, initially displaying 0.
 Pressing PA0 increments the display (stopping at 9). Pressing PA1 decrements the display (stopping at 0). 
  both buttons are depressed (even if not initially simultaneously), the display resets to 0. 
  If a button is held, then the display continues to increment (or decrement) at a rate of once per second.
   Use a synchronous state machine captured in C.




*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"

//Global Variables
unsigned char tempA =0x00; // Temp Variable holding A value
unsigned char c =0x00; // Temp Variable holding c output value
unsigned char dPres =0x00; // holds value when both buttons pressed

//Bit Access functions
inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}
inline unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}



enum States {Start ,Wait ,Inc ,Dec ,Pres,Reset } State;

int Tick(void){
	switch(State){ //Transition States
		case Start:
		if(1){ // always enters Wait state
			State = Wait;
		}
		break;
		case Wait:
		if(tempA == 0x01 && (c<9)){ //if A0 pressed and less tan 9 Inc count
			State = Inc;
			c = c+1;

		}
		else if(tempA == 0x02 && c>0){ // if A0 pressed and c is greater than dec count
			State = Dec;
			c = c-1;
			} else if ((tempA == 0x03)){ // If both buttons pressed enter Prep resset
			State = Pres;
			}else{
			State = Wait;
		}

		break;
		case Inc:
		if(tempA == 0x01){ // if A0 is still held stay
			State = Inc;
			}else if(!(tempA == 0x01)){ // not held go to wait
			State = Wait;
		}
		else{ //both buttons pressed
			State = Pres;
		}

		break;
		case Dec:
		if(tempA == 0x02){ // if A0 is still held stay
			State = Dec;
			}else if(!(tempA == 0x02)){ // not held go to wait
			State = Wait;
		}
		else{ //both buttons pressed
			State = Pres;
			
			
			break;
			case Pres:
			if((tempA == 0x03)){ // If at least 1 button is being held stay
				State = Pres;
			}
			else if (!(tempA == 0x03)){ // in both depressed Reset
				State = Reset;
			}
			else{
				State = Pres;
			}
			
			break;
			case Reset:
			State = Wait;
			c = 0x00; // Reset cnt to 7

			break;

			default:
			State = Start;
			break;
		}
		switch(State){//Actions
			case Start:
			break;
			case Wait:
			
			break;
			case Inc:
			
			break;
			case Dec:
			break;
			case Pres:
			break;
			case Reset:
			break;
		}
		
	}
	tempA = ~PINA & 0xFF;
	LCD_DisplayString(1, c + '0');
	return 0;
}

int main(void)
{
	//Port Declarations
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as Outputs, initializes to 0
	DDRD = 0xFF; PORTD = 0x00; //LCD Control Lines

	// Initializes the LCD display
	LCD_init();

	

	//Initial Value Assignments
	tempA = ~PINA & 0xFF; // Reads from A
	//c= 0x07; //Holds c Temp to write to Output
	LCD_DisplayString(1, c + '0');
	//dPres = 0x00; // Initializes to 0 i.e not pressed
	State=Start;


	
	while (1)
	{
		Tick();
		
	}
	
}















