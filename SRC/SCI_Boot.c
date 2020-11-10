//###########################################################################
//
// FILE:    SCI_Boot.c
//
// TITLE:   SCI Boot mode routines
//
// Functions:
//
//     Uint32 SCI_Boot(void)
//     inline void SCIA_Init(void)
//     inline void SCIA_AutobaudLock(void)
//     Uint32 SCIA_GetWordData(void)
//
// Notes:
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "Boot.h"
#include "stdint.h"



// Private functions
#ifdef BAUD_SET
inline SCI_Init(volatile struct SCI_REGS *regs,uint32_t baudRate);
#else
inline void SCI_Init(void);
#endif
inline void SCIA_AutobaudLock(void);
Uint16 SCIA_GetWordData(void);
Uint16 SCIA_GetOnlyWordData(void);

// External functions
extern void CopyData(void);
Uint32 GetLongData(void);
extern void ReadReservedFn(void);

extern unsigned int checksum;

//#################################################
// Uint32 SCI_Boot(void)
//--------------------------------------------
// This module is the main SCI boot routine.
// It will load code via the SCI-A port.
//
// It will return a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine.
//--------------------------------------------
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCI_Boot, "ramfuncs");
#endif
Uint32 SCI_Boot()
{
   Uint32 EntryAddr;

   // Assign GetWordData to the SCI-A version of the
   // function.  GetOnlyWordData is a pointer to a function.
   // This version doesn't send echo back each character.
  // GetOnlyWordData = SCIA_GetWordData;
   GetOnlyWordData = SCIA_GetOnlyWordData;

#ifdef BAUD_SET
   SCI_Init(&UART_REG, 230400);
   for(;;)
   {
       if (UART_REG.SCICTL2.bit.TXRDY)
           UART_REG.SCITXBUF=0x41;
       timoutReset();
   }
#else
   SCI_Init();
#endif
   SCIA_AutobaudLock();
   checksum = 0;
   timoutReset();
   // If the KeyValue was invalid, abort the load
   // and return the flash entry point.
   if (GetOnlyWordData() != 0x08AA) return FLASH_ENTRY_POINT;

   ReadReservedFn();

   EntryAddr = GetLongData();

   CopyData();

   return EntryAddr;
}


//#################################################
// void SCIA_Init(void)
//----------------------------------------------
// Initialize the SCI-A port for communications
// with the host.
//----------------------------------------------
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCI_Boot, "ramfuncs");
#endif


inline void SCI_Init()
{

    // Enable the SCI-A clocks
        EALLOW;
        SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
        #ifdef F2806x_PRE_DEF
        SysCtrlRegs.PCLKCR0.bit.SCIBENCLK=1;
        #endif
        SysCtrlRegs.LOSPCP.all = 0x0002;
        UART_REG.SCIFFTX.all=0x8000;
        // 1 stop bit, No parity, 8-bit character
        // No loopback
        UART_REG.SCICCR.all = 0x0007;
        // Enable TX, RX, Use internal SCICLK
        UART_REG.SCICTL1.all = 0x0003;
        // Disable RxErr, Sleep, TX Wake,
        // Diable Rx Interrupt, Tx Interrupt
        UART_REG.SCICTL2.all = 0x0000;
        // Relinquish SCI-A from reset
        UART_REG.SCICTL1.all = 0x0023;

        EDIS;
}

//#################################################
// void SCIA_AutobaudLock(void)
//------------------------------------------------
// Perform autobaud lock with the host.
// Note that if autobaud never occurs
// the program will hang in this routine as there
// is no timeout mechanism included.
//------------------------------------------------
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCIA_AutobaudLock, "ramfuncs");
#endif

inline void SCIA_AutobaudLock()
{

    Uint16 byteData;

    // Must prime baud register with >= 1
    UART_REG.SCIHBAUD = 0;
    UART_REG.SCILBAUD = 1;
    // Prepare for autobaud detection
    // Set the CDC bit to enable autobaud detection
    // and clear the ABD bit
    UART_REG.SCIFFCT.bit.CDC = 1;
    UART_REG.SCIFFCT.bit.ABDCLR = 1;
    // Wait until we correctly read an
    // 'A' or 'a' and lock
    while(UART_REG.SCIFFCT.bit.ABD != 1) {}
    timoutReset();

    // After autobaud lock, clear the ABD and CDC bits
    UART_REG.SCIFFCT.bit.ABDCLR = 1;
    UART_REG.SCIFFCT.bit.CDC = 0;
    while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
    byteData = UART_REG.SCIRXBUF.bit.RXDT;
    UART_REG.SCITXBUF = byteData;

    return;
}

//#################################################
// Uint16 SCIA_GetWordData(void)
//-----------------------------------------------
// This routine fetches two bytes from the SCI-A
// port and puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the order LSB followed by MSB.
//-----------------------------------------------
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCIA_GetWordData, "ramfuncs");
#endif
Uint16 SCIA_GetWordData()
{
	Uint16 wordData;
	Uint16 byteData;

	wordData = 0x0000;
	byteData = 0x0000;

	// Fetch the LSB and verify back to the host
	while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
	wordData =  (Uint16)UART_REG.SCIRXBUF.bit.RXDT;
	UART_REG.SCITXBUF = wordData;

	// Fetch the MSB and verify back to the host
	while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
	byteData =  (Uint16)UART_REG.SCIRXBUF.bit.RXDT;
	UART_REG.SCITXBUF = byteData;

	checksum += wordData + byteData;

	// form the wordData from the MSB:LSB
	wordData |= (byteData << 8);

	return wordData;
}


#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCIA_GetOnlyWordData,"ramfuncs");
#endif
Uint16 SCIA_GetOnlyWordData()
{
	Uint16 wordData;
	Uint16 byteData;


	wordData = 0x0000;
	byteData = 0x0000;

	// Fetch the LSB and verify back to the host
	while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
	wordData =  (Uint16)UART_REG.SCIRXBUF.bit.RXDT;
	//UART_REG.SCITXBUF = wordData;

	// Fetch the MSB and verify back to the host
	while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
	byteData =  (Uint16)UART_REG.SCIRXBUF.bit.RXDT;
	//UART_REG.SCITXBUF = byteData;

	checksum += wordData + byteData;
	// form the wordData from the MSB:LSB
	wordData |= (byteData << 8);

	return wordData;
}



//#define BAUD_SET
#ifdef BAUD_SET

#define SCI_OPMODE_POLLING      0   /**< SCI polling mode operation */
#define SCI_OPMODE_INTERRUPT    1   /**< SCI interrupt mode operation */

#define SCI_STOP_1              0   /**< 1 stop bit */
#define SCI_STOP_2              1   /**< 2 stop bits */

#define SCI_CHARLEN_1           1   /**< 1 data bits */
#define SCI_CHARLEN_2           2   /**< 2 data bits */
#define SCI_CHARLEN_3           3   /**< 3 data bits */
#define SCI_CHARLEN_4           4   /**< 4 data bits */
#define SCI_CHARLEN_5           5   /**< 5 data bits */
#define SCI_CHARLEN_6           6   /**< 6 data bits */
#define SCI_CHARLEN_7           7   /**< 7 data bits */
#define SCI_CHARLEN_8           8   /**< 8 data bits */

#define SCI_CHARLEN(n)          (((n)-1)&0x7)   /**< create data bits config */
#define SCI_GETCHARLEN(x)       (((x)&0x07)+1)  /**< read data bits config */

#define SCI_PARITY_NONE         0x0 /**< no parity */
#define SCI_PARITY_ODD          0x2 /**< odd parity */
#define SCI_PARITY_EVEN         0x3 /**< even parity */

#define DSP_CLOCK 90e6

unsigned long lspClkRate(void)
{
    const unsigned int lspDivTable[8]= {1, 2, 4, 6, 8, 10, 12, 14};
    volatile uint32_t chSC,chSc1,chSc2;

    chSC=DSP_CLOCK;
    chSc1=lspDivTable[SysCtrlRegs.LOSPCP.all];
    chSc2=chSC/chSc1;
    return ((unsigned long)DSP_CLOCK)/lspDivTable[SysCtrlRegs.LOSPCP.all];

}

void sciSetBaud(volatile struct SCI_REGS *regs, uint32_t baud)
{
    uint16_t brr;

    brr=(uint16_t)((lspClkRate()/(baud*8UL))-1UL);
    regs->SCIHBAUD    = (brr>>8)&0xff;
    regs->SCILBAUD    = (brr)&0xff;
}

inline SCI_Init(volatile struct SCI_REGS *regs, uint32_t baudRate)
{
    // Enable the SCI-A clocks
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
    #ifdef F2806x_PRE_DEF
    SysCtrlRegs.PCLKCR0.bit.SCIBENCLK=1;
    #endif

    regs->SCICTL1.all =0x0000;  // SCI SW reset
    //regs->SCIPRI.bit.FREE=1;    // free run

    regs->SCICCR.all=0;
    regs->SCICCR.bit.SCICHAR=SCI_CHARLEN(SCI_CHARLEN_8); //8bits
    regs->SCICCR.bit.PARITYENA=0;
    regs->SCICCR.bit.PARITY=SCI_PARITY_NONE;
    regs->SCICCR.bit.STOPBITS=SCI_STOP_1;

    // Disable Rx Interrupt, Tx Interrupt
    regs->SCICTL2.all =0;

    //Set baudrate
    sciSetBaud(regs, baudRate);

    /*Fifo*/
    regs->SCIFFTX.all=0x0000;   // disable tx fifo
    regs->SCIFFRX.all=0x0000;   // disable rx fifo
    regs->SCIFFCT.all=0x0000;

    // Relinquish SCI from Reset
    regs->SCICTL1.all=0;
    regs->SCICTL1.bit.RXENA=1; //Enable RX
    regs->SCICTL1.bit.TXENA=1; //Enable TX
    regs->SCICTL1.bit.SWRESET=1;

    EDIS;
}
#endif

// EOF-------

