#include "stm32f4xx.h"

int main(void)
{
    // Set system clock to 168 MHz
    SystemInit();

    // Enable clock for GPIOE
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    // Set mode of pin 13 to general purpose output
    GPIOE->MODER &= ~(GPIO_MODER_MODER13);
    GPIOE->MODER |= (GPIO_MODER_MODER13_0);

    // Set output type of pin 13 to push-pull output
    GPIOE->OTYPER &= ~(GPIO_OTYPER_OT_13);

    // Set output speed of pin 13 to 2 MHz medium speed
    GPIOE->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR13);
    GPIOE->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13_0);

    // Set pin 13 as no pull-up, no pull-down
    GPIOE->PUPDR &= ~(GPIO_PUPDR_PUPDR13);

    while(1)
    {
        // Toggle state of pin 13
        GPIOE->ODR ^= (GPIO_ODR_ODR_13);

        // Simple delay
        for (uint32_t i=0; i<1000000; i++);
    }
}
