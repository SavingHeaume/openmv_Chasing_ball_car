#include "motor.h"
#include "tim.h"

uint16_t left_pulses_num = 0;
uint16_t right_pulses_num = 0;
uint16_t left_turns_num = 0;
uint16_t right_turns_num = 0;

void left_motor_control(int direction, int speed, uint16_t turns)
{
	left_pulses_num = 0;
	left_turns_num = turns;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, direction);

	//设置重装载值,设置速度快慢
		__HAL_TIM_SetAutoreload(&htim2, speed);
	//设置占空比
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, (speed / 2));

	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
}

void right_motor_control(int direction, int speed, uint16_t turns)
{
//	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
	right_pulses_num =0;
	right_turns_num = turns;
	if (direction)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	}
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, direction);

	//设置重装载值,设置速度快慢
		__HAL_TIM_SetAutoreload(&htim3, speed);
	//设置占空比
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (speed / 2));
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);

}

// 定时器溢出中断
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
//{
//	if (htim == (&htim2))
//	{
//		pulses_num++;
//		if (pulses_num >= 3200 * turns_num) // 3200个脉冲为一圈
//		{
//				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0); // 设置占空比，停止旋转
//			pulses_num = 0;
//		}
//	}
//}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
	if (htim == (&htim2))
	{
		left_pulses_num++;
		if (left_pulses_num >= 3200 * left_turns_num) // 3200个脉冲为一圈
		{
			HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
//			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
			left_pulses_num = 0;
		}
	}
	else if (htim == &htim3)
	{
		right_pulses_num++;
		if (right_pulses_num >= 3200 * right_turns_num) // 3200个脉冲为一圈
		{
			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
//			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
			right_pulses_num = 0;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
//	HAL_Delay(16);
//	if (GPIO_PIN == GPIO_PIN_8)
//	{
//		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0)
//		{
//			left_motor_control(1, 135, 3);
//			right_motor_control(1, 135, 3);
//		}
//	}
//	else if (GPIO_PIN == GPIO_PIN_9)
//	{
//		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9) == 0)
//		{
//			left_motor_control(0, 135, 3);
//			right_motor_control(0, 135, 3);
//		}
//	}
}
