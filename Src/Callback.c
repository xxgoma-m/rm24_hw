//
// Created by 69333 on 2023/12/3.
//

#include "Callback.h"

extern uint8_t rx_buffer_[18];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        MainControlLoop();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
    HAL_IWDG_Refresh(&hiwdg);
    if (huart->Instance == huart3.Instance){
        HAL_UART_Receive_IT(huart, rx_buffer_, 18);
        rc_handle_data();
        rc_handle_channel();
    }
}

/*void HAL_UART_AbortReceiveCallback(UART_HandleTypeDef *huart){
    if (huart->Instance == huart3.Instance) {
        HAL_IWDG_Refresh(&hiwdg);
        HAL_UART_Receive_DMA(huart, rx_buffer_, 18);
    }
}*/
