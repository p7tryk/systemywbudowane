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

char * lettertomorse(char letter)
{ 
  switch(letter)
  {
     case 'a': 
      return "-";
     case 'b':
      return "-...";
     case 'c':
      return "-.-.";
     case 'd':
      return "-..";
  }
}

char printMorse(char * string)
{
  for(int n=0; n<sizeof(string); n++)
  {
     if(string[n] = '.')
      dot(LED);
     else if(string[n] = '-')
      dash(LED);
  }
}


void loop() {
  
  
  for(int i=0; i<sizeof(text);i++)
  {
    printMorse(lettertomorse(text[i]));
    delay(2000);
  }
  space(12);
}

