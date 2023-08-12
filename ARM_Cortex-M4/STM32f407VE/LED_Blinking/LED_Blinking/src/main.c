#include "stm32f4xx.h"

void SystemClock_Config(void) {
    // Enable HSE (High-Speed External clock)
    RCC->CR |= RCC_CR_HSEON;

    // Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Configure the PLL factors for HSE and set the system clock source 
    RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_HSE |      // HSE as PLL source
                    25U |                         // PLLM = 25 for 25MHz HSE
                    (336U << 6U) |                // PLLN = 336
                    (0U << 16U) |                 // PLLP = 2 (00: PLLP = 2, 01: PLLP = 4, ...)
                    (7U << 24U));                 // PLLQ = 7

    // Enable the PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait until PLL is ready
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Set flash latency for 168MHz system clock
    FLASH->ACR = FLASH_ACR_LATENCY_5WS;

    // Select PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait until PLL is selected as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    // AHB prescaler (HCLK) set to 1
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    // APB1 prescaler set to 4 (max frequency 42MHz)
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    // APB2 prescaler set to 2 (max frequency 84MHz)
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
}

int main(void) {
    // Initialize system clock
    SystemClock_Config();

    // Enable GPIO E clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    // Configure PE13 as output
    GPIOE->MODER |= GPIO_MODER_MODER13_0;

     // Configure PE14 as output
    GPIOE->MODER |= GPIO_MODER_MODER14_0;

     // Configure PE15 as output
    GPIOE->MODER |= GPIO_MODER_MODER15_0;

    while(1) {
        // Toggle PE13
        GPIOE->ODR ^= GPIO_ODR_ODR_13;
        GPIOE->ODR ^= GPIO_ODR_ODR_14;
        GPIOE->ODR ^= GPIO_ODR_ODR_15;

        // Simple delay
        for (volatile uint32_t i = 0; i < 8000000; i++);
    }
}
