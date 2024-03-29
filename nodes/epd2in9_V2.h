/**
 *  filename   :   epd2in9_V2.h
 *  brief      :   Header file for e-paper display library epd2in9_V2.cpp
 *  author     :   
 *  
 *  Copyright (C) Waveshare     Nov 09 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef EPD2IN9_V2_H
#define EPD2IN9_V2_H

#include <abmt/io/spi.h>
#include <abmt/io/pin.h>

// Display resolution
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

class Epd {
public:
	abmt::io::spi_ptr spi;
	abmt::io::opin_ptr reset_pin;
	abmt::io::opin_ptr dc_pin;
	abmt::io::opin_ptr cs_pin;
	abmt::io::ipin_ptr busy_pin;

	unsigned long width;
	unsigned long height;

    Epd();
    ~Epd();
    void SpiTransfer(unsigned char data);
    int init(void);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
    void Reset(void);
    void SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    );
    void SetFrameMemoryPartial(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height,
        bool swap_endian,
        bool invert
    );
    void SetFrameMemory(const unsigned char* image_buffer);
    void SetFrameMemory_Base(const unsigned char* image_buffer);
    void ClearFrameMemory(unsigned char color);
    void DisplayFrame(void);
	void DisplayPartFrame(void);
    void Sleep(void);

private:
		
	void SetLut(unsigned char *lut);
    void SetLut_by_host(unsigned char *lut);
    void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
    void SetMemoryPointer(int x, int y);
};

#endif /* EPD2IN9_V2_H */

/* END OF FILE */
