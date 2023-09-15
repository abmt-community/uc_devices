/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#ifndef UC_DEVICES_ADXL_345_H
#define UC_DEVICES_ADXL_345_H UC_DEVICES_ADXL_345_H

#include <abmt/math/vec.h>
#include <abmt/io/i2c.h>

namespace uc_devices{

//@node: auto
struct adxl_345{
    uint8_t param_adr = 83;
    
    abmt::io::i2c_bus_ptr in_i2c_bus;
    abmt::vec3 out_acc;

    void init();
    void tick();
};

} // namespace uc_devices

#endif // UC_DEVICES_ADXL_345_H
