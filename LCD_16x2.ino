//CHUYEN TU CHUOI SANG FLOAT 

#include <LCD1602_Baremetal.h>

LCD1602_Baremetal lcd(
    12,   // RS
    11,   // E
    5,    // D4
    4,    // D5
    3,    // D6
    2     // D7
);

char buffer[20];
byte index = 0;

void setup()
{
    Serial.begin(9600);

    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.print("Enter float:");
    
    Serial.println("Nhap so float:");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();

        // Khi nhan Enter
        if (c == '\n' || c == '\r')
        {
            if (index > 0)
            {
                // Ket thuc chuoi
                buffer[index] = '\0';

                // Chuyen chuoi -> float
                float value = atof(buffer);

                // Xoa man hinh
                lcd.clear();

                // Hien thi gia tri
                lcd.setCursor(0, 0);
                lcd.print(value);

                // Hien thi lai tren Serial
                Serial.print("LCD = ");
                Serial.println(value);

                // Reset buffer
                index = 0;
            }
        }
        else
        {
            // Luu ky tu vao buffer
            if (index < sizeof(buffer) - 1)
            {
                buffer[index] = c;
                index++;
            }
        }
    }
}