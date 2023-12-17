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

#include "usart.h"
#include "tim.h"
#include "iwdg.h"
#include <string.h>

/* ----------------------- Data Struct ------------------------------------- */
enum INPUT_MODE
{
    REMOTE_INPUT = 1,
    KEY_MOUSE_INPUT = 3,
    STOP = 2,
};
enum SWITCH
{
    UP = 1,
    MIDDLE = 3,
    DOWN = 2
};
struct rc{
    uint16_t ch0;
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint8_t s1, s2;
    float right_yaw;
    float right_pitch;
    float left_yaw;
    float left_pitch;
    uint16_t IWDG_cnt;
    enum INPUT_MODE inputmode;
};
void rc_handle_data();
void rc_handle_channel();
void rc_IWDG_handle();

#endif //EC_HW_PLATFORM_REMOTE_CONTROL_H