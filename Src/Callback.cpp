//
// Created by 69333 on 2023/12/3.
//

#include "Callback.h"

extern uint8_t rx_buffer_[18];
extern uint8_t dji_motor_rx_data_[8];
extern Motor test;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        MainControlLoop();
    }
}

// UART Receive Callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
    HAL_IWDG_Refresh(&hiwdg);
    if (huart->Instance == huart3.Instance){
        HAL_UART_Receive_IT(huart, rx_buffer_, 18);
        rc_handle_data();
        rc_handle_channel();
    }
}

// CAN Receive Callback
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    if (rx_header.StdId >= 0x201 && rx_header.StdId <= 0x20B){
        memcpy(dji_motor_rx_data_, &rx_data, 8);
        test.HandleData();
    }
}