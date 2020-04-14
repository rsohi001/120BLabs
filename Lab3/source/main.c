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
  	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	unsigned char tempD, tempB;
	unsigned int total;
    /* Insert your solution below */
    while (1) {
	tempD = PIND;
	tempB = PINB & 0x01;
	total = tempD << 1;
	total = total + tempB;
	tempB = 0x00;
	if(total >= 70)
	tempB = tempB + 0x02;
	if((total > 5) && (total < 70))
	tempB = tempB + 0x04;
	PORTB = tempB; 
	
    }
    return 1;
}
