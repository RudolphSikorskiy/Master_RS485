#include "UART_STDIO.h"

char MyADDR[] = "60";
unsigned int AddrLen = sizeof(MyADDR)-1;

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

 void USARTinit(void)
 {	 
	 UBRRL=51; //103-9600 51-19.2
	 UCSRB=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
	 UCSRC=(1<<URSEL)|(3<<UCSZ0);

	 DDRD = 0xFF;
	PORTD = 00000100;

	 //blink13(3); //ready indication
	 IDX=0;
	 done=0;
	 sei();

	 stdout = &mystdout;
}
 

int uart_putchar(char c, FILE *stream)
{
   if (c == '\n')
   uart_putchar('\r', stream);
   loop_until_bit_is_set(UCSRA, UDRE);
   UDR = c;
   return 0;
}

void clearStr(char* str)
{
        for(IT=0;IT<LEN;IT++)
                str[IT]=0;
}

ISR(USART_RXC_vect)
{
        PORTD &= ~(1<<(PORTD4));
		char bf= UDR;
        buffer[IDX]=bf;
        IDX++;
		if (bf == '*' || IDX >= LEN)
        {
				buffer[IDX-1]='\0';
                IDX=0;
                done=1;
				SOFT_UART_send(buffer);
				SOFT_UART_send("\r\n");
				buffer[0] = '\0';
				//printf("%s",buffer);
				//Response485();
				
        }
		//printf("%c",buffer[IDX]);

}
/*
char Response485(void)				// Возврат строки полученной при прерывании
{
	memcpy(response, buffer, sizeof(response)); // тут возможно нужен размер респонса
	
	
	
//--------------------------------------------------------------------------------------------//

	IDX=0;
	buffer[0] = '\0';
	return response;
	
}*/