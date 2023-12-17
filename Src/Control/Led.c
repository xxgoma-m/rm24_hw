//
// Created by 69333 on 2023/12/8.
//

#include "Led.h"

void led(struct rc *rc1){
    uint8_t a = 0;
    static uint8_t state = 0;

    if (rc1->s2 == 0x01){
        TIM5->CCR1 = 15;
        TIM5->CCR2 = 0;
        TIM5->CCR3 = 0;
    } else if (rc1->s2 == 0x02){
        TIM5->CCR2 = 15;
        TIM5->CCR1 = 0;
        TIM5->CCR3 = 0;
    } else if (rc1->s2 == 0x03){
        TIM5->CCR3 = 15;
        TIM5->CCR1 = 0;
        TIM5->CCR2 = 0;
    } else{
        TIM5->CCR1 = 15;
        TIM5->CCR2 = 15;
        TIM5->CCR3 = 15;
    }

    /*if (state == 0){
        if (rc1->ch0 > 1354){
            state = 1;
            a = 1;
        } else if(rc1->ch0 < 694){
            state = 3;
            a = 2;
        }
    } else if(state == 1 || state == 3){
        state = 2;
        a = 0;
    } else if(state == 2){
        if (rc1->ch0 > 694 && rc1->ch0 < 1354){
            state = 0;
        }
    } else{
        state = 0;
        a = 0;
    }*/
    //handle_led(a);
}