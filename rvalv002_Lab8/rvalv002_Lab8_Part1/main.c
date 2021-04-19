/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 8  Exercise 1
*
objective -
Make sure your breadboard is wired according to the prelab.
The potentiometer is used to adjust the voltage supplied to the microcontroller for ADC .
Design a system that reads the 10-bit ADC result from the ADC register, and displays the result on a bank of 10 LEDs



*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>

//Initates analog to digital conversion with the ATMega1284
void ADC_init() {
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) ;
}
//Global variables
unsigned short tempADC = 0x0000;
unsigned char tempb = (char)tempADC;
unsigned char tempd = (char)tempADC;


int main(void)
{
		DDRA = 0x00; PORTA = 0xFF; // Sets as input
		DDRB = 0xFF; PORTB = 0x00; // Sets as outputs and intitaes to 0's
		DDRD = 0xFF; PORTD = 0x00; // Sets as outputs and intitaes to 0's
   

		ADC_init();

    while (1) 
    {
	 tempADC = ADC;
	 
	 tempb = (char)(tempADC >> 4);
	 tempd = (char)(tempADC >> 8);

	 PORTB = tempb;
	 PORTD = tempd;

	 
	
	 



    }
}

