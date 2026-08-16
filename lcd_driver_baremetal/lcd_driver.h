#ifndef _LCD_BAREMETAL_H
#define _LCD_BAREMETAL_H
// LCD1602 HD44780 - 4 BIT MODE
//==================================================
// KHAI BÁO CHÂN LCD
//==================================================


#define LCD_RS 12
#define LCD_E  11


#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

void SendByteToLCD(byte data, bool rs);
void SendNibble(byte data);
void PulseEnable();
void LCD_Init();
void LCD_WriteChar(char c);
#endif // _LCD_BAREMETAL_H
