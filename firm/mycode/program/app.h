

//超常用的全局变量


#ifndef __APP_H
#define __APP_H
#include<sys.h>
// 工作模式
#define MODE_CLOCK    0
#define MODE_DISPLAY  1//尚未用上的模式
extern uint8_t mode;

// 时间、闹钟、自定义显示模式下要显示的内容， 在 "main.c" 中定义
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;
extern uint8_t per25ms;
extern uint8_t sleepMode;
#endif
