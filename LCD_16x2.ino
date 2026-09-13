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
    lcd.print("Select Mode (1-3):");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == '\n' || c == '\r')
        {
            if (index > 0)
            {
                buffer[index] = '\0';
                
                // Chuyển chuỗi nhập vào sang số nguyên (int)
                int command = atoi(buffer);

                lcd.clear();

                // Thực thi câu lệnh dựa trên số vừa nhập
                switch (command)
                {
                    case 1:
                        lcd.setCursor(0, 0);
                        lcd.print("Xin chao!");
                        Serial.println("Da thuc hien: Lenh 1");
                        break;

                    case 2:
                        lcd.setCursor(0, 0);
                        lcd.print("Hello!");
                        Serial.println("Da thuc hien: Lenh 2 (Hello)");
                        break;

                    case 3:
                        lcd.setCursor(0, 0);
                        lcd.print("LCD1602 Running");
                        Serial.println("Da thuc hien: Lenh 3");
                        break;

                    default:
                        lcd.setCursor(0, 0);
                        lcd.print("Lenh khong hop le");
                        Serial.println("Loi: Nhap 1, 2 hoac 3");
                        break;
                }

                index = 0; // Reset buffer
            }
        }
        else
        {
            if (index < sizeof(buffer) - 1)
            {
                buffer[index] = c;
                index++;
            }
        }
    }
}