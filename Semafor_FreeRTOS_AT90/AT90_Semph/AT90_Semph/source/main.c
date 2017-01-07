/*
 * AT90_Semph.c
 *
 * Created: 28-Dec-16 19:50:03
 * Author : lupuv
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "../include/FreeRTOS.h"
#include "../include/semphr.h"
#include "../include/task.h"
#include "../include/BitOperations_V1.5.h"
#include "../include/button.h"
#include "../include/LCD_V3.6.h"

#define mainLED_TASK_PRIORITY			( tskIDLE_PRIORITY +1)
#define mainButton_TASK_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainLCD_TASK_PRIORITY				( tskIDLE_PRIORITY  )
xSemaphoreHandle xButtonSemaphore=NULL;




/*-----------------------------------------------------------*/

static void vLEDFlashTask( void * pvParameters )
{	OUTPUT(G,0);
	portTickType xLastWakeTime;
	const portTickType xFrequency = 1000;
	xLastWakeTime=xTaskGetTickCount();
	for (;;)
	{
		TOGGLE_PIN(G,0);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

static void vLEDFlashTask1( void * pvParameters )
{	OUTPUT(G,1);
	portTickType xLastWakeTime;
	const portTickType xFrequency = 1500;
	xLastWakeTime=xTaskGetTickCount();
	for (;;)
	{
		TOGGLE_PIN(G,1);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}



static void vButtonCheckTask( void *pvParameters )
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 20;
	xLastWakeTime=xTaskGetTickCount();
	xSemaphoreTake(xButtonSemaphore, (portTickType)0);
	vButtonInit();
	for (;;)
	{
		if (xButtonGetStatus()==pdTRUE)
		{
			xSemaphoreGive(xButtonSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}



void update_LCD_Task ( void *pvParameters )
{

	portTickType xLastWakeTime;
	const portTickType xFrequency = 500;
	xLastWakeTime=xTaskGetTickCount();
	unsigned portBASE_TYPE uxTasks;
	unsigned portBASE_TYPE uxTasks1;
	LCDInit();

	LCDShowChar("BT:", 0, 1);
	LCDShowChar("TSKS:", 0, 0);
	
	for (;;)
	{
		uxTasks=uxTaskGetNumberOfTasks();
		uxTasks1=uxTasks;
		//works only up to 9 tasks
		
		LCDShowInt(uxTasks1,5,0);
		if (xButtonSemaphore != NULL)
		{
			//LCDGotoXY(3,1);
			//poll
			
			if (xSemaphoreTake(xButtonSemaphore, (portTickType)0)==pdTRUE)
			{
				LCDShowInt(1,3,1);
			}
			else
			{
				LCDShowInt(0,3,1);
			}
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

portSHORT main( void )
{
	// initialize port
DDRE=0xFF;

	vSemaphoreCreateBinary(xButtonSemaphore);
	if(xButtonSemaphore!=NULL)
	{
		//successfully created
		xTaskCreate( vButtonCheckTask,"Button", configMINIMAL_STACK_SIZE, NULL, mainButton_TASK_PRIORITY, NULL );
	}
	xTaskCreate( vLEDFlashTask,"LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
		xTaskCreate( update_LCD_Task,"LCD", configMINIMAL_STACK_SIZE, NULL, mainLCD_TASK_PRIORITY, NULL );
		xTaskCreate( vLEDFlashTask1,"LED1", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );

	vTaskStartScheduler();

	return 0;
}