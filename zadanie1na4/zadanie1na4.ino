int interval;

void setup() {
  pinMode(12, OUTPUT);
  interval = 200;
}



void flash(int pin, int pdelay)
{
 digitalWrite(pin, HIGH);
 delay(pdelay);
 digitalWrite(pin, LOW);
}
void dot(int pin)
{
  flash(pin, interval);
  delay(interval);
}
void dash(int pin)
{
  flash(pin, interval*3);
  delay(interval);
}
void space(int pin)
{
  delay(interval*2); 
}

void loop() {
  //P
  dot(12);
  dash(12);
  dash(12);
  dot(12);
  
  space(12);
  //K
  
  dash(12);
  dot(12);
  dash(12);
  
  space(12);
}

