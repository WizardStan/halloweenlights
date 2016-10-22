#include <pic18fregs.h>
#include <stdint.h>

#include <delay.h>

#pragma config XINST=OFF

#pragma config FOSC = INTOSCIO_EC

#pragma config WDT = OFF

#pragma config LVP = OFF

#define LED_LAT LATD
#define LED_TRIS TRISD

#define NUM_LEDS (8)
#define LED_DIV (3)
#define STARE_DELAY (15000 / NUM_LEDS)
#define BLINK_DELAY (180 / NUM_LEDS)

uint16_t randDelay = STARE_DELAY;
uint16_t getDelay() {
	randDelay ^= randDelay >> 3;
	randDelay ^= randDelay << 6;
	randDelay ^= randDelay >> 7;
	// TODO: how to divide by NUM_LEDS efficiently?
	randDelay >>= (2 + LED_DIV);
	randDelay += STARE_DELAY;
	return randDelay;
}

// concept: Long period LED on, rapid succession off-on-off, then back to start
// How long is the period?  Pseudo random, between 10 and 20 seconds
typedef enum {
	STARE,
	BLINK_ONE,
	GLANCE,
	BLINK_TWO
} BlinkState;

typedef struct {
	uint16_t countDown;
	BlinkState state;
	uint8_t mask;
} EyeBlinker;

EyeBlinker blink[NUM_LEDS];

void main(void)
{
	uint8_t i;
	LED_TRIS = 0;   // Pin as output
	LED_LAT = 0xFF; // All LEDs on
	
	for (i = 0; i < NUM_LEDS; ++i) {
		blink[i].countDown = getDelay();
		blink[i].state = STARE;
		blink[i].mask = 1 << i;
	}

	i = 0;
	while (1) {
		--blink[i].countDown;
		if (blink[i].countDown == 0) {
			++blink[i].state;
			if (blink[i].state > BLINK_TWO) {
				blink[i].state = STARE;
				blink[i].countDown = getDelay();
			} else {
				blink[i].countDown = BLINK_DELAY;
			}
			LED_LAT ^= blink[i].mask; // Toggle LED
		}
		++i;
		if (i == NUM_LEDS) i = 0;
	}
}
