/*
 * keypad.h
 *
 * Created: 2022-04-04 오전 10:36:18
 *  Author: COMPUTER
 */ 

#include <avr/io.h>
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPADPIN	DDRA //0b 1111 1000
#define KEYPADDATA	PORTA
#define ROWPIN		PORTA		//출력
#define ROW_OUT_COL_IN	0xF8
#define COLUMN		PINA		//입력

#define COL0	0x01
#define COL1	0x02
#define COL2	0x04
#define ROW0	0x08
#define ROW1	0x10
#define ROW2	0x20
#define ROW3	0x40

void init_keypad();		//keypad 초기화
unsigned char keyscan();//키스캔 함수



#endif /* KEYPAD_H_ */