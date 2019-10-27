#include <Arduino.h>
#include "TM1637.h"
void setup();
void loop();
void CalculaDigitos( int Num);
void CambiaEstadoLuz();
void ContarTiempo();
#line 1 "src/sketch.ino"
//https://www.prometec.net/display-con-interface/


//#include "TM1637.h"
#define CLK 3    
#define DIO 2

// inicializacion dispositivos
TM1637 Display1(CLK,DIO);
int8_t Digits[] = {1,2,3,4};

const int pulsadorLuz = 4;
int EstadoPulsadorLuz = 0;
int value = 0;
int cnt = 5;
//
int LED = 13 ; int boton = 4 ;
bool estado = true ;
bool estado_anterior = true ;
//
unsigned long time_ini = millis();
unsigned long time_fin = time_ini + 1000;

void setup(){  
  Display1.set();
  Display1.init() ;
  //pinMode(pulsadorLuz, INPUT);
  pinMode(boton, INPUT_PULLUP);        //Hemos eliminado R3 INPUT_PULLUP
  pinMode(LED, OUTPUT);

}

void loop(){
  CambiaEstadoLuz();
  ContarTiempo();
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

void CambiaEstadoLuz(){
  estado = digitalRead(boton);
  if (estado != estado_anterior)      //hay cambio : Han pulsado o soltado
  {
    if (estado == LOW)            //Al pulsar botón cambiar LED, pero no al soltar
          digitalWrite(LED, !digitalRead(LED));
    estado_anterior = estado ;     // Para recordar el ultimo valor
  }
}

void ContarTiempo(){
    CalculaDigitos(cnt);
    if (millis() - time_ini > 1000){
    cnt++;
    time_ini = millis();
    time_fin = time_ini + 1000;
    }
    
    //si se presiona el pulsador
    EstadoPulsadorLuz = digitalRead(boton);
    if ( EstadoPulsadorLuz == LOW) {
      cnt=cnt+1000;
    }

    //si el contador llegar a maximo vuelve a comenzar
    if (cnt > 9999) { 
      cnt=2;
    }
}