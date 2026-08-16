// Reference  https://cdn.sparkfun.com/assets/9/5/f/7/b/HD44780.pdf
// Flow: Figure 24 4-Bit interface page 46
//==================================================
// HÀM TẠO XUNG ENABLE
// Figure 17, page 33
//==================================================
void PulseEnable()
{
  digitalWrite(LCD_E, HIGH);
  delayMicroseconds(1);


  digitalWrite(LCD_E, LOW);
  delayMicroseconds(100);
}


//==================================================
// HÀM GỬI 4 BIT
//==================================================


void SendNibble(byte data)
{
  digitalWrite(LCD_D4, bitRead(data, 0));
  digitalWrite(LCD_D5, bitRead(data, 1));
  digitalWrite(LCD_D6, bitRead(data, 2));
  digitalWrite(LCD_D7, bitRead(data, 3));


  PulseEnable();
}




//==================================================
// HÀM GỬI 1 BYTE
//==================================================


void SendByteToLCD(byte data, bool rs)
{
  // RS = 0: Command
  // RS = 1: Data
  digitalWrite(LCD_RS, rs);


  // Gửi 4 bit cao - MSB
  SendNibble(data >> 4);


  // Gửi 4 bit thấp - LSB
  SendNibble(data & 0x0F);


  delayMicroseconds(50);
}




//==================================================
// HÀM KHỞI TẠO LCD
//==================================================
void LCD_Init()
{
  // Cấu hình các chân LCD là OUTPUT
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_E, OUTPUT);


  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);


  // Trạng thái ban đầu
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_E, LOW);
  // BƯỚC 1: Chờ LCD ổn định sau khi cấp nguồn
  delay(20);
  // BƯỚC 2: Gửi 0011
  SendNibble(0x03);
  // Chờ > 4.1 ms
  delay(5);
  // BƯỚC 3: Gửi 0011 lần 2
  SendNibble(0x03);
  // Chờ > 100 us
  delayMicroseconds(150);
  // BƯỚC 4: Gửi 0011 lần 3
  SendNibble(0x03);
  // BƯỚC 5: Chuyển LCD sang giao tiếp 4-bit
  SendNibble(0x02);
  /*
   * BƯỚC 6: FUNCTION SET 
   * 0x28 = 0010 1000
   * DL = 0 → 4-bit 
   * N  = 1 → 2 dòng 
   * F  = 0 → font 5x8
   */
  SendByteToLCD(0x28, false);
  // BƯỚC 7: DISPLAY OFF
  // 0x08 = 0000 1000
  SendByteToLCD(0x08, false);




  //================================================
  // BƯỚC 8: DISPLAY CLEAR
  //
  // 0x01 = 0000 0001
  //================================================


  SendByteToLCD(0x01, false);


  // Clear Display cần thời gian xử lý
  delay(2);




  //================================================
  // BƯỚC 9: ENTRY MODE SET
  //
  // 0x06 = 0000 0110
  //================================================

  SendByteToLCD(0x06, false);
}

void LCD_WriteChar(char c)
{
  // RS = 1 → gửi DATA
  SendByteToLCD(c, true);
}

