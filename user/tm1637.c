//#include<reg52.h>
#include "config.h"
//����˿�
//sbit clk = P1^0;
//sbit dio = P1^1;

volatile U8 g_led[5];

U8 digit_num[10] ={

	CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5, CHAR_6, CHAR_7, CHAR_8, CHAR_9,
};



#if 1
#define LED_CLK_HIGH   GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_SET)
#define LED_CLK_LOW	  GPIO_WriteBit(GPIOD,GPIO_Pin_15,Bit_RESET)

#endif


#define LED_DAT_HIGH   	GPIO_WriteBit(GPIOC,GPIO_Pin_6,Bit_SET)
#define LED_DAT_LOW  	GPIO_WriteBit(GPIOC,GPIO_Pin_6,Bit_RESET)


#define LED_DAT_READ 	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)

void LED_DAT_INPUT() {
	
  	  GPIO_InitTypeDef  GPIO_InitStructure; 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	 
}
void LED_DAT_OUTPUT() {
	
  	  GPIO_InitTypeDef  GPIO_InitStructure; 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	  
}

static void Delay_us(U8 us)
{
U16 i,j;
//OSTimeDlyHMSM(0,0,0,1);
for(j=0;j<us;j++);
	for(i=0;i<200;i++); /*���ڵ���CLK ������*/
}

///======================================
void I2CStart(void) //1637 ��ʼ
{
LED_CLK_HIGH;
LED_DAT_OUTPUT();

LED_DAT_HIGH;
Delay_us(2);
LED_DAT_LOW;
}
//=============================================
void I2Cask(void) //1637Ӧ��
{
U16 i = 0;
LED_CLK_LOW;
LED_DAT_INPUT()	;

//Delay_us(5);
while(LED_DAT_READ){

	i++;
	if(i>2000)
		break;
	
}
LED_CLK_HIGH;
Delay_us(5);

//while(LED_DAT_READ);
LED_CLK_LOW;
}
//========================================
void I2CStop(void) // 1637 ֹͣ
{
	LED_DAT_OUTPUT() ;

LED_CLK_LOW;
Delay_us(2);
LED_DAT_LOW;
Delay_us(2);
LED_CLK_HIGH;
Delay_us(2);
LED_DAT_HIGH;
}
//=========================================
				  void I2CWrByte(unsigned char oneByte) //дһ���ֽ�
{
unsigned char i;
LED_DAT_OUTPUT()  ;

for(i=0;i<8;i++)
{ LED_CLK_LOW;
if(oneByte&0x01) //��λ��ǰ
{
LED_DAT_HIGH;
}
else
{
LED_DAT_LOW;
}
Delay_us(3);
oneByte=oneByte>>1;
LED_CLK_HIGH;
Delay_us(3);
}
}
//-------------------------------------------------
#if 0
unsigned char ScanKey(void) //������
{
unsigned char rekey,rkey,i;
I2CStart();
I2CWrByte(0x42); //����������
I2Cask();
LED_DAT_HIGH; // �ڶ�����ǰ����������
for(i=0;i<8;i++) //�ӵ�λ��ʼ��
{ LED_CLK_LOW;
rekey=rekey>>1;
Delay_us(30);
LED_CLK_HIGH;
if(LED_DAT_READ)
{
rekey=rekey|0x80;
}
else
{
rekey=rekey|0x00;
}
Delay_us(30);
}
I2Cask();
I2CStop();
return (rekey);
}
#endif

///================================================
void SmgDisplay(U8 data) //д��ʾ�Ĵ���
{
unsigned char i;
U8 j = 0;
//printf("led��Ļ���� %d \r\n", data);
I2CStart();
I2CWrByte(0x40); // 40H��ַ�Լ� 44H�̶���ַģʽ,����������Լ�1ģʽ
I2Cask();
I2CStop();		I2CStart();
I2CWrByte(0xc0); //�����׵�ַ��
I2Cask();
for(i=0;i<6;i++) //��ַ�Լӣ�����ÿ�ζ�д��ַ
{


I2CWrByte(data); //������
I2Cask();
}
I2CStop();
I2CStart();
I2CWrByte(0x8f); //����ʾ ���������
I2Cask();
I2CStop();

//printf("led��Ļ����\r\n");

}

void SmgDisplay0(U8 addr, U8 data) //д��ʾ�Ĵ���
{
unsigned char i;
U8 j = 0;
//printf("led��Ļ���� %d %d \r\n", addr, data);
I2CStart();
I2CWrByte(0x40); // 40H��ַ�Լ� 44H�̶���ַģʽ,����������Լ�1ģʽ
I2Cask();
I2CStop();	

I2CStart();
I2CWrByte(0xc0+addr); //�����׵�ַ��
I2Cask();
//for(i=0;i<6;i++) //��ַ�Լӣ�����ÿ�ζ�д��ַ
{


I2CWrByte(data); //������
I2Cask();
}
I2CStop();


I2CStart();
I2CWrByte(0x8f); //����ʾ ���������
I2Cask();
I2CStop();


//printf("led��Ļ����\r\n");

}

void led_light(void) {

	I2CStart();
	I2CWrByte(0x8f); //����ʾ ���������
	I2Cask();
	I2CStop();


}

void led_down(void) {



		memset((U8 *)g_led, 0, 5);

		SmgDisplay(0);
	

}


void led_gpio_init(void) {


  	 GPIO_InitTypeDef  GPIO_InitStructure; 

	/* Configure USARTx_Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* Configure USARTx_Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);



	 
}


void led_test(void)
{
	U8 i,j;
	
	
	led_gpio_init();
	led_light();



	SmgDisplay(0xff);

	OSTimeDlyHMSM(0,0,1,500);

	SmgDisplay(0);


	for(j=0;j<6;j++) {
		for(i= 0; i<8;i++) {
			printf("i:	%d, j:	%d\r\n",j, 0x01<<i);

			if((j== 0 || j == 3)&& i==7)
				continue;
			
				
			SmgDisplay0(j, 0x01<<i);
			OSTimeDlyHMSM(0,0,0,500);
		}
	}


}



void led_init(void)
{
	U8 i,j;
	
	
	led_gpio_init();
	led_light();


	memset((U8 *)g_led, 0, 5);

	SmgDisplay(0xff);

	OSTimeDlyHMSM(0,0,2,500);

	SmgDisplay(0);




}




void led_update(U8 addr ) {



	SmgDisplay0(addr, g_led[addr]);


}






