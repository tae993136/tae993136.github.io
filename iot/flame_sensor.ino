/*flame_sensor.ino */
#include <Keypad.h> //키패드헤더
#include <string.h>

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] =   //4x4키패드 초기화행렬 
{
  {'1', '5', '9', 'C'},
  {'2', '6', '0', 'D'},
  {'3', '7', 'A', 'E'},
  {'4', '8', 'B', 'F'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //행 핀번호 
byte colPins[COLS] = {6, 7, 8, 9}; //열 핀번호 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //키패드 초기화 

char call[10] = {'0',}; //키패드로 입력받을 배열 
int i = 0;              //call배열 인덱스 
char emergency[10] = {'1','1','9'}; //call배열과 비교할 배열 

void setup ()
{
  Serial.begin(115200);
  pinMode(A0, INPUT); //불꽃감지 센서 
  pinMode (11, OUTPUT); //부저 
  pinMode (10, OUTPUT); //LED
}

void loop ()
{
  char key = customKeypad.getKey();//키패드로 입력된 값 저장 
  
  if (key != NO_KEY) {    
    call[i] = key;      //key에 저장된 값을 call에 저장 
    i++;                //call의 인덱스 증가 
  }
  
  int light = analogRead (A0); //감지된 불꽃 값 저장 
    
  if (light < 800) {       //light가 800보다 작으면 부저와 LED켜짐 
    digitalWrite (11, HIGH);
    digitalWrite (10, HIGH);
  }
  else if(!strcmp(call,emergency)) {//키패드에서 1,1,9가 입력되면 부저와 LED중지 
    digitalWrite (11, LOW);
    digitalWrite (10, LOW);
  }
  
if (i >= 3) {           //call의 인덱스가 3이상일 경우 
  i = 0;                //새로운 번호 입력을 위한 인덱스 초기화 
  for(int j = 0; j<3; j++){ //call배열 초기화 
    call[j] = '0';
    }
  }

}
