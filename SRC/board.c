
;//###########################################################################
;// FILE:  board.c
;//
;// TITLE: Board specific functions:
;//
;// Shlomi Dar
;//###########################################################################

#include "board.h"


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
#define BOARD RAYON70
#endif


#if (BOARD == SINGLE_BOARD)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//  2) If IN, can leave next to lines commented
//  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//             uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

    /*********Qualification Sampling Frequency for GPIO inputs***************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = Hall_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
      GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = Hall_3
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO3=1;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = Hall_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO5=1;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = CPU_IN4
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
      GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO6 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = CPU_UART1_RX
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
//        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-08 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=LINRX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = CPU_UART1_TX
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
//        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
        GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPICLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = SPI_SSn
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
//        GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
//        GpioCtrlRegs.GPAQSEL2.bit.GPIO19=0x01;  // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = EQEPA
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = EQEPB
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - In_Intn, IO input interrupt
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=Resv,  3=LINTX-A
//        GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = EQEPI
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=Resv,  3=LINRX-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=Resv,  3=SPISIMO-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = NA
    //    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPICLK-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISTE-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = I2CSDA
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = I2CSCL
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CANRX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CANTX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = Hall_2
//        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
//      GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;     // 1=OUTput,  0=INput
//    //  GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
//    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially
//        GpioCtrlRegs.GPBQSEL1.bit.GPIO34=1;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;    // 0=GPIO,  1=EPWM7A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;    // 0=GPIO,  1=EPWM7B,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-43 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------

    /*DRV Enable Gate*/
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO10 = 1;
    GpioDataRegs.AIOSET.bit.AIO10 = 1;

    /*Driver Fault*/
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO4 = 0;

    /*O_Current_O_Temp */
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO6 = 0;

    /*DRV Enable Gate*/
    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO2 = 1;
    GpioDataRegs.AIOSET.bit.AIO2 = 1;


    EDIS;   // Disable register access
}


void peripherals_clk(void)
{
    EALLOW;
    // PERIPHERAL CLOCK ENABLES
    //---------------------------------------------------
    // If you are not using a peripheral you may want to switch
    // the clock off to save power, i.e. set to =0
    //
    // Note: not all peripherals are available on all 280x derivates.
    // Refer to the datasheet for your particular device.

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;  // COMP1
   SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;  // COMP2
   SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = 0;  // COMP3
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  //eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=0;   // eCAN-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;  // ePWM5
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;  // ePWM6
   SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 0;  // ePWM7
   SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 0;    // HRPWM
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.LINAENCLK = 0;   // LIN-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;   // CLA1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
   SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 0;     // SPI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
   //------------------------------------------------
   EDIS;
 }

#elif (BOARD == SINGLE_M)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//  2) If IN, can leave next to lines commented
//  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//             uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------


void gpioInit(void)
{
    EALLOW;
    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Disable Pullup

    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = HALL_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //Disable Pullup
        GpioCtrlRegs.GPAQSEL1.bit.GPIO1= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = HALL_3
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;      //Disable Pullup
        GpioCtrlRegs.GPAQSEL1.bit.GPIO3= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = HALL_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO5= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = Extrn_SPI (not in used)
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
        GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;    // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //    GpioDataRegs.GPASET.bit.GPIO6 = 0;    // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = BiSS_CLK_Enable
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //    GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAQSEL1.bit.GPIO7= 1; // input pull up
    //--------------------------------------------------------------------------------------

    //  GPIO-08 - PIN FUNCTION = BiSS_RX_Data_Disable
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
        GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 0;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = BiSS_TX_Data_Enable
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=SCITXDB,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = CPU_OC1
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
        GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 0;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = CPU_OC2
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=SCIRXD-B,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = CPU_IN1
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO12= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = CPU_IN2
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO13= QUAL_SYSCLK_3; // 5.67*3 = 17uSec


    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = CPU_IN3
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO,  1=TZ3,  2=SCITXDB,  3=SPICLKB
        GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO14=1;
        GpioCtrlRegs.GPAQSEL1.bit.GPIO14= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = CPU_IN4        (One-Shot Gate Disable)
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO,  1=ECAP2,  2=SCIRXDB,  3=SPISTEB
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO15= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPI_CLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LSCITXDB,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = SPI_STE
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1= SPI_STE-A,  2=SCIRXDB,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = Encoder_A
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=MDXA,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = NO_QUAL_ASYNC;
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = Encoder_B
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=MDRA,  3=COMP2OUT
    //    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = NO_QUAL_ASYNC;
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - CPU_IN4 / One-Shot Gate Disable
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=MCLKXA,  3=SCITX-B
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;   // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO22= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = Encoder_INX
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=MFSXA,  3=SCIRXDB
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = NO_QUAL_ASYNC;
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = Trig_B (One-Shot)
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;    // 0=GPIO,  1=ECAP1,  2=EQEP2A,  3=SPISIMOB
        GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = RS422_TX_En
        GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;    // 0=GPIO,  1=ECAP2,  2=EQEP2B,  3=SPISOMIB
        GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = TP23
        GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    // 0=GPIO,  1=ECAP3,  2=EQEP2,  3=USB0DP/SPICLKB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAQSEL2.bit.GPIO26= 1;

    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = TP24
        GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    // 0=GPIO,  1=HRCAP2,  2=EQEP2S,  3=USB0DM/SPISTEB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = RS422/RS232_UART1_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = RS422/RS232_UART1_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CAN_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=EQEP2I,  3=EPWM7A
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CAN_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=EQEP2S,  3=EPWM8A
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = I2C_SDA
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = I2C_SCL
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = BOOT
        //do not use
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = LED1
        GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;     // 1=OUTput,  0=INput
    //    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------




        /*Fault */
        GpioCtrlRegs.AIOMUX1.bit.AIO4 = 1;
        GpioCtrlRegs.AIODIR.bit.AIO4 = 0;

        /*O_Current_O_Temp */
        GpioCtrlRegs.AIOMUX1.bit.AIO6 = 1;
        GpioCtrlRegs.AIODIR.bit.AIO6 = 0;

    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    EDIS;   // Disable register access
}


void peripherals_clk(void)
{
    EALLOW;
    // PERIPHERAL CLOCK ENABLES
    //---------------------------------------------------
    // If you are not using a peripheral you may want to switch
    // the clock off to save power, i.e. set to =0
    //
    // Note: not all peripherals are available on all 280x derivates.
    // Refer to the datasheet for your particular device.

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;  // COMP1
   SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;  // COMP2
   SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = 0;  // COMP3
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  //eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=1;   // eCAN-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;  // ePWM5
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;  // ePWM6
   SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 0;  // ePWM7
   SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 0;  // HRPWM
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;   // CLA1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
   SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
   SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 1;   // SPI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
   //------------------------------------------------
   EDIS;
 }

#elif (BOARD == STXI_M1)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//  2) If IN, can leave next to lines commented
//  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//             uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------


void gpioInit(void)
{
    EALLOW;
    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Disable Pullup

    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = HALL_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //Disable Pullup
        GpioCtrlRegs.GPAQSEL1.bit.GPIO1= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = HALL_3
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;      //Disable Pullup
        GpioCtrlRegs.GPAQSEL1.bit.GPIO3= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = HALL_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO5= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = STO-Int
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
        GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;    // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //    GpioDataRegs.GPASET.bit.GPIO6 = 0;    // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = BiSS_CLK_Enable
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //    GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAQSEL1.bit.GPIO7= 1; // input pull up
    //--------------------------------------------------------------------------------------

    //  GPIO-08 - PIN FUNCTION = BiSS_RX_Data_Disable
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
        GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 0;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = BiSS_TX_Data_Enable
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=SCITXDB,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = Enable Gates
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
        GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = TP5
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=SCIRXD-B,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = TP12
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO12= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = 5V_OUT_En
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAQSEL1.bit.GPIO13= QUAL_SYSCLK_3; // 5.67*3 = 17uSec


    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = not in use (TBD MASTER-SLAVE)
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO,  1=TZ3,  2=SCITXDB,  3=SPICLKB
        GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO14=1;
        GpioCtrlRegs.GPAQSEL1.bit.GPIO14= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = Pull up for MISO (bug) (TBD MASTER-SLAVE)
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO,  1=ECAP2,  2=SCIRXDB,  3=SPISTEB
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
        //GpioCtrlRegs.GPAQSEL1.bit.GPIO15= NO_QUAL_ASYNC; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPI_CLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LSCITXDB,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = SPI_STE
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1= SPI_STE-A,  2=SCIRXDB,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = NO_QUAL_ASYNC; //SPI signals needs to use ASYNC option
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = Encoder_A
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=MDXA,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = QUAL_SYSCLK_1;
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = Encoder_B
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=MDRA,  3=COMP2OUT
    //    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = QUAL_SYSCLK_1; //
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = not connected
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;    // 0=GPIO,  1=EQEPS-1,  2=MCLKXA,  3=SCITX-B
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;   // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO22= QUAL_SYSCLK_3; // 5.67*3 = 17uSec
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = Encoder_INX
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=MFSXA,  3=SCIRXDB
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = QUAL_SYSCLK_1;
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = SPI_SIMOB
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=EQEP2A,  3=SPISIMOB
    //    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = SPI_SOMIB
        GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;    // 0=GPIO,  1=ECAP2,  2=EQEP2B,  3=SPISOMIB
    //    GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //    GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = SPI_CLKB
        GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;    // 0=GPIO,  1=ECAP3,  2=EQEP2,  3=USB0DP/SPICLKB (USBIOEN)
    //    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAQSEL2.bit.GPIO26= 1;

    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = SPI_STEBn
        GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;    // 0=GPIO,  1=HRCAP2,  2=EQEP2S,  3=USB0DM/SPISTEB (USBIOEN)
    //    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = RS422/RS232_UART1_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = RS422/RS232_UART1_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CAN_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=EQEP2I,  3=EPWM7A
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CAN_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=EQEP2S,  3=EPWM8A
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = I2C_SDA
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = I2C_SCL
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = BOOT to uart
        //do not use
        //Static_RAM_CEn
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = LED1
        GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;     // 1=OUTput,  0=INput
    //    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------




        /*Fault */
        GpioCtrlRegs.AIOMUX1.bit.AIO4 = 1;
        GpioCtrlRegs.AIODIR.bit.AIO4 = 0;


    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    EDIS;   // Disable register access
}

void peripherals_clk(void)
{
    EALLOW;
    // PERIPHERAL CLOCK ENABLES
    //---------------------------------------------------
    // If you are not using a peripheral you may want to switch
    // the clock off to save power, i.e. set to =0
    //
    // Note: not all peripherals are available on all 280x derivates.
    // Refer to the datasheet for your particular device.

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;  // COMP1
   SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;  // COMP2
   SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = 0;  // COMP3
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  //eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=1;   // eCAN-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;  // ePWM5
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;  // ePWM6
   SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 0;  // ePWM7
   SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 0;  // HRPWM
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;   // CLA1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
   SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
   SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 1;   // SPI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
   //------------------------------------------------
   EDIS;
 }

#elif (BOARD == URAYON)

#define HW_REV 3
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//  2) If IN, can leave next to lines commented
//  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//             uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

    /*********Qualification Sampling Frequency for GPIO inputs***************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = Hall_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO1=0x01;  // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = Hall_3
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO3=0x01;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = Hall_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO5=0x01;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = PWM4A
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
    //  GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO6 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = SCIRX
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-08 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=LINRX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = CPU_UART1_TX
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
        GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPICLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    #if(HW_REV == HW_REV_2)// GPIO-19 - PIN FUNCTION = Hall_2
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO19=0x01;  // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.
    #else
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
    //   GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
    #endif


    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = EQEPA
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = EQEPB
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - In_Intn, IO input interrupt
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=Resv,  3=LINTX-A
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = EQEPI
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=Resv,  3=LINRX-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=Resv,  3=SPISIMO-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = NA
    //    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPICLK-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISTE-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = I2CSDA
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = I2CSCL
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CANRX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CANTX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------

    //  GPIO-34 - PIN FUNCTION =  Boot Mode wait  do not use this port as input.

    //    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;    // 0=GPIO,  1=EPWM7A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;    // 0=GPIO,  1=EPWM7B,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-43 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------

    #if(HW_REV == HW_REV_2)
    /*DRV Enable Gate*/
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO6 = 1;
    GpioDataRegs.AIOSET.bit.AIO6 = 0;

    /*SPI Chip Select*/
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO10 = 1;
    GpioDataRegs.AIOSET.bit.AIO10 = 1;
#else

    /*422 TX Enable*/
    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO2 = 1;
    GpioDataRegs.AIOSET.bit.AIO2 = 1;

    /*O_Current_O_Temp */
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO4 = 0;

    /*O_Current_O_Temp */
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO6 = 0;

    /*DRV Enable Gate*/
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO10 = 1;
    GpioDataRegs.AIOSET.bit.AIO10 = 0;

#endif

    EDIS;   // Disable register access
}




#elif (BOARD == RAYON_HP_V1)//Rayon 250
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
// FOR TMS320F28069 PZP/PZ 100-Pin Package
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

#ifdef QUAL
    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
#endif



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Disable Pullup

    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = EPWM1B
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = EPWM2B
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = EPWM3B
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = PWM_Current_Limit - as out => no limit
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
        GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO6 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = HALL_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
#ifdef KUKU
    //  GPIO-08 - PIN FUNCTION = WD_Trig
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
        GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
#endif
    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = Analog_Select for ADC input B7, CHK_12V/CHK_5V
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=SCITXDB,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = TP19/USB_SUSPEND
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
        GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO10 = 0;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = HALL_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=SCIRXD-B,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = TP25
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = Eth_SPI_MISO
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = Eth_SPI_SCK
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // 0=GPIO,  1=TZ3,  2=SCITXDB,  3=SPICLKB
    //  GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAPUD.bit.GPIO14=1;
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = Eth_SPI_NSS
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;    // 0=GPIO,  1=ECAP2,  2=SCIRXDB,  3=SPISTEB
    //  GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI2_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI2_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPI2_CLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LSCITXDB,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = SPI_STE
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1=SPISTE-A,  2=SCIRXDB,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = Encoder_A
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=MDXA,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = Encoder_B
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=MDRA,  3=COMP2OUT
    //    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - MCU_Ex_Brake -  En VCC motor FET output
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=MCLKXA,  3=SCITX-B
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = Encoder_INX
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=MFSXA,  3=SCIRXDB
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = Eth_SPI_MOSI
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=EQEP2A,  3=SPISIMOB
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = PWM_IO (TP24) ECAP2 PWM input
        GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;    // 0=GPIO,  1=ECAP2,  2=EQEP2B,  3=SPISOMIB
//      GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = HALL_3
        GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    // 0=GPIO,  1=ECAP3,  2=EQEP2,  3=USB0DP/SPICLKB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = TP18
        GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    // 0=GPIO,  1=HRCAP2,  2=EQEP2S,  3=USB0DM/SPISTEB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = RS232_UART1_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = RS232_UART1_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CAN_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=EQEP2I,  3=EPWM7A
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CAN_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=EQEP2S,  3=EPWM8A
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = I2C_SDA
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = I2C_SCL
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = BOOT
        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=COMP2OUT,  2=Resv,  3=COMP3OUT
//      GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput,  0=INput
//      GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = LED1
        GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = UART2_TX
        GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 2;    // 0=GPIO,  1=EPWM7A,  2=SCITXDB,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = UART2_RX
       GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 2;    // 0=GPIO,  1=EPWM7B,  2=SCIRXDB,  3=Resv
    // GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = One_Shot_Trign
       GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;    // 0=GPIO,  1=EPWM8A,  2=TZ1,  3=COMP1OUT
       GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-43 - PIN FUNCTION = Eth_Semaphor_B
        GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=EPWM8B,  2=TZ2,  3=COMP2OUT
        GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = Eth_Semaphor_A
        GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=MFSRA,  2=SCIRXDB,  3=EPWM7B
        GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-50 - PIN FUNCTION = TP15
       GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;    // 0=GPIO,  1=EQEP1A,  2=MDXA,  3=TZ1
       GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO50 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-51 - PIN FUNCTION = TP17
       GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;    // 0=GPIO,  1=EQEP1B,  2=MDRA,  3=TZ2
       GpioCtrlRegs.GPBDIR.bit.GPIO51 = 0;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO51 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
        //GPIO-52 - PIN FUNCTION = TP14
        GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // 0=GPIO,  1=EQEP1S,  2=MCLKXA,  3=TZ3
        GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO52 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-53 - PIN FUNCTION = In_Intn
        GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // 0=GPIO,  1=EQEP1I,  2=MFSXA,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO53 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-54 - PIN FUNCTION = CLKA
        GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 2;    // 0=GPIO,  1=SPISIMOA,  2=EQEP2A,  3=HRCAP1
    //  GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO54 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-55 - PIN FUNCTION = CLKB
        GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 2;    // 0=GPIO,  1=SPISOMIA,  2=EQEP2B,  3=HRCAP2
    //  GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO55 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-56 - PIN FUNCTION = IDX2
        GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 2;    // 0=GPIO,  1=SPICLKA,  2=EQEP2I,  3=HRCAP3
    //  GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO56 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //GPIO-57 - PIN FUNCTION = F_Master_Slaven, master/slave input select
        GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;    // 0=GPIO,  1=SPISTEA,  2=EQEP2S,  3=HRCAP4
        GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO57 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-58 - PIN FUNCTION = PWM_DIR_IO, PWM direction input command
        GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;    // 0=GPIO,  1=MCLKRA,  2=SCITXDB,  3=EPWM7A
        GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO58 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    EDIS;   // Disable register access
}


#elif (BOARD == RAYON70)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
// FOR TMS320F28069 PZP/PZ 100-Pin Package
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

#ifdef QUAL
    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
#endif



    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Disable Pullup

    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = EPWM1B
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = EPWM2B
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = EPWM3B
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = PWM_Current_Limit - as out => no limit
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
        GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO6 = 0;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = HALL_2
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO7= 1;
    //--------------------------------------------------------------------------------------
#ifdef KUKU
    //  GPIO-08 - PIN FUNCTION = WD_Trig
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
        GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = Analog_Select for ADC input B7, CHK_12V/CHK_5V
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=SCITXDB,  3=ECAP3
        GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
#endif
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = TP19/USB_SUSPEND
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
        GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO10 = 0;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = HALL_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=SCIRXD-B,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL1.bit.GPIO11= 1;

    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = TP2
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = Eth_SPI_MISO
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = Eth_SPI_SCK
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // 0=GPIO,  1=TZ3,  2=SCITXDB,  3=SPICLKB
    //  GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAPUD.bit.GPIO14=1;
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = Eth_SPI_NSS
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;    // 0=GPIO,  1=ECAP2,  2=SCIRXDB,  3=SPISTEB
    //  GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI2_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI2_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPI2_CLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LSCITXDB,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = SPI_STE
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;    // 0=GPIO,  1=SPISTE-A,  2=SCIRXDB,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = Encoder_A
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=MDXA,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = Encoder_B
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=MDRA,  3=COMP2OUT
    //    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - MCU_Ex_Brake -  En VCC motor FET output
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=MCLKXA,  3=SCITX-B
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = Encoder_INX
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=MFSXA,  3=SCIRXDB
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = Eth_SPI_MOSI
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=EQEP2A,  3=SPISIMOB
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = PWM_IO (TP24) ECAP2 PWM input
        GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;    // 0=GPIO,  1=ECAP2,  2=EQEP2B,  3=SPISOMIB
//      GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = HALL_3
        GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    // 0=GPIO,  1=ECAP3,  2=EQEP2,  3=USB0DP/SPICLKB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO26= 1;

    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = TP18
        GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    // 0=GPIO,  1=HRCAP2,  2=EQEP2S,  3=USB0DM/SPISTEB (USBIOEN)
        GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = RS232_UART1_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = RS232_UART1_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CAN_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=EQEP2I,  3=EPWM7A
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CAN_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=EQEP2S,  3=EPWM8A
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
        // Opto_Iso_2_In
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
        GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
        // Opto_Iso_3_In
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = BOOT
        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=COMP2OUT,  2=Resv,  3=COMP3OUT
//      GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput,  0=INput
//      GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = LED1
        GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = UART2_TX
        GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 2;    // 0=GPIO,  1=EPWM7A,  2=SCITXDB,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = UART2_RX
       GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 2;    // 0=GPIO,  1=EPWM7B,  2=SCIRXDB,  3=Resv
    // GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = One_Shot_Trign
       GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;    // 0=GPIO,  1=EPWM8A,  2=TZ1,  3=COMP1OUT
       GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
       //GPIO-43 Opto_Iso_4_Inn
        GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=EPWM8B,  2=TZ2,  3=COMP2OUT
        GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = TP8
        GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=MFSRA,  2=SCIRXDB,  3=EPWM7B
        GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-50 - PIN FUNCTION = Current_Tripn
       GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;    // 0=GPIO,  1=EQEP1A,  2=MDXA,  3=TZ1
       GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO50 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-51 - PIN FUNCTION = TP17
       GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;    // 0=GPIO,  1=EQEP1B,  2=MDRA,  3=TZ2
       GpioCtrlRegs.GPBDIR.bit.GPIO51 = 0;     // 1=OUTput,  0=INput
    // GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1;   // uncomment if --> Set Low initially
    // GpioDataRegs.GPBSET.bit.GPIO51 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
        //GPIO-52 - PIN FUNCTION = TP14
        GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // 0=GPIO,  1=EQEP1S,  2=MCLKXA,  3=TZ3

        GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO52 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-53 - PIN FUNCTION = Opto_Iso_2_IN/OUT == IN
        GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // 0=GPIO,  1=EQEP1I,  2=MFSXA,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO53 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-54 - PIN FUNCTION = CLKA
        GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 2;    // 0=GPIO,  1=SPISIMOA,  2=EQEP2A,  3=HRCAP1
    //  GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO54 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-55 - PIN FUNCTION = CLKB
        GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 2;    // 0=GPIO,  1=SPISOMIA,  2=EQEP2B,  3=HRCAP2
    //  GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO55 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-56 - PIN FUNCTION = IDX2
        GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 2;    // 0=GPIO,  1=SPICLKA,  2=EQEP2I,  3=HRCAP3
    //  GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO56 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //GPIO-57 - PIN FUNCTION = F_Master_Slaven, master/slave input select
        GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;    // 0=GPIO,  1=SPISTEA,  2=EQEP2S,  3=HRCAP4
        GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO57 = 1;     // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //GPIO-58 - PIN FUNCTION = PWM_DIR_IO, PWM direction input command
        GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;    // 0=GPIO,  1=MCLKRA,  2=SCITXDB,  3=EPWM7A
        GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO58 = 1;     // uncomment if --> Set High initially


    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    EDIS;   // Disable register access
}



#elif (BOARD == TMDM_MK6_V2)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
// FOR TMS320F28069MPFPQ HTQFP80
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

#ifdef QUAL
    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5uS@60Mhz, 5.67uS@90Mhz
#endif


    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Disable Pullup

    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = EPWM1B
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = EPWM2B
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //  GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //Disable Pullup
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = EPWM3B
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially

    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = M1_M2_SYNC
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
        GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO6 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = DRV_nFAULT
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-08 - PIN FUNCTION = SPIA_nSS
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
        GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = LED3
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;     // 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=Resv
        GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = M1_SPIB_CHL DRV_CS_DEMUX
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
        GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 0;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = DBG_UART_B_RX
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;    // 0=GPIO,  1=EPWM6B,  2=SCIRXD-B,  3=ECAP1
    //  GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = D1_EN_Gate
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = SPISOMI-B
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = SPICLK-B
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //    GpioCtrlRegs.GPAPUD.bit.GPIO14=1;
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = SPISTE
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;    // 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = DRV_nOCTW
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
        GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPICLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = CLK_10MHz
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = TP302
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;    // 0=GPIO,  1=EQEPA-1,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = TP303
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;    // 0=GPIO,  1=EQEPB-1,  2=Resv,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - DBG_UART_B_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;    // 0=GPIO,  1=EQEPS-1,  2=MCLKXA,  3=SCITX-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = TP301
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;    // 0=GPIO,  1=EQEPI-1,  2=Resv,  3=LINRX-A
        GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = SPISIMO-B
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=Resv,  3=SPISIMO-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = TP307
        GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = Ecap_HS2
        GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // 0=GPIO,  1=ECAP3,  2=SPICLKB,  3=USB0DP
    //  GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = Ecap_HS1
        GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;    // 0=GPIO,  1=HRCAP2,  2=SPISTEB,  3=USB0DM
    //  GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = ARM_UART2_TX
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = ARM_UART2_RX
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = M1_SYNC
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;    // 0=GPIO,  1=CANRX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = TP308
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;    // 0=GPIO,  1=CANTX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = I2C_SCL
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = I2C_SDA
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = DRV_DC_CAL
        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=COMP2OUT,  2=COMP3OUT,  3=Resv
        GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput,  0=INput
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = SYNC_DIR
        GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;    // 0=GPIO,  1=EPWM7A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;    // 0=GPIO,  1=EPWM7B,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-43 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    EDIS;   // Disable register access
}

#elif (BOARD == RAYON30)
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//  2) If IN, can leave next to lines commented
//  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//             uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void gpioInit(void)
{
    EALLOW;

    /*********Qualification Sampling Frequency for GPIO inputs****************************/
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0=255; //GPIO[0-7] Sampling Frequency  =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0=255; //GPIO[8-15] Sampling Frequency =SYSCLKOUT/510, T=8.5 uSec fo 60Mhz device

    GpioCtrlRegs.GPAQSEL1.bit.GPIO5=0x01;   // 0=SYSCLKOUT,  1=3 QUALPRD samples,  2=6  QUALPRD samples,  3=no synchronization.

    //  GPIO-00 - PIN FUNCTION = PWM1A
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO0 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-01 - PIN FUNCTION = RS422_TX_Err
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
        GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO1 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-02 - PIN FUNCTION = PWM2A
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO2 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-03 - PIN FUNCTION = Hall_3
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO3 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-04 - PIN FUNCTION = PWM3A
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO4 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-05 - PIN FUNCTION = Hall_1
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO5 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-06 - PIN FUNCTION = PWM4A
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;     // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
    //  GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO6 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-07 - PIN FUNCTION = CPU_IN4
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
        GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO7 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-08 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-09 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;      // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;    // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO9 = 1;      // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-10 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO10 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-11 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO,  1=EPWM6B,  2=LINRX-A,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO11 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-12 - PIN FUNCTION = CPU_UART1_TX
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;    // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
        GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // 1=OUTput,  0=INput
    //   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO12 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-13 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;    // 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO13 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-14 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
        GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO14 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-15 - PIN FUNCTION = NA
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
        GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO15 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-16 - PIN FUNCTION = SPI_SIMO
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;    // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
    //    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-17 - PIN FUNCTION = SPI_SOMI
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;    // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-18 - PIN FUNCTION = SPICLK
        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;    // 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-19 - PIN FUNCTION = Hall_2
        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
        GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-20 - PIN FUNCTION = EQEPA
        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;    // 0=GPIO,  1=EQEPA-1,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO20=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-21 - PIN FUNCTION = EQEPB
        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;    // 0=GPIO,  1=EQEPB-1,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO21=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-22 - PIN FUNCTION = - In_Intn, IO input interrupt
        GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO,  1=EQEPS-1,  2=Resv,  3=LINTX-A
        GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-23 - PIN FUNCTION = EQEPI
        GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;    // 0=GPIO,  1=EQEPI-1,  2=Resv,  3=LINRX-A
    //  GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
        GpioCtrlRegs.GPAQSEL2.bit.GPIO23=0; //Synchronize to SYSCLKOUT only.
    //--------------------------------------------------------------------------------------
    //  GPIO-24 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;    // 0=GPIO,  1=ECAP1,  2=Resv,  3=SPISIMO-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO24 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-25 - PIN FUNCTION = NA
    //    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISOMI-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO25 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-26 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPICLK-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO26 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-27 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;    // 0=GPIO,  1=Resv,  2=Resv,  3=SPISTE-B
    //  GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO27 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-28 - PIN FUNCTION = I2CSDA
        GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;    // 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
    //  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-29 - PIN FUNCTION = I2CSCL
        GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;    // 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
    //  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-30 - PIN FUNCTION = CANRX
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO,  1=CANRX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-31 - PIN FUNCTION = CANTX
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO,  1=CANTX-A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
        GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-32 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
    //  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO32 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-33 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
    //  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO33 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-34 - PIN FUNCTION = TP2 (boot Select)
        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
    // usage.
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    //  GPIO-39 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO39 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-40 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;    // 0=GPIO,  1=EPWM7A,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO40 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-41 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;    // 0=GPIO,  1=EPWM7B,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO41 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-42 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP1OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO42 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-43 - PIN FUNCTION = NA
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=COMP2OUT
    //  GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO43 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //  GPIO-44 - PIN FUNCTION = --Spare--
    //  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    //  GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;     // 1=OUTput,  0=INput
    //  GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;   // uncomment if --> Set Low initially
    //  GpioDataRegs.GPBSET.bit.GPIO44 = 1;     // uncomment if --> Set High initially
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------

    /*DRV Enable Gate*/
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO6 = 1;
    GpioDataRegs.AIOSET.bit.AIO6 = 0;

    /*SPI Chip Select*/
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 1;
    GpioCtrlRegs.AIODIR.bit.AIO10 = 1;
    GpioDataRegs.AIOSET.bit.AIO10 = 1;


    EDIS;   // Disable register access
}


#else
#error BOARD not defined in progect properties - > predefines
#endif
