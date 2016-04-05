#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>


/* vim: set sw=8 ts=8 si et: */
#ifndef TOUT_H
#define TOUT_H

void delay_ms(unsigned char ms);
void delay_msD(unsigned char ms);
void wd_init(void);
void wd_kick(void);

#endif /* TOUT_H */
