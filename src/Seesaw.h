/*
Library for Adafruit I2C Stemma QT Rotary Encoder, NeoKey and NeoSlider is placed under the MIT license
Copyright (c) 2025 Stefan Staub

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef SEESAW_H
#define SEESAW__H

#include "Arduino.h"
#include "Wire.h"
#include "SeesawDefs.h"

/**
 * @brief Seesaw Encoder Class
 * 
 */
class SeesawEncoder {
public:
	/**
	 * @brief Construct a new Seesaw Encoder object
	 * 
	 * @param i2cAddr default i2c address 0x36
	 * @param i2cPort alternatives I2C Ports, Wire and Wire1 ...
	 */
	SeesawEncoder(uint8_t i2cAddr = ENCODER_I2C_ADDRESS, TwoWire &i2cPort = Wire);

	/**
	 * @brief 
	 * 
	 */
	void begin();

	/**
	 * @brief Set interrupt for the encoder
	 * 
	 * @param intterupt true for set interrupt, false for clear interrupt
	 */
	void interruptEncoder(bool interrupt);

	/**
	 * @brief Set interrupt for the button
	 * 
	 * @param intterupt true for set interrupt, false for clear interrupt
	 */
	void interruptButton(bool interrupt);
	
	/**
	 * @brief Get the encoder position
	 * 
	 * @return int32_t encoder position
	 */
	int32_t position();

	/**
	 * @brief Set the encoder position
	 * 
	 * @param pos new encoder position
	 */
	void position(int32_t pos);

	/**
	 * @brief Get the encoder button press
	 * 
	 * @return true if encoder button press
	 * @return false if no encoder button press
	 */
	bool button();

	/**
	 * @brief Set the neopixel colors
	 * 
	 * @param red neopixel red color
	 * @param green neopixel green color
	 * @param blue neopixel blue color
	 */
	void pixel(uint8_t red, uint8_t green, uint8_t blue);

	virtual size_t write(uint8_t value);
	virtual size_t write(const uint8_t *buffer, size_t size);
	uint8_t read(uint8_t addr);

private:
	void write(uint8_t base, uint8_t function);
	void write(uint8_t base, uint8_t function, uint8_t value);
	void write(uint8_t base, uint8_t function, uint8_t *buf, uint8_t num);
	void read(uint8_t base, uint8_t gunction, uint8_t *buf, uint8_t num);
	TwoWire *i2cPort;
	uint8_t i2cAddr;
	};

#endif
