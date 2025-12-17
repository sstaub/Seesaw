#include "Seesaw.h"

SeesawEncoder::SeesawEncoder(uint8_t i2cAddr, TwoWire &i2cPort) {
	this->i2cAddr = i2cAddr;
	this->i2cPort = &i2cPort;
	}

void SeesawEncoder::begin() {
	i2cPort->begin();
	// sw reset
	i2cPort->beginTransmission(i2cAddr);
	i2cPort->write(SEESAW_BASE_ADDRESS_STATUS);
	i2cPort->write(SEESAW_STATUS_SWRST);
	i2cPort->endTransmission();
	// pixel setup
	write(SEESAW_BASE_ADDRESS_NEOPIXEL, SEESAW_NEOPIXEL_SPEED, 1);
	uint8_t buf[] = {0, 3};
	write(SEESAW_BASE_ADDRESS_NEOPIXEL, SEESAW_NEOPIXEL_BUF_LENGTH, buf, 2);
	write(SEESAW_BASE_ADDRESS_NEOPIXEL, SEESAW_NEOPIXEL_PIN, ENCODER_NEOPIXEL_PIN);
	pixel(0, 0, 0);
	// button setup
	uint32_t pins = 1 << ENCODER_BUTTON_PIN;
	uint8_t pin[] = {(uint8_t)(pins >> 24), (uint8_t)(pins >> 16), (uint8_t)(pins >> 8), (uint8_t)pins};
	write(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_DIRCLR_BULK, pin, 4);
	write(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_PULLENSET, pin, 4);
	write(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_BULK_SET, pin, 4);
	}

void SeesawEncoder::interruptEncoder(bool interrupt) {
	if (interrupt) write(SEESAW_BASE_ADDRESS_ENCODER, SEESAW_ENCODER_INTENSET, 0x01);
	else write(SEESAW_BASE_ADDRESS_ENCODER, SEESAW_ENCODER_INTENCLR, 0x01);
	}

int32_t SeesawEncoder::position() {
	uint8_t buf[4];
	read(SEESAW_BASE_ADDRESS_ENCODER, SEESAW_ENCODER_POSITION, buf, 4);
	return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) | ((uint32_t)buf[2] << 8) | (uint32_t)buf[3];
	}

void SeesawEncoder::position(int32_t pos) {
	uint8_t buf[] = {(uint8_t)(pos >> 24), (uint8_t)(pos >> 16), (uint8_t)(pos >> 8), (uint8_t)(pos & 0xFF)};
	write(SEESAW_BASE_ADDRESS_ENCODER, SEESAW_ENCODER_POSITION, buf, 4);
	}

void SeesawEncoder::interruptButton(bool interrupt) {
	uint32_t pins = 1 << ENCODER_BUTTON_PIN;
	uint8_t pin[] = {(uint8_t)(pins >> 24), (uint8_t)(pins >> 16), (uint8_t)(pins >> 8), (uint8_t)pins};
	if (interrupt) write(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_INTENSET, pin, 4);
	else write(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_INTENCLR, pin, 4);
	}

bool SeesawEncoder::button() {
	uint8_t buf[4];
	read(SEESAW_BASE_ADDRESS_GPIO, SEESAW_GPIO_BULK, buf, 4);
	uint32_t ret = ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) | ((uint32_t)buf[2] << 8) | (uint32_t)buf[3];
	if (ret & (1 << ENCODER_BUTTON_PIN)) return false;
	else return true;
	}

void SeesawEncoder::pixel(uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t buf[5];
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = green;
	buf[3] = red;
	buf[4] = blue;
	write(SEESAW_BASE_ADDRESS_NEOPIXEL, SEESAW_NEOPIXEL_BUF, buf, 5);
	write(SEESAW_BASE_ADDRESS_NEOPIXEL, SEESAW_NEOPIXEL_SHOW);
	}

size_t SeesawEncoder::write(uint8_t value) {
	i2cPort->beginTransmission(i2cAddr);
	i2cPort->write(value);
	i2cPort->endTransmission();
	return 1;
	}

size_t SeesawEncoder::write(const uint8_t *buffer, size_t size) {
	i2cPort->beginTransmission(i2cAddr);
	while (size--) i2cPort->write(*buffer++);
	i2cPort->endTransmission();
	return size;
	}

uint8_t SeesawEncoder::read(uint8_t addr) {
	i2cPort->beginTransmission(i2cAddr);
	i2cPort->write(addr);
	i2cPort->endTransmission();
	i2cPort->requestFrom(i2cAddr, 1);
	return i2cPort->read();
	}

void SeesawEncoder::write(uint8_t base, uint8_t function) {
	i2cPort->beginTransmission(i2cAddr);
	i2cPort->write(base);
	i2cPort->write(function);
	i2cPort->endTransmission();
	}

void SeesawEncoder::write(uint8_t base, uint8_t function, uint8_t value) {
	i2cPort->beginTransmission(i2cAddr);
	i2cPort->write(base);
	i2cPort->write(function);
	i2cPort->write(value);
	i2cPort->endTransmission();
	}

void SeesawEncoder::write(uint8_t base, uint8_t function, uint8_t *buf, uint8_t num) { 
	i2cPort->beginTransmission((uint8_t)i2cAddr);
	i2cPort->write((uint8_t)base); //module base register address
	i2cPort->write((uint8_t)function); //module function register address
	i2cPort->write((uint8_t *)buf, num); //data bytes
	i2cPort->endTransmission();
	}

void SeesawEncoder::read(uint8_t base, uint8_t function, uint8_t *buf, uint8_t num) {
	i2cPort->beginTransmission((uint8_t)i2cAddr);
	i2cPort->write((uint8_t)base); //module base register address
	i2cPort->write((uint8_t)function); //module function register address
	i2cPort->endTransmission();
	delayMicroseconds(I2C_READ_DELAY_US);
	i2cPort->requestFrom((uint8_t)i2cAddr, num);
	for(int i = 0; i < num; i++){
		buf[i] = i2cPort->read();
		}
	}
