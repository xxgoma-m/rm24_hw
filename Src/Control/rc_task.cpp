//
// Created by 69333 on 2023/12/16.
//

#include "rc_task.h"

extern struct rc RC1;
extern Motor test;

void rc_task_handle() {
    if (RC1.s2 == DOWN){
        test.mode_ = Motor::POWER_OFF;
    } else {
        if (RC1.s2 == MIDDLE){
            test.mode_ = Motor::STOP;
        } else if (RC1.s2 == UP){
            test.mode_ = Motor::WORKING;
            test.SetAngle(RC1.right_pitch * 1);
            test.SetSpeed(RC1.right_pitch * 1000);
        }
    }
}
