#include "myuart.h"
#include "oled.h"

void UART1_Send(uint8_t* data, uint16_t len)
{
	HAL_UART_Transmit(&huart1, data, len, 0xffff);
}

void UART1_Receive(uint16_t len)
{
//	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rxchar, len);

}
//uint16_t uart_2_rx[3];
uint16_t rx_uint16;
//uint16_t flag = 1;
//uint16_t count = 0;
uint16_t CX, CY, CZ;

void UART2_Send(uint8_t* data, uint16_t len)
{

}
void UART2_Receive()
{
	HAL_UART_Receive_IT(&huart2, (void*)&rx_uint16, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	uint16_t temp;
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);

	if (huart->Instance == USART2)
	{
//		UART1_Send((uint8_t*)&rx_uint16, 1);
		temp = rx_uint16;
		Openmv_Receive(temp);

		UART2_Receive();
	}
}

void Openmv_Receive(uint16_t Com_Data)
{
	/*循环体变量*/
	uint8_t i;
	/*计数变量*/
	static uint8_t RxCounter1 = 0;//计数
	/*数据接收数组*/
	static uint16_t RxBuffer1[6] = { 0 };
	/*数据传输状态位*/
	static uint8_t RxState = 0;
	/*对数据进行校准，判断是否为有效数据*/
	if (RxState == 0 && Com_Data == 0x2C)  //0x2c帧头
	{

		RxState = 1;
		RxBuffer1[RxCounter1++] = Com_Data;
	}

	else if (RxState == 1 && Com_Data == 0x12)  //0x12帧头
	{
		RxState = 2;
		RxBuffer1[RxCounter1++] = Com_Data;
	}
	else if (RxState == 2)
	{

		RxBuffer1[RxCounter1++] = Com_Data;
		if (RxCounter1 >= 5 || Com_Data == 0x5B)       //RxBuffer1接受满了,接收数据结束
		{
			RxState = 3;
			CX = RxBuffer1[2];
			CY = RxBuffer1[3];
			CZ = RxBuffer1[4];
//			OLED_ShowString(0, 0, "CX: ", 16, 0);
//			OLED_ShowNum(4 * 16, 0, CX, 3, 16, 0);
//			OLED_ShowString(0, 3, "Cy: ", 16, 0);
//			OLED_ShowNum(4 * 16, 3, CY, 3, 16, 0);
//			OLED_ShowString(0, 6, "CZ: ", 16, 0);
//			OLED_ShowNum(4 * 16, 6, CZ, 3, 16, 0);
		}
	}

	else if (RxState == 3)//检测是否接受到结束标志
	{
		if (RxBuffer1[RxCounter1 - 1] == 0x5B)
		{
			//RxFlag1 = 0;
			RxCounter1 = 0;
			RxState = 0;
		}
		else   //接收错误
		{
			RxState = 0;
			RxCounter1 = 0;
			for (i = 0; i < 5; i++)
			{
				RxBuffer1[i] = 0x00;      //将存放数据数组清零
			}
		}
	}
	else   //接收异常
	{
		RxState = 0;
		RxCounter1 = 0;
		for (i = 0; i < 5; i++)
		{
			RxBuffer1[i] = 0x00;      //将存放数据数组清零
		}
	}
}
