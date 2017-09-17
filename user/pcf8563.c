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


void SDA_IN(void) //sda线输入 ,PA11
{
	GPIO_InitTypeDef GPIO_InitStructure;//声明GPIO初始化结构体			
	// Configure I2C1 pins:SDA
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void SDA_OUT(void) //sda线输出
{
	GPIO_InitTypeDef GPIO_InitStructure;//声明GPIO初始化结构体
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


//初始化IIC
void IIC_PCF8563_Init(void)
{
	U8 rc = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;//声明GPIO初始化结构体
		
	// Configure I2C1 pins: SCL and SDA 
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	IIC_Write_Addr(0,0);	

}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT(); //sda线输出
	IIC_SDA=1;
	IIC_SCL=1;
	delay(4);
	IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	delay(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	delay(4);
	IIC_SCL=1;
	delay(4);
	IIC_SDA=1;//发送I2C总线结束信号
	delay(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
// 0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN(); //SDA设置为输入
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
	IIC_SCL=0;//时钟输出0
	return 0;
}

//产生ACK应答
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
//不产生ACK应答
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL=0;//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1;
		delay(2); //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay(2);
		IIC_SCL=0;
		delay(2);
	}
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(u8 ack)
{
	u8 i,receive=0;
	SDA_IN();//SDA设置为输入
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
	IIC_NAck();//发送nACK
	else
	IIC_Ack(); //发送ACK
	return receive;
}


void IIC_Write_Addr(u8 add,u8 date)
{
	IIC_Start();
	IIC_Send_Byte(0XA2);  //写指令
	IIC_Wait_Ack();
	IIC_Send_Byte(add);  //写指令
	IIC_Wait_Ack();
	IIC_Send_Byte(date);  //写指令
	IIC_Wait_Ack();
	IIC_Stop();

}

u8 IIC_Read_Addr(u8 add)
{
	u8 date;

	//OS_ENTER_CRITICAL();
	
	IIC_Start();
	IIC_Send_Byte(0XA2);  //写指令
	IIC_Wait_Ack();
	IIC_Send_Byte(add); 
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA3);  //写指令
	IIC_Wait_Ack();
	date=IIC_Read_Byte(0); 	
	IIC_Stop();
	//OS_EXIT_CRITICAL();
	
	return date;
}

/*秒、分钟、小时、日、月、年、分钟报警、小时报警、日报警寄存器，
编码格式为 BCD， 星期和星期报警寄存器不以 BCD 格式编码 	*/
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


/*秒、分钟、小时、日、月、年、分钟报警、小时报警、日报警寄存器，
编码格式为 BCD， 星期和星期报警寄存器不以 BCD 格式编码 	*/
void IIC_WRITE8563(u8 year, u8 month, u8 day, u8 hour, u8 mint, u8 second)	//写入初始值
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



u8 BCD_To_Decimal(u8 source_char)//将BCD码转换成十进制码
{
	u8	temp1,temp2,desit_char;
	temp1 = source_char>>4;
	temp2 = source_char&0x0f;
	desit_char = temp1*10 + temp2;
	return	desit_char;
}
	  
u8 Decimal_To_BCD(u8 source_char)//将十进制码转换成BCD码
{
	u8	temp1,temp2,desit_char;
	temp1 = source_char/10;
	temp2 = source_char%10;
	desit_char = temp1*16 + temp2;
	return	desit_char;
}


















