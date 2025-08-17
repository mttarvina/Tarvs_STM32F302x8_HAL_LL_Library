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


#include "tarvs_f302x8_sysclk.h"
#include "tarvs_f302x8_gpio.h"


static uint32_t _sys_clk;


void SYS_ClkInit(sys_clk_src_t clk_src, sys_freq_t freq){
    if (_SYS_CLK_SRC_HSI == clk_src){
        switch (freq){
            case _SYS_FREQ_8MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_0;
                _sys_clk = (8000000UL);
                break;
            case _SYS_FREQ_16MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_0;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL4;
                _sys_clk = (16000000UL);
                break;
            case _SYS_FREQ_20MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_0;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL5;
                _sys_clk = (20000000UL);
                break;
            case _SYS_FREQ_24MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_0;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL6;
                _sys_clk = (24000000UL);
                break;
            case _SYS_FREQ_32MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_1;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL8;
                _sys_clk = (32000000UL);
                break;
            case _SYS_FREQ_36MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_1;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL9;
                _sys_clk = (36000000UL);
                break;
            case _SYS_FREQ_48MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_1;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL12;
                RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
                _sys_clk = (48000000UL);
                break;
            case _SYS_FREQ_64MHZ:
                FLASH->ACR |= FLASH_ACR_LATENCY_2;
                RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
                RCC->CFGR |= RCC_CFGR_PLLMUL16;
                RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
                _sys_clk = (64000000UL);
                break;
            case _SYS_FREQ_72MHZ:
                /* Revert to 8MHz since PLL cannot generate 72MHz clock when using HSI as CLK source */
                FLASH->ACR |= FLASH_ACR_LATENCY_0;
                _sys_clk = (8000000UL);
                break;              
            default:
                break;
        }

        if ((freq > _SYS_FREQ_8MHZ) && (freq < _SYS_FREQ_72MHZ)){
            /* Turn on PLL and wait for it to be ready */
            RCC->CR |= RCC_CR_PLLON;
            while(!(RCC->CR & RCC_CR_PLLRDY)){}

            /* Switch system clock to PLL and wait for it to be ready */
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){}
        }
    }

    else if (_SYS_CLK_SRC_HSE == clk_src){
        /* Revert to 8MHz for now */
        FLASH->ACR |= FLASH_ACR_LATENCY_0;
        _sys_clk = (8000000UL);
    }
}


void SYS_ClkOutEn(void){
    GPIO_EnablePort(_PORTA);
    GPIO_ConfigPin(GPIOA, _PIN8, _ALTERNATE, _PUSH_PULL, _HIGH_SPEED, _NO_PULLUP_PULLDOWN);
    GPIO_SetAltFunction(GPIOA, _PIN8, _AF0);

    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV128;
    RCC->CFGR |= RCC_CFGR_MCOSEL_SYSCLK;

    /*
        SYS_CLK = 8MHz  --> MCO_FREQ = 62.5kHz
        SYS_CLK = 16MHz --> MCO_FREQ = 125kHz
        SYS_CLK = 20MHz --> MCO_FREQ = 156.25kHz
        SYS_CLK = 24MHz --> MCO_FREQ = 187.5kHz
        SYS_CLK = 32MHz --> MCO_FREQ = 250kHz
        SYS_CLK = 36MHz --> MCO_FREQ = 281.25kHz
        SYS_CLK = 48MHz --> MCO_FREQ = 375kHz
        SYS_CLK = 64MHz --> MCO_FREQ = 500kHz
    */
}


uint32_t SYS_GetClkFreq(void){
    return _sys_clk;
}