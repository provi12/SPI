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

void spi_init_master (void)
{
	DDRB = (1<<5)|(1<<7);              //Set MOSI, SCK as Output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
	//Prescaler: Fosc/16, Enable Interrupts
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
	SPDR = data;                       //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	return(SPDR);                      //Return received data
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
  unsigned char data; 
   uint8_t x = 0;
  spi_init_master();  
  LCD_Init();
  LCD_String("Test");
  while(1)
  {
	  data = spi_tranceiver(++x);
	  test_value(data);
	  _delay_ms(20);  
  }
  

  
}

