
//引脚定义
#ifndef __PINDEF_H
#define __PINDEF_H

//HV57708 引脚定义

#define HV57708_CLK PBout(4)
#define HV57708_LE  PBout(10)
#define HV57708_POL PBout(3)
#define HV57708_DI1 PBout(9)
#define HV57708_DI2 PBout(8)
#define HV57708_DI3 PBout(7)
#define HV57708_DI4 PBout(6)

//DS3231 引脚定义

#define I2C_SCL PAout(1)
#define I2C_SDA PAout(2)

//串口引脚定义（就是个uart1）

//氖灯引脚定义

#define NEON_DOT0 PBout(15)
#define NEON_DOT1 PBout(14)
#define NEON_DOT2 PBout(13)
#define NEON_DOT3 PBout(12)

//蜂鸣器引脚定义

#define BUZ = PAout(3)


#endif
