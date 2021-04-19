/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 11  Exercise 1
*
objective -
Modify the keypad code to be in an SM task. Then, modify the keypad SM to utilize the simple task scheduler format. 
All code from here on out should use the task scheduler. 

*    I acknowledge all content contained herein, excluding template
*     or example code, is my own original work.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "bit.h"
#include "timer.h"
#include "io.c"
#include "io.h"
#include "keypad.h"
#include "scheduler.h"

//Global Shared variables

unsigned char tempb = 0x00;

enum SMSKEYboard{outputs};
int SMkeyTick(int state){
	unsigned char x;

	/* Replace with your application code */
	x = GetKeypadKey();
	switch(state){

		case outputs:
		switch (x){
			
			case '\0' : tempb = 0x1F; break;
			case '1' : tempb = 0x01; break;
			case '2' : tempb = 0x02; break;
			case '3' : tempb = 0x03; break;
			case '4' : tempb = 0x04; break;
			case '5' : tempb = 0x05; break;
			case '6' : tempb = 0x06; break;
			case '7' : tempb = 0x07; break;
			case '8' : tempb = 0x08; break;
			case '9' : tempb = 0x09; break;
			case 'A' : tempb = 0x0A; break;
			case 'B' : tempb = 0x0B; break;
			case 'C' : tempb = 0x0C; break;
			case 'D' : tempb = 0x0D; break;
			case '*' : tempb = 0x0E; break;
			case '0' : tempb = 0x00; break;
			case '#' : tempb = 0x0F; break;
			default: tempb = 0x1B; break; // should never occur.  Middle LED off.

		}
		PORTB = tempb;
		state = outputs;
		break;
	}
	return state;
}
int main()
{
	// Set Data Direction Registers
	// Buttons PORTA[0-7], set AVR PORTA to pull down logic
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0x00;
	// Period for the tasks
	unsigned long int SMkeyTick_calc = 20;

	//Calculating GCD
	unsigned long int tmpGCD = 10;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMkeyTick_period = SMkeyTick_calc/GCD;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = SMkeyTick_period;//Task Period.
	task1.elapsedTime = SMkeyTick_period;//Task current elapsed time.
	task1.TickFct = &SMkeyTick;//Function pointer for the tick.


	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	
	return 0;
}