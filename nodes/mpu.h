/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#ifndef IO_NODES_I2C_DEVICES_H
#define IO_NODES_I2C_DEVICES_H IO_NODES_I2C_DEVICES_H

#include <abmt/math/vec.h>
#include <abmt/io/i2c.h>

namespace uc_devices{

//@node: auto
struct mpu6050{
    bool param_enable_magnetometer = false;
    bool param_use_alternate_address = false;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    int16_t out_ax;
    int16_t out_ay;
    int16_t out_az;
    int16_t out_wx;
    int16_t out_wy;
    int16_t out_wz;
    int16_t out_mx;
    int16_t out_my;
    int16_t out_mz;
    int16_t out_temp;
    
    uint8_t adr = 0x68;
    
    uint32_t out_whoami = 0;
    
    bool init = false;
    
    void tick();
    
};


} // namespace io

#endif // IO_NODES_I2C_DEVICES_H
