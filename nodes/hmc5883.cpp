#include "hmc5883.h"

using namespace std;
using namespace uc_devices;

struct int16_big_endian{
    union{
        int16_t value;
        char bytes[2];
    };
    void swap(){
        char mem = bytes[0];
        bytes[0] = bytes[1];
        bytes[1] = mem;
    }
};

void hmc5883::init(){
    in_i2c_bus->write(adr, { 0x00, 0x70 }); // 8-average, 15 Hz default, normal measurement
    in_i2c_bus->write(adr, { 0x01, 0xE0 }); // max gain, or any other desired gain
    in_i2c_bus->write(adr, { 0x02, 0x00 }); // Continuous-measurement mode
}

void hmc5883::tick(){
    int16_big_endian data[3];
    uint8_t reg = 0x03;
    in_i2c_bus->write_read(adr,reg,data);
    data[0].swap();
    data[1].swap();
    data[2].swap();
    out_mx = data[0].value;
    out_my = data[2].value; // XZY instead of XYZ
    out_mz = data[1].value;
}


