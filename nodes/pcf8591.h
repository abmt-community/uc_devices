/**
 * Author: Hendrik van Arragon, 2022
 * SPDX-License-Identifier: MIT
 */

#ifndef UC_DEVICES_PCF8591_H
#define UC_DEVICES_PCF8591_H UC_DEVICES_PCF8591_H

#include <abmt/io/i2c.h>

namespace uc_devices{

//@node: auto
struct pcf8591{
    uint8_t param_adr = 72; // 0x48 == 60
    bool    param_request_analog_data = true;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    double  in_aout;
    double  out_ain0 = 0;
    double  out_ain1 = 0;
    double  out_ain2 = 0;
    double  out_ain3 = 0;
    
    void tick();
    
};

} // namespace uc_devices

#endif // UC_DEVICES_PCF8591_H
