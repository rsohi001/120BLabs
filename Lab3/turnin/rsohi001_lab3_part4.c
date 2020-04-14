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

int main(void) {
    /* Insert DDR and PORT initializations */
  	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tempA, tempB, tempC;
    /* Insert your solution below */
    while (1) {
	tempA = PINA & 0xF0;
	tempB = 0;
	tempA = tempA >> 4;
	tempB = tempA;
	PORTB = tempB;

	tempA = PINA & 0x0F;
	tempC = 0;
	tempA = tempA << 4;
	tempC = tempA;	
	PORTC = tempC;	
    }
    return 1;
}
