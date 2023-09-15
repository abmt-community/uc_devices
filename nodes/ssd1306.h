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
    uint8_t         param_adr   = 60; // 0x3c == 60
    uint8_t         param_contr = 255;
    uint8_t         param_px_threshold = 127;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    abmt::img_gray  in_img;
    
    uint8_t pages[8][128+1] = {}; // +1: frist byte = i2c_command
    int page_to_send = 0;
    void img2pages();
    
    void init();
    void tick();
    
};

} // namespace uc_devices

#endif // UC_DEVICES_SSD1306_H
