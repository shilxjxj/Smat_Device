#include "dht11.h"

void GPIOG_Out_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
   
	// 配置AHB总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   
	GPIO_InitStruct.GPIO_Pin         = GPIO_Pin_9; // 配置的引脚
	GPIO_InitStruct.GPIO_Mode        = GPIO_Mode_OUT; // 配置GPIO端口模式：输出 GPIOF
	GPIO_InitStruct.GPIO_OType       = GPIO_OType_PP; // 配置GPIO端口类型：推挽输出
	GPIO_InitStruct.GPIO_Speed       = GPIO_Fast_Speed; // 配置GPIO端口速度：50M
	//GPIO_InitStruct.GPIO_PuPd        = GPIO_PuPd_UP;    // 配置GPIO端口上下拉：上拉
   
	// 配置完成初始化
	GPIO_Init(GPIOG, &GPIO_InitStruct);
    
}
void GPIOG_In_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
   
	// 配置AHB总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   
	GPIO_InitStruct.GPIO_Pin         = GPIO_Pin_9; // 配置的引脚
	GPIO_InitStruct.GPIO_Mode        = GPIO_Mode_IN; // 配置GPIO端口模式：输出 GPIOF
	//GPIO_InitStruct.GPIO_OType       = GPIO_OType_PP; // 配置GPIO端口类型：输入
	GPIO_InitStruct.GPIO_Speed       = GPIO_Fast_Speed; // 配置GPIO端口速度：50M
	//GPIO_InitStruct.GPIO_PuPd        = GPIO_PuPd_UP;    // 配置GPIO端口上下拉：上拉
   
	// 配置完成初始化
	GPIO_Init(GPIOG, &GPIO_InitStruct);
		
}



//复位DHT11
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
//判断DHT11传感器是否响应
int DHT11_cheak(void)
{
	u8 retry=0;
	GPIOG_In_Init();;//SET INPUT	 
    while (PGin(9)&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!PGin(9)&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
*/

//从DHT11读取一个位
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


//从DHT11读取一个字节
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

//读取一次数据
u8 DHT11_Read_Data(u8 buffer[5])    
{        
	u8 i = 0;
	u8 checksum;
    DHT11_Rst();
    if (DHT11_IN == Bit_RESET)
    {
        //检测到DHT11响应
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

