#define LEDPIN 5
#define PHOTOSTART 6
#define PHOTOEND 697


void setup()
{
	for(int i=3;i<14;i++)
		pinMode(i, OUTPUT);

	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A0, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A0, HIGH);
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A1, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A1, HIGH);
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A2, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A2, HIGH);
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A3, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A3, HIGH);
	
	pinMode(A5, INPUT_PULLUP);
	
	Serial.begin(9600);
	reset();
}

// zmienne globalne
volatile unsigned int mode = 0;
unsigned long lastON = 0; //czas ostatniego zapalonego swiatlo
unsigned long lastOFF = 0;
bool button_pressed = 0; //opoznienie zeby nie zbierac wielokrotnuch nacisnien przycisku

unsigned int ontime = 0;
unsigned int offtime = 0;
unsigned int light = 0;


void display2Numbers(int first, int second)
{
	for(int i=0;i<5;i++)
		{
			digitalWrite(i+3,first & (1<<i) ? HIGH : LOW);
		}
	for(int i=0;i<5;i++)
		{
			digitalWrite(i+8,second & (1<<i) ? HIGH : LOW);
		}
}
void displayNumber(int number)
{
	int mask = 1;
	Serial.println(number);
	for(int i=0;i<10;i++)
		{
			digitalWrite(i+3,number & (1<<i) ? HIGH : LOW);
		}
}

void lightsensormode()
{
	light = analogRead(A4);
	
  for(int i=0;i<10;i++)
	  digitalWrite(i+3,(map(light,PHOTOSTART,PHOTOEND,0,1100)/(i+1))>100 ? HIGH : LOW);
	Serial.println("aplikacja korzystajaca z fotorezystora");
}


int currentLED = 0;
int ledbrightness[6] = {15,15,15,15,15,15};
const int pwm[6] = {11,10,9,6,5,3};
void pwmmode()
{
	if(digitalRead(A0) == LOW)
		{
			delay(30);
			currentLED++;
		}
	if(digitalRead(A1) == LOW)
		{
			delay(30);
			currentLED--;
		}
	if(digitalRead(A2) == LOW)
	  {
			delay(1);
			ledbrightness[currentLED%6]+=10;
		}
	if(digitalRead(A3) == LOW)
	  {
			delay(1);
			ledbrightness[currentLED%6]+=10;
		}
	Serial.println(currentLED);
	if(ledbrightness[currentLED]>255)
		ledbrightness[currentLED]=0;
	if(ledbrightness[currentLED]<0)
		ledbrightness[currentLED]=255;
	for(int i=0;i<6;i++)
		analogWrite(pwm[i],ledbrightness[i]);
	Serial.println("Aplikacja korzystajaca z PWM");
	
}


void speakermode()
{
	if(digitalRead(A0)==LOW)
		{
			ontime++;
			delay(100);
		}
	if(digitalRead(A1)==LOW)
		{
			ontime--;
			delay(100);
		}
	if(digitalRead(A2)==LOW)
		{
			offtime++;
			delay(100);
		}
	if(digitalRead(A3)==LOW)
		{
			offtime--;
			delay(100);
		}
	if(ontime>31)
		ontime=1;
	if(offtime<1)
		ontime=31;
	if(offtime>31)
		offtime=1;
	if(offtime<1)
		offtime=31;

	display2Numbers(ontime,offtime);
	
	if(millis()-lastON>ontime*100)
		{
			tone(2,1000);
			lastON=millis();
			Serial.println("1000khz");
		}
	else if(millis()-lastOFF>offtime*100)
		{
			tone(2,2000);
			lastOFF=millis();
			Serial.println("2000khz");
		}
	
	Serial.println("Aplikacja korzystająca z glosnika");
}
int logreduction(int input)
{
	return input;
}
void lightpwmmode()
{
	Serial.println("Aplikacja korzystająca z fotorezystora i PWM");
	light = analogRead(A4);
	Serial.print(light);
	light = map(light,6,697,0,256);
	Serial.print('\t');
	Serial.println(light);
	for(int i=0; i<6;i++)
		analogWrite(pwm[i],light);
	
			
	//digitalWrite(i+3,(map(light,6,697,0,1100)/i)>100 ? HIGH : LOW);						

}
void speakerpwmmode()
{
	Serial.println("Aplikacja korzystająca z fotorezystora i glosnika");
	light = analogRead(A4);
	Serial.print(light);
	light = map(light,PHOTOSTART,PHOTOEND,1000,30000);
	Serial.print('\t');
	Serial.println(light);
	for(int i=0; i<6;i++)
		tone(2,light);
	
			
	//digitalWrite(i+3,(map(light,6,697,0,1100)/i)>100 ? HIGH : LOW);						

}

void reset()
{
	for(int i=3;i<14;i++)
		{
			digitalWrite(i, LOW);
		}
	lastON = millis();
	lastOFF = millis();
	ontime=1;
	offtime=1;
	noTone(2);
	Serial.println(mode);
}

void loop()
{
	if(button_pressed==true)
		{
			delay(100);
			button_pressed=0;
		}
	
	// sekcja odczytu przycisków zmiany trybu pracy:
  if (digitalRead(A5) == LOW)
		{
			mode++;
			reset();
			button_pressed=1;
		}
	// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (mode%6)
		{
		case 0:
			lightsensormode();
			break;
		case 1:
			pwmmode();
			break;
		case 2:
			speakermode();
			break;
		case 3:
		  lightpwmmode();
			break;
		case 4:
		  speakerpwmmode();
			break;
		}
}
