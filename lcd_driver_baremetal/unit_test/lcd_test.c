unit-test
Công dụng: 
giúp test độc lập để kiểm tra phần cứng hoạt động đúng chức năng hay không
Giúp người mới dễ tiếp cận -> bắt đầu tiếp cận bằng unit-test và example
Powerpoint:
mapping giữa code với lưu đồ


//================== Pin Definition ==================
#define LCD_RS 12
#define LCD_E  11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

//================== Pulse Enable ==================
void PulseEnable()
{
  digitalWrite(LCD_E, HIGH);
  delayMicroseconds(2);
  digitalWrite(LCD_E, LOW);
  delayMicroseconds(100);
}

//================== Send 4-bit ==================
void SendNibble(byte data)
{
  digitalWrite(LCD_D4, bitRead(data, 0));
  digitalWrite(LCD_D5, bitRead(data, 1));
  digitalWrite(LCD_D6, bitRead(data, 2));
  digitalWrite(LCD_D7, bitRead(data, 3))

  PulseEnable();
}

//================== Send 8-bit ==================
void SendByteToLCD(byte data, bool isData)
{
  digitalWrite(LCD_RS, isData);

  // Gửi 4 bit cao (MSB)
  SendNibble(data >> 4);

  // Gửi 4 bit thấp (LSB)
  SendNibble(data & 0x0F);

  delayMicroseconds(50);
}

//================== LCD Initialization ==================
void LCD_Init()
{
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_E, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);

  delay(50);

  SendNibble(0x03);
  delay(5);

  SendNibble(0x03);
  delayMicroseconds(150);

  SendNibble(0x03);
  SendNibble(0x02);

  SendByteToLCD(0x28, false); // 4-bit, 2 dòng
  SendByteToLCD(0x0C, false); // Display ON
  SendByteToLCD(0x06, false); // Entry mode
  SendByteToLCD(0x01, false); // Clear

  delay(5);
}

void setup()
{
  LCD_Init();

  // Đợi để xung khởi tạo kết thúc
  delay(2000);

  // Gửi duy nhất ký tự 'A'
  SendByteToLCD('A', true);
}

void loop()
{
  // Không làm gì thêm
}
