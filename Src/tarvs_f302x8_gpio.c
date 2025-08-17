/**
  ******************************************************************************
  * @file    tarvs_f302x8_gpio.c
  * @author  Mark Angelo Tarvina
  * @brief   Custom STM32F302x8 GPIO Library.
  *
  *          This library contains:
  *           - Simplified function calls for setting up and controlling GPIO
  *
  * ****************************************************************************
  */


#include "tarvs_f302x8_gpio.h"


void (*_GPIO_IntHandler0) (void);
void (*_GPIO_IntHandler1) (void);
void (*_GPIO_IntHandler2) (void);
void (*_GPIO_IntHandler3) (void);
void (*_GPIO_IntHandler4) (void);
void (*_GPIO_IntHandler5) (void);
void (*_GPIO_IntHandler6) (void);
void (*_GPIO_IntHandler7) (void);
void (*_GPIO_IntHandler8) (void);
void (*_GPIO_IntHandler9) (void);
void (*_GPIO_IntHandler10) (void);
void (*_GPIO_IntHandler11) (void);
void (*_GPIO_IntHandler12) (void);
void (*_GPIO_IntHandler13) (void);
void (*_GPIO_IntHandler14) (void);
void (*_GPIO_IntHandler15) (void);


void GPIO_EnablePort(gpio_port_t port){
    switch (port) {
        case _PORTA:
            RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
            break;
        case _PORTB:
            RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
            break;
        case _PORTC:
            RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
            break;
        case _PORTD:
            RCC->AHBENR |= RCC_AHBENR_GPIODEN;
            break;
        case _PORTF:
            RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
            break;
    }
}


void GPIO_ConfigPin(GPIO_TypeDef *gpiox, gpio_pin_t pin, gpio_mode_t mode, gpio_type_t type, gpio_speed_t speed, gpio_pupd_t pupd){
    /* Reset MODER bits of the designated pin */
    gpiox->MODER &= ~(0x3 << (2 * pin));

    /* Set MODER bits of the designated pin */
    gpiox->MODER |= mode << (2 * pin);
    
    switch(type){
        case _PUSH_PULL:
            gpiox->OTYPER &= ~(0x1 << pin);
            break;
        case _OPEN_DRAIN:
            gpiox->OTYPER |= (0x1 << pin);
        default:
            break;
    }

    /* Set GPIO Speed */
    gpiox->OSPEEDR |= speed << (2 * pin);

    /* Set GPIO Pull-up/Pull-down Option */
    gpiox->PUPDR |= pupd << (2 * pin);
}


void GPIO_ConfigInterrupt(gpio_port_t port, gpio_pin_t pin, gpio_int_trig_t trig, void (*Int_Handler)(void)){
    /* Enable CLK on SYSCFG that manages interrupt line connections from GPIO */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* Enable external interrupt line assigned to the port & pin. Assign interrupt handler function */
    switch (pin) {
        case _PIN0:
            SYSCFG->EXTICR[0] &= ~0xF;          // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[0] |= port;          // enable interrupt on Px0
            _GPIO_IntHandler0 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN1:
            SYSCFG->EXTICR[0] &= ~(0xF << 4);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[0] |= (port << 4);   // enable interrupt on Px1
            _GPIO_IntHandler1 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN2:
            SYSCFG->EXTICR[0] &= ~(0xF << 8);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[0] |= (port << 8);   // enable interrupt on Px2
            _GPIO_IntHandler2 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN3:
            SYSCFG->EXTICR[0] &= ~(0xF << 12);  // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[0] |= (port << 12);  // enable interrupt on Px3
            _GPIO_IntHandler3 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN4:
            SYSCFG->EXTICR[1] &= ~0xF;          // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[1] |= port;          // enable interrupt on Px4
            _GPIO_IntHandler4 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN5:
            SYSCFG->EXTICR[1] &= ~(0xF << 4);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[1] |= (port << 4);   // enable interrupt on Px5
            _GPIO_IntHandler5 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN6:
            SYSCFG->EXTICR[1] &= ~(0xF << 8);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[1] |= (port << 8);   // enable interrupt on Px6
            _GPIO_IntHandler6 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN7:
            SYSCFG->EXTICR[1] &= ~(0xF << 12);  // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[1] |= (port << 12);  // enable interrupt on Px7
            _GPIO_IntHandler7 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN8:
            SYSCFG->EXTICR[2] &= ~0xF;          // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[2] |= port;          // enable interrupt on Px8
            _GPIO_IntHandler8 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN9:
            SYSCFG->EXTICR[2] &= ~(0xF << 4);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[2] |= (port << 4);   // enable interrupt on Px9
            _GPIO_IntHandler9 = Int_Handler;    // assign interrept handler function
            break;
        case _PIN10:
            SYSCFG->EXTICR[2] &= ~(0xF << 8);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[2] |= (port << 8);   // enable interrupt on Px10
            _GPIO_IntHandler10 = Int_Handler;   // assign interrept handler function
            break;
        case _PIN11:
            SYSCFG->EXTICR[2] &= ~(0xF << 12);  // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[2] |= (port << 12);  // enable interrupt on Px11
            _GPIO_IntHandler11 = Int_Handler;   // assign interrept handler function
            break;
        case _PIN12:
            SYSCFG->EXTICR[3] &= ~0xF;          // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[3] |= port;          // enable interrupt on Px12
            _GPIO_IntHandler12 = Int_Handler;   // assign interrept handler function
            break;
        case _PIN13:
            SYSCFG->EXTICR[3] &= ~(0xF << 4);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[3] |= (port << 4);   // enable interrupt on Px13
            _GPIO_IntHandler13 = Int_Handler;   // assign interrept handler function
            break;
        case _PIN14:
            SYSCFG->EXTICR[3] &= ~(0xF << 8);   // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[3] |= (port << 8);   // enable interrupt on Px14
            _GPIO_IntHandler14 = Int_Handler;   // assign interrept handler function
            break;
        case _PIN15:
            SYSCFG->EXTICR[3] &= ~(0xF << 12);  // reset the corresponding EXTIx bit fields first
            SYSCFG->EXTICR[3] |= (port << 12);  // enable interrupt on Px15
            _GPIO_IntHandler15 = Int_Handler;   // assign interrept handler function
            break;
        default:
            break;
    }

    /* Enable interrupt mask register for the corresponding external interrupt line */
    EXTI->IMR |= 0x1 << pin;

    /* Configure edge trigger type */
    switch (trig) {
        case _FALLING:
            EXTI->FTSR |= 0x1 << pin;
            break;
        case _RISING:
            EXTI->RTSR |= 0x1 << pin;
            break;
        case _RISING_FALLING:
            EXTI->FTSR |= 0x1 << pin;
            EXTI->RTSR |= 0x1 << pin;
            break;
        default:
            break;
    }

    __disable_irq();
    switch (pin) {
        case _PIN0:
            NVIC_SetPriority(EXTI0_IRQn, 7);
            NVIC_EnableIRQ(EXTI0_IRQn);
            break;
        case _PIN1:
            NVIC_SetPriority(EXTI1_IRQn, 7);
            NVIC_EnableIRQ(EXTI1_IRQn);
            break;
        case _PIN2:
            NVIC_SetPriority(EXTI2_TSC_IRQn, 7);
            NVIC_EnableIRQ(EXTI2_TSC_IRQn);
            break;
        case _PIN3:
            NVIC_SetPriority(EXTI3_IRQn, 7);
            NVIC_EnableIRQ(EXTI3_IRQn);
            break;
        case _PIN4:
            NVIC_SetPriority(EXTI4_IRQn, 7);
            NVIC_EnableIRQ(EXTI4_IRQn);
            break;
        case _PIN5:
        case _PIN6:
        case _PIN7:
        case _PIN8:
        case _PIN9:
            NVIC_SetPriority(EXTI9_5_IRQn, 7);
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case _PIN10:
        case _PIN11:
        case _PIN12:
        case _PIN13:
        case _PIN14:
        case _PIN15:
            NVIC_SetPriority(EXTI15_10_IRQn, 7);
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        default:
            break;
    }
    __enable_irq();
}


bool GPIO_ReadPin(GPIO_TypeDef *gpiox, gpio_pin_t pin){
    return ((gpiox->IDR & (0x1 << pin)) >> pin);
}


void GPIO_DrivePin(GPIO_TypeDef *gpiox, gpio_pin_t pin, bool level){
    switch (level) {
        case _LOW:
            gpiox->BRR |= (0x1 << pin);
            break;
        case _HIGH:
            gpiox->BSRR |= (0x1 << pin);
            break;
    }
}


void GPIO_SetAltFunction(GPIO_TypeDef *gpiox, gpio_pin_t pin, gpio_altfunc_t af){
    uint32_t val;
    /* Set AFRL and AFRH bits accordingly */
    if ((pin > _PIN7) && (pin <= _PIN15)) {
        val = 4 * (pin % 8);
        gpiox->AFR[1] &= ~(0xF << (4 * (pin % 8)));
        gpiox->AFR[1] |= af << (4 * (pin % 8)); 
    }
    else if (pin <= _PIN7) {
        gpiox->AFR[0] &= ~(0xF << (4 * pin));
        gpiox->AFR[0] |= af << (4 * pin);
    }
}


void EXTI0_IRQHandler () {
    if (EXTI->PR & (0x1 << 0)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 0;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler0();            // Call interrupt handler function
    }
}


void EXTI1_IRQHandler () {
    if (EXTI->PR & (0x1 << 1)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 1;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler1();            // Call interrupt handler function
    }
}


void EXTI2_TSC_IRQHandler () {
    if (EXTI->PR & (0x1 << 2)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 2;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler2();            // Call interrupt handler function
    }
}


void EXTI3_IRQHandler () {
    if (EXTI->PR & (0x1 << 3)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 3;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler3();            // Call interrupt handler function
    }
}


void EXTI4_IRQHandler () {
    if (EXTI->PR & (0x1 << 4)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 4;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler4();            // Call interrupt handler function
    }
}


void EXTI9_5_IRQHandler () {
    if (EXTI->PR & (0x1 << 5)) {        // Check for pending register bit
        EXTI->PR |= 0x1 << 5;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler5();            // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 6)) {   // Check for pending register bit
        EXTI->PR |= 0x1 << 6;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler6();            // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 7)) {   // Check for pending register bit
        EXTI->PR |= 0x1 << 7;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler7();            // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 8)) {   // Check for pending register bit
        EXTI->PR |= 0x1 << 8;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler8();            // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 9)) {   // Check for pending register bit
        EXTI->PR |= 0x1 << 9;           // Clear pending register bit by writing '1'
        _GPIO_IntHandler9();            // Call interrupt handler function
    }
}


void EXTI15_10_IRQHandler () {
    if (EXTI->PR & (0x1 << 10)) {       // Check for pending register bit
        EXTI->PR |= 0x1 << 10;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler10();           // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 11)) {  // Check for pending register bit
        EXTI->PR |= 0x1 << 11;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler11();           // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 12)) {  // Check for pending register bit
        EXTI->PR |= 0x1 << 12;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler12();           // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 13)) {  // Check for pending register bit
        EXTI->PR |= 0x1 << 13;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler13();           // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 14)) {  // Check for pending register bit
        EXTI->PR |= 0x1 << 14;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler14();           // Call interrupt handler function
    }
    else if (EXTI->PR & (0x1 << 15)) {  // Check for pending register bit
        EXTI->PR |= 0x1 << 15;          // Clear pending register bit by writing '1'
        _GPIO_IntHandler15();           // Call interrupt handler function
    }
}