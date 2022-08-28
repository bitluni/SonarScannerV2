//ESP32S2
//
//clk and CS are connectet to gpoi 10(clk) and 9(CS) externally. this way we need only to

const int pinData = 1;
const int pinCLK = 21;
const int pinCS = 26;
const int pinCount = 8;
const int pins[pinCount] = {1,2,3,4,5,6,7,8};
const int sampleCount = 20000;
unsigned short samples[sampleCount];
const int pulseCount = 8;

#include "RMT.h"

void setup() 
{
	Serial.begin(2000000);
  for(int i = 0; i < 8; i++)
    pinMode(pins[i], INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
	//pinMode(pinData, INPUT);
	//pinMode(pinCLK, OUTPUT);
	//pinMode(pinCS, OUTPUT);
	pinMode(45, OUTPUT);
	//digitalWrite(pinCS, 1);
  //digitalWrite(pinCLK, 1);
	disableCore0WDT();
  initRMT();
//  gpio_set_direction((gpio_num_t)9, GPIO_MODE_INPUT);
//  gpio_set_direction((gpio_num_t)10, GPIO_MODE_INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

inline void delayCycles(unsigned long n)
{
  //unsigned long t = ESP.getCycleCount();
  //while(ESP.getCycleCount() - t < n);
  asm("nop;");
}

inline unsigned long readBits()
{
  return *(volatile unsigned long*)GPIO_IN_REG;
}


void loop() 
{
  //########################### emit 40kHz pulse ###############################  
  for(int i = 0; i < pulseCount; i++)
  {
    digitalWrite(11, 1);
    digitalWrite(12, 0);
    delayMicroseconds(12);
    digitalWrite(11, 0);
    digitalWrite(12, 1);
    delayMicroseconds(12);    
  }
  digitalWrite(12, 0);

  //########################### read sample block ###############################  

  portDISABLE_INTERRUPTS();
  uint32_t t = ESP.getCycleCount();
  for(int i = 0; i < sampleCount; i++)
    samples[i] = readBits();  //15 cycles
  portENABLE_INTERRUPTS();


  int p = 0;
  int mode = 0;
  unsigned short pinData[8] = {0};
  int bits = 0;
  int lastBit = 0;
  int currentBit = 0;
  
  //########################### find chip select and decode samples ###############################
  while(p < sampleCount)
  {
    switch(mode)
    {
      case 0: //find sync
        if(((samples[p] >> 9) & 1) == 1)
          mode = 1;
        p++;
      break;
      case 1: //find sync end
        if(((samples[p] >> 9) & 1) == 0)
        {
          mode = 2;
          bits = 0;
          lastBit = 1;
          for(int k = 0; k < 8; k++)
            pinData[k] = 0;
        }
        else
          p++;
      break;
      case 2: //read in
        currentBit = ((samples[p] >> 10) & 1); 
        if(lastBit == 0 && currentBit == 1)
        {
          for(int k = 0; k < pinCount; k++)
          {
            pinData[k] = (pinData[k] << 1) | ((samples[p] >> pins[k]) & 1);
          }
          bits++;
          if(bits == 11)
          {
            for(int j = 0; j < pinCount; j++)
            {
              Serial.print(pinData[j] + j * 260);
              Serial.print(' ');
            }
            Serial.println();/**/
            mode = 0;
          }
        }
        lastBit = currentBit;
        p++;
      break;
    }
  }
    
  /*for(int i = 0; i < 1000; i++)
  {
    Serial.print(((samples[i] >> 1) & 1) * 3);
    Serial.print(' ');
    Serial.print(((samples[i] >> 9) & 1)  *2);
    Serial.print(' ');
    Serial.println((samples[i] >> 10) & 1);
  }/**/
  delay(100);
}
