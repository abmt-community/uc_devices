#include "epd290.h"

using namespace std;
using namespace uc_devices;

void epd290::init(){
    epd.spi = in_spi;
	epd.reset_pin = in_reset;
	epd.dc_pin = in_dc;
	epd.cs_pin = in_cs;
	epd.busy_pin = in_busy;

    update_next_time = true;
}

void epd290::tick(){
    abmt::img_bw next_img = in_img;
    if(in_img.width == 296){
        next_img = in_img.rotate_90();
    }
    
    if(next_img.width != 128 && next_img.height != 296){
        return; // wrong size;
    }
    
    if(last_img.width != 0){
        // not first image;
        bool img_same = true;
        for(int i = 0; i < last_img.data.size; i++){
            if(last_img.data.data[i] != next_img.data.data[i]){
                img_same = false;
                break;
            }   
        }
        if(img_same){
            return;
        }
    }
    
    last_img = next_img;
    epd.init();
    epd.WaitUntilIdle();
    epd.SetFrameMemory_Base((const unsigned char*)next_img.data.data);
    epd.DisplayFrame();
    epd.Sleep();
    update_next_time = false;
}