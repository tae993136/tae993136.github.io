/*
* keypad_main.c
*
* Created: 2022-04-04 오후 3:10:35
*  Author: COMPUTER
*/
#define F_CPU 7372800
#include "keypad.h"			//키패드 헤더파일
#include "lcd.h"			//lcd 헤더파일
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

unsigned char mot_tbi[]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};	//스탭 모터 배열



int main()
{
	DDRC = 0xff;		//lcd사용을 위한 출력 포트 설정
	DDRB = 0xff;		//led사용을 위한 출력 포트 설정
	DDRF = 0x0f;		//스탭 모터 
	DDRD = 0x01;		//cnt 
	
	lcdInit();			//lcd 초기화
	lcdClear();			//lcd 화면 지움
	init_keypad();		//키패드 초기화
	
	char* correct = "open door!";	//맞는 번호 입력 시 출력할 문자열
	char* wrong = "try again";		//틀린 번호 입력 시 출력할 문자열
	char* password = "2580";		//비교할 번호
	
	char pass_in[10] = "";			//입력할 문자열
	int i = 0;						//배열 인덱스
	char newkey = 0;				//이전 키패드 입력 변수
	char key = 0;					//키패드 입력 변수
	char led = 1;					//led변수
	
	while(1){
		newkey = keyscan();			
		lcdGotoXY(0,0);				//0,0부터 출력
		_delay_ms(10);
		lcdPrintData("password",8); //lcd에 password 출력

		if(newkey != '\0' && newkey != key && newkey != '*'){	// 기본 출력 값 \0이 아니고,
																// 이전 입력값과 새 입력이 다르고, *을 입력하지 않은 조건		
																	
			lcdGotoXY(i,1);										// lcd 0행 i열부터 출력
			key = newkey;										
			lcdDataWrite('*');									//키패드 입력 시 *출력
			pass_in[i++] = key;									//입력 배열에 key저장
		}
		
		if(keyscan()=='*'){										//*을 눌렀을 때
			if(strlen(pass_in)==4){								//비밀번호의 길이가 4일 때
				
				if(password[0]==pass_in[0]&&password[1]==pass_in[1]  //각 자리가 미리 설정된 번호와 같으면
				&&password[2]==pass_in[2]&&password[3]==pass_in[3]){
					lcdGotoXY(0,0);									 
					_delay_ms(20);			
					lcdPrintData(correct,strlen(correct));			 //lcd에 open door출력
					for(int j = 0; j < 8; j++){						 //led가 왼쪽부터 오른쪽으로 한칸씩 이동	
						PORTB = led;						
						_delay_ms(150);
						led <<= 1;
						_delay_ms(5);
						
					}
					led = 0x80;
					for(int k = 0; k < 6; k++){			//모터가 돌아감(열림)
						for(int l = 0; l < 8; l++ ){
							PORTF = mot_tbi[l];
							_delay_ms(20);
						}						
					}
					_delay_ms(2000);					//약 2초 후
					for(int j = 0; j < 8; j++){			//led가 오른쪽에서 왼쪽으로 이동
						PORTB = led;
						_delay_ms(150);
						led >>= 1;
					}
					PORTB = 0;
					
					for(int k = 0; k < 6; k++){			//모터가 제자리로 돌아감(잠김)
						for(int l = 7; l > 0; l--){
							PORTF = mot_tbi[l];
							_delay_ms(20);
						}
					}			
					for(int k =0; k < 10; k++){			//키패드 입력배열 초기화
						pass_in[k] = 0;
					}
					led = 1;
					i = 0;
					
					_delay_ms(2000);					
					
					
				}
				/*입력 값이 같지 않을 때*/
				else{
					lcdGotoXY(0,0);
					_delay_ms(20);
					lcdPrintData(wrong,strlen(wrong));		//try again 출력
					
					for (int k = 0; k < 3; k++)				//led가 세번 깜빡거림
					{
						PORTB = 0xff;
						_delay_ms(200);
						PORTB = 0x00;
						_delay_ms(200);
					}
					_delay_ms(2000);						//2초 뒤 재 입력
					
					for(int k =0; k < 10; k++){
						pass_in[k] = 0;
					}
					
					i = 0;
				}
				lcdClear();
			}
			/*입력된 값이 4자리가 아닐 때*/
			else{
				lcdGotoXY(0,0);
				_delay_ms(20);
				lcdPrintData(wrong,strlen(wrong));
				
				for (int k = 0; k < 3; k++)
				{
					PORTB = 0xff;
					_delay_ms(200);
					PORTB = 0x00;
					_delay_ms(200);
				}
				_delay_ms(2000);
				
				for(int k =0; k < 10; k++){
					pass_in[k] = 0;
				}
				
				i = 0;
			}
			lcdClear();
			
		}
		
	}
}
