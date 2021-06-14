#include <stdlib.h>
#include <stdio.h>
#define LCD_Dir  DDRA			/* Define LCD data port direction */
#define LCD_Port PORTA			/* Define LCD data port */
#define RS PA7				/* Define Register Select pin */
#define EN PA6 				/* Define Enable signal pin */


void LCD_Command(unsigned char cmnd)
{
	LCD_Port = (LCD_Port & 0xF0) | (cmnd >> 4); //here we convert 8 bit cmnd into higher 4 bit (nibbles ) as we use AND operation with 11110000
	LCD_Port &= ~ (1<<RS);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	
	_delay_us(200);
	
	LCD_Port = (LCD_Port & 0xF0) |(cmnd & 0x0F); // here we shift the cmnd to left by 4 position to get lower 4bit(nibble)
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
	
}

void LCD_Char(unsigned char data)
{
	
	LCD_Port = (LCD_Port & 0xF0) | (data >> 4);
	LCD_Port |= (1<<RS);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	
	_delay_us(200);
	
	LCD_Port = (LCD_Port & 0xF0) |(data& 0x0F);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);

}

void LCD_Init(void)
{
	LCD_Dir = 0xFF;
	_delay_ms(20);
	
	LCD_Command(0x02);
	LCD_Command(0x28);
	LCD_Command(0x0c);
	LCD_Command(0x06);
	LCD_Command(0x01);
	_delay_ms(2);
	
}

void LCD_String(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_Char(str[i]);
	}
	
}

void LCD_String_xy(char row,char pos,char *str)
{
	
	if(row==0 && pos<20)
	LCD_Command((pos&0x0F)|0x80);
	else if (row==1 && pos<20)
	LCD_Command((pos & 0x0F)|0xC0);
	else if (row==2 && pos<20)
	{
		LCD_Command(((pos) & 0x0F)+0x94);
	}
	
	else if (row==3 && pos<20)
	{
		LCD_Command(((pos) & 0x0F)+0xD4);
	}
	
	LCD_String(str);
	
}

void LCD_Clear()
{
	LCD_Command(0x01);
	_delay_ms(2);
	LCD_Command(0x80);
	
}