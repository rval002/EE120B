/*   Partner Name & E-mail: Oscar Carreon ocarr011@ucr.edu
*    Lab Section: 021
*    Assignment: Lab 11  Exercise 2
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
unsigned char cnt;
unsigned char tempb = 0x00;
unsigned char disp[] = "CS120B is Legend... wait for it DARY!";
//CS120B is Legend... wait for it DARY! 0-36

enum LCD_States{output};

int LCD_Tick(int state){
	


	switch(state){
		case output:
		for(int i = 0; i<=16; i++){
			LCD_Cursor(i);
			LCD_WriteData(disp[cnt]);
			cnt++;
			if(cnt >= 37){
			cnt =0;
			}
		}
		
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
	unsigned long int LCD_Tick_calc = 10;

	//Calculating GCD
	unsigned long int tmpGCD = 1;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int LCD_Tick_period = LCD_Tick_calc/GCD;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = LCD_Tick_period;//Task Period.
	task1.elapsedTime = LCD_Tick_period;//Task current elapsed time.
	task1.TickFct = &LCD_Tick;//Function pointer for the tick.


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