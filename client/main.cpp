/*
 * GccApplication5.cpp
 *
 * Created: 04-06-2021 16:55:20
 * Author : Prashant Mishra
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_lib.h"

void spi_init_client (void)
{
	DDRB=(1<<6);                                  //MISO as OUTPUT
	SPCR=(1<<SPE);                                //Enable SPI
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
	SPDR = data;                                  //Load data into buffer
	while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
	return(SPDR);                                 //Return received data
}

 void test_value(unsigned long a)        //Main display
 {
	 
	 
	 char st[12];

	 
	 sprintf(st,"%lu",a);

	 LCD_Clear();
	 LCD_String_xy(1,1,"data  :          ");
	 LCD_String_xy(1,8,st);
	 
	 
	 
 }

int main(void)
{
 spi_init_client();                             //Initialize slave SPI
    uint8_t x = 0;
 unsigned char data;
  LCD_Init();
  LCD_String("Test");
  while(1)
  {
	  data = spi_tranceiver(++x);
	  test_value(data);
	  _delay_ms(20);  
  }
_delay_ms(20);  

  
}

