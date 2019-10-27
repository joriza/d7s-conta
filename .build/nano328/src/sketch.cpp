#include <Arduino.h>
#include "TM1637.h"
void setup();
void loop();
void CalculaDigitos( int Num);
#line 1 "src/sketch.ino"
//https://www.prometec.net/display-con-interface/


//#include "TM1637.h"
#define CLK 3    
#define DIO 2

const int pulsadorPin = 4;
int valorPulsador = 0;
int value = 0;
int cnt = 5;

// inicializacion
TM1637 Display1(CLK,DIO);
int8_t Digits[] = {1,2,3,4};

void setup(){  
  Display1.set();
  Display1.init() ;
  pinMode(pulsadorPin, INPUT);
}

void loop(){
  while(cnt<10000){
    CalculaDigitos(cnt);
    delay(250);
    cnt++;
    valorPulsador = digitalRead(pulsadorPin);
    
    //si el contador llegar a maximo vuelve a comenzar
    if (valorPulsador == HIGH) { //si se presiona el pulsador
      cnt=cnt+1000;
    }

    //si el contador llegar a maximo vuelve a comenzar
    if (cnt > 9999) { 
      cnt=2;
    }
  }
}

void CalculaDigitos( int Num){
  int8_t Digit0 = Num %10 ;
  int8_t Digit1 = (Num % 100) / 10 ;
  int8_t Digit2 = (Num % 1000) / 100 ;
  int8_t Digit3 = Num  / 1000  ;
  Digits[3] = Digit0 ;
  Digits[2] = Digit1 ;
  Digits[1] = Digit2 ;
  Digits[0] = Digit3 ;
  Display1.display(Digits);
   }
