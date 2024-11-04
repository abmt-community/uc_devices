#ifndef UC_DEVICES_HMC5883_H
#define UC_DEVICES_HMC5883_H UC_DEVICES_HMC5883_H

#include <abmt/io/i2c.h>

namespace uc_devices{

//@node: auto
//@raster: auto
struct hmc5883{
    abmt::io::i2c_bus_ptr in_i2c_bus;
    uint8_t adr = 0x1E;
    
    int16_t out_mx;
    int16_t out_my;
    int16_t out_mz; 
    
    void init();
    void tick();
};




} // namespace uc_devices

#endif // UC_DEVICES_HMC5883_H
