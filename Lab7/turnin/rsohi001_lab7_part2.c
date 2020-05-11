 /*	Author: rahulsohi99
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <avr/interrupt.h>
#include "io.h"
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
enum States{Init, S_1, S_2, S_2A, S_3, AY0, AN0}state;
unsigned char score = 0;

void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M)
{
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
				if(score > 0)
				score--;
			}
			else
				state = S_2;
			break;
		case S_2:
			if(A0){
				tempB = PORTB;
				state = AY0;
				score++;
			}
			else
				state = S_3;
			break;
		case S_3:
			if(A0){
				tempB = PORTB;
				state = AY0;
				if(score > 0)
				score--;
			}
			else
				state = S_2A;
			break;
		case S_2A:
			if(A0){
				tempB = PORTB;
				state = AY0;
				score++;
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
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			break;
		case S_2:
			PORTB = 0x02;
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			break;
		case S_3:
			PORTB = 0x04;
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			break;
		case S_2A:
			PORTB = 0x02;
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			break;
		case AY0:
			PORTB = tempB;
			if(score == 9){
			LCD_ClearScreen();
			LCD_DisplayString(1, "You Win!");
			score = 0;
			}
			break;
		case AN0:
			PORTB = tempB;
			break;
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
		default:
			PORTB = 0x01;
	}
}

int main(void)
{   
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    LCD_init();
    LCD_Cursor(1);
    TimerSet(50);
    TimerOn();
    state = Init;
    LCD_WriteData(0 + '0');
    while (1)
    {
        Tick();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}
