#include <SSD1306_Logwriter.h>

SSD1306_OLED display;

void setup() {

  display.begin();
  display.setFont(2); // use 8*6 font
  delay(1000);
  display.println("Logwriter");
  display.println(" ");
  display.println("Beispiel 1");
  display.println(" ");
  display.println("Nutzt 8*6 Font");
  display.println(" ");
  display.setWhiteBackground();
  delay(1000);
  display.setBlackBackground();
  delay(1000);
  display.setDisplayOff();
  delay(1000);
  display.setDisplayOn();
  delay(1000);
  display.clear();

}

void loop() {

  for(byte i=0;i<30;i++) {
   display.print("Zeile ");
   display.println(i);
  }
  delay(1000);
  display.clear();
}
