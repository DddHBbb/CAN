/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   can回环测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值
CanTxMsg TxMessage;			     //发送缓冲区
CanRxMsg RxMessage;				 //接收缓冲区


/// 不精确的延时
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint8_t sbuff[] = "123456789abcde";
	uint8_t rbuff[sizeof(sbuff)];
	
	LED_GPIO_Config();
	
  /*初始化USART1*/
  Debug_USART_Config();
	
	/*初始化按键*/
	Key_GPIO_Config();
 
	/*初始化can,在中断接收CAN数据包*/
	CAN_Config();


  while(1)
	{
		CAN_SetMsg(&TxMessage);

		if(flag == 0)   CAN_SendDataProces(&TxMessage,sbuff,sizeof(sbuff));
		can_delay(10000000);//等待发送完毕，可使用CAN_TransmitStatus查看状态
		
		if(flag==1)
		{		
			printf("\r\nCAN接收到数据：");	
		  CAN_REVDataProces(&RxMessage,rbuff);
			printf("%s",rbuff);
			flag=0;
		}
	
	}
}

