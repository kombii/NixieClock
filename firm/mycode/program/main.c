#include "stm32f10x.h"
#include "Display.h"
#include "app.h"
#include "delay.h"
#include "HV57708.h"
#include "PinDef.h"
#include "i2c.h"
#include "ds3231.h"
#include "usart1.h"


// ���浱ǰʱ��,����ģʽ��ȫ�ֱ������� "app.h" ������
uint8_t hour = 10;
uint8_t minute = 50;
uint8_t second = 20;
uint8_t per25ms = 0;
uint8_t second_tmp = 0;
// ҹ��ģʽ����Чǰ����ʱ��ģʽ������
uint8_t sleepMode = 1;
// ģʽ�����Ӱɡ���������
uint8_t mode = MODE_CLOCK;
extern Time_Typedef TimeValue;

int main(void)
{
	// ���ֳ�ʼ��
	displayInit();
	delay_init(72);
	IIC_Config();
	USART1_Config();
	//beepInit();
	
	
  while(1)
	{
			Time_Handle();
			hour=	Display_Time[0]*10+Display_Time[1]-16;
			minute=	Display_Time[3]*10+Display_Time[4]-16;
			second=Display_Time[6]*10+Display_Time[7]-16;

			//USART1_printf(USART1,"%d:%d:%d\n",hour,
							//	minute,second);

	//delay_us(100);

///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(second_tmp != second && mode == MODE_CLOCK)  // ʱ��ģʽ��ÿ��ˢ��һ����ʾ
		{
			if(sleepMode && hour >= 1 && hour <= 6)
			{
				displayUserNumber("     ");   // ҹ��ģʽ������ʾ
			}
			else
			{
				displayTime();//��display��
			}
/////////////////////////////////////////////////
			if(second % 2 == 0)
			{
				displayDots();
			}
			else
			{
				haltDots();
			}
			second_tmp = second;
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////		
		if((minute % 10 == 0) && (second < 10))  // ÿ�� 10 ����ѭ����ʾ�������֣���ֹ�����ж�
		{
			displayNumber(000000);
			delay_ms(50);
			displayNumber(111111);
			delay_ms(50);
			displayNumber(222222);
			delay_ms(50);
			displayNumber(333333);
			delay_ms(50);
			displayNumber(444444);
			delay_ms(50);
			displayNumber(555555);
			delay_ms(50);
			displayNumber(666666);
			delay_ms(50);
			displayNumber(777777);
			delay_ms(50);
			displayNumber(888888);
			delay_ms(50);
			displayNumber(999999);
			delay_ms(50);
		}

		//for(int i=1;i<99;i++)
		//{displayNumber(i+i*100+i*10000);
			//delay_ms(5);}
///////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//return 0;
}