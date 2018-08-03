# SSD1306_Logwriter
A simple buffered Textdisplay on a 0.96" OLED display on Arduino

This is a library for monochrome OLEDs based on SSD1306 drivers

It is NOT a complete Library if you are looking for all the features
this display can do! 

This Library has a very small Memory/RAM footprint (~377Byte)
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
