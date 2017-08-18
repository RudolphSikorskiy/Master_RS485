#include "SoftUART.h"
#define BufLEN 32

uint8_t n=0;						// ������ ������
char instr[BufLEN];					// ����� ������
char BUF[BufLEN];



//--------------------------------------------------------------------------------------------//

ISR(INT0_vect)
{
	GICR&=~(1<<6);						//��������� ���������� �� INT0
	MCUCR&=~(1<<1);						//��������� ���������� �� ������������ ������ ������� �� INT0  MLN/BTREIT/2
	_delay_us(MLN/BTREIT/2);
	if (!CheckBit(PIND,RX_PIN))			//n=PIND&(1<<RX_PIN);
	{
		uint8_t x = SOFT_UART_read();
		instr[n] = x;
		//USART_Transmit(x);
		//printf("%c",x);
		//SOFT_UART_byte(x);
		
		n++;
		
		if(n>BufLEN) n=0;					//�������� ����������� �������
	}
	
	//-----------------------------------------------------------------------------------------------------//
	
	
	
	//-----------------------------------------------------------------------------------------------------//
	
	GICR|=(1<<6);						//��������� ���������� �� INT0
	MCUCR|=(1<<1);						//���������� �� ������������ ������ ������� �� INT0
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_byte( char a)			// �������� �����
{
	SOFT_UART_bit(0x00);//start bit
	for (int i = 0; i < 8; i++)
	{
		if ((a >> i) & 0x01)
		{
			SOFT_UART_bit(0x01);//data bit
		}
		else
		{
			SOFT_UART_bit(0x00);//data bit
		}
	}
	SOFT_UART_bit(0x01);//stop bit
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_init(void)					// ������������� ����������� �����
{
	DDRD |=(1<<TX_PIN);
	PORTD |=(1<<TX_PIN);
	DDRD &= ~(1<<RX_PIN);
	GICR|=(1<<6);   //��������� ���������� �� INT0
	MCUCR|=(1<<1); //���������� �� ������������ ������ ������� �� INT0

}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_bit(char b)			//�������� ����
{
	if (b == 0x00)
	{
		PORTD &= ~(1<<TX_PIN);
	}
	_delay_us(MLN/BTREIT);
	PORTD |= (1<<TX_PIN);
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_send( char *str)		//�������� �����
{
	unsigned char i=0;
	while (str[i])
	{
		SOFT_UART_byte(str[i++]);
	}
}

//--------------------------------------------------------------------------------------------//

unsigned char SOFT_UART_read(void)			// ����� ������
{
	char i;
	unsigned char ch=0;
	for(i=0;i<8;i++)
	{
		_delay_us(MLN/BTREIT);
		if(CheckBit(PIND,RX_PIN)) ch|= 1<<i;
	}
	return ch;


}

//--------------------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------------------//

char *OperationResponse(void)				// ������� ������ ���������� ��� ����������
{
	//SOFT_UART_byte(command);
	/*_delay_ms(10);
	SOFT_UART_byte(comand);					// �������� ������� ������*/
	//USART_Transmit_str(instr);
	
	memcpy(BUF, instr, sizeof(instr));
	
	
	
//--------------------------------------------------------------------------------------------//

	n=0;
	instr[0] = '\0';
	return BUF;
	
}

//--------------------------------------------------------------------------------------------//