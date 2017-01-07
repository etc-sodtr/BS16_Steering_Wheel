/* LCD2x8.cpp
 * Last updated: 2014.07.24;
	* If LCD_CLK will don't have delay and the 4 bit DATALENGTH will be used, then:
	** LCDShowNumberXY function takes 1.03ms to 1.16ms, depends by the number value (32767 respectively -32768);
	** LCDShowStringXY function takes 304us to 1.22ms, depends by the string length value (1 character respectively 8 characters)
*/ 
#include <stdlib.h>

#define LCD_CHARACTERSONXAXIX 16 //LCD_COLUMNs_NUMBER or Number_of_characters on the X axis;
#define LCD_DATALENGTH 4 //Data length of LCD;
#define LCD_DATA_PORT C //Change to port where LCD_DATA_BUS_PINs are connected: [A,B,C,D,E,F...];
#define LCD_D0 0 //Data0_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Otherwise even if this will be defined, it will not be taken into consideration;
#define LCD_D1 1 //Data1_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Otherwise even if this will be defined, it will not be taken into consideration;
#define LCD_D2 2 //Data2_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Otherwise even if this will be defined, it will not be taken into consideration;
#define LCD_D3 3 //Data3_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Otherwise even if this will be defined, it will not be taken into consideration;
#define LCD_D4 4 //Data4_Bit from LCD_DPORT;
#define LCD_D5 5 //Data5_Bit from LCD_DPORT;
#define LCD_D6 6 //Data6_Bit from LCD_DPORT;
#define LCD_D7 7 //Data7_Bit from LCD_DPORT;
#define LCD_INST_PORT C
#define LCD_EN 3 //Enable_Data from LCD_IPORT;
#define LCD_RS 2 //Register_Selector_Bit from LCD_IPORT;
#define LCD_RW 1 //Read_Write_Bit from LCD_IPORT;

#if(LCD_DATALENGTH==4)
	#undef LCD_D0
	#undef LCD_D1
	#undef LCD_D2
	#undef LCD_D3
	#define LCD_D0 LCD_D4 //Data0_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Else if LCD_DATALENGTH=4, LCD_D0=LCD_D4;
	#define LCD_D1 LCD_D5 //Data1_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Else if LCD_DATALENGTH=4, LCD_D1=LCD_D5;
	#define LCD_D2 LCD_D6 //Data2_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Else if LCD_DATALENGTH=4, LCD_D2=LCD_D6;
	#define LCD_D3 LCD_D7 //Data3_Bit from LCD_DPORT;This must be defined only if the DATALENGTH=8;Else if LCD_DATALENGTH=4, LCD_D3=LCD_D7;
#endif

void LCD_CLK(void){
	SET_PIN_HI(LCD_INST_PORT,LCD_EN);_delay_us(2);//delay_us(10);
	SET_PIN_LO(LCD_INST_PORT,LCD_EN);_delay_us(2);
}
unsigned char String_Length(const char *str){
	unsigned char strLength=0;
	while(str[strLength]!='\0'){strLength++;}
	return strLength;
}
void LCDReadBusyFlag(){
	uint16_t timer=2000;//[us];
	INPUT(LCD_DATA_PORT,LCD_D7);
	INPUT(LCD_DATA_PORT,LCD_D6);
	INPUT(LCD_DATA_PORT,LCD_D5);
	INPUT(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==8){
		INPUT(LCD_DATA_PORT,LCD_D3);
		INPUT(LCD_DATA_PORT,LCD_D2);
		INPUT(LCD_DATA_PORT,LCD_D1);
		INPUT(LCD_DATA_PORT,LCD_D0);
	}
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_HI(LCD_INST_PORT,LCD_RW);
	SET_PIN_HI(LCD_INST_PORT,LCD_EN);_delay_us(2);
	while(READ_PIN(LCD_DATA_PORT,LCD_D7)!=0 && timer--){_delay_us(1);}
	SET_PIN_LO(LCD_INST_PORT,LCD_EN);_delay_us(2);
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	OUTPUT(LCD_DATA_PORT,LCD_D7);
	OUTPUT(LCD_DATA_PORT,LCD_D6);
	OUTPUT(LCD_DATA_PORT,LCD_D5);
	OUTPUT(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==8){
		OUTPUT(LCD_DATA_PORT,LCD_D3);
		OUTPUT(LCD_DATA_PORT,LCD_D2);
		OUTPUT(LCD_DATA_PORT,LCD_D1);
		OUTPUT(LCD_DATA_PORT,LCD_D0);
	}
}
void LCDFunctionSet(char N,char F){
	/*LCDFunctionSet:0 0 0 0 1 DL N F * *;
		DL=DataLength[0:4Bit,1:8Bit];
		N=NumberOfLines[0:1,1:2];
		F=Font[0:5x8,1:5x10];
		eg: LCDFunctionSet(1,0);DataLength:8Bit;NumberOfDisplaiedLines:2;Font:5*8;
		??? Sets to 8-bit operation and
				selects 2-lines display and 5 · 8
				dot character font. (Number of
				display lines and character
				fonts cannot be changed after
				this step;*/
	char DL=1;
	if(LCD_DATALENGTH==4){DL=0;}
		SET_PIN_LO(LCD_INST_PORT,LCD_RS);
		SET_PIN_LO(LCD_INST_PORT,LCD_RW);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
		SET_PIN_HI(LCD_DATA_PORT,LCD_D5);
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D4,DL);
		if(LCD_DATALENGTH==4){LCD_CLK();}
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D3,N);
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D2,F);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D1);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D0);
		LCD_CLK();
		LCDReadBusyFlag();
}
void LCDDisplayOnOff(char D,char C,char B){
	/*LCDDisplayOnOff: 0 0 0 0 0 0 1 D C B;
		D=EntireDisplay[0:Off,1:On];
		C=Cursor[0:Off,1:On];
		B=Blinking_or_CursorPosition[0:Off,1:On];
		??? This function sets entire display (D)
				on/off, cursor on/off (C), and
				blinking of cursor position character (B);*/
		SET_PIN_LO(LCD_INST_PORT,LCD_RS);
		SET_PIN_LO(LCD_INST_PORT,LCD_RW);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D4);
		if(LCD_DATALENGTH==4){LCD_CLK();}
		SET_PIN_HI(LCD_DATA_PORT,LCD_D3);
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D2,D);
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D1,C);
		SET_PIN_VAL(LCD_DATA_PORT,LCD_D0,B);
		LCD_CLK();
		LCDReadBusyFlag();
}
void LCDEntryMode(char ID,char S){
	/*EntireMode: 0 0 0 0 0 0 0 1 I/D S;
		I/D=Increment/Decrement[1:I,0:D];
		S=Shift[1:Yes,0:No];
		???	Sets cursor move direction and
				specifies display shift.
				These operations are performed
				during data write and read;*/
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_LO(LCD_DATA_PORT,LCD_D3);
	SET_PIN_HI(LCD_DATA_PORT,LCD_D2);
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D1,ID);
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D0,S);
	LCD_CLK();
	LCDReadBusyFlag();
}
void LCDReturnHome(void){
	//LCDReturnHome: 0 0 0 0 0 0 0 0 1 0;
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_LO(LCD_DATA_PORT,LCD_D3);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D2);
	SET_PIN_HI(LCD_DATA_PORT,LCD_D1);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D0);
	LCD_CLK();
	LCDReadBusyFlag();
}
void LCDClear(void){
	//LCDClear: 0 0 0 0 0 0 0 0 0 1;
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_LO(LCD_DATA_PORT,LCD_D3);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D2);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D1);
	SET_PIN_HI(LCD_DATA_PORT,LCD_D0);
	LCD_CLK();
	LCDReadBusyFlag();
}
void LCDCursorOrDisplayShift(char SC,char RL){
	/*LCDCursorOrDisplayShift: 0 0 0 0 0 1 S/C R/L * *;
		SC=ShitCursor[?,?];
		RL=Right/Left[0:R,1:L];
		??? Set cursor moving and
				display shift control bit, and
				the direction, without changing
				DDRAM data;*/
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
	SET_PIN_HI(LCD_DATA_PORT,LCD_D4);
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D3,SC);
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D2,RL);
	LCD_CLK();
	LCDReadBusyFlag();
}
void LCDSetDDRAMaddress(char addr){
	/* SetDDRAMaddress: eg. 0 0 1 AC6 AC5 AC4 AC3 AC2 AC1 AC0;
	???	- Sets DDRAM address so that
			the cursor is positioned at the
			head of the second line;
			- However, when N is 0 (1-line display), AC6~AC0 can be 00H to 4FH(79);
			- When N is 1 (2-line display), AC6~AC0 can be 00H(0) to 27H(39)
			for the first line, and 40H(63) to 67H(103) for the second line;*/
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	SET_PIN_HI(LCD_DATA_PORT,LCD_D7);
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D6,GET_BIT(addr,6));
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D5,GET_BIT(addr,5));
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D4,GET_BIT(addr,4));
	if(LCD_DATALENGTH==4){LCD_CLK();}
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D3,GET_BIT(addr,3));
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D2,GET_BIT(addr,2));
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D1,GET_BIT(addr,1));
	SET_PIN_VAL(LCD_DATA_PORT,LCD_D0,GET_BIT(addr,0));
	LCD_CLK();
	LCDReadBusyFlag();
}
void LCDSetDDRAMaddressXY(uint8_t x,uint8_t y){
	/* SetDDRAMaddress: eg. 0 0 1 AC6 AC5 AC4 AC3 AC2 AC1 AC0;
	???	- Sets DDRAM address so that
			the cursor is positioned at the
			head of the second line;
			- However, when N is 0 (1-line display), AC6~AC0 can be 00H to 4FH(79);
			- When N is 1 (2-line display), AC6~AC0 can be 00H(0) to 27H(39)
			for the first line, and 40H(64) to 67H(103) for the second line;*/
	switch(y){
		case 0:y=0x00;break;
		case 1:y=0x40;break;
		case 2:y=0x14;break;
		case 3:y=0x54;break;
		default:y=0x00;break;
	}
	LCDSetDDRAMaddress(x+y);
}
void LCDShowString(const char *str){
	uint8_t k=0;//String_length;
	uint8_t DataBits[8]={LCD_D7,LCD_D6,LCD_D5,LCD_D4,LCD_D3,LCD_D2,LCD_D1,LCD_D0};
	LCDFunctionSet(1,0);//NumberOfLines=2;Font5x8;
	LCDDisplayOnOff(1,1,0);//EntireDisplay-ON, Cursor-ON;Blinking-OFF;
	while(str[k]!='\0'){
		SET_PIN_HI(LCD_INST_PORT,LCD_RS);
		SET_PIN_LO(LCD_INST_PORT,LCD_RW);
		for(uint8_t j=0;j<8;j++){
			SET_PIN_VAL(LCD_DATA_PORT,DataBits[j],GET_BIT(str[k],(7-j)));
			if((j==3)&&(LCD_DATALENGTH==4)){LCD_CLK();}
		}
		LCD_CLK();
		LCDReadBusyFlag();
		LCDDisplayOnOff(1,0,0);
		k++;
	}
}
void LCDShowChar(const char str[],uint8_t x, uint8_t y){
//void LCDShow(const char *str,char x, char y){//Other modality to define a string;
	LCDSetDDRAMaddressXY(x,y);
	LCDShowString(str);
}
void LCDShowNumber(int number){
	char qString[6];
	itoa(number,qString,10);
	LCDShowString(qString);
	LCDShowString(" ");
}
void LCDShowInt(int number,uint8_t x, uint8_t y){
	LCDSetDDRAMaddressXY(x,y);
	LCDShowNumber(number);
}
void LCDClearXY(uint8_t x, uint8_t y){
	LCDSetDDRAMaddressXY(x,y);
	LCDShowString(" ");
}
void LCDClearMore(uint8_t xStart, uint8_t xStop, uint8_t y){
	for(uint8_t x=xStart;x<=xStop;x++){LCDShowChar(" ",x,y);}
}
void LCDTurnOff(void){
	LCDDisplayOnOff(0,0,0);
	LCDClear();
	SET_PIN_LO(LCD_DATA_PORT,LCD_D4);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D5);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D6);
	SET_PIN_LO(LCD_DATA_PORT,LCD_D7);
	SET_PIN_LO(LCD_INST_PORT,LCD_EN);
	SET_PIN_LO(LCD_INST_PORT,LCD_RS);
	SET_PIN_LO(LCD_INST_PORT,LCD_RW);
	if(LCD_DATALENGTH==8){
		SET_PIN_LO(LCD_DATA_PORT,LCD_D0);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D1);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D2);
		SET_PIN_LO(LCD_DATA_PORT,LCD_D3);
	}
}
void LCDInit(void){
	_delay_ms(50);
	OUTPUT(LCD_DATA_PORT,LCD_D7);
	OUTPUT(LCD_DATA_PORT,LCD_D6);
	OUTPUT(LCD_DATA_PORT,LCD_D5);
	OUTPUT(LCD_DATA_PORT,LCD_D4);
	OUTPUT(LCD_INST_PORT,LCD_EN);
	OUTPUT(LCD_INST_PORT,LCD_RS);
	OUTPUT(LCD_INST_PORT,LCD_RW);
	if(LCD_DATALENGTH==8){
		OUTPUT(LCD_DATA_PORT,LCD_D3);
		OUTPUT(LCD_DATA_PORT,LCD_D2);
		OUTPUT(LCD_DATA_PORT,LCD_D1);
		OUTPUT(LCD_DATA_PORT,LCD_D0);
	}
	LCDFunctionSet(1,0);//NumberOfLines=2;Font5x8;
	LCDDisplayOnOff(1,1,0);//EntireDisplay-ON, Cursor-ON;Blinking-OFF;
	LCDClear();
	LCDEntryMode(1,0);//Increment-YES, Shift-NO;
	LCDShowChar("",0,0);//Please do not delete this line. Without this when the ShowStringXY("STRING") function will not display the "STRING" parameter when it is used first time;
}
//Before using this file, in the beginning of the file, please change the LCD_PINs and LCD_PORTs variables (#define ...);
//In the main function will be called LCDInit();
//In the main while will be called LCDShow("Characters",5,0);//Column 5, Row 1;
/*Using example:
		LCDClear();
		LCDShow("Te",0,0);
		LCDShow("B",5,0);
		LCDShow("Gi",0,1);
		LCDShow("R",5,1);
		LCDShow("1",3,0);
		LCDShow("1",3,1);
		LCDShow("1",7,0);
		LCDShow("1",7,1);
		LCDClearXY(1,1);
		_delay_ms(10);
*/