#include <LCD1602_Baremetal.h>

//==================================================
// LCD Pin Definition
//==================================================

LCD1602_Baremetal lcd(
    12,   // RS
    11,   // E
    5,    // D4
    4,    // D5
    3,    // D6
    2     // D7
);


//==================================================
// Custom Character: Degree
//==================================================

byte degreeChar[8] =
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


//==================================================
// Test 1: Basic Print
//==================================================

void testBasicPrint()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("LCD1602");

    lcd.setCursor(0, 1);
    lcd.print("Baremetal");

    delay(5000);
}


//==================================================
// Test 2: Integer
//==================================================

void testInteger()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Integer:");

    lcd.setCursor(0, 1);
    lcd.print(12345);

    delay(5000);
}


//==================================================
// Test 3: Float
//==================================================

void testFloat()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Float:");

    lcd.setCursor(0, 1);
    lcd.print(25.36, 2);

    delay(5000);
}


//==================================================
// Test 4: Custom Character
//==================================================

void testCustomChar()
{
    lcd.clear();

    lcd.createChar(0, degreeChar);

    lcd.setCursor(0, 0);
    lcd.print("Temperature:");

    lcd.setCursor(0, 1);
    lcd.print(25.36, 2);

    lcd.write(0);

    lcd.print("C");

    delay(2000);
}


//==================================================
// Test 5: Cursor
//==================================================

void testCursor()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Cursor Test");

    lcd.setCursor(5, 1);

    lcd.cursor();

    delay(5000);

    lcd.noCursor();

    delay(5000);
}


//==================================================
// Test 6: Blink
//==================================================

void testBlink()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Blink Test");

    lcd.setCursor(5, 1);

    lcd.blink();

    delay(3000);

    lcd.noBlink();

    delay(1000);
}


//==================================================
// Test 7: Display ON / OFF
//==================================================

void testDisplay()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Display Test");

    delay(5000);

    lcd.noDisplay();

    delay(5000);

    lcd.display();

    delay(5000);
}


//==================================================
// Test 8: Scroll Left
//==================================================

void testScrollLeft()
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ABCDEFGHIJKLMNOP");

    for (int i = 0; i < 10; i++)
    {
        lcd.scrollLeft();
        delay(200);
    }

    delay(500);
}


//==================================================
// Test 9: Scroll Right
//==================================================

void testScrollRight()
{
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollRight();
        delay(200);
    }

    delay(500);
}


//==================================================
// Test 10: Scroll Up / Down
//==================================================

void testScrollVertical()
{
    lcd.scrollDown("Hello", "World", 500);

    delay(500);

    lcd.scrollUp("Hello", "World", 500);

    delay(500);
}


//==================================================
// Setup
//==================================================

void setup()
{
    lcd.begin();

    // Test basic functions
    testBasicPrint();

    // Test integer
    testInteger();

    // Test float
    testFloat();

    // Test custom character
    testCustomChar();

    // Test cursor
    testCursor();

    // Test blink
    testBlink();

    // Test display
    testDisplay();

    // Test scroll
    testScrollLeft();

    testScrollRight();

    // Test vertical animation
    testScrollVertical();
}


//==================================================
// Loop
//==================================================

void loop()
{
}