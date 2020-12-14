#define SIZE sizeof(action)

struct operation {
  char operand[20];
  void (*funptr)(int);
};

const struct operation action[] = {
	{"on\0",&on},
	{"off\0",&off},
	{"toggle\0",&toggle},
	{"onbelow\0",&onbelow},
	{"offbelow\0",&offbelow},
	{"togglebelow\0",&togglebelow}
};


	
void setup()
{
	for(int i=3;i<14;i++)
		pinMode(i, OUTPUT);
	Serial.begin(9600);

}




bool lights[10] = {false,true,false,true,false,true,false,true,false,true};

char operand[256];
char * argument;
int number = 0;

char buffer[256];

bool reading = true;

void toggle(int input)
{
	Serial.print("toggle ");
	Serial.println(input);
	lights[input]=!lights[input];
}

void on(int input)
{
	Serial.print("on ");
	Serial.println(input);
	lights[input]=true;
}
void off(int input)
{
	Serial.print("off ");
	Serial.println(input);
	lights[input]=false;
}
void onbelow(int input)
{
	Serial.print("onbelow ");
	Serial.println(input);
	for(input;input>=0;input--)
		lights[input]=true;
}
void offbelow(int input)
{
	Serial.print("offbelow ");
	Serial.println(input);
	for(input;input>=0;input--)
		lights[input]=false;
}
void togglebelow(int input)
{
	Serial.print("togglebelow ");
	Serial.println(input);
	for(input;input>=0;input--)
		lights[input]=!lights[input];
}


void display()
{
	for(int i=0;i<10;i++)
		digitalWrite(i+3, lights[i] ? HIGH : LOW);
}


void parse()
{
	Serial.println("parse");
	for(int i=0; i<sizeof(action);i++)
		{
			if(number<=0)
				break;
			if(!strcmp(operand,action[i].operand))
				(*action[i].funptr)(number-1); //zeby zaczynac diody byly 1-10 a nie 0-9
		}
}

void clearbuffer()
{
	for(int i=0;i<256;i++)
		buffer[i]='\n';
}

void loop()
{
	display();
	if(Serial.available()>0)
		{
		  Serial.readBytesUntil('\n',buffer,256);
			reading=false;
		}
	if(reading == false)
		{
			for(int i=0;i<256; i++)
				{
					if(buffer[i] == ' ')
						{
							buffer[i]='\n';
							//argument=&buffer[i+1];
						}
				}
			Serial.print("scanf ");
		  Serial.println(sscanf(buffer, "%s %d",&operand,&number));
			parse();
			number=0;
			reading=true;
			clearbuffer();
		}
		
}
