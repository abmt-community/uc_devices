/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */

#include "pcf8591.h"

using namespace std;
using namespace uc_devices;


void pcf8591::tick(){
    uint8_t raw_data[5];
    if(in_aout > 1){
        in_aout = 1;
    }else if(in_aout < 0) {
        in_aout = 0;
    }
    uint8_t control_byte = 0x44; //0b01000100;
    uint8_t dac_value = in_aout*255;
    
    if(param_request_analog_data){
        in_i2c_bus->write_read(param_adr, {control_byte, dac_value}, raw_data);
    
        // fist byte is not uesed
        out_ain0 = raw_data[1]/255.0;
        out_ain1 = raw_data[2]/255.0;
        out_ain2 = raw_data[3]/255.0;
        out_ain3 = raw_data[4]/255.0;
    }else{
        in_i2c_bus->write(param_adr, {control_byte, dac_value});
    }
}