#include <pic18fregs.h>
#include <stdint.h>

#pragma config XINST=OFF
#pragma config FOSC = INTOSCIO_EC
#pragma config WDT = OFF
#pragma config LVP = OFF

#define LED_LAT LATCbits.LATC0
#define LED_TRIS TRISCbits.TRISC0

void main(void)
{
	uint16_t blink = 0;

	LED_TRIS = 0; // Pin as output
	LED_LAT = 0; // LED off
	blink = 0;
	while (1) {
		if (blink < 1000) {
			LED_LAT = !LED_LAT; // Toggle LED
		} else if (blink == 1000) {
			LED_LAT = 0;
		} else if (blink > 2000) {
			blink = 0;
		}
		++blink;
	}
}
