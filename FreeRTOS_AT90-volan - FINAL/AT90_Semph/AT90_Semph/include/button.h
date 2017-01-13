/*
 * button.h
 *
 * Created: 28-Dec-16 19:58:28
 *  Author: lupuv
 */ 

#define PORT_SWITCH_IP  PORTE
#define DDR_SWITCH_IP   DDRE
#define PIN_SWITCH_IP   PINE
#define BIT_SWITCH_IP   5


void vButtonInit(void)
{
	//INPUT(B,5);
	//PULLUP_PIN(B,5);
	// Set SWITCH_IP as input pin
	DDR_SWITCH_IP &= ~(1<<BIT_SWITCH_IP);
	// Enable pull-up on SWITCH_IP
	PORT_SWITCH_IP |= (1<<BIT_SWITCH_IP);
}
char xButtonGetStatus(void)
{
	// See if switch is pressed
	if((PIN_SWITCH_IP&(1<<BIT_SWITCH_IP)) == 0)
	//if(READ_PIN(B,5)==0)
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
