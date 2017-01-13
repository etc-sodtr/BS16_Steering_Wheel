//Last update:2014.11.28;
//These defines are independent by other files;

#define NOP asm("nop")//OK;
void NOPS(int nopNo){while(nopNo--){NOP;}}

#define _CONCAT(a,b) (a ## b)//OK;
#define CONCAT(a,b) (_CONCAT(a,b))//OK;

#define DDRX(PortLetter) CONCAT(DDR,PortLetter)//OK;
#define PORTX(PortLetter) CONCAT(PORT,PortLetter)//OK;
#define PINX(PortLetter) CONCAT(PIN,PortLetter)//OK;

#define INPUT(PortLetter,pin) (DDRX(PortLetter) &= ~(1<<(pin)))//OK;
#define INPUTS(PortLetter,pins) (DDRX(PortLetter) &= ~pins)//OK;
#define OUTPUT(PortLetter,pin) (DDRX(PortLetter) |= (1<<(pin)))//OK;
#define OUTPUTS(PortLetter,pins) (DDRX(PortLetter) |= pins)//OK;

#define TOGGLE_PIN(port,pin)	(PORTX(port) ^= (1<<(pin)))
#define SET_PIN_HI(PortLetter,pin) (PORTX(PortLetter) |= (1<<(pin)))//OK;
#define SET_PINS_HI(PortLetter,pins) (PORTX(PortLetter) = pins)//OK;
#define SET_PIN_LO(PortLetter,pin) (PORTX(PortLetter) &= ~(1<<(pin)))//OK;
#define SET_PINS_LO(PortLetter,pins) (PORTX(PortLetter) &= ~pins)//OK;
#define SET_PIN_VAL(PortLetter,pin,LogicValue) ((LogicValue) ? SET_PIN_HI(PortLetter,pin) : SET_PIN_LO(PortLetter,pin))//OK;//v=[0,1];0=Clear;1=Write;
#define SET_PINS_VAL(PortLetter,pins,LogicValue) ((LogicValue) ? SET_PINS_HI(PortLetter,pins) : SET_PINS_LO(PortLetter,pins))//OK;//v=[0,1];0=Clear;1=Write;
#define CLR_PIN_VAL(PortLetter,pin,LogicValue) ((LogicValue) ? SET_PIN_LO(PortLetter,pin) : SET_PIN_HI(PortLetter,pin))//OK;//v=[0,1];1=Clear;0=Write;
#define CLR_PINS_VAL(PortLetter,pins,LogicValue) ((LogicValue) ? SET_PINS_LO(PortLetter,pins) : SET_PINS_HI(PortLetter,pins))//OK;//v=[0,1];1=Clear;0=Write;

#define READ_PIN(PortLetter,pin) ((PINX(PortLetter)>>pin)&1)//OK;
#define PULLUP_PIN(PortLetter,pin) (PORTX(PortLetter) |= (1<<(pin)))//OK;This will be applied after the 'pin' was made INPUT;
#define FLIP_PIN(PortLetter,pin) (PORTX(PortLetter) ^= (1<<(pin)))
#define FLIP_PINS(PortLetter,pins) (PORTX(PortLetter) ^= (pins))

//For Variables or Registries;

#define GET_BIT(reg,bit) ((reg>>bit)&1)//OK;

#define SET_BIT_HI(reg,bit) ((reg) |= (1<<(bit)))//OK;
#define SET_BITS_HI(reg,val) ((reg) |= (val))//OK;
#define SET_BIT_LO(reg,bit) ((reg) &= ~(1<<(bit)))//OK;
#define SET_BITS_LO(reg,val) ((reg) &= ~(val))//OK;
#define SET_BIT_VAL(reg,bit,LogicValue) ((LogicValue) ? B1(reg,bit) : B0(reg,bit))//OK; pin=[0,1...7]; LogicValue=[0,1];

//============ These are used in the Library Files because are Shorts =============//
#define B1(reg,bit) ((reg) |= (1<<(bit)))//OK; B1 comes from Bit1;
#define B0(reg,bit) ((reg) &= ~(1<<(bit)))//OK; B0 comes from Bit0;
#define M1(reg,val) ((reg) |= (val))//OK; M1 comes from Masked Bits will be made one;
#define M0(reg,val) ((reg) &= ~(val))//OK; M0 comes from Masked Bits will be made zero;

#define FLIP_BIT(reg,bit) ((reg) ^= (1<<(bit)))//OK;
#define FLIP_BITS(reg,val) ((reg) ^= (val))//OK;

/*__V2__*/
//#define READ_PIN(PortLetter,bit) (PINX(PortLetter) & (1<<(bit)) == (1<<(bit))) ? 1 : 0)//OK;

/* HELP:
	"|" bit OR 
	"&" bit AND 
	"~" bit NOT (Invert);
	"^" bit EXLUSIVE OR (XOR) 
	"<<" bit LEFT SHIFT 
	">>" bit RIGHT SHIFT
*/
