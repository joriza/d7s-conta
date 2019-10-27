#include "TM1637.h"
#define CLK 3    
#define DIO 2

TM1637 Display1(CLK,DIO);
int8_t Digits[] = {1,2,3,4};

void setup()
   {  
       Display1.set();
       Display1.init() ;
   }

void loop()
   {
       for (int i = 0 ; i<10000 ; i++)
            {
                CalculaDigitos(i);
                delay(100);
             }
   }

void CalculaDigitos( int Num)
   {
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
