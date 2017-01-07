/*
 * LED.h
 *
 * Created: 7/5/2011 0:04:32
 *  Author: MMM
 */ 


#ifndef LED_H_
#define LED_H_
// Output Port pin LED_O
#define PORT_LED_O      PORTG
#define DDR_LED_O       DDRG
#define BIT_LED_O       2
void vLEDInit(void);
void vLEDToggle(void);



#endif /* LED_H_ */