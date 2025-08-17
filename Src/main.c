/**
 * Bare Metal STM32
**/

#include <stm32f302x8.h>
#include "tarvs_f302x8_gpio.h"
#include "tarvs_f302x8_sysclk.h"
#include "tarvs_f302x8_delay.h"


gpio_pin_t led = _PIN13;	// PB13
gpio_pin_t btn = _PIN13;	// PC13
bool led_state = false;


void Toggle_LED () {
	led_state = !led_state;
	GPIO_DrivePin(GPIOB, led, led_state);
}


int main(void) {
	SYS_ClkInit(_SYS_CLK_SRC_HSI, _SYS_FREQ_8MHZ);	

	GPIO_EnablePort(_PORTB);
	// GPIO_EnablePort(_PORTC);

	GPIO_ConfigPin(GPIOB, led, _OUTPUT, _PUSH_PULL, _MEDIUM_SPEED, _NO_PULLUP_PULLDOWN);
	// GPIO_ConfigPin(GPIOC, btn, _INPUT, _PUSH_PULL, _MEDIUM_SPEED, _NO_PULLUP_PULLDOWN);
	// GPIO_ConfigInterrupt(_PORTC, btn, _FALLING, &Toggle_LED);

	SYS_ClkOutEn();

	DELAY_Timer_Init();
	DELAY_Timer_Start();
	
	while (1){
		Toggle_LED();
		Delay(1);
    }
}