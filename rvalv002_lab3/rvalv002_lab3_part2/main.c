/*    Partner Name & E-mail: Bryant Palominob bpalo005@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab 3  Exercise 2
 *    
 *    I acknowledge all content contained herein, excluding template 
 *     or example code, is my own original work.
 */ 

#include <avr/io.h>

inline unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, intitalize to 0
	unsigned char tempA = 0x00; // Temporary variable to hold the value of A
	unsigned char tempC = 0x00; //Temporary variable to hold the value of B
	unsigned char lowLight = 0x00; // Holds PC6 Value value for low light

    while (1) 
    {
	tempA = PINA & 0x0F; //Read low nibble Input From A

	if(tempA == 0x01 ||tempA == 0x02){ // If fuel level is 1 or 2  PC5 lights up
		tempC = 0x20;
		lowLight = 0x01;
	}
	else if(tempA == 0x03 ||tempA == 0x04){ // If fuel level is 3 or 4  PC5 & 4 lights up
		tempC = 0x30;
		lowLight = 0x01;
    }
	else if(tempA == 0x05 ||tempA == 0x06){ // If fuel level is 5 or 6  PC5-3 lights up
		tempC = 0x38;
	}
	else if( tempA == 0x07 || tempA ==0x08 ||tempA== 0x09 ){ // If fuel level is 7-9 PC5-2 lights up
		tempC = 0x3C;
	}
	else if(tempA == 0x0A ||tempA== 0x0B||tempA== 0x0C){ // If fuel level is 10-12  PC5-1 lights up
		tempC = 0x3E;
	}
	else if(tempA == 0x0D ||tempA== 0x0E||tempA== 0x0F){ // If fuel level is 13-15  PC5-0 lights up
		tempC = 0x3F;
	}

	if (lowLight == 0x01){ //sets Low light fuel light on
		tempC = SetBit(tempC,6,1);
	}

	PORTC = tempC;  // Assigns out to 
	}
}

