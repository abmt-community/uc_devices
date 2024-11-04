#include "bh1750.h"

using namespace std;
using namespace uc_devices;

struct uint16_big_endian{
    union{
        uint16_t value;
        char bytes[2];
    };
    void swap(){
        char mem = bytes[0];
        bytes[0] = bytes[1];
        bytes[1] = mem;
    }
};

void bh1750::init(){
    uint8_t byte = 0b00010000;
    in_i2c_bus->write(param_adr, byte);
}

void bh1750::tick(){
     uint16_big_endian data;
     in_i2c_bus->read(param_adr, data);
     data.swap();
     out_lux = data.value / 1.2;
}


