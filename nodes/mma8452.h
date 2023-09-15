/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */
#ifndef UC_DEVICES_MMA8452_H
#define UC_DEVICES_MMA8452_H UC_DEVICES_MMA8452_H

#include <abmt/math/vec.h>
#include <abmt/io/i2c.h>

namespace uc_devices{

//@node: auto
struct mma8452{
    uint8_t param_adr = 28;
    
    abmt::io::i2c_bus_ptr in_i2c_bus;
    abmt::vec3f out_acc;

    void init();
    void tick();
};


} // namespace uc_devices

#endif // UC_DEVICES_MMA8452_H
