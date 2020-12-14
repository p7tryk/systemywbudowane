

#define SIZE 50
#define READ_DELAY 200
#define LED_OFFSET 3
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
}

struct state {
	bool button1 = false;
	bool button2 = false;
	bool button3 = false;
	bool button4 = false;
	int photo = PHOTOEND;
};



struct state history[SIZE];

struct state * currentstate = &history[0];


bool mode = true;

int lastON = 0;

int historylength =0;



void fetchstate()
{
	currentstate->button4 = !digitalRead(A0);
	currentstate->button3 = !digitalRead(A1);
	currentstate->button2 = !digitalRead(A2);
	currentstate->button1 = !digitalRead(A3);
	currentstate->photo = analogRead(A4);
}
void savestate()
{

	//TODO nadp
	if(millis()-lastON>READ_DELAY)
		{
			Serial.println("savemode");
			fetchstate();
			playstate();
			if(historylength>=SIZE)
				{
					historylength=0;
				}
			currentstate=&history[historylength];
			historylength++;
						
			lastON=millis();
		}

}

void playmode()
{
	if(millis()-lastON>READ_DELAY)
		{
			Serial.println("readmode");
			if(historylength>SIZE)
				{
					historylength=0;
				}
			playstate();
			currentstate=&history[historylength];
			historylength++;
			
						
			lastON=millis();
		}
}

void playstate()
{
	digitalWrite(LED_OFFSET+0,currentstate->button1);
	digitalWrite(LED_OFFSET+1,currentstate->button2);
	digitalWrite(LED_OFFSET+2,currentstate->button3);
	digitalWrite(LED_OFFSET+3,currentstate->button4);
	int light = map(currentstate->photo,PHOTOSTART,PHOTOEND,0,256);
	Serial.print(light);
	analogWrite(9, light);
	debug();
}

void debug()
{
	Serial.println("length");
	Serial.println(historylength);
	Serial.println();
	Serial.println(currentstate->button1);
	Serial.println(currentstate->button2);
	Serial.println(currentstate->button3);
	Serial.println(currentstate->button4);
	Serial.println(currentstate->photo);
}

/* template <class T> int EEPROM_writeAnything(int ee, const T& value) */
/* { */
/* 	const byte* p = (const byte*)(const void*)&value; */
/* 	unsigned int i; */
/* 	for (i = 0; i < sizeof(value); i++) */
/* 		EEPROM.write(ee++, *p++); */
/* 	return i; */
/* } */

/* template <class T> int EEPROM_readAnything(int ee, T& value) */
/* { */
/* 	byte* p = (byte*)(void*)&value; */
/* 	unsigned int i; */
/* 	for (i = 0; i < sizeof(value); i++) */
/* 		*p++ = EEPROM.read(ee++); */
/* 	return i; */
/* } */


void exportstate()
{
	Serial.print("writing to eeprom");
	for(int i=0;i<SIZE;i++)
		{
			/* EEPROM_writeAnything(0, historylength); */
			/* EEPROM_writeAnything(1, history[i]); */
		}
}
void importstate()
{
	Serial.print("reading from eeprom");
	for(int i=0;i<SIZE;i++)
		{
			/* EEPROM_readAnything(0, historylength); */
			/* EEPROM_readAnything(1, history[i]); */
		}
}


void loop()
{
	if (digitalRead(A5) == LOW)
		{
			mode=!mode;
			digitalWrite(12,!mode);
		  delay(300);

			historylength=0;
			/* if(digitalRead(A5) == LOW) //if still low (long press) write or read to eeprom */
			/* 	{ */
			/* 		if(!mode) */
			/* 			exportstate(); */
			/* 		else */
			/* 			importstate(); */
			/* 	} */
		}

	if(mode)
		{
			savestate();
		}
	else
		{
			playmode();
		}
}
