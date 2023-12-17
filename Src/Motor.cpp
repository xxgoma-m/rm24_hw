//
// Created by 69333 on 2023/12/15.
//

#include "Motor.h"

uint8_t dji_motor_rx_data_[8];
extern uint8_t can_tx_data_[8];

Motor::Motor(const Motor::Type &type, const float &ratio,
             const Motor::ControlMethod &method, const PID &ppid, const PID &spid)
             :
             ppid_(ppid),
             spid_(spid),
             info_({type, ratio}),
             motor_data_({0, 0, 0,
                          0, 0, 0})
             {
    mode_ = POWER_OFF;
    method_ = method;

    intensity_ = 0x0000;

    target_angle_ = 0;
    target_speed_ = 0;
}

void Motor::Reset() {
    target_angle_ = 0;
    target_speed_ = 0;
    motor_data_ = {0, 0, 0, 0, 0, 0};
    ppid_.Reset();
    spid_.Reset();
}

void Motor::Handle() {
    if (mode_ == POWER_OFF){
        intensity_ = 0x0000;
    } else if (mode_ == STOP){
        target_speed_ = 0;
        intensity_ = (uint8_t)spid_.Calculate(target_speed_, motor_data_.rotate_speed);
    } else if (mode_ == WORKING){
        if (method_ == POSITION_SPEED){
            intensity_ = target_speed_;
            //target_speed_ = ppid_.Calculate(target_angle_, motor_data_.angle);
            //intensity_ = (uint16_t)spid_.Calculate(target_speed_, motor_data_.rotate_speed);
        } else if (method_ == SPEED){
            intensity_ = (uint16_t)spid_.Calculate(target_speed_, motor_data_.rotate_speed);
        }
    }
    can_tx_data_[0] = (intensity_ >> 8);
    can_tx_data_[1] = (uint8_t)intensity_;
}

void Motor::SetAngle(const float &target_angle) {
    target_angle_ = target_angle;
}

void Motor::SetSpeed(const float &target_speed) {
    target_speed_ = target_speed;
}

void Motor::HandleData() {
    if (info_.type == M2006){
        motor_data_.angle = (dji_motor_rx_data_[0] << 8 | dji_motor_rx_data_[1]);
        motor_data_.rotate_speed = (dji_motor_rx_data_[2] << 8 | dji_motor_rx_data_[3]);
        motor_data_.torque = (dji_motor_rx_data_[4] << 8 | dji_motor_rx_data_[5]);
    } else if (info_.type == M3508 || info_.type == GM6020){
        motor_data_.angle = (dji_motor_rx_data_[0] << 8 | dji_motor_rx_data_[1]);
        motor_data_.rotate_speed = (dji_motor_rx_data_[2] << 8 | dji_motor_rx_data_[3]);
        motor_data_.current = (dji_motor_rx_data_[4] << 8 | dji_motor_rx_data_[5]);
        motor_data_.temp = dji_motor_rx_data_[6];
    }
    Handle();
}
