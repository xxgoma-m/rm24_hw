//
// Created by 69333 on 2023/12/10.
//

#include "PID.h"

PID::PID(float kp, float ki, float kd, float i_max, float out_max)
    :
    kp_(kp),
    ki_(ki),
    kd_(kd),
    i_max_(i_max),
    out_max_(out_max)
    {
    err_ = 0;
    err_sum_ = 0;
    last_err_ = 0;
    output_ = 0;
    ref_ = 0;
    fdb_ = 0;
    p_out_ = 0;
    i_out_ = 0;
    d_out_ = 0;
}

float PID::Calculate(float ref, float fdb) {
    ref_ = ref;
    fdb_ = fdb;

    err_sum_ = 0;

    last_err_ = err_;
    err_ = ref_ - fdb_;
    err_sum_ += err_;

    p_out_ = kp_ * err_;
    i_out_ = ki_ * err_sum_;
    if (i_out_ > i_max_){
        i_out_ = i_max_;
    }
    d_out_ = kd_ * (err_ - last_err_);

    output_ = p_out_ + i_out_ + d_out_;
    if (output_ > out_max_){
        output_ = out_max_;
    }

    return output_;
}

void PID::Reset() {
    err_ = 0;
    err_sum_ = 0;
    last_err_ = 0;
    p_out_ = 0;
    i_out_ = 0;
    d_out_ = 0;
}