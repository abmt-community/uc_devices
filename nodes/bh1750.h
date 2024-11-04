#ifndef UC_DEVICES_BH1750_H
#define UC_DEVICES_BH1750_H UC_DEVICES_BH1750_H

#include <abmt/io/i2c.h>
#include <cstdint>

namespace uc_devices{

//@node: auto
//@raster: auto
struct bh1750{
    uint8_t param_adr =  0x5c;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    float out_lux = 0;
    
    void init();
    void tick();
};




} // namespace uc_devices

#endif // UC_DEVICES_BH1750_H
