/**
  ******************************************************************************
  * @file    tarvs_f302x8_delay.h
  * @author  Mark Angelo Tarvina
  * @brief   Custom STM32F302x8 Delay Library.
  *
  *          This library contains:
  *           - Basic delay timer implementation using TIM6
  *
  * ****************************************************************************
  */


// #pragma once


#ifndef __F302x8_DELAY_H
#define __F302x8_DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


#include <stdint.h>
#include <stdbool.h>
#include "stm32f302x8.h"


/// @brief Initialize the delay timer, uses TIM6. This function should be called first when using this module.
/// @param None 
void DELAY_Timer_Init(void);


/// @brief Start the delay timer. Call this after calling DELAY_Timer_Init();
/// @param None 
void DELAY_Timer_Start(void);


/// @brief Stops the delay timer. Note that this will make the Delay() and Millis() functions unusable
/// @param None 
void DELAY_Timer_Stop(void);


/// @brief Delay for a specified count in ms. Note that this is a blocking function!
/// @param delay_count (uint32_t) : Delay count in milliseconds
void Delay(uint32_t delay_count);


/// @brief Returns the number of milliseconds that have passed since calling DELAY_Timer_Start();
/// @param None
/// @return (uint64_t) : Time elapsed in milliseconds
uint64_t Millis(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __F302x8_DELAY_H */