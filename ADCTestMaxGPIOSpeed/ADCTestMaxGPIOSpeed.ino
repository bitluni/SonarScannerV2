const int sampleCount = 50000;
unsigned short samples[sampleCount];

void setup() 
{
	Serial.begin(2000000);
	disableCore0WDT();
}

inline unsigned long readBits()
{
  return *(volatile unsigned long*)GPIO_IN_REG;
}

void loop() 
{
  portDISABLE_INTERRUPTS();
  uint32_t t = ESP.getCycleCount();
  for(int i = 0; i < sampleCount; i++)
    samples[i] = readBits();  //15 cycles
  uint32_t t2 = ESP.getCycleCount();
  portENABLE_INTERRUPTS();
  Serial.print("Cycles per sample: ");
  int cycles = (t2 - t) / sampleCount;
  Serial.println(cycles);
  Serial.print("GPIO readings per second: ");
  Serial.println((ESP.getCpuFreqMHz() * 1000000) / cycles);
  delay(1000);
}
