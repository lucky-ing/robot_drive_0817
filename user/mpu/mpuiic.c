#include "config.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32F103������V1
//MPU6050 IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////




volatile unsigned char rx_new;


static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

#define SCL_H         GPIOE->BSRR = GPIO_Pin_3 /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */
#define SCL_L         GPIOE->BRR  = GPIO_Pin_3 /* GPIO_ResetBits(GPIOB , GPIO_Pin_10) */

#define SDA_H         GPIOE->BSRR = GPIO_Pin_4 /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */
#define SDA_L         GPIOE->BRR  = GPIO_Pin_4 /* GPIO_ResetBits(GPIOB , GPIO_Pin_11) */

#define SCL_read      GPIOE->IDR  & GPIO_Pin_3 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) */
#define SDA_read      GPIOE->IDR  & GPIO_Pin_4 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */





















//MPU IIC ��ʱ����
static void MPU_DAT_OUTPUT() {
  	 GPIO_InitTypeDef  GPIO_InitStructure; 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	  MPU_IIC_Delay();
}
static void MPU_DAT_INPUT() {
  	 GPIO_InitTypeDef  GPIO_InitStructure; 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	  MPU_IIC_Delay();
}
void MPU_IIC_Delay(void)
{
	    volatile int i =   10;
    while (i)
        i--;
}
//��ʼ��IIC
void MPU_IIC_Init(void)
{					     
    GPIO_InitTypeDef gpio;

	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &gpio);


	GPIO_WriteBit(GPIOE,GPIO_Pin_2, Bit_SET);	
	//�Ѹ���
    gpio.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOE, &gpio);

	GPIO_WriteBit(GPIOE, GPIO_Pin_3, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_4, Bit_SET);
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_DAT_OUTPUT();
    SDA_H;
    SCL_H;
    MPU_IIC_Delay();
	
    //if (!SDA_read)
     //   return mpu_false;
    SDA_L;
    MPU_IIC_Delay();
    //if (SDA_read)
     //   return mpu_false;
    SDA_L;
    MPU_IIC_Delay();
	SCL_L;
	
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_DAT_OUTPUT();
	
    SCL_L;
    MPU_IIC_Delay();
    SDA_L;
    MPU_IIC_Delay();
    SCL_H;
    MPU_IIC_Delay();
    SDA_H;
    MPU_IIC_Delay();						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU_IIC_Wait_Ack(void)
{
	U8 ucErrTime = 0;
	
	MPU_DAT_INPUT();
	
    //SCL_L;
    //I2C_delay();
    SDA_H;
    MPU_IIC_Delay();
    SCL_H;
    MPU_IIC_Delay();

	while(SDA_read) {
		ucErrTime++;
		if(ucErrTime++ >250) {
			MPU_IIC_Stop();
			return 1;

		}
		

	}
	
    SCL_L;
    return 0;
} 
//����ACKӦ��
void MPU_IIC_Ack(void)
{
    SCL_L;
	
    MPU_IIC_Delay();
	MPU_DAT_OUTPUT();
	
	SDA_L;
    MPU_IIC_Delay();
    SCL_H;
    MPU_IIC_Delay();
    SCL_L;
    MPU_IIC_Delay();
}
//������ACKӦ��		    
void MPU_IIC_NAck(void)
{
    SCL_L;
    MPU_IIC_Delay();
	MPU_DAT_OUTPUT();
	
    SDA_H;
    MPU_IIC_Delay();
    SCL_H;
    MPU_IIC_Delay();
    SCL_L;
    MPU_IIC_Delay();
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(u8 byte)
{                        
    uint8_t i = 8;
	MPU_DAT_OUTPUT();
	
    while (i--) {
        SCL_L;
        MPU_IIC_Delay();
        if (byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;
        MPU_IIC_Delay();
        SCL_H;
        MPU_IIC_Delay();
    }
    SCL_L;
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
    uint8_t i = 8;
    uint8_t byte = 0;

	MPU_DAT_INPUT();
	
    SDA_H;
    while (i--) {
        byte <<= 1;
        SCL_L;
        MPU_IIC_Delay();
        SCL_H;
        MPU_IIC_Delay();
        if (SDA_read) {
            byte |= 0x01;
        }
    }
    SCL_L;
	if (!ack)
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return byte;
}



























