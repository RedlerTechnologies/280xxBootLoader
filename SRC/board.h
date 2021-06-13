;//###########################################################################
;// FILE:  board.h
;//
;// TITLE: Board definitions
;//
;// Shlomi Dar
;//###########################################################################

#include "DSP28x_Project.h"

#ifndef _BOARD_H
#define _BOARD_H


#define BOARD_HP

#define QUAL_SYSCLK_1   0 // Sync to SYSCLK, Qualification using 1 sample.
#define QUAL_SYSCLK_3   1// Sync to SYSCLK, Qualification using 3 sample.
#define QUAL_SYSCLK_6   2// Sync to SYSCLK, Qualification using 6 sample.
#define NO_QUAL_ASYNC   3// Not Sync, no Qualification.

#define DRV_LED_TOGGLE    (GpioDataRegs.GPBTOGGLE.bit.GPIO39=1)

void gpioInit(void);

#endif
