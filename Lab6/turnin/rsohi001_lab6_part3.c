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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
enum States{Init, Pause, Add, Sub, Reset} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char count = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 123;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void Tick(){
    unsigned char tempA = ~PINA;
    unsigned char tempB = PORTB;
    switch(state) {
        
	case Init:
            state = Pause;
            break;
        case Pause:
            if (tempA == 1) 
                state = Add;
            else if (tempA == 2)
                state = Sub;
            else if (tempA == 3)
                state = Reset;
            else if (tempA == 0)
                state = Pause;
            break;
	case Add:
            if (tempA == 1)
               state = Add;
            else if (tempA == 3)
                state = Reset;
            else 
                state = Pause;
            break;
        case Sub:
            if (tempA == 2) {
                state = Sub;
            }
            else if (tempA == 3)
                state = Reset;
            else
                state = Pause;
            break;
        case Reset:
            state = Pause;
            break;

    }

    switch(state) {
        case Init:
            tempB = 7;
            break;
        case Add:
            if (tempB < 9 && count == 10) {
                tempB = tempB + 1;
                count = 0;
            }
            count += 1;
            break;
        case Sub:
            if (tempB > 0 && count == 10) {
                tempB = tempB - 1;
                count = 0;
            }
            count++;
            break;
        case Reset:
            count = 0;
            tempB = 0;
            break;
        case Pause:
            count = 10;
            break;
        default:
            break;
    }

    PORTB = tempB;

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 7;
	TimerSet(10);
	TimerOn();
	state = Init;
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
