/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#include "adxl_345.h"

using namespace std;
using namespace uc_devices;

void adxl_345::init(){
    in_i2c_bus->write(param_adr,{0x2C, 0x0E}); // datarate 1600hz
    in_i2c_bus->write(param_adr,{0x31, 0x0B}); // full res 16g
    in_i2c_bus->write(param_adr,{0x2D, 0x08}); // endable
}

void adxl_345::tick(){
    int16_t data[3] = {};
    in_i2c_bus->write_read(param_adr,{0x32},data);
    out_acc.x = data[0];
    out_acc.y = data[1];
    out_acc.z = data[2];
}