#include "msp430f5438a.h"
#include "flash.h"


void FERASE(unsigned int address)//address:Òª²Á³ýµÄµØÖ·
{
  unsigned int *Erase_address;
  Erase_address=(unsigned int *)address;
  FCTL1=FWKEY + ERASE;
  FCTL3=FWKEY;
  *Erase_address=0;
  FCTL1=FWKEY;
  FCTL3=FWKEY + LOCK;
}

void FWRITE(unsigned int address, unsigned char* data,unsigned int length)
{
  unsigned int   i;
  unsigned char* Wr_Addr;
  Wr_Addr =(unsigned char*)address;
  FCTL1 = FWKEY + WRT; // Set WRT bit for write operation
  FCTL3 = FWKEY;
  for(i=0;i<length;i++)
  {
    *Wr_Addr= data[i];
    Wr_Addr++;
  }
  FCTL1 = FWKEY;
  FCTL3 = FWKEY + LOCK;  
}