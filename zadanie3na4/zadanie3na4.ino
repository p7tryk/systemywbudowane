void setup() {
  for (int i=3; i<14; ++i)
    pinMode(i, OUTPUT);
// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A3, INPUT);
// włączenie na nim rezystora pull-up:
  digitalWrite(A3, HIGH);
// ustawienie analogowego wejścia A2 jako wejście cyfrowe:
  pinMode(A2, INPUT);
// włączenie na nim rezystora pull-up:
  digitalWrite(A2, HIGH);
// ustawienie analogowego wejścia A1 jako wejście cyfrowe:
  pinMode(A1, INPUT);
// włączenie na nim rezystora pull-up:
  digitalWrite(A1, HIGH);
// ustawienie analogowego wejścia A0 jako wejście cyfrowe:
  pinMode(A0, INPUT);
// włączenie na nim rezystora pull-up:
  digitalWrite(A0, HIGH);

	
// stan startowy diody na płytce -- wyłączona:
  digitalWrite(13, LOW);
}

int pos = 3;
int speed = 512;

void loop() {
	if(pos>12)
		pos-=10;
	digitalWrite(pos, HIGH);
	delay(speed);
	digitalWrite(pos, LOW);
	++pos;

	if (digitalRead(A2) == LOW)
		pos=3;

	if (digitalRead(A1) == LOW)
		{
			speed/=2;
			if(speed<16)
				speed=16;
		}
	if (digitalRead(A0) == LOW)
		{
			speed*=2;
			if(speed>2048)
				speed=2048;
		}

	
// jeśli przycisk zostaje wciśnięty, to włączyć diodę na płytce:
  if (digitalRead(A3) == LOW)
    digitalWrite(13, HIGH);
}
