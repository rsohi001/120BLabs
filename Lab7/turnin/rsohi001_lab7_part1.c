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
enum States{Init, Add, Sub, Pause, Reset}state;
unsigned char count = 0;

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
          tempB = 0;
	    LCD_ClearScreen();
	    LCD_WriteData(0 + '0');
            break;
        case Add:
            if (tempB < 9 && count == 10) {
                tempB = tempB + 1;
                count = 0;
            }
            count += 1;
	    LCD_ClearScreen();
	    LCD_WriteData(tempB + '0');
            break;
        case Sub:
            if (tempB > 0 && count == 10) {
                tempB = tempB - 1;
                count = 0;
            }
            count++;
	    LCD_ClearScreen();
	    LCD_WriteData(tempB + '0');
            break;
        case Reset:
            count = 0;
            tempB = 0;
	    LCD_ClearScreen();
	    LCD_WriteData(0 + '0');
            break;
        case Pause:
            count = 10;
            break;
	    LCD_ClearScreen();
	    LCD_WriteData(tempB + '0');
        default:
            break;
    }

    PORTB = tempB;

}

int main(void)
{   
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    LCD_init();
    LCD_Cursor(1);
    TimerSet(10);
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
