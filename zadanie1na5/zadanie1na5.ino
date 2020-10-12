#define A() dot(LED); dash(LED);
#define B() dash(LED); dot(LED); dot(LED); dot(LED);
#define C() dash(LED); dot(LED); dash(LED); dot(LED);
#define D() dash(LED); dot(LED); dot(LED);


#define LED 12

int interval;
char * text = "abcd";


void setup() {
  pinMode(12, OUTPUT);
  interval = 500;
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

void printLetter(char letter)
{ 
  switch(letter)
  {
   case 'a':
    A();
   case 'b':
    B();
   case 'c':
    C();
   case 'd':
    D();  
  }
}



void loop() {

  for(int i=0; i<sizeof(text);i++)
  {
    printLetter(text[i]);
    delay(2000);
  }
  space(12);
}

