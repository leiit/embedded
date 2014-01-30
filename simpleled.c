/*
 * Simple example how to turn on a led on preproject hardware in C
 */
#include <avr/io.h>

#define LED_PORT PORTC
#define LED_PORT_DDR DDRC

int main()
{
	LED_PORT_DDR = 0xff; //Configure the port as output
	LED_PORT = 1; //Turn on the leftmost led
	for (;;);
	return 0;
}
