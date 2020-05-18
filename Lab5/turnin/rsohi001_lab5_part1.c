/*Lab Demo Link (All Videos): https://drive.google.com/drive/folders/1B_x9TI1NKMIPMK61ckT5ja818MzGXYC2?usp=sharing
*/

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

int main(void) {
     /* Insert DDR and PORT initializations */
  	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tempA, tempB, tempC;
    /* Insert your solution below */
    while (1) {
	tempA = ~PINA & 0x0F;
	tempC = 0;
	if(tempA == 0)
		tempC = 0x40;
	if((tempA == 1) || (tempA == 2))
		tempC = 0x60;
	if((tempA == 3) || (tempA == 4))
                tempC = 0x70;
	if((tempA == 5) || (tempA == 6))
                tempC = 0x38;
	if((tempA == 7) || (tempA == 8) || (tempA == 9))
                tempC = 0x3C;
	if((tempA == 10) || (tempA == 11) || (tempA == 12))
		tempC = 0x3E;
	if((tempA == 13) || (tempA == 14) || (tempA == 15))
                tempC = 0x3F;	
	PORTC = tempC;	
    }
    return 1;
}
