#include <Servo.h>  

Servo servoblau;

void setup() 
{ 
  servoblau.attach(8);
} 

void loop() 
{ 
  for (int i=0;i<=180;i=i+20){
    servoblau.write(i);
    delay(1000);
  }
  delay(3000);
  for (int i=180;i>=0;i=i-20){
    servoblau.write(i);
    delay(1000);
  }
  delay(3000);
}
