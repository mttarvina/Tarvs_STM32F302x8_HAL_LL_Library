/**
  ******************************************************************************
  * @file    tarvs_f302x8_delay.c
  * @author  Mark Angelo Tarvina
  * @brief   Custom STM32F302x8 Delay Library.
  *
  *          This library contains:
  *           - Basic delay timer implementation using TIM6
  *
  * ****************************************************************************
  */


#include "tarvs_f302x8_delay.h"
#include "tarvs_f302x8_sysclk.h"

static bool                 _is_running     = false;
static bool                 _is_waiting     = false;
static volatile uint64_t    _tick_counter   = 0;
static volatile uint32_t    _delay_counter  = 0;


void DELAY_Timer_Init(void){
    RCC->APB1ENR = RCC_APB1ENR_TIM6EN;

    TIM6->PSC = (SYS_GetClkFreq() / 1000000UL) - 1;     // 1us counter resolution
    TIM6->ARR = 999;                                    // 1ms timer resolution
    TIM6->DIER = TIM_DIER_UIE;

    NVIC_SetPriority(TIM6_DAC_IRQn, 4);

    _is_running = false;
    _is_waiting = false;
    _tick_counter = 0;
    _delay_counter = 0;
}


void DELAY_Timer_Start(void){
    if (!_is_running) {
        _is_running = true;
        _tick_counter = 0;
        NVIC_EnableIRQ(TIM6_DAC_IRQn);
        TIM6->CR1 |= TIM_CR1_CEN;
    }
}


void DELAY_Timer_Stop(void){
    if (_is_running){
        _is_running = false;
        NVIC_DisableIRQ(TIM6_DAC_IRQn);
        TIM6->CR1 &= ~TIM_CR1_CEN;
    }

}


void Delay(uint32_t delay_count){
    if (_is_running){
        _delay_counter = 0;
        _is_waiting = true;
        while (_delay_counter < delay_count){
            // do nothing
            // this is a blocking delay function
        }
        _is_waiting = false;
    }
}


uint64_t Millis(void){
    if (_is_running){
        return _tick_counter;
    }
    else {
        return 0;
    }
}


void TIM6_DACUNDER_IRQHandler(void){
    if (TIM6->SR & TIM_SR_UIF) {    // Check for pending register bit
        TIM6->SR &= ~TIM_SR_UIF;    // Clear pending register bit

        _tick_counter++;

        if (_is_waiting){
            _delay_counter++;
        }
    }
}