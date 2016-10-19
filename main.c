#include <pic18fregs.h>
#include <stdint.h>

#include <delay.h>

#pragma config XINST=OFF

#pragma config FOSC = INTOSCIO_EC

#pragma config WDT = OFF

#pragma config LVP = OFF

#define LED_LAT LATCbits.LATC0
#define LED_TRIS TRISCbits.TRISC0

uint16_t randDelay = 20000;
uint16_t getDelay() {
	randDelay ^= randDelay >> 3;
	randDelay ^= randDelay << 6;
	randDelay ^= randDelay >> 7;
	randDelay >>= 1;
	randDelay += 20000;
	return randDelay;
}

// concept: Long period LED on, rapid succession off-on-on, then back to start
// How long is the period?  Pseudo random, between 10 and 20 seconds
typedef enum {
	STARE,
	BLINK_ONE,
	GLANCE,
	BLINK_TWO
} BlinkState;

uint16_t countDown;
BlinkState state;

void main(void)
{
	countDown = getDelay();
	state = STARE;

	LED_TRIS = 0; // Pin as output
	LED_LAT = 0; // LED off
	while (1) {
		if (state == STARE || state == GLANCE) {
			LED_LAT = !LED_LAT; // Toggle LED
		}
		--countDown;
		if (countDown == 0) {
			++state;
			if (state > BLINK_TWO) {
				state = STARE;
				countDown = getDelay();
			} else {
				countDown = 300;
			}
			LED_LAT = !(state & 0x1);
		}
	}
}
