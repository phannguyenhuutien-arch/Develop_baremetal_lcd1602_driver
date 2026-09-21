#include "LCD1602_Baremetal.h"


//==================================================
// Constructor
//==================================================

LCD1602_Baremetal::LCD1602_Baremetal(uint8_t address)
{
    _address = address;

    // Backlight ON
    _backlight = 0x08;
}


//==================================================
// Write data to PCF8574
//==================================================

void LCD1602_Baremetal::writePCF8574(uint8_t data)
{
    Wire.beginTransmission(_address);

    Wire.write(data | _backlight);

    Wire.endTransmission();
}


//==================================================
// Pulse Enable
//==================================================

void LCD1602_Baremetal::pulseEnable(uint8_t data)
{
    // E = HIGH

    writePCF8574(data | 0x04);

    delayMicroseconds(1);


    // E = LOW

    writePCF8574(data & ~0x04);

    delayMicroseconds(100);
}


//==================================================
// Send 4-bit Nibble
//==================================================

void LCD1602_Baremetal::sendNibble(uint8_t data,
                                   bool isData)
{
    uint8_t output = 0;


    //================================================
    // PCF8574 Pin Mapping
    //
    // P0 -> RS
    // P1 -> RW
    // P2 -> E
    // P3 -> Backlight
    // P4 -> D4
    // P5 -> D5
    // P6 -> D6
    // P7 -> D7
    //================================================


    //================================================
    // RS
    //
    // RS = 0 -> Command
    // RS = 1 -> Data
    //================================================

    if (isData)
    {
        output |= 0x01;
    }


    //================================================
    // RW = 0
    // Write mode
    //================================================

    output &= ~0x02;


    //================================================
    // D4
    //================================================

    if (data & 0x01)
    {
        output |= 0x10;
    }


    //================================================
    // D5
    //================================================

    if (data & 0x02)
    {
        output |= 0x20;
    }


    //================================================
    // D6
    //================================================

    if (data & 0x04)
    {
        output |= 0x40;
    }


    //================================================
    // D7
    //================================================

    if (data & 0x08)
    {
        output |= 0x80;
    }


    //================================================
    // Send nibble
    //================================================

    pulseEnable(output);
}


//==================================================
// Send 8-bit Byte
//==================================================

void LCD1602_Baremetal::sendByte(uint8_t data,
                                 bool isData)
{
    // High nibble

    sendNibble(data >> 4, isData);


    // Low nibble

    sendNibble(data & 0x0F, isData);


    delayMicroseconds(50);
}


//==================================================
// LCD Initialization
//==================================================

void LCD1602_Baremetal::begin()
{
    // Start I2C

    Wire.begin();


    // Wait for LCD power-up

    delay(50);


    // Backlight ON

    writePCF8574(0x00);


    //================================================
    // HD44780 4-bit initialization
    //================================================

    sendNibble(0x03, false);

    delay(5);


    sendNibble(0x03, false);

    delayMicroseconds(150);


    sendNibble(0x03, false);


    sendNibble(0x02, false);


    //================================================
    // Function Set
    //
    // 4-bit
    // 2-line
    // 5x8 dots
    //================================================

    command(0x28);


    //================================================
    // Display ON
    // Cursor OFF
    // Blink OFF
    //================================================

    command(0x0C);


    //================================================
    // Entry Mode
    //================================================

    command(0x06);


    //================================================
    // Clear Display
    //================================================

    command(0x01);

    delay(2);
}


//==================================================
// Send Command
//==================================================

void LCD1602_Baremetal::command(uint8_t cmd)
{
    sendByte(cmd, false);
}


//==================================================
// Send Data
//==================================================

void LCD1602_Baremetal::write(uint8_t data)
{
    sendByte(data, true);
}


//==================================================
// Clear Display
//==================================================

void LCD1602_Baremetal::clear()
{
    command(0x01);

    delay(2);
}


//==================================================
// Return Home
//==================================================

void LCD1602_Baremetal::home()
{
    command(0x02);

    delay(2);
}


//==================================================
// Set Cursor
//==================================================

void LCD1602_Baremetal::setCursor(uint8_t col,
                                  uint8_t row)
{
    uint8_t address;


    if (row == 0)
    {
        address = 0x00 + col;
    }
    else
    {
        address = 0x40 + col;
    }


    command(0x80 | address);
}


//==================================================
// Create Custom Character
//==================================================

void LCD1602_Baremetal::createChar(
    uint8_t location,
    const uint8_t charmap[])
{
    // LCD1602 has 8 custom characters

    location &= 0x07;


    // Set CGRAM address

    command(0x40 | (location << 3));


    // Write 8 bytes

    for (uint8_t i = 0; i < 8; i++)
    {
        write(charmap[i]);
    }
}


//==================================================
// Print String
//==================================================

void LCD1602_Baremetal::print(const char *text)
{
    while (*text)
    {
        write(*text);

        text++;
    }
}


//==================================================
// Print Character
//==================================================

void LCD1602_Baremetal::print(char c)
{
    write(c);
}


//==================================================
// Print Integer
//==================================================

void LCD1602_Baremetal::print(int value)
{
    char buffer[12];

    itoa(value, buffer, 10);

    print(buffer);
}


//==================================================
// Print Float
//==================================================

void LCD1602_Baremetal::print(float value)
{
    char buffer[20];

    dtostrf(value, 1, 2, buffer);

    print(buffer);
}


//==================================================
// Print Float with Decimal Places
//==================================================

void LCD1602_Baremetal::print(float value,
                              uint8_t decimals)
{
    char buffer[20];

    dtostrf(value,
            1,
            decimals,
            buffer);

    print(buffer);
}


//==================================================
// Print Double
//==================================================

void LCD1602_Baremetal::print(double value)
{
    char buffer[20];

    dtostrf(value, 1, 2, buffer);

    print(buffer);
}


//==================================================
// Scroll Left
//==================================================

void LCD1602_Baremetal::scrollLeft()
{
    command(0x18);
}


//==================================================
// Scroll Right
//==================================================

void LCD1602_Baremetal::scrollRight()
{
    command(0x1C);
}


//==================================================
// Scroll Up Animation
//==================================================

void LCD1602_Baremetal::scrollUp(
    const char *line1,
    const char *line2,
    uint16_t speed)
{
    // Step 1
    // line1 on row 0

    clear();

    setCursor(0, 0);

    print(line1);

    delay(speed);


    // Step 2
    // line1 + line2

    clear();

    setCursor(0, 0);

    print(line1);


    setCursor(0, 1);

    print(line2);

    delay(speed);


    // Step 3
    // line2 moves to row 0

    clear();

    setCursor(0, 0);

    print(line2);

    delay(speed);
}


//==================================================
// Scroll Down Animation
//==================================================

void LCD1602_Baremetal::scrollDown(
    const char *line1,
    const char *line2,
    uint16_t speed)
{
    // Step 1
    // line2 on row 1

    clear();

    setCursor(0, 1);

    print(line2);

    delay(speed);


    // Step 2
    // line1 + line2

    clear();

    setCursor(0, 0);

    print(line1);


    setCursor(0, 1);

    print(line2);

    delay(speed);


    // Step 3
    // line1 moves to row 1

    clear();

    setCursor(0, 1);

    print(line1);

    delay(speed);
}


//==================================================
// Cursor ON
//==================================================

void LCD1602_Baremetal::cursor()
{
    command(0x0E);
}


//==================================================
// Cursor OFF
//==================================================

void LCD1602_Baremetal::noCursor()
{
    command(0x0C);
}


//==================================================
// Cursor Blink ON
//==================================================

void LCD1602_Baremetal::blink()
{
    command(0x0F);
}


//==================================================
// Cursor Blink OFF
//==================================================

void LCD1602_Baremetal::noBlink()
{
    command(0x0E);
}


//==================================================
// Display ON
//==================================================

void LCD1602_Baremetal::display()
{
    command(0x0C);
}


//==================================================
// Display OFF
//==================================================

void LCD1602_Baremetal::noDisplay()
{
    command(0x08);
}