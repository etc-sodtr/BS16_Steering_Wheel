/*
 * CAN_v0.c
 *
 * Created: 13-Jan-17 18:30:09
 *  Author: lupuv
 */ 
//TRIMITERE
#define CAN_RESET_CONTROLLER B1(CANGCON,SWRES) //reset CAN Controller (CANGCON=0x01)
//xSemaphoreHandle xRPMSemaphore;

char xRpmChangeGetStatus(void)
{
	// See if rpm is new
	if(menuflag==1)

	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

void read_can_mobs0() {
	CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
	unsigned char i;
	unsigned char can_byte[8];

	CANPAGE = 0x08;
	i = 0;
	
	for (i=0; i<=7; i++) {
		CANPAGE = ( 0x08 | (i & 0x7) );
		can_byte[i] = CANMSG;
		//CANMSG = 0;
	};
	
	
	
    rpmMSB = can_byte[0];
	rpmLSB = can_byte[1];
	eng_loadMSB=can_byte[2];
	eng_loadLSB=can_byte[3];
	throttle_posMSB=can_byte[4];
	throttle_posLSB=can_byte[5];
	air_temp=can_byte[6];
    engine_temp = can_byte[7];
	
	//rpm=((rpmMSB<<8)+rpmLSB)*0.390625;
	//eng_load=((eng_loadMSB<<8)+eng_loadLSB)*0.00526428247660249;
	//throttle_pos=((throttle_posMSB<<8)+throttle_posLSB)*0.00152587890625;
	rpm=((rpmMSB<<8)+rpmLSB);
	if (rpm!=rpm_old)
	{
		//menuflag=1;//
		xSemaphoreGive(xRPMSemaphore);
		rpm_old=rpm;
	}
	eng_load=((eng_loadMSB<<8)+eng_loadLSB);
	throttle_pos=((throttle_posMSB<<8)+throttle_posLSB);
	
    CANSTMOB = 0;
    CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
    CANGIT=CANGIT;


CANPAGE = 0x18;
i = 0;
        for (i=0; i<=7; i++) {
            CANPAGE = ( 0x18 | (i & 0x7) );
            can_byte[i] = CANMSG;
        };

  inj_dutyMSB = can_byte[2];
  inj_dutyLSB = can_byte[3];
  map_sensMSB = can_byte[4];
  map_sensLSB = can_byte[5];
  
//   inj_duty = ((inj_dutyMSB<<8)+inj_dutyLSB)*0.00381470005959272;
//   map_sens = ((map_sensMSB<<8)+inj_dutyLSB)*0.0000778198227635585;
  inj_duty = ((inj_dutyMSB<<8)+inj_dutyLSB);
  map_sens = ((map_sensMSB<<8)+inj_dutyLSB);

    CANSTMOB = 0;
    CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
    CANGIT=CANGIT;

CANPAGE = 0x28;
i = 0;
        for (i=0; i<=7; i++) {
            CANPAGE = ( 0x28 | (i & 0x7) );
            can_byte[i] = CANMSG;
        };
battery_rowMSB = can_byte[0];
battery_rowLSB = can_byte[1];
oil_pressMSB = can_byte[2];
oil_pressLSB = can_byte[3];

// battery_row = ((battery_rowMSB<<8)+battery_rowLSB)*0.00032600000849925;
// oil_press = ((oil_pressMSB<<8)+oil_pressLSB)*0.0000778198227635585;
battery_row = ((battery_rowMSB<<8)+battery_rowLSB);
oil_press = ((oil_pressMSB<<8)+oil_pressLSB);

    CANSTMOB = 0;
    CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
    CANGIT=CANGIT;

CANPAGE = 0x38;
i = 0;
        for (i=0; i<=7; i++) {
            CANPAGE = ( 0x38 | (i & 0x7) );
            can_byte[i] = CANMSG;
        };

//lambda1 = (147*((can_byte[0]*0.00390625018553692)+0.5));
lambda1 = can_byte[0];
speedMSB = can_byte[2];
speedLSB = can_byte[3];
gear = can_byte[4];

//speed = ((speedMSB<<8)+speedLSB)*0.00390625;
speed = ((speedMSB<<8)+speedLSB);


    //lambda_1 = (147*((can_byte[0]*0.00390625018553692)+0.5));
    CANSTMOB = 0;
    CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
    CANGIT=CANGIT;


};



/*
void read_can_mobs5() {

	unsigned char i;
	unsigned char can_byte1[8];

	CANPAGE = 0x58;
	i = 0;
	
	for (i=0; i<=7; i++) {
		CANPAGE = ( 0x58 | (i & 0x7) );
		can_byte1[i] = CANMSG;
		
		CANMSG = 0;
	};
	
oil_press = can_byte1[5];
	
	//LCDShowInt(oil_press,6,1);
	CANSTMOB = 0;
	CANCDMOB = 0x98;  // Reconfigure mOb as CAN RX mOb
	CANGIT=CANGIT;

};
*/

/*====================================================*/
/* init_rx_can_mobs () */
/*====================================================*/

void init_rx_can_mobs () {
// First RX message from AEMNet

	CANPAGE = 0x08;

	CANIDT1 = 0x0F;
	CANIDT2 = 0x85;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0xFF;
	CANIDM2 = 0xFF;
	CANIDM3 = 0xFF;
	CANIDM4 = 0xFF;

	CANCDMOB = 0x98;
	
// Second RX message from AEMNet

    CANPAGE = 0x18;
    CANSTMOB = 0;

    CANIDT1 = 0x0F;
    CANIDT2 = 0x85;
    CANIDT3 = 0x00;
    CANIDT4 = 0x08;
    CANIDM1 = 0xFF;
    CANIDM2 = 0xFF;
    CANIDM3 = 0xFF;
    CANIDM4 = 0xFF;

    CANCDMOB = 0x98;

// Third RX message from AEMNet

    CANPAGE = 0x28;
    CANSTMOB = 0;

    CANIDT1 = 0x0F;
    CANIDT2 = 0x85;
    CANIDT3 = 0x00;
    CANIDT4 = 0x10;
    CANIDM1 = 0xFF;
    CANIDM2 = 0xFF;
    CANIDM3 = 0xFF;
    CANIDM4 = 0xFF;

    CANCDMOB = 0x98;

// Fourth RX message from AEMNet


    CANPAGE = 0x38;
    CANSTMOB = 0;

    CANIDT1 = 0x0F;
    CANIDT2 = 0x85;
    CANIDT3 = 0x00;
    CANIDT4 = 0x18;
    CANIDM1 = 0xFF;
    CANIDM2 = 0xFF;
    CANIDM3 = 0xFF;
    CANIDM4 = 0xFF;

    CANCDMOB = 0x98;	
/*
	// First Can message aaaaa
	CANPAGE = 0x48;
	CANSTMOB = 0;

	CANIDT1 = 0x0A;
	CANIDT2 = 0x55;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0xFF;
	CANIDM2 = 0xFF;
	CANIDM3 = 0xFF;
	CANIDM4 = 0xFF;

	CANSTMOB = 0x00;
	CANCDMOB = 0x58;
	CANGIT = CANGIT;

	// Second Can message aaaaa

	CANPAGE = 0x58;
	CANSTMOB = 0;

	CANIDT1 = 0x0A;
	CANIDT2 = 0x5A;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0xFF;
	CANIDM2 = 0xFF;
	CANIDM3 = 0xFF;
	CANIDM4 = 0xFF;

	CANCDMOB = 0x98;


	// First Can message aaaaa
	CANPAGE = 0x68;
	CANSTMOB = 0;

	CANIDT1 = 0x0A;
	CANIDT2 = 0xFA;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0xFF;
	CANIDM2 = 0xFF;
	CANIDM3 = 0xFF;
	CANIDM4 = 0xFF;

	CANSTMOB = 0x00;
	CANCDMOB = 0x58;
	CANGIT = CANGIT;

	// Second Can message aaaaa

	CANPAGE = 0x78;
	CANSTMOB = 0;

	CANIDT1 = 0x0A;
	CANIDT2 = 0xFF;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0xFF;
	CANIDM2 = 0xFF;
	CANIDM3 = 0xFF;
	CANIDM4 = 0xFF;

	CANCDMOB = 0x98;
*/
};

void CAN_Init(){
// Reset all the MObs
for (int ch=0; ch<15; ch++)
{
	CANPAGE=ch<<4;// se muta pe fiecare Message OBject
	CANSTMOB=0;//Status register-
	CANIDT1=0;//ID Tag Registers
	CANIDT2=0;
	CANIDT3=0;
	CANIDT4=0;
	CANIDM1=0;//ID Mask registers
	CANIDM2=0;
	CANIDM3=0;
	CANIDM4=0;
	for (int data=0; data<8; data++) CANMSG=0;
}
// Enable the CAN controller
CANGCON=0x02;
//enable mob0,mob1
CANEN2=0x03;
// MOb0..7 Interrupts: oFF
CANIE2=0x00;
// MOb8..14 Interrupts: Off
CANIE1=0x00;
// CAN Interrupts:
// Timer Overrun: Off
// General Errors: Off
// Frame Buffer: Off
// MOb Errors: Off
// Transmit: Off
// Receive: On
// Bus Off: Off
// All, except Timer Overrun: On
CANGIE=0x00;
// CAN System Clock: 4000.0 kHz
CANBT1=0x06;
// Propagation Time Segement: 0.750 us
// Re-Sync Jump Width: 0.250 us
CANBT2=0x04;
// Sample Point(s): 1
// Phase Segment 1: 0.500 us
// Phase Segment 2: 0.500 us
CANBT3=0x12;
// CAN Timer Clock Period: 0.500 us
CANTCON=0x00;

init_rx_can_mobs();
}












/*====================================================*/
/* downshift() */
/*====================================================*/
/*
void downshift()
{
        unsigned char i;
       // unsigned char j=0;

        //shifter_command=0xF0;
shifter_command=fanStartValue;
//while (j==0)
//{

//CANCDMOB = 0x58;

CANPAGE = 0x08;
i = 0;
        for (i=0; i<=7; i++) {
            CANPAGE = ( 0x08 | (i & 0x7) );
            //CANMSG = shifter_command;

            if(0==i)
            {
            CANMSG = shifter_command;
            }
            if(1==i)
            {
            CANMSG = 0xFF;
            }
            if(2==i)
            {
            CANMSG = 0xFF;
            }
            if(3==i)
            {
            CANMSG = 0xFF;
            }
            if(4==i)
            {
            CANMSG = 0xFF;
            }
            if(5==i)
            {
             CANMSG = 0xFF;
            }
            if(6==i)
            {
             CANMSG = 0xFF;
            }
            if(7==i)
            {
             CANMSG = 0xFF;
            }
        };

CANIDT1 = 0x0A;
CANIDT2 = 0x55;
CANIDT3 = 0x00;
CANIDT4 = 0x00;
CANIDM1 = 0xFF;
CANIDM2 = 0xFF;
CANIDM3 = 0xFF;
CANIDM4 = 0xFF;
 
CANSTMOB = 0x00;
CANCDMOB = 0x58;
CANGIT = CANGIT;

    _delay_ms(1);

}
*/

