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
enum States{Init, S_1, S_2, S_3, S_2A, AY0, AN0} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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
	unsigned char A0 = ~PINA;
	unsigned char tempB = 0x00;
	switch(state){
		case Init:
			state = S_1;
			break;
		case S_1:
			if(A0){
				tempB = PORTB;
				state = AY0;
			}
			else
				state = S_2;
			break;
		case S_2:
			if(A0){
				tempB = PORTB;
				state = AY0;
			}
			else
				state = S_3;
			break;
		case S_3:
			if(A0){
				tempB = PORTB;
				state = AY0;
			}
			else
				state = S_2A;
			break;
		case S_2A:
			if(A0){
				tempB = PORTB;
				state = AY0;
			}
			else
				state = S_1;
			break;
		case AY0:
			if(A0){
				tempB = PORTB;
				state = AY0;
			}
			else if(!A0){
				tempB = PORTB;
				state = AN0;
			}
			break;
		case AN0:
			if(!A0){
				tempB = PORTB;
				state = AN0;
			}
			else if(A0){
				state = S_1;
			}
			break;
		default:
			state = Init;
	}

	switch(state){
		case S_1:
			PORTB = 0x01;
			break;
		case S_2:
			PORTB = 0x02;
			break;
		case S_3:
			PORTB = 0x04;
			break;
		case S_2A:
			PORTB = 0x02;
			break;
		case AY0:
			PORTB = tempB;
			break;
		case AN0:
			PORTB = tempB;
			break;
		default:
			PORTB = 0x01;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(300);
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
