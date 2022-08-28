#include <driver/rmt.h>

rmt_item32_t list1[] = {
  {{{5, 1, 5, 0}}},
  {{{0, 1, 0, 0 }}}
};

rmt_item32_t list2[] = {
  {{{13, 1, 113, 0}}},
  {{{14, 1, 0, 0 }}}
};

void initRMT(int divider = 1)
{
  rmt_config_t config1 = RMT_DEFAULT_CONFIG_TX((gpio_num_t)pinCLK, RMT_CHANNEL_1);
    config1.tx_config.loop_en = true;
    config1.tx_config.loop_count = 10000;
    config1.clk_div = divider;
  rmt_config(&config1);
  rmt_driver_install(config1.channel, 0, 0);
  
  rmt_config_t config2 = RMT_DEFAULT_CONFIG_TX((gpio_num_t)pinCS, RMT_CHANNEL_2);
    config2.tx_config.loop_en = true;
    config2.tx_config.loop_count = 10000;
    config2.clk_div = divider;
  rmt_config(&config2);
  rmt_driver_install(config2.channel, 0, 0);

  rmt_add_channel_to_group(RMT_CHANNEL_1);
  rmt_add_channel_to_group(RMT_CHANNEL_2);
  
  rmt_write_items(RMT_CHANNEL_1, list1, 1, false);
  rmt_write_items(RMT_CHANNEL_2, list2, 2, false);
}
