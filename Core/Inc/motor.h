#ifndef __DIAN_JI_H__
#define __DIAN_JI_H__

#include "main.h"

extern uint16_t left_pulses_num;
extern uint16_t right_pulses_num;
extern uint16_t left_turns_num;
extern uint16_t right_turns_num;

void left_motor_control(int direction, int speed, uint16_t turns);    //方向，速度
void right_motor_control(int direction, int speed, uint16_t turns);

#endif