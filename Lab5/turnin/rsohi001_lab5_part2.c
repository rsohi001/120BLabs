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

enum States {Start, Init, Add_P, Add_R, Sub_P, Sub_R, Zero} state;

void Tick() {
    
    unsigned char tempA = ~PINA;
    unsigned char tempC = PORTC;

    switch(state) {
        case Start:
            state = Init;
            break;

        case Init:
            if (tempA == 1)
                state = Add_P;
            if (tempA == 2) 
                state = Sub_P;
            if (tempA == 3)
                state = Zero;
            break;

        case Add_P:
            state = Add_R;
            break;

        case Add_R:
            if (tempA == 0)
                state = Init;
            if (tempA == 1)
                state = Add_R;
            if (tempA == 3)
                state = Zero;
            break;

        case Sub_P:
            state = Sub_R;
            break;

        case Sub_R:
            if (tempA == 0)
                state = Init;
            if (tempA == 2)
                state = Sub_R;
            if (tempA == 3)
                state = Zero;
            break;

        case Zero:
            if (tempA == 0)
                state = Init;
            else
                state = Zero;
            break;

        default:
            state = Init;
            break;
    }

    switch(state) {
        case Add_P:
            if (tempC < 9)
                tempC = tempC + 1;
            break;

        case Sub_P	:
            if (tempC > 0)
                tempC = tempC - 1;
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
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
