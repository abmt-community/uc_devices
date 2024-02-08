/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#include "ssd1306.h"

using namespace std;
using namespace uc_devices;


void ssd1306::init(){
    for(int p = 0; p < 8; ++p){
        pages[p][0] = 0x40; // i2c_command: write to display ram
    }
    
    num_pages = param_height/8;
    
    in_i2c_bus->write(param_adr, {0x00, 0xAE});             // turn off
    in_i2c_bus->write(param_adr, {0x00, 0xD5, 0x81});       // clock
    in_i2c_bus->write(param_adr, {0x00, 0x81, param_contrast});// contrast
    in_i2c_bus->write(param_adr, {0x00, 0x8D, 0x14});       // charge pump on [Not documented in datasheet :(  ]
    in_i2c_bus->write(param_adr, {0x00, 0x20, 0x00});       // addr mode
    in_i2c_bus->write(param_adr, {0x00, 0x21, 0x00, param_width -1 });  // reset col ptr
    in_i2c_bus->write(param_adr, {0x00, 0x22, 0x00, num_pages -1 });    // reset page ptr
    in_i2c_bus->write(param_adr, {0x00, 0xA8, param_height -1 });         // number of lines -1 (value:63 => 64 lines)
    in_i2c_bus->write(param_adr, {0x00, 0x40});             // start line to 0
    in_i2c_bus->write(param_adr, {0x00, 0xAF});             // turn on
}


void ssd1306::tick(){
    // a lot of room for optimization here!
    for(int p = 0; p < 8; ++p){
        for(int i = 0; i < 128; ++i){
            pages[p][i+1] = 0;
        }
    }
    int x_max = param_width;
    int y_max = param_height;
    if(in_img.width < x_max){
        x_max = in_img.width;
    }
    if(in_img.height < y_max){
        y_max = in_img.height;
    }
    for(int x = 0; x < x_max; ++x){
        for(int y = 0; y < y_max; ++y){
            if(in_img.at(x,y)){
                int page = y/8;
                int row  = y%8;
                pages[page][x+1] |= (1 << row);
            }
        }
    }
    for(int i = 0; i < num_pages; i++){
        in_i2c_bus->write_read(param_adr, pages[i], 1 + param_width, 0, 0);  
    }
}
