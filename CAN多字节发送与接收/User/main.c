/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   can�ػ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			     //���ͻ�����
CanRxMsg RxMessage;				 //���ջ�����


/// ����ȷ����ʱ
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint8_t sbuff[] = "123456789abcde";
	uint8_t rbuff[sizeof(sbuff)];
	
	LED_GPIO_Config();
	
  /*��ʼ��USART1*/
  Debug_USART_Config();
	
	/*��ʼ������*/
	Key_GPIO_Config();
 
	/*��ʼ��can,���жϽ���CAN���ݰ�*/
	CAN_Config();


  while(1)
	{
		CAN_SetMsg(&TxMessage);

		if(flag == 0)   CAN_SendDataProces(&TxMessage,sbuff,sizeof(sbuff));
		can_delay(10000000);//�ȴ�������ϣ���ʹ��CAN_TransmitStatus�鿴״̬
		
		if(flag==1)
		{		
			printf("\r\nCAN���յ����ݣ�");	
		  CAN_REVDataProces(&RxMessage,rbuff);
			printf("%s",rbuff);
			flag=0;
		}
	
	}
}

