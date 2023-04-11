#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

int plus = 2;
int minus = 4;
int set = 8;
int buzzer = 9;
int counter =0;
unsigned long A;
unsigned long B;

void Print_time(int s)
{
  int m = s/60;
  int rs = (s%60);
  int print_tim = (m*100)+rs;
  int buff = print_tim;
       matrix.writeDigitNum(4,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(3,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(1,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(0,(buff%10));
       matrix.drawColon(1);
       matrix.writeDisplay();
  }

int Print_Time_s(int s)
{
  int print_tim=0;
  int m = s/60;
  int rs = (s%60)-1;
  for(int i=s-1;i>=0;i--)
  {
//    int s=9;
//    while(s>=0)
//    {
       print_tim = (m*100)+rs;
       Serial.println(rs);
       int buff = print_tim;
       matrix.writeDigitNum(4,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(3,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(1,(buff%10));
       buff = buff/10;
       matrix.writeDigitNum(0,(buff%10));
       matrix.drawColon(1);
       matrix.writeDisplay();
      A = millis();
      while(((B-A)/1000)!=1)
      {
        B = millis();
        }
        rs--;
        if(rs<0)
        {
          m--;
          rs=59;
          }

        
     // }
    }
    
   return(1); 
  }

void setup() {
//#ifndef _AVR_ATtiny85_
Serial.begin(115200);
matrix.begin(0x70);

pinMode(plus, INPUT_PULLUP);
pinMode(set, INPUT_PULLUP);
pinMode(minus, INPUT_PULLUP);
pinMode(buzzer,OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);

//setBrightness(8)
matrix.print("HELO");
  matrix.writeDisplay();
  delay(100);
}

void loop() {
Serial.println(counter);
  int buttonValue1 = digitalRead(plus);
   if (buttonValue1 == LOW){
     delay(300);
     counter+=15;
     Print_time(counter);
     
     }
int buttonValue2 = digitalRead(minus);
   if (buttonValue2 == LOW){
     delay(300);
     counter-=15;
     Print_time(counter);
   }

   int buttonVal3 = digitalRead(set);
   if (buttonVal3 == LOW)
   {
        counter--;
        while(counter>=0)
        {
          Print_time(counter);
          A = millis();
          while(((B-A)/1000)!=1)
          {
            B = millis();
          }
          counter--;
         }     
          for(int i =0;i<5;i++)
          {
            matrix.drawColon(1);
            matrix.writeDisplay();
            tone(buzzer,440);
            delay(500);
                        
            matrix.drawColon(0);
            matrix.writeDisplay();
            noTone(buzzer);
            delay(500);
            }
            counter=0;
         }

         
}
