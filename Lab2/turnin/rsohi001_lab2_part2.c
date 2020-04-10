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
	DDRC = 0xFF; PORTC = 0x00; //output
	
	unsigned char tempA, tempC;
    /* Insert your solution below */
    while (1) {
	tempA = PINA & 0x0F;
	tempC = 0xFF;
	if(tempA == 0x0F){
		tempC = tempC & 0x00;
	}
	if((tempA == 0x0E) || (tempA == 0x0D) || (tempA == 0x0B) || (tempA == 0x07))
		tempC = 0x01;
	if((tempA == 0x0C) || (tempA == 0x0A) || (tempA == 0x09) || (tempA == 0x06) || (tempA == 0x05) || (tempA == 0x03))
		tempC = 0x02;
	if((tempA == 0x08) || (tempA == 0x04) || (tempA == 0x02) || (tempA == 0x01))
		tempC = 0x03;
	if(tempA == 0x00)
		tempC = 0x04;
	PORTC = tempC;
    }
    return 1;
}
