//###########################################################################
//
// FILE:   Boot.h
//
// TITLE:  Boot ROM Definitions.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef TMS320X2802X_BOOT_H
#define TMS320X2802X_BOOT_H

#ifdef F2803x_PRE_DEF
#include "DSP2803x_Device.h"
#include "DSP2803x_Examples.h"
#include "Flash2803x_API_Library.h"
#endif

#ifdef F2806x_PRE_DEF
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "Flash2806x_API_Library.h"
#endif

#ifdef SCI_PINS_28_29
#define UART_REG SciaRegs
#endif

#ifdef SCI_PINS_7_12
#define UART_REG SciaRegs
#endif

#ifdef SCI_PINS_40_41
#define UART_REG ScibRegs
#endif


#ifndef UART_REG
#error SCI_PINS_XX_XX not defined in progect properties - > predefines
#endif

//Length of the programming buffer
#define PROG_BUFFER_LENGTH 0x400

//---------------------------------------------------------------------------
// Boot Modes
//
//           GPIO37    GPIO34   TRSTn
//            TDO      CMP2OUT
// Mode EMU    x         x        1      Emulator connected
// Mode 0      0         0        0      Parallel I/O
// Mode 1      0         1        0      SCI
// Mode 2      1         0        0      wait
// Mode 3      1         1        0      "Get Mode"

#define OTP_KEY             0x3D7BFE
#define OTP_BMODE           0x3D7BFF
#define KEY_VAL             0x55AA

#define PARALLEL_BOOT       0x0000
#define SCI_BOOT            0x0001
#define WAIT_BOOT           0x0002
#define GET_BOOT            0x0003

#define SPI_BOOT            0x0004
#define I2C_BOOT            0x0005
#define OTP_BOOT            0x0006
#define RAM_BOOT            0x000A
#define FLASH_BOOT          0x000B

//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define FLASH_ENTRY_POINT 0x3F7FF6
#define OTP_ENTRY_POINT   0x3D7800
#define RAM_ENTRY_POINT   0x000000

#define DIVSEL_BY_4             0
#define DIVSEL_BY_2             2
#define DIVSEL_BY_1             3

#define ERROR                   1
#define NO_ERROR                0
#define EIGHT_BIT               8
#define SIXTEEN_BIT            16
#define EIGHT_BIT_HEADER   0x08AA
#define SIXTEEN_BIT_HEADER 0x10AA


typedef struct sCircBuf
{
    Uint16 *mem;      /**< Circular buffer memory block  */
    Uint16 *memEnd;   /**< End of circular buffer memory block  */
    Uint16 *head;     /**< Circular buffer head pointer  */
    Uint16 *tail;     /**< Circular buffer tail pointer  */
    unsigned long size;    /**< Circular buffer size  */
    unsigned long count;   /**< Circular buffer contents count  */
    unsigned long bufFullErr;
} CIRCBUF;
extern int circBufInit(Uint16 *mem, unsigned long size);
//---------------------------------------------------------------------------
//
typedef Uint16 (* uint16fptr)();
extern  uint16fptr GetWordData;
extern  uint16fptr GetOnlyWordData;
extern uint16fptr SendCheckSum;
extern  void (*Flash_CallbackPtr) (void);
extern  Uint32 Flash_CPUScaleFactor;
extern  Uint16 EmuKey;
extern  Uint16 EmuBMode;
extern  CIRCBUF *BuffPtr;
extern unsigned long RemainingBytes;
extern unsigned long RemainingBytes1;

#define Device_cal (void   (*)(void))0x3D7C80
#define Get_mode   (Uint16 (*)(void))0x3D7CC0

//---------------------------------------------------------------------------
// Configured by the boot ROM
//
#define BORTRIM (Uint16 *)0x0986

//---------------------------------------------------------------------------
// Timout Reset
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(timoutReset, "ramfuncs");
#endif
inline void timoutReset()
{
	CpuTimer0.InterruptCount=0;
}

#endif  // end of TMS320x2802x_BOOT_H definition
