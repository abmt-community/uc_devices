#ifndef UC_DEVICES_HUT21_H
#define UC_DEVICES_HUT21_H UC_DEVICES_HUT21_H

#include <abmt/io/i2c.h>
#include <cstdint>

namespace uc_devices{

//@node: auto
//@raster: auto
struct hut21{
    uint8_t param_adr =  0x40;
    abmt::io::i2c_bus_ptr in_i2c_bus;
    float out_temp = 0;
    float out_rh = 0;
    
    bool next_data_is_temp = true;
    
    void init();
    void tick();
};




} // namespace uc_devices

#endif // UC_DEVICES_HUT21_H
