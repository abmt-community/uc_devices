/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#include "mma8452.h"

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

void mma8452::init(){
    in_i2c_bus->write(param_adr,{0x2A,0x01});
}

void mma8452::tick(){
    int16_big_endian data[3] = {};
    in_i2c_bus->write_read(param_adr,{0x01},data);
    for(auto& i: data){
        i.swap();
    }
    out_acc.x = data[0].value;
    out_acc.y = data[1].value;
    out_acc.z = data[2].value;
}
