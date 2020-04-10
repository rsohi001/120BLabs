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
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0x00; PORTB = 0xFF; //input
	DDRC = 0x00; PORTC = 0xFF; //input
	DDRD = 0xFF; PORTD = 0x00; //output
	
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	unsigned char tempD = 0x00;
	unsigned short Total= 0x00;
	unsigned short diff = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	tempD = 0x00;
	diff = 0x00;
	Total = tempA + tempB + tempC;
	if(Total > 0x8C)
		tempD = tempD | 0x01;
	
	if(tempA > tempC)
		diff = tempA - tempC;

	else
		diff = tempC - tempA;

	if(diff > 0x50)
		tempD = tempD | 0x02;

	tempD = (Total & 0xFC) | tempD;
	PORTD = tempD; 
    }
    return 1;
}
