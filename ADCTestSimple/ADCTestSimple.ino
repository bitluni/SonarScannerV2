//ESP32S2
//
const int pinData = 1;
const int pinCLK = 21;
const int pinCS = 26;

const unsigned long us = 5;

void setup() 
{
	Serial.begin(2000000);
	pinMode(pinData, INPUT);
	pinMode(pinCLK, OUTPUT);
	pinMode(pinCS, OUTPUT);
	pinMode(45, OUTPUT);
	digitalWrite(pinCS, 1);
  digitalWrite(pinCLK, 1);
	disableCore0WDT();
}

void loop()
{
  unsigned long a = 0;
  digitalWrite(pinCS, 0);
  for(int i = 0; i < 16; i++)
  {
    digitalWrite(pinCLK, 0);
    delayMicroseconds(us);
    digitalWrite(pinCLK, 1);
    delayMicroseconds(us / 2);
    a = (a << 1) | (digitalRead(pinData) ? 1 : 0);
    if(i == 13)
      digitalWrite(pinCS, 1);
    delayMicroseconds(us / 2);
  }
  Serial.println(a);
}
