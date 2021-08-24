/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "mcp23009.h"

mcp23009 mcp; //initialize mcp object

extern "C" void app_main(void)
{
   //config
   mcpxx9_conf_t mcp_conf = {
       .i2c_port = I2C_NUM_0,
       .i2c_conf = {
           //i2c driver config
           .mode = I2C_MODE_MASTER,
           .sda_io_num = GPIO_NUM_21,
           .scl_io_num = GPIO_NUM_22,
           //.master.clk_speed=10000,
       },
       .mcp_addr = 0x27, //address of mcp23009
   };
   mcp_conf.i2c_conf.master.clk_speed = 10000; //clk speed

   mcp.init(&mcp_conf); //initializes variables and reads all registers

   //set whole GPIO port in one call
   mcp.setDir(0x20);

   //read GPIO port state to variable val
   uint8_t val;
   mcp.getDir(&val);
   ESP_LOGI("GPIOs", "0x%x", val);

   //enable pullups
   mcp.setPullup(0xFF);
   //verify
   mcp.getPullup(&val);
   ESP_LOGI("PULLups", "0x%x", val);

   //set just 3rd bit
   mcp.setBit(M_OLAT,3);
   mcp.clrBit(M_OLAT,3);

   //arduino style gpio control, switch 2nd GPIO bit to 1
   mcp.digitalWrite(2,1);
}
