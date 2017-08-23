/*
 * RTC.h
 *
 * Created: 25.01.2016 11:59:12
 *  Author: Владелец
 */ 


#ifndef RTC_H_
#define RTC_H_
unsigned char sec,min,hour,day,date,month,year;
#include "main.h"

unsigned char RTC_ConvertFromDec(unsigned char c);			//перевод двоично-десятичного числа в десятичное
unsigned char RTC_ConvertFromBinDec(unsigned char c);		//перевод десятичного числа в двоично-десятичное
void SetTime(void);
void GetTime(void);
#endif /* RTC_H_ */