//
// Created by 69333 on 2023/12/10.
//

#ifndef EC_HW_PLATFORM_PID_H
#define EC_HW_PLATFORM_PID_H

class PID{
public:
    PID() : PID(0, 0, 0, 0, 0) {}
    PID(float kp, float ki, float kd, float i_max, float out_max);
    float Calculate(float ref, float fdb);
    void Reset();

public:
    float kp_, ki_, kd_;
    float i_max_, out_max_;
    float output_;

protected:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float p_out_, i_out_, d_out_;
};


#endif //EC_HW_PLATFORM_PID_H
