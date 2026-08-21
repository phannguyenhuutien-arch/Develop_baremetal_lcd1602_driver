#include <LCD1602_Baremetal.h>

LCD1602_Baremetal lcd(
    12,   // RS
    11,   // E
    5,    // D4
    4,    // D5
    3,    // D6
    2     // D7
);

void setup()
{
    lcd.begin();

    lcd.print("Hello World");

    lcd.setCursor(0, 1);

    lcd.print("LCD1602");
}

void loop()
{
}