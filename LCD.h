/*
 * LCD.h
 *
 * Created: 23.08.2022 20:40:53
 *  Author: Aboba
 */ 


#ifndef LCD_H_
#define LCD_H_

#define RS_Set PORTC |= 0x10
#define RS_Reset PORTC &= ~(0x10)
#define E_Set PORTC |= 0x20
#define E_Reset PORTC &= ~(0x20)

void sendhalfbyte(unsigned char c);
void sendbyte(unsigned char c, unsigned char mode);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char* st);
void LCD_SetPos(unsigned char x, unsigned char y);

#endif /* LCD_H_ */