/*********************************************************************
This is a library for monochrome OLEDs based on SSD1306 drivers
It is NOT a complete Library if you are looking for all the features
this display can do! This Library has a very small Memory/RAM footprint (~377Byte)
so you can combine it with other libraries and can still run it on an Arduino UNO.
There is no graphic implemented and only 2 simple fixed fonts (8*8 and 8*6).

I just tested it with a 128x64 Display.

Function:
It's just a simple textfield with 8 lines (default). It works like the output 
of the serial monitor. With print/println you will write to the last line.
Example:
	display.print("Test ");
	display.print(56.8);
	display.println("V");
Will produce this output in the last line of the display:
	Test 56.8V
With the next display.print a new line will be written and you will find this text 
on the secondlast line.

This library is licensed under the GNU GPLv3 (https://www.gnu.org/licenses/gpl.html) open source license.


**********************************************************************/

#ifndef _SSD1306_LOGWRITER_H_
#define _SSD1306_LOGWRITER_H_

#ifdef __AVR__
  #include <avr/pgmspace.h>
#endif

#include <stdlib.h>

#include <Wire.h>
#include "Arduino.h"
#include "Print.h"
#include <SPI.h>

#include <SSD1306_Logwriter_font.h>
 
#define SSD1306_MAX_COL 								21
#define SSD1306_MAX_ROW 								8

#define SSD1306_ADDRESS 								0x3C
#define SSD1306_PAGE_ADDRESSING							0x02
#define SSD1306_COMMAND_DISPLAY_OFF 					0xAE
#define SSD1306_COMMAND_DISPLAY_ON 						0xAF
#define SSD1306_COMMAND_BLACK_BACKGROUND 				0xA6
#define SSD1306_COMMAND_WHITE_BACKGROUND 				0xA7
#define SSD1306_COMMAND_MODE 							0x80
#define SSD1306_DATA_MODE 								0x40
#define SSD1306_SET_CONTRAST_CONTROL					0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME					0xA4
#define SSD1306_DISPLAY_ALL_ON							0xA5
#define SSD1306_NORMAL_DISPLAY							0xA6
#define SSD1306_INVERT_DISPLAY							0xA7
#define SSD1306_DISPLAY_OFF								0xAE
#define SSD1306_DISPLAY_ON								0xAF
#define SSD1306_NOP										0xE3
#define SSD1306_HORIZONTAL_SCROLL_RIGHT					0x26
#define SSD1306_HORIZONTAL_SCROLL_LEFT					0x27
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT	0x29
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT		0x2A
#define SSD1306_DEACTIVATE_SCROLL						0x2E
#define SSD1306_ACTIVATE_SCROLL							0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA				0xA3
#define SSD1306_SET_LOWER_COLUMN						0x00
#define SSD1306_SET_HIGHER_COLUMN						0x10
#define SSD1306_MEMORY_ADDR_MODE						0x20
#define SSD1306_SET_COLUMN_ADDR							0x21
#define SSD1306_SET_PAGE_ADDR							0x22
#define SSD1306_PAGE_ADDR_BASE							0xB0
#define SSD1306_SET_START_LINE							0x40
#define SSD1306_SET_SEGMENT_REMAP						0xA0
#define SSD1306_SET_MULTIPLEX_RATIO						0xA8
#define SSD1306_COM_SCAN_DIR_INC						0xC0
#define SSD1306_COM_SCAN_DIR_DEC						0xC8
#define SSD1306_SET_DISPLAY_OFFSET						0xD3
#define SSD1306_SET_COM_PINS							0xDA
#define SSD1306_CHARGE_PUMP								0x8D
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO				0xD5
#define SSD1306_SET_PRECHARGE_PERIOD					0xD9
#define SSD1306_SET_VCOM_DESELECT						0xDB

class SSD1306_OLED : public Print {
    private:
		byte px, py, inv;
		void sendCommand(byte command);
		void sendData(byte data);
		void scrollBuffer(void);
		void setPageMode(void);
		void setCursor(byte posX, byte posY);
		size_t write(uint8_t c);
		void printBuffer(void);
	
	public:
/*		char * printBufferLine(byte line); */
	    /* Constructor to use the full display */
		SSD1306_OLED(void);
	    /* Constructor to use the only a part of the display from row */
		SSD1306_OLED(byte _ssd1306_min_row);
	    /* Constructor to use a part of the display only between min_row and max_row*/
		SSD1306_OLED(byte _ssd1306_min_row, byte _ssd1306_max_row);
#ifdef ESP8266
        void begin(uint8_t _sda, uint8_t _scl);
#endif
        /* be sure to call begin() inside your setup block */
		void begin(void);
		/* sets the background to black / inverts all Pixel if it was white before */
		void setBlackBackground(void);
		/* sets the background to white / inverts all Pixel if it was black before */
		void setWhiteBackground(void);
		/* switches the display off */
		void setDisplayOff(void);
		/* switches the display on */
		void setDisplayOn(void);
        /* selects the font to be used:
           1 = 8*8 Font (default)
		   2 = 8*6 Font    */
		void setFont(byte _myfont);
		/* Clear the display */
		void clear(void);
};

#endif /* _SSD1306_LOGWRITER_H_ */
