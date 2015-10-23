/*
 * BlinkM connections to Arduino
 * PWR - -- gnd -- black -- Gnd
 * PWR + -- +5V -- red   -- 5V
 * I2C d -- SDA -- green -- Analog In 4
 * I2C c -- SCK -- blue  -- Analog In 5
 *
 * Note: This sketch sends to the I2C "broadcast" address of 0,
 *       so all BlinkMs on the I2C bus will respond.
 */

#define blinkm_addr 0x00

void turnLightOff() {
 BlinkM_setRGB( blinkm_addr, 0, 0, 0 );
}

void setLightToRgbColor(int red, int green, int blue) {
 BlinkM_setRGB( blinkm_addr, red, green, blue );
}

void initLights() {
	BlinkM_beginWithPower();
	BlinkM_stopScript(blinkm_addr);  // turn off startup script
}
