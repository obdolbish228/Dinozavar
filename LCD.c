#include "main.h"
#include "LCD.h"

void sendhalfbyte(unsigned char c){
	c &= 0x0F;
	PORTC &= ~(0x0F);
	PORTC |= c;
	E_Set;
	_delay_us(1);
	E_Reset;
	_delay_us(50);
}

void sendbyte(unsigned char c, unsigned char mode){
	unsigned char hc = 0;
	if (mode == 0)
	RS_Reset;
	else RS_Set;
	hc=c>>4;
	sendhalfbyte(hc);
	sendhalfbyte(c);
}

void LCD_Init(void){
	_delay_ms(50);
	PORTC &= ~0x3F;
	_delay_ms(100);
	sendhalfbyte(0x03);
	_delay_us(4500);
	sendhalfbyte(0x03);
	_delay_us(4500);
	sendhalfbyte(0x03);
	_delay_us(200);
	sendhalfbyte(0x02);
	_delay_ms(1);
	sendbyte(0x28, 0);//mode 4 bit, 2 lines (from our large display is 4 lines, font 5x8
	sendbyte(0x0C,0);//Display ON, Cursor OFF, blink OFF
	_delay_ms(1);
	sendbyte(0x01,0);// Clear Display
	_delay_ms(2);
	sendbyte(0x06,0);// direction left to right
	_delay_ms(1);
	sendbyte(0x02,0);//Cursor reset
	sendbyte(0X80,0);//SET POS LINE 0
	_delay_ms(2);
}

void LCD_Clear(void){
	sendbyte(0x01, 0);
	_delay_us(1500);
}

void LCD_String(char* st){
	unsigned char i=0;
	while(st[i]!=0)
	{
		sendbyte(st[i],1);
		i++;
	}
}

void LCD_SetPos(unsigned char x, unsigned char y){
	switch(y)
	{
		case 0:
			sendbyte((unsigned char)( x | 0x80), 0);
			break;
		case 1:
			sendbyte((unsigned char)((0x40+x)|0x80),0);
			break;
		case 2:
			sendbyte((unsigned char)((0x14+x)|0x80),0);
			break;
		case 3:
			sendbyte((unsigned char)((0x54+x)|0x80),0);
			break;
	}
}