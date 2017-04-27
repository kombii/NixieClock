/*
HV57708------ 4并行16位移位寄存器
*/

#ifndef __HV57708_H
#define __HV57708_H
#include<sys.h>
#include<delay.h>
#define HV57708_MODE_NORMAL 1
#define HV57708_MODE_INVERTION 0

void HV57708_Init(uint8_t HV57708_Mode);
void HV57708_SendData(uint32_t datapart1, uint32_t datapart2);
void HV57708_OutputData(void);

#endif
