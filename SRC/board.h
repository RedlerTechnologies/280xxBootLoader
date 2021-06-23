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

/****Select Board**********/
#define URAYON          1
#define RAYON30         2
#define SINGLE_BOARD    3
#define RAYON_HP_V1     4
#define TMDM_MK6_V2     5
#define RAYON70         6
#define SHRAKRAK        7
#define SINGLE_M        8
#define RAYON70L        9// empty
#define STXI_M1         10

#ifdef BOARD_URAYON
#define BOARD URAYON
#else
#define BOARD STXI_M1
#endif

#define BOARD_HP

#define QUAL_SYSCLK_1   0 // Sync to SYSCLK, Qualification using 1 sample.
#define QUAL_SYSCLK_3   1// Sync to SYSCLK, Qualification using 3 sample.
#define QUAL_SYSCLK_6   2// Sync to SYSCLK, Qualification using 6 sample.
#define NO_QUAL_ASYNC   3// Not Sync, no Qualification.

#if (BOARD == RAYON70)
/* Define LED pin */
#define DRV_LED_TOGGLE    (GpioDataRegs.GPBTOGGLE.bit.GPIO39=1)
#endif

void gpioInit(void);

#endif
