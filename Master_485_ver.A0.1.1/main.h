
#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "SoftUART.h"
#include "UART_STDIO.h"
#include "twi.h"
#include "RTC.h"
#define SUMSLAVE 10
uint8_t MasAddr[SUMSLAVE];
unsigned int MasAddrCursor;
unsigned int err;




#endif /* MAIN_H_ */