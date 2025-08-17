/**
  ******************************************************************************
  * @file    tarvs_f302x8_delay.h
  * @author  Mark Angelo Tarvina
  * @brief   Custom STM32F302x8 System Clock Library.
  *
  *          This file contains:
  *           - Simplified function calls to adjust System Clock frequency
  *
  * ****************************************************************************
  */


// #pragma once


#ifndef __F302x8_SYSCLK_H
#define __F302x8_SYSCLK_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


#include <stdint.h>
#include <stdbool.h>
#include "stm32f302x8.h"


typedef enum {
    _SYS_CLK_SRC_HSI,                   /* Use internal high speed oscillator as clock source (8MHz) */
    _SYS_CLK_SRC_HSE                    /* <!CURRENTLY NOT SUPPORTED!> Use external high speed oscillator as clock source */
} sys_clk_src_t;


typedef enum {
    _SYS_FREQ_8MHZ,                     /* System Clock = AHB = APB1 = APB2 = 8MHz, */
    _SYS_FREQ_16MHZ,                    /* System Clock = AHB = APB1 = APB2 = 16MHz, */
    _SYS_FREQ_20MHZ,                    /* System Clock = AHB = APB1 = APB2 = 20MHz, */
    _SYS_FREQ_24MHZ,                    /* System Clock = AHB = APB1 = APB2 = 24MHz, */
    _SYS_FREQ_32MHZ,                    /* System Clock = AHB = APB1 = APB2 = 32MHz, */
    _SYS_FREQ_36MHZ,                    /* System Clock = AHB = APB1 = APB2 = 36MHz, */
    _SYS_FREQ_48MHZ,                    /* System Clock = AHB = APB2 = 48MHz; APB1 = 24MHz */
    _SYS_FREQ_64MHZ,                    /* System Clock = AHB = APB2 = 64MHz; APB1 = 32MHz */
    _SYS_FREQ_72MHZ                     /* <!CURRENTLY NOT SUPPORTED!> */
} sys_freq_t;


/// @brief Configure the system clock frequency, currently do not support HSE as clock source
/// @param clk_src (sys_clk_src_t) : Choose either _SYS_CLK_SRC_HSI or _SYS_CLK_SRC_HSE as clock source, only _SYS_CLK_SRC_HSI is currently supported
/// @param freq (sys_freq_t): Choose any _SYS_FREQ_xMHZ available. _SYS_FREQ_72MHZ is the same as _SYS_FREQ_8MHZ since 72MHz cannot be generated if using HSI as clock source
void SYS_ClkInit(sys_clk_src_t clk_src, sys_freq_t freq);


/// @brief Route system clock signal to PA8, clock frequency is divided by 128
/// @param None 
void SYS_ClkOutEn(void);


/// @brief Get the current value of system clock frequency
/// @return (uint32_t) : System Clock Frequency 
uint32_t SYS_GetClkFreq(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __F302x8_SYSCLK_H */