

//�����õ�ȫ�ֱ���


#ifndef __APP_H
#define __APP_H
#include<sys.h>
// ����ģʽ
#define MODE_CLOCK    0
#define MODE_DISPLAY  1//��δ���ϵ�ģʽ
extern uint8_t mode;

// ʱ�䡢���ӡ��Զ�����ʾģʽ��Ҫ��ʾ�����ݣ� �� "main.c" �ж���
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;
extern uint8_t per25ms;
extern uint8_t sleepMode;
#endif
