/*
��Ҫ���������������
HV57708_CLK - CLK
HV57708_LE  - LE
HV57708_POL - POL
HV57708_DI1 - Din1/Dout4(A)
HV57708_DI2 - Din2/Dout3(A)
HV57708_DI3 - Din3/Dout2(A)
HV67708_DI4 - Din4/Dout1(A)

������ BL��ʱ
				DIR������ʱ���ƴ�
					 ��˳ʱ���ƴ�
*/


#include "HV57708.h"
#include "PinDef.h"
//#include "delay.h"

GPIO_InitTypeDef GPIO_InitStructure;         //GPIO�����ṹ��

/*
HV57708_MODE_NORMAL    - ��׼���ģʽ
HV57708_MODE_INVERTION - �������ģʽ
 */
 
void HV57708_Init(uint8_t HV57708_Mode)
{
///////////////////////////////////////////////////////////////////////////////////////	
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
		// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��
		//DBGMCU->CR = DBGMCU->CR & ~((uint32_t)1<<5); // ������������ţ��ͷ�PB3
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
		// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��
		//AFIOʱ��
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
///////////////////////////////////////////////////////////////////////////////////////		
	
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB,ENABLE); 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;                          
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	 HV57708_CLK = 0;
   HV57708_LE  = 0;
   HV57708_POL = HV57708_Mode;
   HV57708_DI1 = 0;
   HV57708_DI2 = 0;
   HV57708_DI3 = 0;
   HV57708_DI4 = 0;
	
}

/*
���� 64 λ������
datapart1-------��һ�������ݣ�32λ
datapart2-------�ڶ��������ݣ�32λ
 */

void HV57708_SendData(uint32_t datapart1, uint32_t datapart2)
{
	uint8_t i = 0;
	uint32_t tmp = 0;
	tmp = datapart1;
  for(i = 0; i < 8; i++)
	{
		HV57708_CLK = 0;
		HV57708_DI1 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI2 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI3 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI4 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_CLK = 1;
		//delay_ms(10);
		HV57708_CLK = 0;
		//delay_ms(10);
	}
	tmp = datapart2;
  for(i = 0; i < 8; i++)
	{
		HV57708_CLK = 0;
		HV57708_DI1 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI2 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI3 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_DI4 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_CLK = 1;
		//delay_ms(10);
		HV57708_CLK = 0;
		//delay_ms(10);
	}
}

//�������
void HV57708_OutputData(void)
{
	HV57708_LE  = 1;
	//delay_ms(10);
	HV57708_LE  = 0;
	//delay_ms(10);
}
