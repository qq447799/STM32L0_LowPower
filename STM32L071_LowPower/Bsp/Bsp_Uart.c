#include "include.h"
#include "Bsp_Uart.h"

//==================================================
//函数名：UsartSendChar
//功能：串口发送一个字节
//参数：@COM ：串口基地址指针
//			@ch：要发送的字节
//返回值：无
//备注：
//==================================================
void UsartSendChar(USART_TypeDef*COM,char ch)
{
	COM->TDR = ch;
}
//==================================================
//函数名：UsartSendData
//功能：串口发送多个字节
//参数：@COM ：串口基地址指针
//			@buf：要发送的数组指针
//			@len：要发送的数据长度
//返回值：无
//备注：
//==================================================
void UsartSendData(USART_TypeDef*COM, u8* buf, u16 len)
{
		u16 cnt = 0;
    for(u16 i = 0; i < len; i++)
    {
        while((COM->ISR & USART_ISR_TC) != USART_ISR_TC)
				{
					if(cnt++ > 2000)
						break;
				}
        UsartSendChar(COM, *buf++);
				cnt = 0;
    }
}

//==================================================
//函数名：UsartSendData
//功能：串口发送多个字节
//参数：@COM ：串口基地址指针
//			@str：要发送的字符串指针
//返回值：无
//备注：
//==================================================
void UsartSendStr(USART_TypeDef*COM, const char* str)
{
	while( *str != '\0' )
    {
        UsartSendChar(COM, *str);
        str++;
    }

}


