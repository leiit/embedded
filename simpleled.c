/*
 * Simple example on how to turn on, turn off, toggle
 * single pins (leds in example) and how to change state
 * of multiple pins at once.
 *
 * This example contains a lot of comments so that you can
 * get hints on how to write C code for AVR.
 * Note also that this file is overly commented and you
 * should not comment every single line on your code.
 *
 * This file goes through the basics and also contains
 * some optimization hints to those who are used to writing C.
 */

#include <inttypes.h> /* definitions for uint8_t and others */
#include <avr/io.h>   /* definitions for all PORT* and other registers. You absolutely will need this one */

/* following line is needed only when _delay_ms is used
 * read the comment about _delay_ms from the main function */
#include <util/delay.h>
#include <avr/interrupt.h>

#define LEDS_PORT PORTC // 8b 3r / napa
#define LEDS_DDR  DDRC // data direction reg
#define LEDS_PIN  PINC // port input

#define SWITCH_PORT PORTA
#define SWITCH_DDR	DDRA
#define SWITCH_PIN	PINA

#define BLINK_LED PC2
#define OTHER_LED PC0

int ignore = 0;
int loops = 6500;
volatile int timercounter = 0;

void setup_leds(void)
{
	/* Configure the leds port as output
	 * DDR* registers define GPIO pin direction (1 means output and 0 input)
	 * Refer atmega 2560 datasheet for more about this
	 */
	LEDS_DDR = 0xff;
}

void setup_switches(void)
{
	SWITCH_DDR = 0x0;
}


/* Remember that in C you need to prototype functions,
 * when they are referenced before defined.
 * It is good practice to prototype all used functions in start of the file
 */
uint8_t rotate_online_led(uint8_t);
void toggle_blink_led(void);
void toggle_led(void);
uint8_t get_switch_status(void);


int main(void)
{
	/* In start of the main function you would do
	 * Hardware setup/initialization as main function
	 * is run only once after microcontroller is started
	 */

	uint8_t switch_state;
	setup_leds();
	setup_switches();

	for (;;)
	{
		switch_state = ~SWITCH_PIN;
		if (ignore != 0 && switch_state > 0) {
			//ignore = 1;
			LEDS_PORT = switch_state;
		}
	}

	/* when you exit from the main function, the MCU will enter
	 * an infinite loop (note. the MCU is not rebooted)
	 * Normally you code should never exit the main function.
	 */
	return 0;
}


uint8_t rotate_online_led(uint8_t state)
{
	/* Following commented line would be optimal for this
	 * function, but it would broke toggle_blink_led
	 * so we need to do bit more complex way, but this
	 * shows you bit more what you could do
	 */
	// LEDS_PORT = state;

	/* Read the current port value (this is different than
	 * what you need for reading button state)
	 */
	uint8_t current_value = LEDS_PORT;
	/* mask the pins we control to be off */
	current_value &= 0x0f; /* 0b00001111 */
	/* put the state pin up */
	current_value |= state;
	/* update port register (online led will change after this line) */
	LEDS_PORT = current_value;

	/* Above could be written with just single line of code */
	// LEDS_PORT = (LEDS_PORT & 0x0f) | state;

	/* Update the state byte */
	state >>= 1;
	if (state <= 0x08) /* 0b00001000 */
		state = 0x80;  /* 0b10000000 */
	return state;
}

void toggle_led(void) {
	LEDS_PIN = SWITCH_PIN;
}

uint8_t poll_switch_status(void) {
	status = SWITCH_PORT;

	switch ()

}

ISR()


void toggle_blink_led(void)
{
	/* There is no easy way to pass register to a function
	 * in a way that would be optimal.
	 * When you are passing register to the function,
	 * you are trying to do too generic code for this task.
	 * You should avoid this during this exercise.
	 *
	 * Instead hard code registers into the functions
	 * and use C macros to help change the code.
	 */

	/* Most atmega MCU can toggle output state when 1 is
	 * written to the PIN* register */
	LEDS_PIN |= _BV(BLINK_LED);

	/* _BV is macro defined in avr/io.h
	 *    #define _BV(bit) (1 << (bit))
	 * so above is identical to
	 */
	// LEDS_PIN |= 1 << BLINK_LED;
}