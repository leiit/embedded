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

volatile int ignore = 0;
int loops = 6500;

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

void setup_timer(void) {
  TCCR2B |= (1 << WGM22) | (1 << CS20) | (1 << CS21);
  TIMSK2 |= (1 << OCIE2A);
  OCR2A = 254;
}

void change_pwm_signal(int ratio) {
  DDRB = 0xff;
  TCCR1A |= (1 << COM1A0) | (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << CS10) | (1 << CS11) | (1 << WGM12) | (1 << WGM13);
  ICR1 = 4999;
  OCR1A = ICR1 - 300 - ratio;
}

uint8_t rotate_online_led(uint8_t);
void toggle_blink_led(void);
void toggle_led(void);
uint8_t get_switch_status(void);

int main(void)
{
	uint8_t switch_state;
	setup_leds();
	setup_switches();
	setup_timer();
	sei();

	for (;;)
	{
		switch_state = ~SWITCH_PIN;
		if (ignore == 0 && switch_state > 0) {
			ignore = 1;
			LEDS_PORT = switch_state;
			TCNT2 = 0;
			switch_pwm(switch_state);
		}
	}

	return 0;
}


void switch_pwm(uint8_t state) {

  switch (state) {
  case 0b00000001:
    change_pwm_signal(12);
    break;
  case 0b00000010:
    change_pwm_signal(25);
    break;
  case 0b00000100:
    change_pwm_signal(37);
    break;
  case 0b00001000:
    change_pwm_signal(50);
    break;
  case 0b00010000:
    change_pwm_signal(62);
    break;
  case 0b00100000:
    change_pwm_signal(75);
    break;
  case 0b01000000:
    change_pwm_signal(87);
    break;
  case 0b10000000:
    change_pwm_signal(100);
    break;
  default:
    change_pwm_signal(0);
    break;
  }
}

volatile int counter = 0;

ISR(TIMER2_COMPA_vect) {
  if (counter > 7000) {
    ignore = 0;
    LEDS_PORT = 0;
    counter = 0;
    TCCR1A &= ~_BV(COM1A1);
  }
  counter++;
}
