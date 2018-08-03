/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers
More details in header file!
*********************************************************************/

#ifdef __AVR__
  #include <avr/pgmspace.h>
#endif

#include <stdlib.h>

#include <Wire.h>
#include <SSD1306_Logwriter.h>

char dispData[SSD1306_MAX_ROW][SSD1306_MAX_COL];
//char dispData[1][1];
byte posInLine = 0;
byte ssd1306_min_row = 0;
byte ssd1306_max_row = SSD1306_MAX_ROW;
byte ssd1306_max_col = 16;
enum myfont_t { font_8x8, font_8x6 };
myfont_t myfont;


SSD1306_OLED::SSD1306_OLED(void){ 
	ssd1306_min_row=0;
}

SSD1306_OLED::SSD1306_OLED(byte _ssd1306_min_row){ 
	ssd1306_min_row=_ssd1306_min_row;
}

SSD1306_OLED::SSD1306_OLED(byte _ssd1306_min_row, byte _ssd1306_max_row){ 
	ssd1306_min_row=_ssd1306_min_row;
	ssd1306_max_row=_ssd1306_max_row;
}

void SSD1306_OLED::begin(void) {
	for(byte i=ssd1306_min_row; i < ssd1306_max_row; i++) {
		for(byte j=0; j < SSD1306_MAX_COL; j++) {
			dispData[i][j]=' ';
		}
	}
	
	Wire.begin();
	sendCommand(SSD1306_DISPLAY_OFF);
    sendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    sendCommand(0x80);
    sendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    sendCommand(0x3F);
    sendCommand(SSD1306_SET_DISPLAY_OFFSET);
    sendCommand(0x0);
    sendCommand(SSD1306_SET_START_LINE | 0x0);
    sendCommand(SSD1306_CHARGE_PUMP);
	sendCommand(0x14);
    sendCommand(SSD1306_MEMORY_ADDR_MODE);
    sendCommand(0x00);
    sendCommand(SSD1306_SET_SEGMENT_REMAP | 0x1);
    sendCommand(SSD1306_COM_SCAN_DIR_DEC);
    sendCommand(SSD1306_SET_COM_PINS);
    sendCommand(0x12);
    sendCommand(SSD1306_SET_CONTRAST_CONTROL);
	sendCommand(0xCF);
    sendCommand(SSD1306_SET_PRECHARGE_PERIOD);
	sendCommand(0xF1);
    sendCommand(SSD1306_SET_VCOM_DESELECT);
    sendCommand(0x40);
    sendCommand(SSD1306_DISPLAY_ALL_ON_RESUME);
    sendCommand(SSD1306_NORMAL_DISPLAY);
	sendCommand(SSD1306_DISPLAY_ON);
/*    setDisplayOff();
    setBlackBackground();
	setPageMode();
	clear();
    setDisplayOn(); */
    setWhiteBackground();
    delay(500);
    setBlackBackground();	
	printBuffer();
}

void SSD1306_OLED::setCursor(byte posX, byte posY) {

    if ( myfont == font_8x8) {
		sendCommand(SSD1306_SET_LOWER_COLUMN  + (8 * posX & 0x0F)); // set column lower address
		sendCommand(SSD1306_SET_HIGHER_COLUMN + ((8 * posX >> 4) & 0x0F)); // set column higher address
		sendCommand(SSD1306_PAGE_ADDR_BASE + posY); // set page address
	}
    if ( myfont == font_8x6) {
		sendCommand(SSD1306_SET_LOWER_COLUMN  + (6 * posX & 0x0F)); // set column lower address
		sendCommand(SSD1306_SET_HIGHER_COLUMN + ((6 * posX >> 4) & 0x0F)); // set column higher address
		sendCommand(SSD1306_PAGE_ADDR_BASE + posY); // set page address
	}
}

void SSD1306_OLED::setWhiteBackground(void) {
	sendCommand(SSD1306_COMMAND_WHITE_BACKGROUND);
}

void SSD1306_OLED::setBlackBackground(void) {
	sendCommand(SSD1306_COMMAND_BLACK_BACKGROUND);
}

void SSD1306_OLED::setDisplayOff(void) {
	sendCommand(SSD1306_COMMAND_DISPLAY_OFF);
}

void SSD1306_OLED::setDisplayOn(void) {
	sendCommand(SSD1306_COMMAND_DISPLAY_ON);
}

void SSD1306_OLED::sendCommand(byte command) {
	Wire.beginTransmission(SSD1306_ADDRESS); 
	Wire.write(SSD1306_COMMAND_MODE); 
	Wire.write(command); 
	Wire.endTransmission(); 
}

void SSD1306_OLED::sendData(byte data) {
	Wire.beginTransmission(SSD1306_ADDRESS);
	Wire.write(SSD1306_DATA_MODE);
	Wire.write(data);
	Wire.endTransmission();
}

void SSD1306_OLED::setPageMode(void) {
	byte addressingMode = SSD1306_PAGE_ADDRESSING;
	sendCommand(SSD1306_MEMORY_ADDR_MODE); 	//set addressing mode
	sendCommand(SSD1306_PAGE_ADDRESSING); 	//set page addressing mode
}
 
void SSD1306_OLED::setFont(byte _myfont) {
	if (_myfont == 1) {
		ssd1306_max_col = 16;
		myfont = font_8x8; ;
	}
	if (_myfont == 2) {
		ssd1306_max_col = 21;
		myfont = font_8x6; ;
	}
}

void SSD1306_OLED::clear(void) {
	for(byte col = 0; col < SSD1306_MAX_COL; col++)	{
		for(byte row = 0; row < SSD1306_MAX_ROW; row++) { 
			dispData[row][col]=' ';
		}
	}
	printBuffer();
	posInLine=0;
}
 
void SSD1306_OLED::printChar(char pChar) {

	// Display "?" for unused ASCCII characters
	if (pChar < 32 || pChar > 127) {
		pChar = '?'; // ?: characters that can't be displayed
    }
    if ( myfont == font_8x8) {
		for(byte i = 0; i < 8; i++) {
			sendData(pgm_read_byte(&myFont8x6[pChar - 32][i]));
			sendData(0);
			sendData(0);
		}
	}
    if ( myfont == font_8x6) {
		for(byte i = 0; i < 6; i++) {
			sendData(pgm_read_byte(&myFont8x6[pChar - 32][i]));
		}
	}
}

void SSD1306_OLED::printString(const char *data) {
	byte i = 0;

    while(data[i] && posInLine+i < ssd1306_max_col) {
		printChar(data[i]);
		i++;
	} 
}

void SSD1306_OLED::printBuffer(void) {
	for(byte row=ssd1306_min_row; row < ssd1306_max_row; row++) {
		setCursor(0,row);
		printString(dispData[row]);
	}
}

void SSD1306_OLED::scrollBuffer(void) {
	for(byte row=ssd1306_min_row+1; row < ssd1306_max_row; row++) {
		for(byte col=0; col < SSD1306_MAX_COL; col++) {
			dispData[row-1][col]=dispData[row][col];
		}
	}
	for(byte col=0; col < SSD1306_MAX_COL; col++) {
		dispData[ssd1306_max_row-1][col]=' ';
	}
	printBuffer();
}
	
void SSD1306_OLED::print(const char *data) {
	if (posInLine == 0)	scrollBuffer();
	for(byte i=0; i < strlen(data) && posInLine + i < SSD1306_MAX_COL; i++) {
		dispData[ssd1306_max_row-1][posInLine + i]=data[i];
	}
    setCursor(posInLine,ssd1306_max_row-1);	
	printString(data);
	posInLine = posInLine + strlen(data);
}

void SSD1306_OLED::print(const float data, byte precision) {
	float intdata = data;
	byte length;
	
    String bufString = String(intdata, precision);
 	length=bufString.length()+1;
    char buf[length];
    bufString.toCharArray(buf, length);
    print(buf);
}

void SSD1306_OLED::print(const int data) {
	byte length;
	
    String bufString = String(data);
 	length=bufString.length()+1;
    char buf[length];
    bufString.toCharArray(buf, length);
    print(buf);
}

void SSD1306_OLED::println(const char *data) {
	print(data);
    posInLine=0;	
}

void SSD1306_OLED::println(const float data, byte precision) {
	print(data, precision);
    posInLine=0;	
}

void SSD1306_OLED::println(const int data) {
	print(data);
    posInLine=0;	
}
