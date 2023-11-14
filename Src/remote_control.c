//
// Created by 69333 on 2023/11/12.
//

#include "main.h"
#include "remote_control.h"
#include "usart.h"
#include "tim.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    TIM5->CCR3 = 15;
    if (huart->Instance == huart3.Instance){

        struct rc rc1;
        uint8_t rx_data_[18];

        HAL_UARTEx_ReceiveToIdle_IT(huart, rx_data_, Size);

        rc1.ch0 = (rx_data_[0] | rx_data_[1] << 8) & 0x07ff;
        rc1.ch1 = (rx_data_[1] >> 3 | rx_data_[2] << 5) & 0x07ff;
        rc1.ch2 = (rx_data_[2] >> 6 | rx_data_[3] << 2 | rx_data_[4] << 10) & 0x07ff;
        rc1.ch3 = (rx_data_[4] >> 1 | rx_data_[5] << 7) & 0x07ff;
        rc1.s1 = (rx_data_[5] >> 4) & 0x03;
        rc1.s2 = (rx_data_[5] >> 6) & 0x03;

        handle_rc(&rc1);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == huart3.Instance){
        struct rc rc1;
        uint8_t rx_data_[6];
        HAL_UART_Receive_IT(huart, rx_data_, 18);

        rc1.ch0 = (rx_data_[0] | rx_data_[1] << 8) & 0x07ff;
        rc1.ch1 = (rx_data_[1] >> 3 | rx_data_[2] << 5) & 0x07ff;
        rc1.ch2 = (rx_data_[2] >> 6 | rx_data_[3] << 2 | rx_data_[4] << 10) & 0x07ff;
        rc1.ch3 = (rx_data_[4] >> 1 | rx_data_[5] << 7) & 0x07ff;
        rc1.s1 = (rx_data_[5] >> 4) & 0x03;
        rc1.s2 = (rx_data_[5] >> 6) & 0x03;

        handle_rc(&rc1);
    }
}

void handle_rc(struct rc *rc1){
    uint8_t a = 0;
    static uint8_t state = 0;

    if (rc1->s1 == 0x00){
        TIM5->CCR2 = 50;
    } else if(rc1->s1 == 0x01){
        TIM5->CCR2 = 25;
    } else if(rc1->s1 == 0x02){
        TIM5->CCR2 = 35;
    } else if(rc1->s1 == 0x03){
        TIM5->CCR2 = 45;
    } else{
        TIM5->CCR2 = 0;
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

void handle_led(uint8_t a){
    if (a == 1){
        TIM5->CCR2 += 10;
    } else if(a == 2){
        TIM5->CCR2 -= 10;
    }
}