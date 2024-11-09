#include "hut21.h"

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

void hut21::init(){
    next_data_is_temp = true;
    uint8_t byte = 0xF3;
    in_i2c_bus->write(param_adr, byte);
}

void hut21::tick(){
    uint16_big_endian data;
    in_i2c_bus->read(param_adr, data);
    data.swap();
    if(next_data_is_temp){
        out_temp = (data.value * 175.72 / 65536.00) - 46.85;
        uint8_t byte = 0xF5;
        in_i2c_bus->write(param_adr, byte);
        next_data_is_temp = false;
    }else{
        out_rh = (data.value * 125.0 / 65536.0) - 6.0;
        uint8_t byte = 0xF3;
        in_i2c_bus->write(param_adr, byte);
        next_data_is_temp = true;
    }
    
}


