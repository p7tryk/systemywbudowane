#include <LiquidCrystal.h>
#define SECOND 1
#define MINUTE 60
#define HOUR (60*60)
#define TIMESTOP 1000

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int timestamp = 0;
int mode = 0;
int lastON = 0;

void setup()
{

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
	lcd.begin(16,2);
	lcd.print("Hello");
	lcd.setCursor(0,1);
	lcd.print("World!");
	delay(100);
	lcd.clear();

	test();
	timestamp = -1000;
}
//ZEGAR

struct time{
	byte hour;
	byte minute;
	byte second;
} globaltime;

int epoch;


void test()
{
	epoch = 14030;
}
void updateTime()
{
	int time;
	time = epoch / HOUR;
	globaltime.hour=time;
	
	time = epoch - time * HOUR;
	globaltime.minute = time / 60;
	
	time = time - globaltime.minute * 60;
	globaltime.second = time;
}
void incrementTime()
{
	epoch++;
}

void writeTime()
{
	/*
		HH:MM:SS
		count/set
	*/
	//lcd.clear();
	lcd.setCursor(0,0);
	if(globaltime.hour<10)
		lcd.print(0);
	lcd.print(globaltime.hour);
	
	lcd.setCursor(2,0);
	lcd.print(":");
	if(globaltime.minute<10)
		lcd.print(0);
	lcd.print(globaltime.minute);

	lcd.setCursor(5,0);
	lcd.print(":");
	if(globaltime.second<10)
		lcd.print(0);
	lcd.print(globaltime.second);
	debug();
}

int selected = 0;
const int position[] = {0,3,6};
const int interval[] = {HOUR, MINUTE, SECOND};

void blinkSelected()
{
	if(selected>2)
		selected=0;
	else if(selected<0)
		selected = 2 ;
	if(millis() - lastON > TIMESTOP)
		{
			lcd.setCursor(0,1);
			lcd.print("           ");
			lcd.setCursor(position[selected],1);
			lcd.print("^^");
			lastON=millis();
			updateTime();
			writeTime();
		}
}
void decrementCurrent()
{
	epoch -= interval[selected];
}
void incrementCurrent()
{
	epoch += interval[selected];
}

void inputTime()
{
	/* Serial.println("inputTime()"); */

	if(digitalRead(A3) == LOW)
		{
			selected++;
			delay(100);
		}
	if(digitalRead(A2) == LOW)
		{
			selected--;
			delay(100);
		}
	blinkSelected();

	if(digitalRead(A1) == LOW)
		{
			incrementCurrent();
			delay(100);
		}
	if(digitalRead(A0) == LOW)
		{
			decrementCurrent();
			delay(100);
		}
}
void debug()
{
	Serial.println(epoch);
	Serial.print(globaltime.hour);
	if(globaltime.hour<10)
		Serial.print(0);
	Serial.print(":");
	if(globaltime.second<10)
		Serial.print(0);
	Serial.print(globaltime.minute);
	Serial.print(":");
	if(globaltime.second<10)
		Serial.print(0);
	Serial.println(globaltime.second);
}


void loop()
{
	if(digitalRead(A5) == LOW)
		{
			mode=!mode;
			lcd.clear();
			writeTime();
			delay(100);
		}

	/* Serial.print("mode "); */
	/* Serial.println(mode); */
		
	
	if(mode == 0)
		{
		if(millis()-timestamp > TIMESTOP)
			{
				updateTime();
				writeTime();
				incrementTime();
				timestamp = millis();
			}
		}
	else
		inputTime();


}
