#include <Servo.h>
#include <Ethernet.h>
#include<WiFi.h>



int pin = 5;
void setup(){
    pinMode(pin, INPUT);
}

void loop()
{
    //amongus loop
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
}