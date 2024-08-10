#ifndef UC_DEVICES_WS2812_H
#define UC_DEVICES_WS2812_H UC_DEVICES_WS2812_H

#include <abmt/io/spi.h>
#include <abmt/blob.h>
#include <cstdint>

namespace uc_devices{

//@node: auto
//@raster: auto
struct ws2812_strip{
    abmt::blob_shared out_data;
    uint8_t in_r;
    uint8_t in_g;
    uint8_t in_b;
    
    int param_num_leds = 1;
    
    void init();
    void tick();
};


//@node: auto
//@raster: auto
struct ws2812_device{
    abmt::io::spi_ptr in_spi_6360khz;
    abmt::blob_shared in_data;
    void tick();
};





} // namespace uc_devices

#endif // UC_DEVICES_WS2812_H
