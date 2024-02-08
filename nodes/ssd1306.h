/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#ifndef UC_DEVICES_SSD1306_H
#define UC_DEVICES_SSD1306_H UC_DEVICES_SSD1306_H

#include <abmt/math/vec.h>
#include <abmt/io/i2c.h>
#include <abmt/img.h>

namespace uc_devices{

//@node: auto
struct ssd1306{
    uint8_t param_adr    = 0x3c; // 0x3c == 60
    uint8_t param_contrast  = 255;
    uint8_t param_width  = 128;
    uint8_t param_height = 64;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    abmt::img_bw  in_img;
    
    uint8_t pages[8][128+1] = {}; // +1: frist byte = i2c_command
    int num_pages = 0;
    
    void init();
    void tick();
    
};

} // namespace uc_devices

#endif // UC_DEVICES_SSD1306_H
