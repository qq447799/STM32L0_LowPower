#include "include.h"
#include "Bsp_Uart.h"

//==================================================
//��������UsartSendChar
//���ܣ����ڷ���һ���ֽ�
//������@COM �����ڻ���ַָ��
//			@ch��Ҫ���͵��ֽ�
//����ֵ����
//��ע��
//==================================================
void UsartSendChar(USART_TypeDef*COM,char ch)
{
	COM->TDR = ch;
}
//==================================================
//��������UsartSendData
//���ܣ����ڷ��Ͷ���ֽ�
//������@COM �����ڻ���ַָ��
//			@buf��Ҫ���͵�����ָ��
//			@len��Ҫ���͵����ݳ���
//����ֵ����
//��ע��
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
//��������UsartSendData
//���ܣ����ڷ��Ͷ���ֽ�
//������@COM �����ڻ���ַָ��
//			@str��Ҫ���͵��ַ���ָ��
//����ֵ����
//��ע��
//==================================================
void UsartSendStr(USART_TypeDef*COM, const char* str)
{
	while( *str != '\0' )
    {
        UsartSendChar(COM, *str);
        str++;
    }

}


