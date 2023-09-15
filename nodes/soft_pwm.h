/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#ifndef UC_DEVICES_SOFT_PWM_H
#define UC_DEVICES_SOFT_PWM_H UC_DEVICES_SOFT_PWM_H

namespace uc_devices{

/**
 * Output is true when the input is bigger then the counter.
 * input == 0 -> output always false
 * input == param_cnt_limit output always true;
 * @node: auto
 */
struct soft_pwm{
    bool out = false;
    unsigned int in;
    unsigned int  param_cnt_limit = 10;
    unsigned int  cnt = 0;
    void tick();
};


} // namespace uc_devices

#endif // UC_DEVICES_SOFT_PWM_H
