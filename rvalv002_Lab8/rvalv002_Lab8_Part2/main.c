/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 8  Exercise 2
*
objective -
A photoresistor is a resistor whose resistance varies based on how much light the photoresistor detects.
 An additional resistor needs to be connected in parallel with the photoresistor.
  Without the additional resistor, results from ADC will be too small to observe.
   A 330 ohm resistor is chosen because it is common in the lab kits. 
   Connect the photoresistor to the microcontroller according to the diagram below.


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
unsigned char tempb = 0x00;
unsigned char tempd = 0x00;


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
tempd = (char)(tempADC >> 14);

PORTB = tempb;
PORTD = tempd;







}
}


