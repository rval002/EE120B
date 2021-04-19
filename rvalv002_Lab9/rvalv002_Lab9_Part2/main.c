/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 9  Exercise 2
*
objective -




*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>

//Global variable
unsigned char button = 0x00;
unsigned char toggle = 0x00;
const double tone[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i = 0x00;


void set_PWM(double frequency) {
	
	
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency
	// changes, plays music uninterrupted.
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; //stops timer/counter
		else TCCR3B |= 0x03; // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) OCR3A = 0xFFFF;
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) OCR3A = 0x0000;
		
		// set OCR3A based on desired frequency
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; // resets counter
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


enum states { Start, Off,ON} state;

void Tick (){
	switch(state) // Transitions
	{
		case Start:
		state = Off;
		break;

		case Off:
		if(toggle){
		state = ON;

		}else{
		state = Off;
		}
		break;

		case ON:
		if (toggle){
		state = Off;
		} else {
		state = ON;
		}
		break;
		default:
		break;
	}

	switch(state) // Actions
	{
		case Start:
		set_PWM(0);
		break;

		case Off:
		set_PWM(0);
		break;

		case ON:

		if (button == 0x02 && i<8 )
		{
			i++;
		
		} else if ( button == 0x04 && i >= 0){
			i--;
		}

		set_PWM(tone[i]);

		break;

	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	toggle = ~PINA & 0x01;
	button = ~PINA & 0x06;
	PWM_on();
	
	while (1)
	{
		Tick();
	}
}



