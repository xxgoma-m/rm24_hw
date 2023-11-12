//
// Created by 69333 on 2023/11/12.
//

#ifndef EC_HW_PLATFORM_REMOTE_CONTROL_H
#define EC_HW_PLATFORM_REMOTE_CONTROL_H

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)

#endif //EC_HW_PLATFORM_REMOTE_CONTROL_H

#include "main.h"

/* ----------------------- Data Struct ------------------------------------- */
struct rc{
    uint16_t ch0;
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint8_t s1;
    uint8_t s2;
};

void handle_rc(struct rc *rc1);
void handle_led(uint8_t a);