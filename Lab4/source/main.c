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

unsigned char tempA = 0x00;
unsigned char tempB = 0x00;

enum States{Init, Off_R, Off_P, On_R, On_P} state;

void Tick(){
	switch(state){
		case Init:
			state = Off_R;
			break;
		case Off_R:
			state = (tempA==0) ? Off_R: On_P;
			break;
		case On_P:
			state = (tempA==1) ? On_P: On_R;
			break;
		case On_R:
			state = (tempA==0) ? On_R: Off_P;
			break;
		case Off_P:
			state = (tempA==1) ? Off_P: Off_R;
		default:
			state = Off_R;
			break;
	}
	
	switch(state){
		case Off_R:
			tempB = 1;
			break;
		case On_P:
			tempB = 2;
			break;
		case On_R:
			tempB = 2;
			break;
		case Off_P:
			tempB = 1;
			break;
		default:
			tempB = 0;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = 0;
	Tick();
	PORTB = tempB;
    }
    return 1;
}
