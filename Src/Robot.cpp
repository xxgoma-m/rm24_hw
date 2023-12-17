//
// Created by 69333 on 2023/12/3.
//

#include "Robot.h"

extern Motor test;
uint8_t can_tx_data_[8];

void MainControlLoop(){
    rc_IWDG_handle();
    rc_task_handle();
    CAN_Send_Data(&hcan1, 0x200, can_tx_data_, 8);
};