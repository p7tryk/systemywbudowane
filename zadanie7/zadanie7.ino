#define SIZE 4

struct operation {
	char operand[256];
	void (*funptr)(int);
};

struct operation action[SIZE];


	
void setup()
{
	for(int i=3;i<14;i++)
		pinMode(i, OUTPUT);
	Serial.begin(9600);


	strcpy(action[0].operand,"on");
	action[0].funptr=&on;
	strcpy(action[1].operand,"off");
	action[1].funptr=&off;
	strcpy(action[2].operand,"onbelow");
	action[2].funptr=&onbelow;
	strcpy(action[3].operand,"offbelow");
	action[3].funptr=&offbelow;
}
//constants
const char test[] = "test";




bool lights[10] = {false,true,false,true,false,true,false,true,false,true};

char operand[256];
char * argument;
int number = 0;

char buffer[256];

bool reading = true;

void on(int input)
{
	Serial.println("on");
	Serial.println(input);
	lights[input]=true;
}
void off(int input)
{
	Serial.println("off");
	Serial.println(input);
	lights[input]=false;
}
void onbelow(int input)
{
	Serial.println("onbelow");
	Serial.println(input);
	for(input;input>=0;input--)
		lights[input]=true;
}
void offbelow(int input)
{
	Serial.println("offbelow");
	Serial.println(input);
	for(input;input>=0;input--)
		lights[input]=false;
}


void display()
{
	for(int i=0;i<10;i++)
		digitalWrite(i+3, lights[i] ? HIGH : LOW);
}

void debug()
{
	Serial.println("parse");
	Serial.println(strcmp(operand,test));
	Serial.println(operand);
	Serial.println(number);
}

void parse()
{
	for(int i=0; i<SIZE;i++)
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
			for(int i;i<256; i++)
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
