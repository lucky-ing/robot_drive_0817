#include "config.h"

#include "pcf8563.h"




void delay(unsigned int ms) 
{
   u8 t;
   while(ms--)
   { 
     for(t = 0; t <40; t++);
   }
}


void SDA_IN(void) //sda������ ,PA11
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO��ʼ���ṹ��			
	// Configure I2C1 pins:SDA
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void SDA_OUT(void) //sda�����
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO��ʼ���ṹ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


//��ʼ��IIC
void IIC_PCF8563_Init(void)
{
	U8 rc = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO��ʼ���ṹ��
		
	// Configure I2C1 pins: SCL and SDA 
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	IIC_Write_Addr(0,0);	

}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT(); //sda�����
	IIC_SDA=1;
	IIC_SCL=1;
	delay(4);
	IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	delay(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	delay(4);
	IIC_SCL=1;
	delay(4);
	IIC_SDA=1;//����I2C���߽����ź�
	delay(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
// 0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN(); //SDA����Ϊ����
	IIC_SDA=1;delay(1);
	IIC_SCL=1;delay(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0
	return 0;
}

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay(2);
	IIC_SCL=1;
	delay(2);
	IIC_SCL=0;
}
//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay(2);
	IIC_SCL=1;
	delay(2);
	IIC_SCL=0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1;
		delay(2); //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay(2);
		IIC_SCL=0;
		delay(2);
	}
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 IIC_Read_Byte(u8 ack)
{
	u8 i,receive=0;
	SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
		IIC_SCL=0;
		delay(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)receive++;
		delay(1);
	}
	if (!ack)
	IIC_NAck();//����nACK
	else
	IIC_Ack(); //����ACK
	return receive;
}


void IIC_Write_Addr(u8 add,u8 date)
{
	IIC_Start();
	IIC_Send_Byte(0XA2);  //дָ��
	IIC_Wait_Ack();
	IIC_Send_Byte(add);  //дָ��
	IIC_Wait_Ack();
	IIC_Send_Byte(date);  //дָ��
	IIC_Wait_Ack();
	IIC_Stop();

}

u8 IIC_Read_Addr(u8 add)
{
	u8 date;

	//OS_ENTER_CRITICAL();
	
	IIC_Start();
	IIC_Send_Byte(0XA2);  //дָ��
	IIC_Wait_Ack();
	IIC_Send_Byte(add); 
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA3);  //дָ��
	IIC_Wait_Ack();
	date=IIC_Read_Byte(0); 	
	IIC_Stop();
	//OS_EXIT_CRITICAL();
	
	return date;
}

/*�롢���ӡ�Сʱ���ա��¡��ꡢ���ӱ�����Сʱ�������ձ����Ĵ�����
�����ʽΪ BCD�� ���ں����ڱ����Ĵ������� BCD ��ʽ���� 	*/
void IIC_READ_TIME(void)
{
#if 0
	timer.sec=BCD_To_Decimal(IIC_Read_Addr(0X02)&0x7f);
	timer.min=BCD_To_Decimal(IIC_Read_Addr(0X03)&0x7f);
	timer.hour=BCD_To_Decimal(IIC_Read_Addr(0X04)&0x3f); 
	timer.w_date=BCD_To_Decimal(IIC_Read_Addr(0X05)&0x3f); 
//	timer.week=IIC_Read_Addr(0X06)&0x07;
	timer.w_month=BCD_To_Decimal(IIC_Read_Addr(0X07)&0x1f);
	timer.w_year=BCD_To_Decimal(IIC_Read_Addr(0X08)&0xff);
	timer.w_year+=2000;	 
	#endif
}


/*�롢���ӡ�Сʱ���ա��¡��ꡢ���ӱ�����Сʱ�������ձ����Ĵ�����
�����ʽΪ BCD�� ���ں����ڱ����Ĵ������� BCD ��ʽ���� 	*/
void IIC_WRITE8563(u8 year, u8 month, u8 day, u8 hour, u8 mint, u8 second)	//д���ʼֵ
{
	IIC_Write_Addr(0x02,second);
	IIC_Write_Addr(0x03,mint);
	IIC_Write_Addr(0x04,hour);
	IIC_Write_Addr(0x05,day);
//	IIC_Write_Addr(0x06,0x04);
	IIC_Write_Addr(0x07,month);
	IIC_Write_Addr(0x08,year);
}


void ds1302_setime_1(unsigned char week, unsigned char hour, unsigned char min)
{


	if(week > 0)
		week -=1;

	

	IIC_Write_Addr(0x03,Decimal_To_BCD(min));
	IIC_Write_Addr(0x04,Decimal_To_BCD(hour));

	IIC_Write_Addr(0x06,Decimal_To_BCD(week));


	//printf("set time:	%d	%d	%d\r\n", week, hour, min);
	
	return;
}



void DS1302_GetTime(SYSTEMTIME *Time){



	Time->Week = BCD_To_Decimal(IIC_Read_Addr(0X06)&0x7) + 1;

	Time->Hour = BCD_To_Decimal(IIC_Read_Addr(0X04)&0x3f);
	#if 1
	Time->Minute = BCD_To_Decimal(IIC_Read_Addr(0X03)&0x7f);
	Time->Second = BCD_To_Decimal(IIC_Read_Addr(0X02)&0x7f);

	//printf("week:%d	hour:%d		min:%d	second:%d\r\n", Time->Week, Time->Hour, Time->Minute, Time->Second);


	if(Time->Hour >= 24 || Time->Minute >= 60) {
		
		Time->Hour = global_setting.clock_hour;
		Time->Minute = global_setting.clock_min;
		Time->Week = global_setting.clock_week;

		
		

	} 
	#endif

}



u8 BCD_To_Decimal(u8 source_char)//��BCD��ת����ʮ������
{
	u8	temp1,temp2,desit_char;
	temp1 = source_char>>4;
	temp2 = source_char&0x0f;
	desit_char = temp1*10 + temp2;
	return	desit_char;
}
	  
u8 Decimal_To_BCD(u8 source_char)//��ʮ������ת����BCD��
{
	u8	temp1,temp2,desit_char;
	temp1 = source_char/10;
	temp2 = source_char%10;
	desit_char = temp1*16 + temp2;
	return	desit_char;
}


















