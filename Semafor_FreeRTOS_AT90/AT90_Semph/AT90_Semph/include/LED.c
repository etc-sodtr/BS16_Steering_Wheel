/*
 * LED.c
 *
 * Created: 7/5/2011 0:04:45
 *  Author: MMM
 */ 

#include <avr/io.h>
#include "LED.h"
void vLEDInit(void)
{
// Set LED_O as output pin
    DDR_LED_O |= (1<<BIT_LED_O);
}
void vLEDToggle(void)
{
   //Toggle LED
   PORT_LED_O ^= (1<<BIT_LED_O);	
}
