/*	Author: rahulsohi99
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

unsigned char tempB;
unsigned char tempD;
unsigned short ADC_Var;
unsigned short MAX;

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

    /* Insert your solution below */
    ADC_init();

	MAX = 0x0F;

    while (1) {	
	ADC_Var = ADC;
	if(ADC_Var > (MAX/2)){
		PORTD = 0x01;
}
	else
		PORTD = 0x00;
    }
    return 1;
}
