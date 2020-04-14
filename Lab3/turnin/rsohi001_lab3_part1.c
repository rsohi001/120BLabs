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
	unsigned char tempA, tempB, tempC, cnt;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	cnt = 0;
	while(tempA > 0){
		cnt = cnt + (tempA & 1);
		tempA = tempA >> 1;
	}
	while(tempB > 0){
		cnt = cnt + (tempB & 1);
		tempB = tempB >> 1;
	}
	tempC = cnt;
	PORTC = tempC;	
    }
    return 1;
}
