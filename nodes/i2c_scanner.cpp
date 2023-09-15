/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#include "i2c_scanner.h"

#include <abmt/os.h>

using namespace std;
using namespace uc_devices;

void i2c_scanner::tick(){
    cnt++;
    if(cnt > param_interval_s){
        cnt = 0;
        for(uint8_t i = 1; i < 127;i++){
            uint8_t reg = 0;
            if(in_i2c_bus->write_read(i,&reg,1,0,0)){
                abmt::log("Found i2c device: " + to_string(i));
            }
        }
    }
}