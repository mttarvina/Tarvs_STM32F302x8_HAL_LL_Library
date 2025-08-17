/**
  ******************************************************************************
  * @file    tarvs_f302x8_gpio.h
  * @author  Mark Angelo Tarvina
  * @brief   Custom STM32F302x8 GPIO Library.
  *
  *          This library contains:
  *           - Simplified function calls for setting up and controlling GPIO
  *
  * ****************************************************************************
  */


// #pragma once


#ifndef __F302x8_GPIO_H
#define __F302x8_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


#include <stdint.h>
#include <stdbool.h>
#include "stm32f302x8.h"


#define _LOW        false
#define _HIGH       true


typedef enum {
    _PORTA,                             /* Corresponds to GPIOA */
    _PORTB,                             /* Corresponds to GPIOB */
    _PORTC,                             /* Corresponds to GPIOC */
    _PORTD,                             /* Corresponds to GPIOD */
    _PORTF                              /* Corresponds to GPIOF */
} gpio_port_t;


typedef enum {
    _PIN0,
    _PIN1,
    _PIN2,
    _PIN3,
    _PIN4,
    _PIN5,
    _PIN6,
    _PIN7,
    _PIN8,
    _PIN9,
    _PIN10,
    _PIN11,
    _PIN12,
    _PIN13,
    _PIN14,
    _PIN15
} gpio_pin_t;


typedef enum {
    _AF0,
    _AF1,
    _AF2,
    _AF3,
    _AF4,
    _AF5,
    _AF6,
    _AF7,
    _AF8,
    _AF9,
    _AF10,
    _AF11,
    _AF12,
    _AF13,
    _AF14,
    _AF15
} gpio_altfunc_t;


typedef enum {
    _INPUT,
    _OUTPUT,
    _ALTERNATE,
    _ANALOG
} gpio_mode_t;


typedef enum {
    _PUSH_PULL,
    _OPEN_DRAIN
} gpio_type_t;


typedef enum {
    _LOW_SPEED       = 0,
    _MEDIUM_SPEED    = 1,
    _HIGH_SPEED      = 3
} gpio_speed_t;


typedef enum {
    _NO_PULLUP_PULLDOWN,
    _PULLUP,
    _PULLDOWN,
} gpio_pupd_t;


typedef enum {
    _FALLING,
    _RISING,
    _RISING_FALLING
} gpio_int_trig_t;


/// @brief Enable clock signal on a GPIO port. Make sure to call this function before configuring or controlling any GPIO
/// @param port (gpio_port_t) : _PORTx
void GPIO_EnablePort(gpio_port_t port);


/// @brief Configure a GPIO pin
/// @param gpiox (GPIO_TypeDef *) : GPIOx
/// @param pin (gpio_pin_t) : _PINx
/// @param mode (gpio_mode_t) : _INPUT, _OUTPUT, _ALTERNATE, or _ANALOG
/// @param type (gpio_type_t) : _PUSH_PULL or _OPEN_DRAIN
/// @param speed (gpio_speed_t) : _LOW_SPEED, _MEDIUM_SPEED, or _HIGH_SPEED
/// @param pupd (gpio_pupd_t) : _NO_PULLUP_PULLDOWN, _PULLUP, or _PULLDOWN
void GPIO_ConfigPin(GPIO_TypeDef *gpiox, gpio_pin_t pin, gpio_mode_t mode, gpio_type_t type, gpio_speed_t speed, gpio_pupd_t pupd);


/// @brief Enable interrupt on a GPIO pin
/// @param port (gpio_port_t) : _PORTx
/// @param pin (gpio_pin_t) : _PINx
/// @param trig (gpio_int_trig_t) : _FALLING, _RISING, or _RISING_FALLING
/// @param Int_Handler (void *) : Address of callback function
void GPIO_ConfigInterrupt(gpio_port_t port, gpio_pin_t pin, gpio_int_trig_t trig, void (*Int_Handler)(void));


/// @brief Read from a GPIO pin
/// @param gpiox (GPIO_TypeDef *) : GPIOx
/// @param pin (gpio_pin_t) : _PINx
/// @return (bool) : true (high) or false (low) based on digital input level
bool GPIO_ReadPin(GPIO_TypeDef *gpiox, gpio_pin_t pin);


/// @brief Drive a GPIO pin to either _HIGH or _LOW
/// @param gpiox (GPIO_TypeDef *) : GPIOx
/// @param pin (gpio_pin_t) : _PINx
/// @param level (bool) : _HIGH or _LOW; true or false, 1 or 0
void GPIO_DrivePin(GPIO_TypeDef *gpiox, gpio_pin_t pin, bool level);


/// @brief Configure an alternate function for the GPIO pin
/// @param gpiox (GPIO_TypeDef *) : GPIOx
/// @param pin (gpio_pin_t) : _PINx
/// @param af (gpio_altfunc_t) : _AFx (Refer to datasheet)
void GPIO_SetAltFunction(GPIO_TypeDef *gpiox, gpio_pin_t pin, gpio_altfunc_t af);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __F302x8_GPIO_H */