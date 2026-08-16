#include "lcd_driver.h"

void setup()
{

    Serial.begin(9600);
    // Khởi tạo LCD
    LCD_Init();


    // Bật Display
    // 0x0C = Display ON
    // Cursor OFF
    // Blink OFF
    SendByteToLCD(0x0C, false);


    // Test gửi ký tự A
    LCD_WriteChar('A');
    Serial.println("HelloWorld")
}

void loop()
{
}

