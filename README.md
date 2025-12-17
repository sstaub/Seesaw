# Adafruit Seesaw library for Arduino

Arduino library for Adafruit Seesaw with a small footprint and easy to use.

Supported Hardware, still in progress:
- [x] Rotary Encoder https://www.adafruit.com/product/4991
- [ ] NeoKey https://www.adafruit.com/product/4978
- [ ] NeoKey 1x4 https://www.adafruit.com/product/4980
- [ ] NeoSlider https://www.adafruit.com/product/5295

## Example for the rotary encoder
```cpp
#include "Arduino.h"
#include "Seesaw.h"

SeesawEncoder enc;

int32_t position;
int32_t positionLast;
bool buttonLast;

void setup() {
	Serial.begin(9600);
	delay(2000);
	enc.begin();
	enc.position(0);
	enc.pixel(0, 32, 0); // green
	}

void loop() {
	position = enc.position();
	if (position != positionLast) {
    Serial.print("Encoder: ");
    Serial.println(position);
		if (position > 0) enc.pixel(32, 0, 0); // red
		if (position < 0) enc.pixel(0, 0, 32); // blue
		if (position == 0) enc.pixel(0, 32, 0); // green
		positionLast = position;
		}
	if (enc.button() != buttonLast) {
		if (buttonLast == false) {
			buttonLast = true;
			Serial.println("Encoder: Button pressed!");
			}
		else {
			buttonLast = false;
			}
		}
	}
```

# Documentation Encoder

## Constructor
```cpp
SeesawEncoder(uint8_t i2cAddr = ENCODER_I2C_ADDRESS, TwoWire &i2cPort = WIRE);
```
- **i2caddr** optional I2C Address of the encoder, default is 0x36, [0x36 ... 0x3F]
- **i2cPort** optional I2C Port, this is only needed if you another interface than the standard Wire like Wire1 ...

Create an Encoder object with a given address of the I2C interface and port.

**Example**
```cpp
const uint8_t i2caddr = 0x37;
SeesawEncoder enc(i2caddr, Wire1); // use Wire1
SeesawEncoder enc; // use default port and address
```

## Methods

### **begin()**
```cpp
void begin();
```

Initialize the encoder, this must done in `setup()`.

**Example**
```cpp
enc.begin();
```

### **interruptEncoder()**
```cpp
void interruptEncoder(bool interrupt);
```
- **interrupt** true for interrupt set, false to disable interrupt

Set the Interrupt of the encoder, this should done in `setup()`.

**Example**
```cpp
enc.interruptEncoder(true);
```

### **interruptButton()**
```cpp
void interruptButton(bool interrupt);
```
- **interrupt** true for interrupt set, false to disable interrupt

Set the Interrupt of the button, this should done in `setup()`. Beware that you get an interrupt for press and release the button!

**Example**
```cpp
enc.interruptButton(true);
```

### **position()**
```cpp
int32_t position();
void position(int32_t pos);
```
- **pos** optional for set a position

Get the position of the encoder, this should done in `loop()`. You can also set a position.

**Example**
```cpp
int32_t pos = enc.position(); // get the encoder position
enc.position(0); // set the encoder position to 0
```

### **button()**
```cpp
bool button();
```

Get the state of the button, this should done in `loop()`.

**Example**
```cpp
bool btn = enc.button(); // get the button state
```

### **pixel()**
```cpp
void pixel(uint8_t red, uint8_t green, uint8_t blue);
```
- **red** value for red
- **green** value for green
- **blue** value for blue

Set the Neopixel values.

**Example**
```cpp
enc.pixel(32, 32, 32);
```
