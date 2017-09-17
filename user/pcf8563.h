#ifndef __PCF8563_H
#define __PCF8563_H


#include "stm32f10x_lib.h"
//#include "RTC.h"

typedef struct __SYSTEMTIME__
{
unsigned char Second;
unsigned char Minute;
unsigned char Hour;
unsigned char Week;
#if 0
unsigned char Day;
unsigned char Month;
unsigned char Year;
unsigned char DateString[9];
#endif
//unsigned char TimeString[9];
}SYSTEMTIME;


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 


#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001080C 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 


/////////////////////////////////////////////////////////////////
//Ex_NVIC_Configר�ö���
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

///**���Զ���һ���ṹ�������RTC����**********************/ 
////ʱ��ṹ��
//typedef struct
//{
//	u8 hour;
//	u8 min;
//	u8 sec;
//	//������������
//	u8 w_year;
//	u8 w_month;
//	u8 w_date;
//}tm;


//IO��������
#define IIC_SCL PAout(12) //SCL
#define IIC_SDA PAout(11) //SDA
#define READ_SDA PAin(11) //����SDA


//IIC���в�������
void delay(unsigned int ms);
void SDA_IN(void); //sda������
void SDA_OUT(void); //sda�����
void IIC_PCF8563_Init(void); //��ʼ��IIC��IO��
void IIC_Start(void); //����IIC��ʼ�ź�
void IIC_Stop(void); //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd); //IIC����һ���ֽ�
void IIC_Write_Addr(u8 add,u8 date);
void IIC_Ack(void); //IIC����ACK�ź�
void IIC_NAck(void); //IIC������ACK�ź�
void IIC_WRITE8563( u8 year, u8 month, u8 day, u8 hour, u8 mint, u8 second);	//д���ʼֵ
void IIC_READ_TIME(void);
u8 BCD_To_Decimal(u8 source_char);//��BCD��ת����ʮ������
u8 Decimal_To_BCD(u8 source_char);//��ʮ������ת����BCD��
u8 IIC_Read_Byte(u8 ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); //IIC�ȴ�ACK�ź�
u8 IIC_Read_Addr(u8 add);


void DS1302_GetTime(SYSTEMTIME *Time);
void ds1302_setime_1(unsigned char week, unsigned char hour, unsigned char min);


void IIC_PCF8563_Init(void);




#endif




