#include "LCD1602_Baremetal.h"

//==================================================
// Constructor
//==================================================

LCD1602_Baremetal::LCD1602_Baremetal(uint8_t rs,
                                     uint8_t en,
                                     uint8_t d4,
                                     uint8_t d5,
                                     uint8_t d6,
                                     uint8_t d7)
{
    _rs = rs;
    _en = en;
    _d4 = d4;
    _d5 = d5;
    _d6 = d6;
    _d7 = d7;
}

//==================================================
// Pulse Enable
//==================================================

void LCD1602_Baremetal::pulseEnable()
{
    digitalWrite(_en, HIGH);

    delayMicroseconds(1);

    digitalWrite(_en, LOW);

    delayMicroseconds(100);
}

//==================================================
// Send 4-bit Nibble
//==================================================

void LCD1602_Baremetal::sendNibble(uint8_t data)
{
    digitalWrite(_d4, bitRead(data, 0));
    digitalWrite(_d5, bitRead(data, 1));
    digitalWrite(_d6, bitRead(data, 2));
    digitalWrite(_d7, bitRead(data, 3));

    pulseEnable();
}

//==================================================
// Send 8-bit Byte
//==================================================

void LCD1602_Baremetal::sendByte(uint8_t data, bool isData)
{
    // RS = 0 -> Command
    // RS = 1 -> Data

    digitalWrite(_rs, isData);

    // High nibble
    sendNibble(data >> 4);

    // Low nibble
    sendNibble(data & 0x0F);

    delayMicroseconds(50);
}

//==================================================
// LCD Initialization
//==================================================

void LCD1602_Baremetal::begin()
{
    pinMode(_rs, OUTPUT);
    pinMode(_en, OUTPUT);

    pinMode(_d4, OUTPUT);
    pinMode(_d5, OUTPUT);
    pinMode(_d6, OUTPUT);
    pinMode(_d7, OUTPUT);

    delay(50);

    // HD44780 initialization

    sendNibble(0x03);
    delay(5);

    sendNibble(0x03);
    delayMicroseconds(150);

    sendNibble(0x03);

    sendNibble(0x02);

    // Function Set
    // 4-bit, 2-line, 5x8 dots
    command(0x28);

    // Display ON
    // Cursor OFF
    // Blink OFF
    command(0x0C);

    // Entry Mode
    command(0x06);

    // Clear Display
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

void LCD1602_Baremetal::setCursor(uint8_t col, uint8_t row)
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

void LCD1602_Baremetal::createChar(uint8_t location,
                                   const uint8_t charmap[])
{
    location &= 0x07;

    // Set CGRAM address
    command(0x40 | (location << 3));

    // Write 8 bytes to CGRAM
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

void LCD1602_Baremetal::print(float value, uint8_t decimals)
{
    char buffer[20];

    dtostrf(value, 1, decimals, buffer);

    print(buffer);
}
void LCD1602_Baremetal::print(double value)
{
    char buffer[20];

    dtostrf(value, 1, 2, buffer);

    print(buffer);
}
void LCD1602_Baremetal::scrollLeft()
{
    command(0x18);
}

void LCD1602_Baremetal::scrollRight()
{
    command(0x1C);
}
//==================================================
// Scroll Up Animation
//==================================================

void LCD1602_Baremetal::scrollUp(const char *line1,
                                 const char *line2,
                                 uint16_t speed)
{
    // Bước 1: line1 ở dòng 1
    clear();

    setCursor(0, 0);
    print(line1);

    delay(speed);

    // Bước 2: cả hai dòng
    clear();

    setCursor(0, 0);
    print(line1);

    setCursor(0, 1);
    print(line2);

    delay(speed);

    // Bước 3: line2 ở dòng 1
    clear();

    setCursor(0, 0);
    print(line2);

    delay(speed);
}
//==================================================
// Scroll Down Animation
//==================================================

void LCD1602_Baremetal::scrollDown(const char *line1,
                                   const char *line2,
                                   uint16_t speed)
{
    // Bước 1: line2 ở dòng 2
    clear();

    setCursor(0, 1);
    print(line2);

    delay(speed);

    // Bước 2: cả hai dòng
    clear();

    setCursor(0, 0);
    print(line1);

    setCursor(0, 1);
    print(line2);

    delay(speed);

    // Bước 3: line1 ở dòng 2
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