void setup()
{
	for(int i=3;i<14;i++)
		pinMode(i, OUTPUT);
	Serial.begin(9600);
}
//constants
char test[] = "test";
//
bool lights[10] = {true,true,true,true,true,true,true,true,true,true};

char * operand;
char * argument;


char buffer[256];

char incoming;

int counter = 0;

bool reading = true;

void display()
{
	for(int i=0;i<10;i++)
		digitalWrite(i+3, (lights[i]) ? HIGH : LOW);
}


void parse()
{
	strcmp(operand,test);
	serial.print(operand);
	serial.println(test);
}

void loop()
{
	if(Serial.available()>0)
		{
		  Serial.readBytesUntil('\n',buffer,256);
			counter++;
			buffer[counter] = '\0';
			reading=false;
		}
	if(reading == false)
		{
			for(int i=0; i<counter;i++)
				{
					if(buffer[i]==' ')
						{
							buffer[i]='\0';
							argument=buffer[i+1];
						}
				}
			parse();
			display();
			reading=true;
			counter=0;
		}
		
}
