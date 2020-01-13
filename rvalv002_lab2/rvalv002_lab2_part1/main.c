/*    Partner Name & E-mail: Bryant Palominob palo005@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab 2  Exercise 1 
 *    
 *    I acknowledge all content contained herein, excluding template 
 *     or example code, is my own original work.
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char led  = 0x00; //LED holds value of B
	while(1)
	{
		//Read input
		tmpA = PINA & 0x03;
		if(tmpA == 0x01) // PA is aaaaaa01  no light and open
		{
		led = 0x01; // LED ON
		}
		else {
		led = 0x00; // LED OFF
		}
		PORTB = led;
	}
	return 0;
}



