#include <reg51.h>
#include <intrins.h>
#include "sys.h"
void delayms(int counter)  // /* X1ms */
{
        int i,j;
        for(i=0;i<counter;i++)
                for(j=0;j<1000;j++);
}