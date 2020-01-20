/*    Partner Name & E-mail: Bryant Palominob bpalo005@ucr.edu
 *    Lab Section: 021
 *    Assignment: Lab 3  Exercise 1 
 *    
 *    I acknowledge all content contained herein, excluding template 
 *     or example code, is my own original work.
 */ 

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tempA = 0x00; // Temporary variable to hold the value of A
	unsigned char tempB = 0x00; //Temporary variable to hold the value of B
	unsigned char totalCnt = 0x00; // Holds the Total count 
	while(1)
	{
	totalCnt=0;
		tempA = PINA & 0xFF; // Reads From A
		tempB = PINB & 0xFF; // Reads From B
		
		for( char i=0 ; i<=8; i++){
			
			if( GetBit(tempA,i)){
				totalCnt++;
			}
			if( GetBit(tempB,i)){
				totalCnt++;
			}
			
		}
		
		PORTC = totalCnt; 
		
		
	}
	return 0;
}