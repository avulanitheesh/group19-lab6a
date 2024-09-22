#include <stdint.h>
#include "tm4c123gh6pm.h"
volatile uint32_t dutyCycle = 50;  // Initial duty cycle: 50%
volatile uint32_t count = 160;      // Count value for 100 kHz PWM with 16 MHz clock PWM Frequency=

  // Function declarations
void GPIO_Handler(void);
void Systick_Handler(void);
int main(void) {

