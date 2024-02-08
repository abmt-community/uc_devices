#ifndef UC_DEVICES_EPD_29_NODE_H
#define UC_DEVICES_EPD_29_NODE_H UC_DEVICES_EPD_29_NODE_H

#include <abmt/time.h>
#include <abmt/io/spi.h>
#include <abmt/io/pin.h>
#include <abmt/img.h>

#include "epd2in9_V2.h"

//@compile: epd2in9_V2.cpp

namespace uc_devices{

// Resolution 128x296 / auto flip to 296x128;

//@node:auto
struct epd290{
    
    abmt::img_bw in_img;
    abmt::io::spi_ptr in_spi;
    abmt::io::opin_ptr in_cs;
    abmt::io::opin_ptr in_dc;
    abmt::io::opin_ptr in_reset;
    abmt::io::ipin_ptr in_busy;
    
    abmt::img_bw last_img;
    
    bool param_swap_endian = true;
    bool param_invert_px = false;
    
    bool update_next_time = true;
    
    Epd epd;
    void init();
    void tick();
};

} // namespace uc_devices

#endif // UC_DEVICES_EPD_29_NODE_H
