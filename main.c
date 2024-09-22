#include <stdint.h>
#include "tm4c123gh6pm.h"
volatile uint32_t dutyCycle = 50;  // Initial duty cycle: 50%
volatile uint32_t count = 160;      // Count value for 100 kHz PWM with 16 MHz clock PWM Frequency=

  // Function declarations
void GPIO_Handler(void);
void Systick_Handler(void);
int main(void) {
      SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock for Port F
      GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock Port F
      GPIO_PORTF_CR_R |= 0x10;          // Allow changes to PF4

      // Configure PF1 as output for LED
      GPIO_PORTF_DIR_R |= 0x02; // PF1 as output
      GPIO_PORTF_DEN_R |= 0x13; // Enable digital function for PF1 and PF4

      // Enable pull-up resistors on PF4 and PF0
      GPIO_PORTF_PUR_R |= 0x11;

      // Configure interrupts for PF4 and PF0
      GPIO_PORTF_IS_R &= ~0x11;   // Edge-sensitive
      GPIO_PORTF_IBE_R &= ~0x11;  // Trigger on one edge
      GPIO_PORTF_IEV_R &= ~0x11;  // Falling edge trigger
      GPIO_PORTF_ICR_R = 0x11;    // Clear prior interrupts
      GPIO_PORTF_IM_R |= 0x11;     // Unmask interrupts for PF4 and PF0
NVIC_EN0_R |= 0x40000000; // Enable interrupt for Port F             // Initialize GPIO for switches and LED


      // Initialize SysTick timer for PWM

      NVIC_ST_RELOAD_R = 160 - 1; // Reload value for 100 kHz frequency
        NVIC_ST_CTRL_R = 0x07;      // Enable SysTick with core clock and interrupts

    while (1) {
        // Main loop does nothing, PWM and duty cycle control is handled by interrupts
    }
}
void Systick_Handler(void) {
