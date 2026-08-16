#include "lcd_driver.h"

void setup()
{
  // Khởi tạo LCD
  LCD_Init();


  // Bật Display
  // 0x0C = Display ON
  // Cursor OFF
  // Blink OFF
  SendByteToLCD(0x0C, false);


  // Test gửi ký tự A
  LCD_WriteChar('A');
}

void loop()
{
}

