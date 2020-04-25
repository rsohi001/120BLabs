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

enum States {Start, Init, S1, S2, S3, S4, S5} state;

void Tick() {
    
    unsigned char tempA = ~PINA;
    unsigned char tempC = PORTC;

    switch(state) {
        case Start:
            state = Init;
            break;

        case Init:
            if (tempA == 1)
                state = S1;

        case S1:
	    if(tempA == 1)
            state = S2;
            break;

        case S2:
            if (tempA == 1)
                state = S3;
            break;

        case S3:
	    if (tempA == 1)
            	state = S4;
            break;

        case S4:
            if (tempA == 1)
                state = S5;
            break;

        case S5:
            if (tempA == 1)
                state = S1;
            break;

        default:
            state = Init;
            break;
    }

    switch(state) {
        case S1:
            tempC = 0x21;
            break;

        case S2:
            tempC = 0x12;
            break;

        case S3:
            tempC = 0x0C;
            break;

	case S4:
	    tempC = 0x25;
	    break;
	
	case S5:
	    tempC = 0x3F;
     	    break;

        default:
            break;
    }
    PORTC = tempC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
