/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#ifndef UC_DEVICES_MAX31865_H
#define UC_DEVICES_MAX31865_H UC_DEVICES_MAX31865_H

#include <cstdint>
#include <abmt/io/spi.h>
#include <abmt/io/pin.h>


namespace spi_nodes{

//@node: auto
struct max31865{
    abmt::io::spi_ptr in_spi;
    abmt::io::opin_ptr in_cs;
    
    float param_r_ref = 429;
    
    float out_temp;
    float out_R;
    bool out_error;
    
    void init(){
        uint8_t config = 0b11010011;
        uint8_t data[2] = {0};
        data[0] = 0b10000000; // write register 0
        data[1] = config;
        abmt::blob b(&data, 2);
        in_cs->clear();
        in_spi->tranceive(b);
        in_cs->set();
        
    }
    
    void tick(){
        uint8_t data[3] = {0};
        data[0] = 0x01; 
        abmt::blob b(&data, 3);
    
        in_cs->clear();
        in_spi->tranceive(b);
        in_cs->set();
        uint16_t value = ((b.get<uint8_t>(1) *256 ) + b.get<uint8_t>(2));
        if(value & 0x01){
            out_error = true;
            value = 65535;
        }else{
            out_error = false;
        }
        out_temp = (value * 430.0 / 400 )/ 32.0 / 2 - 256; //((double)value)/16 - 256;
        out_R = value/2 * param_r_ref / 32768.0;
        
        
    }
};


} // namespace themp

#endif // UC_DEVICES_MAX31865_H
