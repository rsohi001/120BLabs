/*	Author: rsohi001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{Start, Init, Plus_P, Plus_R, Minus_P, Minus_R, Zero}state;

void Tick(){
	unsigned char tempA = PINA;
	unsigned char tempC = PORTC;
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(tempA == 1)
				state = Plus_P;
			if(tempA == 2)
				state = Minus_P;
			if(tempA == 3)
				state = Zero;
			break;
		case Plus_P:
			state = Plus_R;
			break;
		case Plus_R:
			if(tempA == 0)
				state = Init;
			else if(tempA == 1)
				state = Plus_R;
			else if(tempA == 3)
				state = Zero;
			break;
		case Minus_P:
			state = Minus_R;
			break;
		case Minus_R:
			if(tempA == 0)
				state = Init;
			else if(tempA == 2)
				state = Minus_R;
			else if(tempA == 3)
				state = Zero;
		case Zero:
			state = Zero;
			break;
		default:
			state = Init;
			break;
	}
	
	switch(state){
		case Plus_R:
			if(tempC < 9)
				tempC = tempC +1;
			break;
		case Minus_R:
			if(tempC > 0)
				tempC = tempC -1;
			break;
		case Zero:
			tempC = 0;
			break;

		default:
			break;
	}
	PORTC = tempC;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
    while(1){
	Tick();
    }
    return 1;
}
