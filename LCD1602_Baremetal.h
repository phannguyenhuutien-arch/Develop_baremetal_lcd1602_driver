#ifndef LCD1602_BAREMETAL_H
#define LCD1602_BAREMETAL_H

#include <Arduino.h>

class LCD1602_Baremetal
{
public:
    LCD1602_Baremetal(uint8_t rs,
                      uint8_t en,
                      uint8_t d4,
                      uint8_t d5,
                      uint8_t d6,
                      uint8_t d7);

    void begin();

    void command(uint8_t cmd);
    void write(uint8_t data);

    void clear();
    void home();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    
    void setCursor(uint8_t col, uint8_t row);

    void createChar(uint8_t location, const uint8_t charmap[]);
    
    void display();
    void noDisplay();

    
    void print(const char *text);
    
    void print(char c);
    void print(int value);
    void print(float value);
    void print(float value, uint8_t decimals);
    void print(double value);
    
    void scrollLeft();
    void scrollRight();
    
    void scrollUp(const char *line1, const char *line2, uint16_t speed);
    void scrollDown(const char *line1, const char *line2, uint16_t speed);
    
private:
    uint8_t _rs;
    uint8_t _en;
    uint8_t _d4;
    uint8_t _d5;
    uint8_t _d6;
    uint8_t _d7;

    void pulseEnable();
    void sendNibble(uint8_t data);
    void sendByte(uint8_t data, bool isData);
};

#endif