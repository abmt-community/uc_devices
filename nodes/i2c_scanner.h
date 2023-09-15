/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
 
#ifndef UC_DEVICES_I2C_SCANNER_H
#define UC_DEVICES_I2C_SCANNER_H UC_DEVICES_I2C_SCANNER_H

#include <abmt/io/i2c.h>
#include <cstdint>

namespace uc_devices{

//@node: auto
//@raster: 1s;
struct i2c_scanner{
    abmt::io::i2c_bus_ptr in_i2c_bus;
    uint32_t param_interval_s = 5;
    uint32_t cnt = 0;
    void tick();
};


} // namespace uc_devices

#endif // UC_DEVICES_I2C_SCANNER_H
