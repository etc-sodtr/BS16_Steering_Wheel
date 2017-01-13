//To used this file, please include in the project the BitOperations.h file;
//last update 22.09.2015

//============ AT90CAN ========================================================================//

#define SPI_INTERRUPT_ENABLE B1(SPCR,SPIE)
#define SPI_ENABLE B1(SPCR,SPE)
#define SPI_DISABLE B0(SPCR,SPE)

#define DATA_ORDER_LSB_FIRST B1(SPCR,DORD)
#define DATA_ORDER_MSB_FIRST B0(SPCR,DORD)
//Master/Slave Select
#define MASTER_SELECT B1(SPCR,MSTR)
#define SLAVE_SELECT B0(SPCR,MSTR)
//Clock Parity
#define SCK_PARITY_HIGH B1(SPCR,CPOL)
#define SCK_PARITY_LOW B0(SPCR,CPOL)
//Clock Phase
#define SCK_SAMPLE_FIRST B0(SPCR,CPHA)
#define SCK_SAMPLE_LAST B1(SPCR,CPHA)
//SPI Clock Rate
#define SCK_FREQ_4		B0(SPSR,SPI2X); B0(SPCR,SPR1); B0(SPCR,SPR0)
#define SCK_FREQ_16		B0(SPSR,SPI2X); B0(SPCR,SPR1); B1(SPCR,SPR0)
#define SCK_FREQ_64		B0(SPSR,SPI2X); B1(SPCR,SPR1); B0(SPCR,SPR0)
#define SCK_FREQ_128	B0(SPSR,SPI2X); B1(SPCR,SPR1); B1(SPCR,SPR0)
#define SCK_FREQ_2		B1(SPSR,SPI2X); B0(SPCR,SPR1); B0(SPCR,SPR0)
#define SCK_FREQ_8		B1(SPSR,SPI2X); B0(SPCR,SPR1); B1(SPCR,SPR0)
#define SCK_FREQ_32		B1(SPSR,SPI2X); B1(SPCR,SPR1); B0(SPCR,SPR0)
#define SCK_FREQ_64_sec	B1(SPSR,SPI2X); B1(SPCR,SPR1); B1(SPCR,SPR0)
//SPI INTERRUPT FLAG
#define SPI_INTERRUPT_FLAG GET_BIT(SPSR,SPIF)
void SPI_Init(void)
{	
	OUTPUT(B,0);//set SS pin as output
	OUTPUT(B,1);//set SCK pin as output
	OUTPUT(B,2);//set MOSI pin as output
	INPUT(B,3);//set MISO pin as input
	SPI_ENABLE;
	MASTER_SELECT;
	SCK_FREQ_64;
}
void SPIWriteByte(unsigned char byte)
{
	SPDR=byte;//load byte in data register
	while (!(SPI_INTERRUPT_FLAG==1));//wait for transmission complete
}
// void SPIReadByte(char addr)
// {
// 	SPDR=addr; //load byte to data register
// 	while (!(SPI_INTERRUPT_FLAG==1));//wait for transmission complete
// 	addr=SPDR;
// 	return addr;
// }


