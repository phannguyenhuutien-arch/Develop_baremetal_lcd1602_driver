#ifndef LCD1602_BAREMETAL_H
#define LCD1602_BAREMETAL_H

#include <Arduino.h>
#include <Wire.h>

class LCD1602_Baremetal
{
public:
    // Constructor
    LCD1602_Baremetal(uint8_t address = 0x27);
    // LCD Initialization
    void begin();
    // Low-level LCD functions
    void command(uint8_t cmd);
    void write(uint8_t data);
    // Basic LCD functions
    void clear();
    void home();
    // Cursor functions
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    // Set Cursor
    void setCursor(uint8_t col, uint8_t row);
    // Custom Character
    void createChar(uint8_t location,
                    const uint8_t charmap[]);
    // Display
    void display();
    void noDisplay();
    // Print functions
    void print(const char *text);
    void print(char c);
    void print(int value);
    void print(float value);
    void print(float value, uint8_t decimals);
    void print(double value);
    // Horizontal Scroll
    void scrollLeft();
    void scrollRight();
    // Vertical Scroll Animation
    void scrollUp(const char *line1,
                  const char *line2,
                  uint16_t speed);

    void scrollDown(const char *line1,
                    const char *line2,
                    uint16_t speed);


private:
    // I2C Address
    uint8_t _address;
    // PCF8574 control
    uint8_t _backlight;
    // Internal functions
    void writePCF8574(uint8_t data);

    void pulseEnable(uint8_t data);

    void sendNibble(uint8_t data,
                    bool isData);

    void sendByte(uint8_t data,
                  bool isData);
};

#endif