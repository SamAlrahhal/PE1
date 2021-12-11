int pin = 5;
void setup(){
    pinMode(pin, INPUT);
}

void loop()
{
    int temVar = 0;
    //amongus loop
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
    leesAlles(&temVar);
}

void leesAlles(int *alles)
{
    *alles = digitalRead(pin);
}