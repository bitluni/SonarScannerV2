//ESP32S2
//
const int pinData = 1;
const int pinCLK = 21;
const int pinCS = 26;
const int sampleCount = 1000;
unsigned long samples[sampleCount * 16];

const unsigned long wait1 = 5;

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

inline void delayCycles(unsigned long n)
{
  //unsigned long t = ESP.getCycleCount();
  //while(ESP.getCycleCount() - t < n);
  asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
}

inline void setCS()
{
  *(volatile unsigned long*)GPIO_OUT_W1TS_REG = (1 << pinCS);
}

inline void clearCS()
{
  *(volatile unsigned long*)GPIO_OUT_W1TC_REG = (1 << pinCS);
}

inline void setCLK()
{
  *(volatile unsigned long*)GPIO_OUT_W1TS_REG = (1 << pinCLK);
}

inline void clearCLK()
{
  *(volatile unsigned long*)GPIO_OUT_W1TC_REG = (1 << pinCLK);
}

inline unsigned long readBits()
{
  return *(volatile unsigned long*)GPIO_IN_REG;
}

inline void storeBits(int &p)
{
  clearCLK();
  asm("nop;");
  setCLK();
  //asm("nop;");
  samples[p++] = readBits();
}

void loop() 
{
  int p = 0;
  for(int i = 0; i < sampleCount; i++)
  {
    clearCS();
    clearCLK(); //1
    delayCycles(wait1);
    setCLK();
    unsigned long b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //2
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //3
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //4
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //5
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //6
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //7
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //8
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //9
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //10
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //11
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //12
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    b = *(unsigned long*)GPIO_IN_REG;
    clearCLK(); //13
    delayCycles(wait1);
    samples[p++] = b;
    setCLK();
    delayCycles(wait1);
    clearCLK(); //14
    delayCycles(wait1);
    setCLK();
    delayCycles(wait1);
    clearCLK(); //15
    delayCycles(wait1);
    setCLK();
    setCS();     
    clearCLK(); //16
    delayCycles(wait1);
    setCLK();
  }
  p = 0;
  for(int i = 0; i < sampleCount; i++)
  {
    unsigned long a = 0;
    for(int j = 0; j < 12; j++)
      a = (a << 1) | ((samples[p++] >> pinData) & 1);
    Serial.println(a);
  }
}
