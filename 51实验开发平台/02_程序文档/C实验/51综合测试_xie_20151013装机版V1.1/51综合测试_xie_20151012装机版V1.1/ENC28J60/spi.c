#include "uip.h"
#include "spi.h"

void WriteByte(u8_t temp)
{
	idata u8_t i;
	for(i=0;i<8;i++)
	{
		SCKN=0;		//delay_us(2);
		SIN = temp & 0x80;
		SCKN=1;		//delay_us(2);
		temp <<=1;
	}
	SCKN=0;
}

u8_t ReadByte(void)
{
	idata u8_t i,dat1;
	SCKN=0;
	dat1=0;
	for(i=0;i<8;i++)
	{	
		SCKN=1;			//delay_us(2);
		dat1 <<=1;
		dat1 |= SON; 
		SCKN=0;			//delay_us(2);
	}
	return dat1;
}
