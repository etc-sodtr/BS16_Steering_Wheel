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
#include "../include/define.h"
#include "../include/BitOperations_V1.5.h"
#include "../include/button.h"
#include "../include/LCD_V3.6.h"
#include "../include/SPI_V0.1.h"

#include "../include/functions_lib.h"
#include "../include/CAN_v0.1.h"

#define maintask1			( tskIDLE_PRIORITY +2)
#define maintask2			( tskIDLE_PRIORITY +4)
#define maintask3			( tskIDLE_PRIORITY +3)
#define maintask4			( tskIDLE_PRIORITY +1)
#define maintask5			( tskIDLE_PRIORITY )
xSemaphoreHandle xRPMSemaphore=NULL;
/*-----------------------------------------------------------*/

void update_RPM_Task ( void *pvParameters )
{

	//portTickType xLastWakeTime;
	//const portTickType xFrequency = 50;
	//xLastWakeTime=xTaskGetTickCount();
	//unsigned portBASE_TYPE uxTasks;
	//unsigned portBASE_TYPE uxTasks1;
	
	for (;;)
	{
		//uxTasks=uxTaskGetNumberOfTasks();
		//uxTasks1=uxTasks;
		//works only up to 9 tasks
		
		
		if (xRPMSemaphore != NULL)
		{
			//poll
			if (xSemaphoreTake(xRPMSemaphore, (portTickType)portMAX_DELAY)==pdTRUE)
			{
				select_menu1();
				//menuflag=0;
				//LCDShowInt(uxTasks1,3,3);
			}
		}
		//vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}


/*
static void vRPMCheckTask( void *pvParameters )
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 20;
	xLastWakeTime=xTaskGetTickCount();
	xSemaphoreTake(xRPMSemaphore, (portTickType)0);
	
	for (;;)
	{
		if (xRpmChangeGetStatus()==pdTRUE)
		{
			xSemaphoreGive(xRPMSemaphore);
		}
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}
*/
void Display_segments ( void *pvParameters )
{
	
	
	portTickType xLastWakeTime;
	const portTickType xFrequency = 10;
	xLastWakeTime=xTaskGetTickCount();
	//LCDInit();
	
	for (;;)
	{
		//display_value(0x00, 0x81, 0x82, 0x92, 0x99, 0xB0, 0xA4, 0xF9);
		display_value(0x00, gear_to_display, buffer[testvar3], buffer[testvar2], buffer[testvar], buffer[speed_digit3], buffer[speed_digit2], buffer[speed_digit1]);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}


void Right_Switch ( void *pvParameters )
{
	
	
	portTickType xLastWakeTime;
	const portTickType xFrequency = 200;
	xLastWakeTime=xTaskGetTickCount();
	
	
	
	for (;;)
	{
		select_menu();
		
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void Read_CAN_mobs ( void *pvParameters )
{
	
	
	portTickType xLastWakeTime;
	const portTickType xFrequency = 50;
	xLastWakeTime=xTaskGetTickCount();
	
	
	
	for (;;)
	{
		read_can_mobs0();
		for_segments_decode();
		
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}



portSHORT main( void )
{
	// initialize port
DDRA=0xFF;
DDRB=0xFF;
DDRC=0x00;
DDRE=0xFF;
DDRG=0xFF;
PORTC=0xFF;

INPUTS(E,3);
PULLUP_PIN(E,3);
INPUTS(D,1);
INPUTS(D,2);
INPUTS(D,3);
OUTPUT(D,5);
INPUT(D,6);

SET_PIN_LO(E,5);
SET_PIN_HI(E,2);
SET_PIN_HI(E,4);

SPCR=0x52;
SPSR=0x00;
LCDInit();
CAN_Init();




	//vSemaphoreCreateBinary(xRPMSemaphore);
	xRPMSemaphore=xSemaphoreCreateBinary();
	//if(xRPMSemaphore!=NULL)
	//{
		//successfully created
		//xTaskCreate( vRPMCheckTask,"task5", configMINIMAL_STACK_SIZE, NULL, maintask5, NULL );
	//}
	xTaskCreate( update_RPM_Task,"task4", configMINIMAL_STACK_SIZE, NULL, maintask4, NULL );
	xTaskCreate( Display_segments,"task1", configMINIMAL_STACK_SIZE, NULL, maintask1, NULL );
	//xTaskCreate( Right_Switch,"task2", configMINIMAL_STACK_SIZE, NULL, maintask2, NULL );
	xTaskCreate( Read_CAN_mobs,"task3", configMINIMAL_STACK_SIZE, NULL, maintask3, NULL );
	vTaskStartScheduler();

	return 0;
}


