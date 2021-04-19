/*
 * rvalv002_Lab9_Part1.c
 *
 * Created: 2/8/2020 10:03:10 PM
 * Author : Toomy
 */ 

#include <avr/io.h>

//Global variable
unsigned char button = 0x00;


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


enum states { Start, Wait} state;

void Tick (){
	switch(state) // Transitions
	{
		case Start:
		state = Wait;
		break;

		case Wait:
		state = Wait;

		default:
		break;
	}

	switch(state) // Actions
	{
		case Start:
		set_PWM(0);
		break;

		case Wait:

		if ( (button == 0x00) || (button <=7)){ // If all buttons pressed or no buttons pressed do nothing
		set_PWM(0);

		}else if ( button == 0x01){
		set_PWM(261.63);
		
		}
		else if (button == 0x02){
		set_PWM(293.66);
		}
		else if (button == 0x04){
		set_PWM(329.63);
		}
		break;

	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	button = ~PINA & 0x07;
	PWM_on();
    
    while (1) 
    {
		Tick();
    }
}

