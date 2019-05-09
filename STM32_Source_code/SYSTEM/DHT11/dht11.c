#include "dht11.h"

void GPIOG_Out_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
   
	// ����AHB����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   
	GPIO_InitStruct.GPIO_Pin         = GPIO_Pin_9; // ���õ�����
	GPIO_InitStruct.GPIO_Mode        = GPIO_Mode_OUT; // ����GPIO�˿�ģʽ����� GPIOF
	GPIO_InitStruct.GPIO_OType       = GPIO_OType_PP; // ����GPIO�˿����ͣ��������
	GPIO_InitStruct.GPIO_Speed       = GPIO_Fast_Speed; // ����GPIO�˿��ٶȣ�50M
	//GPIO_InitStruct.GPIO_PuPd        = GPIO_PuPd_UP;    // ����GPIO�˿�������������
   
	// ������ɳ�ʼ��
	GPIO_Init(GPIOG, &GPIO_InitStruct);
    
}
void GPIOG_In_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
   
	// ����AHB����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   
	GPIO_InitStruct.GPIO_Pin         = GPIO_Pin_9; // ���õ�����
	GPIO_InitStruct.GPIO_Mode        = GPIO_Mode_IN; // ����GPIO�˿�ģʽ����� GPIOF
	//GPIO_InitStruct.GPIO_OType       = GPIO_OType_PP; // ����GPIO�˿����ͣ�����
	GPIO_InitStruct.GPIO_Speed       = GPIO_Fast_Speed; // ����GPIO�˿��ٶȣ�50M
	//GPIO_InitStruct.GPIO_PuPd        = GPIO_PuPd_UP;    // ����GPIO�˿�������������
   
	// ������ɳ�ʼ��
	GPIO_Init(GPIOG, &GPIO_InitStruct);
		
}



//��λDHT11
void DHT11_Rst(void)
{
	
	GPIOG_Out_Init();
	PGout(9) = 0;
	Delay_ms(20);
	PGout(9) = 1;
	Delay_us(40);
	GPIOG_In_Init();
	
}

/*
//�ж�DHT11�������Ƿ���Ӧ
int DHT11_cheak(void)
{
	u8 retry=0;
	GPIOG_In_Init();;//SET INPUT	 
    while (PGin(9)&&retry<100)//DHT11������40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!PGin(9)&&retry<100)//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
*/

//��DHT11��ȡһ��λ
u8 DHT11_Read_Bit(void) 			 
{
    while (DHT11_IN == Bit_RESET);
    Delay_us(40);
	
    if (DHT11_IN == Bit_SET)
    {
        while (DHT11_IN == Bit_SET);
        return 1;
    }
    else
    {
        return 0;
    }		   
}


//��DHT11��ȡһ���ֽ�
u8 DHT11_Read_Byte(void)    
{        
	u8 i;
    u8 data = 0;
    for (i = 0; i < 8; i++)
    {
		
        data <<= 1;
		
        data |= DHT11_Read_Bit();
		
    }
    return data;
}

//��ȡһ������
u8 DHT11_Read_Data(u8 buffer[5])    
{        
	u8 i = 0;
	u8 checksum;
    DHT11_Rst();
    if (DHT11_IN == Bit_RESET)
    {
        //��⵽DHT11��Ӧ
        while (DHT11_IN == Bit_RESET);
        while (DHT11_IN == Bit_SET);
		
        for (i = 0; i < 5; i++)
        {
            buffer[i] = DHT11_Read_Byte(); 
        }
       /*
        while (DHT11_IN == Bit_RESET);
        GPIOG_Out_Init();
        PGout(9) = 1;
		*/
        
        checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (checksum != buffer[4])
        {
            // checksum error
            return 1;
        }
    }
    
    return 0;   
}

