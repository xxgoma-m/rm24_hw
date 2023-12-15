//
// Created by 69333 on 2023/11/12.
//

#include "remote_control.h"

extern uint8_t rx_buffer_[18];
struct rc RC1;
uint8_t rx_data_[18];

void rc_handle_data(){
    RC1.IWDG_cnt = 0;
    memcpy(rx_data_, rx_buffer_, 18);
    RC1.ch0 = (rx_data_[0] | rx_data_[1] << 8) & 0x07ff;
    RC1.ch1 = (rx_data_[1] >> 3 | rx_data_[2] << 5) & 0x07ff;
    RC1.ch2 = (rx_data_[2] >> 6 | rx_data_[3] << 2 | rx_data_[4] << 10) & 0x07ff;
    RC1.ch3 = (rx_data_[4] >> 1 | rx_data_[5] << 7) & 0x07ff;
    RC1.s1 = 0;
    RC1.s2 = (rx_data_[5] >> 4 & 0x03);
    //RC1.s1 = (rx_data_[5] >> 4 & 0x03);
    //RC1.s2 = (rx_data_[5] >> 4 & 0x0C) >> 2;

    if (RC1.s2 == UP){
        RC1.inputmode = REMOTE_INPUT;
    } else if (RC1.s2 == MIDDLE){
        RC1.inputmode = KEY_MOUSE_INPUT;
    } else{
        RC1.inputmode = STOP;
    }
}

void rc_handle_channel(){
    RC1.right_yaw = ((float)RC1.ch0 - 1024) / 660;
    RC1.right_pitch = ((float)RC1.ch1 - 1024) / 660;
    RC1.left_yaw = ((float)RC1.ch2 - 1024) / 660;
    RC1.left_pitch = ((float)RC1.ch3 - 1024) / 660;
    //boundary
    if (RC1.right_yaw > 1){
        RC1.right_yaw = 1;
    } else if (RC1.right_yaw < -1){
        RC1.right_yaw = -1;
    }
    if (RC1.right_pitch > 1){
        RC1.right_pitch = 1;
    } else if (RC1.right_pitch < -1){
        RC1.right_pitch = -1;
    }
    if (RC1.left_yaw > 1){
        RC1.left_yaw = 1;
    } else if (RC1.left_yaw < -1){
        RC1.left_yaw = -1;
    }
    if (RC1.left_pitch > 1){
        RC1.left_pitch = 1;
    } else if (RC1.left_pitch < -1){
        RC1.left_pitch = -1;
    }
}

void rc_IWDG_handle(){
    if (RC1.IWDG_cnt < 1000){
        RC1.IWDG_cnt++;
    }
    if (RC1.IWDG_cnt > 100){
        RC1.inputmode = STOP;
    }
    if (RC1.IWDG_cnt < 100){
        HAL_IWDG_Refresh(&hiwdg);
    }
}
