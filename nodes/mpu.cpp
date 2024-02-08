/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#include "mpu.h"

using namespace std;
using namespace uc_devices;

struct int16_big_endian{
    union{
        int16_t value;
        char bytes[2];
    };
    void swap(){
        char mem = bytes[0];
        bytes[0] = bytes[1];
        bytes[1] = mem;
    }
};

void mpu6050::tick(){
    if(!in_i2c_bus){
        return;
    }
    
    if(init == false){
        if(param_use_alternate_address){
            adr = 0x69;
        }
        in_i2c_bus->write(adr, { 0x6B, 0x00 });        // power up
        in_i2c_bus->write(adr, { 0x19, 0x07 });        // freq 1khz
        in_i2c_bus->write(adr, { 0x1a, 0 });           // disable filter
        if(param_enable_magnetometer){
            uint8_t who_am_i;
            in_i2c_bus->write(adr, { 0x34, 0x09 });    // i2c slave query delay to every 10th sample 
            in_i2c_bus->write(adr, { 0x67, 0x01 });    // enable i2c delay
            in_i2c_bus->write(adr, { 0x6A, 0x20 });    // enable i2c-slave
            
    	    in_i2c_bus->write(adr, { 0x25, 0x0c });    // SLV0_ADR -> 0x0c
    	    in_i2c_bus->write(adr, { 0x26, 0x0A });    // SLV0_REG -> 0x0A (control regster)
    	    in_i2c_bus->write(adr, { 0x63, 0x06 });    // SLV0_D0  -> 0x06 (continiues mode)
    	    in_i2c_bus->write(adr, { 0x27, 0x81 });    // send one byte 
    	    
    	    in_i2c_bus->write_read(adr, { 117 }, who_am_i);  // waste a little time
    	    in_i2c_bus->write_read(adr, { 117 }, who_am_i);  // that request can be completed
    	    in_i2c_bus->write_read(adr, { 117 }, who_am_i);
    	    in_i2c_bus->write_read(adr, { 117 }, who_am_i);
    	    
    	    //out_whoami = who_am_i;
    	    
    	    in_i2c_bus->write(adr, { 0x25, 0x0c | 0x80 });    // SLV0_ADR -> 0x0c
    	    in_i2c_bus->write(adr, { 0x26, 0x00 });           // SLV0_REG -> 0x00 (status regster)
    	    in_i2c_bus->write(adr, { 0x27, 0x01 });           // request 1 byte
            
            in_i2c_bus->write_read(adr, { 117 }, who_am_i);   // waste a little time
    	    in_i2c_bus->write_read(adr, { 117 }, who_am_i);  
            
    	    in_i2c_bus->write(adr, { 0x25, 0x0c | 0x80 });    // SLV0_ADR -> 0x0c
    	    in_i2c_bus->write(adr, { 0x26, 0x03 });           // SLV0_REG -> 0x03 (data regster)
    	    in_i2c_bus->write(adr, { 0x27, 0x87 });           // request 7 byte + continues reading
    	    
        }
        init = true;
    }
    
    int16_big_endian data[10] = {};
    uint8_t reg = 0x3b;
    if(param_enable_magnetometer){
        in_i2c_bus->write_read(adr,reg,data);
    }else{
        in_i2c_bus->write_read(adr,&reg,1,data,7*2);
        data[7].value = 0;
        data[8].value = 0;
        data[9].value = 0;
    }
    
    for(int i = 0; i < 7; ++i){
        data[i].swap();
    }
    
    out_ax = data[0].value;
    out_ay = data[1].value;
    out_az = data[2].value;
    //out_temp  = data[3].value;
    out_wx   = data[4].value;
    out_wy   = data[5].value;
    out_wz   = data[6].value;
    out_mx = data[7].value;
    out_my = data[8].value;
    out_mz = data[9].value;
}
