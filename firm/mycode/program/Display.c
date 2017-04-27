#include "app.h"
#include "PinDef.h"
#include "delay.h"
#include "HV57708.h"

// 要显示的数字所在位置
const uint8_t numbers[][10] = {
	{24, 25, 26, 27, 20, 21, 22, 23, 16, 17},
  {18, 19, 12, 13, 14, 15, 8,  9,  10, 11},
  {4,  5,  6,  7,  0,  1,  2,  3,  60, 61},
  {62, 63, 56, 57, 58, 59, 52, 53, 54, 55},
  {48, 49, 50, 51, 44, 45, 46, 47, 40, 41},
  {42, 43, 36, 37, 38, 39, 32, 33, 34, 35}
};


//显示初始化

void displayInit(void)
{
	HV57708_Init(HV57708_MODE_INVERTION);  // 反相输出
  //NEON |= DISPLAY_DOTS_ALL;//还未实现！！！！调用寄存器
	//displayNumber(654321);
}

//显示数字（6个10进制数，直接写123456就行）
void displayNumber(uint32_t number)
{
	uint32_t data_part2  = 0;
	uint32_t data_part1  = 0;
	uint8_t tmp_number = 0;
	
	tmp_number = numbers[0][number / 100000ul];
	data_part1 |= 1ul << tmp_number;
	
	tmp_number = numbers[1][(number % 100000ul) / 10000ul];
	data_part1 |= 1ul << tmp_number;
	
	tmp_number = numbers[2][(number % 10000ul) / 1000ul];
	if(tmp_number < 32)
	{
		data_part1 |= 1ul << tmp_number;
	}
	else
	{
		data_part2 |= 1ul << (tmp_number - 32);
	}
		
	tmp_number = numbers[3][(number % 1000) / 100];
  data_part2 |= 1ul << (tmp_number - 32);
	
	tmp_number = numbers[5][(number % 100) / 10];
	data_part2 |= 1ul << (tmp_number - 32);
	
	tmp_number = numbers[4][number % 10];       // 调换上面数组两行的位置不行0.0谁知道发生了什么
	data_part2 |= 1ul << (tmp_number - 32);
	
	HV57708_SendData(data_part2, data_part1);
	HV57708_OutputData();
}
//更高端的调用方法（允许空格）
//6 位 unsigned char 类型数组
void displayUserNumber(uint8_t* number)
{
	uint32_t data_part2  = 0;
	uint32_t data_part1  = 0;
	uint8_t tmp_number = 0;
	if(number[0] <= '9' && number[0] >= '0')
	{
		tmp_number = numbers[0][number[0] - '0'];
		data_part1 |= 1ul << tmp_number;
	}
	
	if(number[1] <= '9' && number[1] >= '0')
	{
		tmp_number = numbers[1][number[1] - '0'];
		data_part1 |= 1ul << tmp_number;
	}
	
	if(number[2] <= '9' && number[2] >= '0')
	{
		tmp_number = numbers[2][number[2] - '0'];
		if(tmp_number < 32)
		{
			data_part1 |= 1ul << tmp_number;
		}
		else
		{
			data_part2 |= 1ul << (tmp_number - 32);
		}
	}
		
	if(number[3] <= '9' && number[3] >= '0')
	{
		tmp_number = numbers[3][number[3] - '0'];
		data_part2 |= 1ul << (tmp_number - 32);
	}
	
	if(number[4] <= '9' && number[4] >= '0')
	{
		tmp_number = numbers[5][number[4] - '0'];
		data_part2 |= 1ul << (tmp_number - 32);
	}
	
	if(number[5] <= '9' && number[5] >= '0')
	{
		tmp_number = numbers[4][number[5] - '0'];       // 调换上面数组两行的位置不行0.0谁知道发生了什么
		data_part2 |= 1ul << (tmp_number - 32);
	}
	
	HV57708_SendData(data_part2, data_part1);
	HV57708_OutputData();
}

//发送时间.....(时间在全局变量中(app.h))

void displayTime(void)
{
	displayNumber(hour * 10000ul + minute * 100ul + second);
}

//显示点
void displayDots(void)
{
NEON_DOT0=1;
NEON_DOT1=1;
NEON_DOT2=1;
NEON_DOT3=1;
}
//点笑死
void haltDots(void)
{
NEON_DOT0=0;
NEON_DOT1=0;
NEON_DOT2=0;
NEON_DOT3=0;
}
