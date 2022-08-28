const int pinData = 1;
const int pinCLK = 21;
const int pinCS = 26;

#include <driver/rmt.h>

rmt_item32_t list1[] = {
  {{{0, 1, 1, 0}}},
};

void initRMT(int divider = 1)
{
  rmt_config_t config1 = RMT_DEFAULT_CONFIG_TX((gpio_num_t)pinCLK, RMT_CHANNEL_1);
    config1.tx_config.loop_en = true;
    config1.tx_config.loop_count = 10000;
    config1.clk_div = divider;
  rmt_config(&config1);
  rmt_driver_install(config1.channel, 0, 0);
  rmt_write_items(RMT_CHANNEL_1, list1, 1, false);
}

void setup() 
{
  initRMT();
}

void loop() 
{
}
