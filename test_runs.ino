#include <Wire.h> 
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

                                              // declarations of the variables 

int plus = 7;
int minus = 12;
int set = 8;
int pause_play = 2;
bool btn_plus,btn_minus,btn_set,btn_pause_play;

int time_seconds = 0;
unsigned long A;
unsigned long B;

                                              //Setup function

void setup() {
  Serial.begin(115200);
  matrix.begin(0x70);

  pinMode(plus, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP); 
  pinMode(minus, INPUT_PULLUP);
  pinMode(pause_play, INPUT_PULLUP);

}

                                              //Time adjusting function
                                              
void set_time()
{
  while(digitalRead(set) == 1)
  {
    if(digitalRead(plus) == 0)
    {
      time_seconds += 15;
      delay(150);
      }
    
    if(digitalRead(minus) == 0)
    {
      time_seconds -= 15;
      delay(150);
      }
      Serial.println(time_seconds);
    }
}

                                              //Function to start printing time
  
void start_print()
{
  for(int i = time_seconds; i>=0; i--)
  {
     
    if(digitalRead(pause_play)==0)
    {
      delay(50);
      while(digitalRead(pause_play)==1);
      }
    Serial.println(i);
    A = millis();
    B = millis();
    while(((B-A)/1000)!=1)
    { B = millis();
      if(digitalRead(pause_play)==0)
      {
        delay(250);
        Serial.println("just paused");
        bool btn_val = digitalRead(set);
        while(btn_val==1)
        {
          Serial.println("in pause");
          btn_val = digitalRead(set);
          if(digitalRead(pause_play)==0)
          {
            delay(250);
            i = -1;
            break;
            }
          }
          delay(250);
          Serial.println("left pause");
        A = millis();
        B = millis();
      }
      
    }
  }
}

void start_timer()
{
  set_time();
  Serial.println("outta loop");
  start_print();
  Serial.println("outta loop 2");
  }

void loop() {
  start_timer();
//  int a;
//  a = (1000*btn_plus)+(100*btn_minus)+(10*btn_set)+(1*btn_pause_play);
//  Serial.println(a);
  

}
