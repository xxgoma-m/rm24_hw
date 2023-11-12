//
// Created by 69333 on 2023/11/12.
//

#include "main.h"
#include "remote_control.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    struct rc rc1;
    uint8_t rx_data_[6];

    HAL_UARTEx_ReceiveToIdle_IT(huart, rx_data_, 6);

    rc1.ch0 = (rx_data_[0] | rx_data_[1] << 8) & 0x07ff;
    rc1.ch1 = (rx_data_[1] >> 3 | rx_data_[2] << 5) & 0x07ff;
    rc1.ch2 = (rx_data_[2] >> 6 | rx_data_[3] << 2 | rx_data_[4] << 10) & 0x07ff;
    rc1.ch3 = (rx_data_[4] >> 1 | rx_data_[5] << 7) & 0x07ff;
    rc1.s1 = (rx_data_[5] >> 4) & 0x03;
    rc1.s2 = (rx_data_[5] >> 6) & 0x03;

    handle_rc(&rc1);
}

void handle_rc(struct rc *rc1){
    uint8_t a = 0;
}