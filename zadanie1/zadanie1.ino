void setup() {
  pinMode(12, OUTPUT);
}

void flash(int pin, int pdelay)
{
 digitalWrite(pin, HIGH);
 delay(pdelay);
 digitalWrite(pin, LOW);
}
void dot(int pin)
{
  flash(pin, 500);
  delay(500);
}
void dash(int pin)
{
  flash(pin, 1500);
  delay(500);
}
void space(int pin)
{
  delay(1000); 
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

