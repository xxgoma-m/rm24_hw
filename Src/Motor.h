//
// Created by 69333 on 2023/12/15.
//

#ifndef EC_HW_PLATFORM_MOTOR_H
#define EC_HW_PLATFORM_MOTOR_H

#include "main.h"
#include "PID.h"
#include <string.h>

class Motor{
public:
    enum Type{
        M3508,
        M2006,
        GM6020
    };
    enum ControlMethod{
        POSITION_SPEED,
        SPEED
    };
    enum Mode{
        POWER_OFF,
        STOP,
        WORKING
    };

public:
    Motor(const Type& type, const float& ratio, const ControlMethod& method,
          const PID& ppid, const PID& spid);
    void Reset();
    void Handle();
    void SetAngle(const float& target_angle);
    void SetSpeed(const float& target_speed);
    void HandleData();

public:
    struct MotorInfo{
        Type type;
        float ratio;
    } info_;

    Mode mode_;
    ControlMethod method_;

    uint16_t intensity_;

    float target_angle_, target_speed_;

    struct MotorData{
        uint16_t angle;
        float ecd_angle;
        float last_ecd_angle;
        uint16_t rotate_speed;
        uint16_t current;
        uint8_t temp;
        uint16_t torque;
    } motor_data_;

    PID ppid_, spid_;
};

#endif //EC_HW_PLATFORM_MOTOR_H
