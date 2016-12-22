/*
 * leds.c
 *
 * Created: 17-Dec-16 16:23:24
 * Author : lupuv
 */ 


// include AVR headers
#include <avr/io.h>

// include the operating system
#include "../include/FreeRTOS.h"
#include "../include/task.h"
#include "../include/BitOperations_V1.5.h"
// tasks
static void blink( void *pvParameters );


/*-----------------------------------------------------------*/

int main( void )
{
	
	// initialize port
	DDRG=0x01;
	PORTG = 0x01;
	
	

	// create blinking task
	xTaskCreate( blink, "Blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	// start the scheduler
	vTaskStartScheduler();

	return 0;
}
/*-----------------------------------------------------------*/

static void blink( void *pvParameters )
{
	//uint8_t dir = 1; // direction flag
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t delay = 500;

	(void)pvParameters; // parameters not used

	// forever loop
	for(;;)
	{
		vTaskDelayUntil(&xLastWakeTime, delay);

TOGGLE_PIN(G,0);
	}
}
