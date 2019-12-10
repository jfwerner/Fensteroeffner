
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}


void loop(void) {
  int temp = 10;
  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_courB10_tf); // choose a suitable font
  //u8g2.drawStr(0,10,"Hello World!");  // write something to the internal memory
  u8g2.drawStr(0,20,"Temperature");
  u8g2.setFont(u8g2_font_courB24_tf);
  u8g2.setCursor(40,50); //für .print braucht man setCursor
  u8g2.print(temp);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}
// + String(temp,0)
