/*
需要定义下面的引脚们
HV57708_CLK - CLK
HV57708_LE  - LE
HV57708_POL - POL
HV57708_DI1 - Din1/Dout4(A)
HV57708_DI2 - Din2/Dout3(A)
HV57708_DI3 - Din3/Dout2(A)
HV67708_DI4 - Din4/Dout1(A)

！！！ BL高时
				DIR低则逆时针移存
					 高顺时针移存
*/


#include "HV57708.h"
#include "PinDef.h"
//#include "delay.h"

GPIO_InitTypeDef GPIO_InitStructure;         //GPIO操作结构体

/*
HV57708_MODE_NORMAL    - 标准输出模式
HV57708_MODE_INVERTION - 反相输出模式
 */
 
void HV57708_Init(uint8_t HV57708_Mode)
{
///////////////////////////////////////////////////////////////////////////////////////	
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
		// 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
		//DBGMCU->CR = DBGMCU->CR & ~((uint32_t)1<<5); // 不分配跟踪引脚，释放PB3
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
		// 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
		//AFIO时钟
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
发送 64 位的数据
datapart1-------第一部分数据，32位
datapart2-------第二部分数据，32位
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

//启动输出
void HV57708_OutputData(void)
{
	HV57708_LE  = 1;
	//delay_ms(10);
	HV57708_LE  = 0;
	//delay_ms(10);
}
