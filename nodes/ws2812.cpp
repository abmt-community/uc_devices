#include "ws2812.h"

using namespace std;
using namespace uc_devices;

void ws2812_strip::init(){
    out_data.realloc(param_num_leds*3);
}

void ws2812_strip::tick(){
    for(int i = 0; i < param_num_leds; i++){
        out_data.data[i*3] = in_g;
        out_data.data[i*3 + 1] = in_r;
        out_data.data[i*3 + 2] = in_b;
    }
}

// https://www.newinnovations.nl/post/controlling-ws2812-and-ws2812b-using-only-stm32-spi/
static void convert8(uint8_t src, uint8_t* dst){
    uint8_t one = 0b11111100;
    uint8_t zero =0b10000000;
    for(int i = 0; i < 8; i++){
        if( src & (1<<(7-i)) ){
            dst[i] = one;
        }else{
            dst[i] = zero;
        }
    }
}

void ws2812_device::tick(){
    abmt::blob_shared out_data(in_data.size * 8);
    for(int i = 0; i < in_data.size; i++){
        convert8(in_data.data[i], (uint8_t*) &out_data.data[i*8]);
    }
    in_spi_6360khz->write(out_data);
}


