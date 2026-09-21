#include <LCD1602_Baremetal.h>
LCD1602_Baremetal lcd(0x27);
// Custom Characters
//==================================================

uint8_t heart[8] =
{
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};


uint8_t degree[8] =
{
    0b00110,
    0b01001,
    0b01001,
    0b00110,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};


void setup()
{
    lcd.begin();
    delay(1000);
    lcd.createChar(0, heart);
    lcd.createChar(1, degree);
}

void loop()
{
    // TEST 1
    // Basic String
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LCD1602 I2C");
    lcd.setCursor(0, 1);
    lcd.print("Baremetal");
    delay(2000);
    // TEST 2
    // Character
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Character:");
    lcd.setCursor(0, 1);
    lcd.print('A');
    delay(2000);
    // TEST 3
    // Integer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Integer:");
    lcd.setCursor(0, 1);
    lcd.print(12345);
    delay(2000);
    // TEST 4
    // Float
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Float:");
    lcd.setCursor(0, 1);
    lcd.print(25.36f);
    delay(2000);
    // TEST 5
    // Float with decimals
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Decimal:");
    lcd.setCursor(0, 1);
    lcd.print(25.3698f, 3);
    delay(2000);
    // TEST 6
    // Home
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("HOME");
    delay(1000);
    lcd.home();
    delay(1000);
    lcd.print("HOME OK");
    delay(2000);
    // TEST 7
    // Cursor
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cursor Test");
    lcd.setCursor(0, 1);
    lcd.cursor();
    delay(2000);
    lcd.noCursor();
    delay(1000);
    // TEST 8
    // Blink
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blink Test");
    lcd.setCursor(0, 1);
    lcd.blink();
    delay(3000);
    lcd.noBlink();
    delay(1000);
    // TEST 9
    // Display OFF / ON
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Display OFF");
    delay(1500);
    lcd.noDisplay();
    delay(1500);
    lcd.display();
    delay(1500);
    // TEST 10
    // Scroll Left
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LCD1602 BAREMETAL");
    delay(1000);
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollLeft();

        delay(300);
    }
    delay(1000);
    // TEST 11
    // Scroll Right
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollRight();

        delay(300);
    }
    delay(1000);
    // TEST 12
    // Scroll Up
    lcd.scrollUp(
        "LINE 1",
        "LINE 2",
        600
    );
    delay(1000);
    // TEST 13
    // Scroll Down
    lcd.scrollDown(
        "LINE 1",
        "LINE 2",
        600
    );
    delay(1000);
    // TEST 14
    // Custom Character
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Custom:");
    lcd.setCursor(0, 1);
    lcd.write(0);
    lcd.print(" LOVE ");
    lcd.write(1);
    delay(3000);
    // TEST 15
    // Temperature Display
    float temperature = 25.36;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(temperature, 2);
    lcd.print(" C");
    delay(3000);
    // TEST 16
    // Command / Data
    lcd.clear();
    lcd.command(0x80);
    lcd.write('A');
    lcd.write('B');
    lcd.write('C');
    lcd.write('D');
    delay(3000);
}