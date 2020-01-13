/*    Partner Name & E-mail: Bryant Palominob palo005@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab 2  Exercise 3
 *    
 *    I acknowledge all content contained herein, excluding template 
 *     or example code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char cntavail = 0x00; // # of spaces available in binary
	
	while (1)
	{
		
		tmpA = PINA & 0x0F; //Read input
		
		if(tmpA & 0x08){ // if PA3 = 1
			cntavail = cntavail - 1;
		}
		if (tmpA & 0x04){ // if PA2 = 1
			cntavail = cntavail - 1;
		}
		if (tmpA & 0x02){ // if PA1 = 1
			cntavail = cntavail - 1;
		}
		if (tmpA & 0x01){ // if PA0 = 1
			cntavail = cntavail - 1;
		}

		if(cntavail == 0x00){
		cntavail = 0x80; 
		}

	PORTC = cntavail;
	}
	

}

