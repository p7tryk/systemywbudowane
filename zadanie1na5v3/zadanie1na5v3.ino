#define LED 12

int interval;
char * text = "abcdef fedcba";


void setup() {
  pinMode(12, OUTPUT);
  interval = 500;
}

char decode[][6] = {
  {".-***"}, //a
  {"-...*"}, //b
  {"-.-.*"}, //c
  {"-..**"}, //d
  {".****"}, //e
  {"..-.*"}  //f
};

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



void printMorse(char * string)
{
  for(int n=0; n<sizeof(string); n++)
  {
     if(string[n] == '.')
      dot(LED);
     else if(string[n] == '-')
      dash(LED);
  }
}


void loop() {
  
  
  for(int i=0; i<sizeof(text);i++)
  {
    if(text[i]== ' ')
      space(LED);
    
    printMorse(decode[text[i]-97]);
  }
  space(12);
}

