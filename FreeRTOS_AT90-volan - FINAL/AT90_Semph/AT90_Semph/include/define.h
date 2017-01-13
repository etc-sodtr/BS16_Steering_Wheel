



extern xSemaphoreHandle xRPMSemaphore;
int k = 0;
//butoane
unsigned long button1 = 0;
unsigned long button2 = 0;
unsigned long button3 = 0;
unsigned long button4 = 0;
unsigned char button1_activated = 0;
unsigned char button2_activated = 0;
unsigned char button3_activated = 0;
unsigned char button4_activated = 0;

//variabile butoane rotative
unsigned char  changedbits, portchistory, changedBitsLeft, portcHistoryLeft;
unsigned char menuflag=0;
//variabile date monopost
int fanStartValue=87;
int autoshiftState=0;
int battVoltage=0;
int tempchangedbits;
uint16_t rpm, rpm_old ;
uint16_t eng_load;
uint16_t throttle_pos;
uint16_t inj_duty;
uint16_t map_sens;
uint16_t battery_row;
uint16_t oil_press;
uint16_t speed;



unsigned char engine_temp;
unsigned char fuel_press;
unsigned char air_temp;
unsigned char lambda1;
unsigned char gear;
unsigned char gear_to_display;
uint8_t gear_to_displayint;
unsigned char radio;
uint8_t testvar;
uint8_t testvar2;
uint8_t testvar3;
uint8_t speed_digit1;
uint8_t speed_digit2;
uint8_t speed_digit3;


unsigned char shifter_command;
unsigned char communication_command;


//ecu variables 16bits
unsigned char rpmMSB, rpmLSB;
unsigned char eng_loadMSB, eng_loadLSB;
unsigned char throttle_posMSB, throttle_posLSB;
unsigned char inj_dutyMSB, inj_dutyLSB;
unsigned char map_sensMSB, map_sensLSB;
unsigned char battery_rowMSB, battery_rowLSB;
unsigned char oil_pressMSB, oil_pressLSB;
unsigned char speedMSB, speedLSB;
unsigned char gear_flag = 0;
char nr=0;
unsigned char can_byte[8];
int count=0;


//====================================================================

#define DISP_TYPE_GEAR_0 0x81
#define DISP_TYPE_GEAR_1 0xF3
#define DISP_TYPE_GEAR_2 0x49
#define DISP_TYPE_GEAR_3 0x61
#define DISP_TYPE_GEAR_4 0x33
#define DISP_TYPE_GEAR_5 0x25
#define DISP_TYPE_GEAR_6 0x05
#define DISP_TYPE_GEAR_7 0xF1
#define DISP_TYPE_GEAR_8 0x01
#define DISP_TYPE_GEAR_9 0x21
#define DISP_TYPE_GEAR_BAR 0x7F

// Leds =========================================================
#define DISP_TYPE_RPM_1 0x01
#define DISP_TYPE_RPM_2 0x03
#define DISP_TYPE_RPM_3 0x07
#define DISP_TYPE_RPM_4 0x0F
#define DISP_TYPE_RPM_5 0x1F
#define DISP_TYPE_RPM_6 0x3F
#define DISP_TYPE_RPM_7 0x7F
#define DISP_TYPE_RPM_8 0xFF
#define DISP_TYPE_RPM_LIMIT 0xFF
#define DISP_TYPE_RPM_LIMIT_LOW 0x00


char  buffer[]={
	0xC0,
	0xF9,
	0xA4,
	0xB0,
	0x99,
	0x92,
	0x82,
	0xF8,
	0x80,
	0x90,
};

int getRotary(unsigned char selection1)
{
	//changedBitsLeft=PINC>>4;
	switch (selection1)
	{
		case(0x0F):
		tempchangedbits=0;
		break;
		case(0x0B):
		tempchangedbits=1;
		break;
		case(0x0E):
		tempchangedbits=2;
		break;
		case(0x0A):
		tempchangedbits=3;
		break;
		case(0x07):
		tempchangedbits=4;
		break;
		case(0x03):
		tempchangedbits=5;
		break;
		case(0x06):
		tempchangedbits=6;
		break;
		case(0x02):
		tempchangedbits=7;
		break;		
		case(0x0D):
		tempchangedbits=8;
		break;
		case(0x09):
		tempchangedbits=9;
		break;
		case(0x0C):
		tempchangedbits=10;
		break;
		case(0x08):
		tempchangedbits=11;
		break;
		case(0x05):
		tempchangedbits=12;
		break;
		case(0x01):
		tempchangedbits=13;
		break;
		case(0x04):
		tempchangedbits=14;
		break;
		case(0x00):
		tempchangedbits=15;
		break;		
		default: ;
	}
	
	return tempchangedbits;
}
