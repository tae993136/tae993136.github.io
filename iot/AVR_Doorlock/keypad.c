/*
* keypad.c
*
* Created: 2022-04-04 오전 10:36:36
*  Author: COMPUTER
*/
#define F_CPU 7372800

#include "keypad.h"
#include <util/delay.h>

void init_keypad()
{
	KEYPADPIN |= ROW_OUT_COL_IN;		//DDRA = 0xf8;
	KEYPADDATA &= ~(ROW_OUT_COL_IN);	//PORTA = 0X07;
}

unsigned char keyscan()
{
	ROWPIN = ROW0;
	_delay_ms(10);
	if(COLUMN&COL0)	return '1';
	else if(COLUMN&COL1) return '2';
	else if(COLUMN&COL2) return '3';
	
	ROWPIN = ROW1;
	_delay_ms(10);
	if(COLUMN&COL0)	return '4';
	else if(COLUMN&COL1) return '5';
	else if(COLUMN&COL2) return '6';
	
	ROWPIN = ROW2;
	_delay_ms(10);
	if(COLUMN&COL0)	return '7';
	else if(COLUMN&COL1) return '8';
	else if(COLUMN&COL2) return '9';
	
	ROWPIN = ROW3;
	_delay_ms(10);
	if(COLUMN&COL0)	return '*';
	else if(COLUMN&COL1) return '0';
	else if(COLUMN&COL2) return '#';
	
	return '\0';
	
}

