#include "RTC.h"

unsigned char RTC_ConvertFromDec(unsigned char c)
{
	unsigned char ch = ((c>>4)*10+(0b00001111&c));
	return ch;
}

unsigned char RTC_ConvertFromBinDec(unsigned char c)
{
	unsigned char ch = ((c/10)<<4)|(c%10);
	return ch;
}

void SetTime(void)
{
	I2C_StartCondition();
	I2C_SendByte(0b11010000);
	I2C_SendByte(0);//Переходим на 0x00
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //секунды
 	I2C_SendByte(RTC_ConvertFromBinDec(35)); //минуты
 	I2C_SendByte(RTC_ConvertFromBinDec(14)); //часы
 	I2C_SendByte(RTC_ConvertFromBinDec(3)); //день недели
 	I2C_SendByte(RTC_ConvertFromBinDec(23)); //дата
 	I2C_SendByte(RTC_ConvertFromBinDec(8)); //месяц
 	I2C_SendByte(RTC_ConvertFromBinDec(17)); //год
 	I2C_StopCondition();
}

void GetTime(void)
{
	I2C_SendByteByADDR(0,0b11010000);	//переходим на адрес 0
	//_delay_ms(300);
	I2C_StartCondition(); //Отправим условие START
	I2C_SendByte(0b11010001); //отправим в устройство бит чтения
	sec = I2C_ReadByte();
	min = I2C_ReadByte();
	hour = I2C_ReadByte();
	day = I2C_ReadByte();
	date = I2C_ReadByte();
	month = I2C_ReadByte();
	year = I2C_ReadLastByte();
	I2C_StopCondition(); //Отправим условие STOP
	sec = RTC_ConvertFromDec(sec); //Преобразуем в десятичный формат
	min = RTC_ConvertFromDec(min); //Преобразуем в десятичный формат
	hour = RTC_ConvertFromDec(hour); //Преобразуем в десятичный формат
	day = RTC_ConvertFromDec(day); //Преобразуем в десятичный формат
	year = RTC_ConvertFromDec(year); //Преобразуем в десятичный формат
	month = RTC_ConvertFromDec(month); //Преобразуем в десятичный формат
	date = RTC_ConvertFromDec(date); //Преобразуем в десятичный формат
	/*SOFT_UART_byte(day);
	SOFT_UART_byte('.');
	SOFT_UART_byte(month);
	SOFT_UART_byte('.');
	SOFT_UART_byte(year);*/
	SOFT_UART_byte(date/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(date%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte('.');
	SOFT_UART_byte(month/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(month%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte('.');
	SOFT_UART_byte(year/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(year%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte('\t');
	/*SOFT_UART_byte(hour);
	SOFT_UART_byte(':');
	SOFT_UART_byte(min);
	SOFT_UART_byte(':');
	SOFT_UART_byte(sec);*/
	SOFT_UART_byte(hour/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(hour%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(':');
	SOFT_UART_byte(min/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(min%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(':');
	SOFT_UART_byte(sec/10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte(sec%10+0x30);//Преобразуем число в код числа
	SOFT_UART_byte('\t');
	
}