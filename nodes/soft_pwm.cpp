/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#include "soft_pwm.h"

using namespace std;
using namespace uc_devices;

void soft_pwm::tick(){
    if( in > cnt ){
        out = true;
    }else{
        out = false;
    }
    cnt++;
    if(cnt >= param_cnt_limit){
        cnt = 0;
    }
}