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
#include "ecan.h"
#include "SCI_Boot.h"
#include "descriptor.h"
// Private functions
#ifdef BAUD_SET
inline SCI_Init(volatile struct SCI_REGS *regs,uint32_t baudRate);
#else
inline void SCI_Init(void);
#endif

#ifdef CAN
#else
inline void SCIA_AutobaudLock(void);
#endif


Uint16 SCIA_GetWordData(void);
Uint16 SCIA_GetOnlyWordData(void);
Uint16 SendCheckSumSci(void);
Uint16 SendCheckSumCAN(void);
inline void communicationLock();

// External functions
extern void CopyData(void);
Uint32 GetLongData(void);
extern void ReadReservedFn(void);

extern unsigned int checksum;
extern Uint16 toggleBit;


/*
 * Master CAN  flow chart
 *
 *
 * 1. Send loader command 0x203E[10] = 1 , (wait for echo, retry 3 times, if fail continue anyway)
 * 2. Send CAN-Lock SDO 0x2000, Data 0xAAAA ((wait for echo, retry 3 times, Fail)
 * 3. Send 11 words (22 bytes) from file
 * 4. Unit erase sectors, wait for checksum (10s timeout)
 * 5. Read and send next word from file,  this is the "Block Size" .
 * 6. Send next words data from file up to "Block Size"
 * 7. Unit Program sectors, wait for checksum and compare (1s timout Fail)
 * 8. if not End of File go to step 6
 * 9.End of File  = Success
 *
 * If Success: unit will reboot to operational mode.
 * If Fail: unit will return to boot mode stage 3
 *
 * CAN master sends data as words, (SDO 0x2000 - 2 bytes data size).
 *
 */
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



#ifdef CAN
   communicationLock();
#else
   SCIA_AutobaudLock();
#endif

   checksum = 0;
   timoutReset();
   // If the KeyValue was invalid, abort the load
   // and return the flash entry point.

   /*Master Send first Word in .txt file 0x08AA*/
   if (GetOnlyWordData() != 0x08AA) return FLASH_ENTRY_POINT;

   /*master send next 8 words from .txt file*/
   ReadReservedFn();

   /*master send next 2 words from .txt file*/
   EntryAddr = GetLongData();

   CopyData();

   return EntryAddr;
}


/**
* @fn int circBufInit(CIRCBUF *circBuf, void *mem, size_t size)
*
* This function initializes a circular buffer of characters.
*
* @author Eli Schneider
*
* @param circBuf pointer to circular buffer structure
* @param mem pointer to buffer memory start
* @param size buffer memory size
*
* @return 0=Success, -1=Fail.
*
* @date 10.01.2009
*/
#define NULL 0
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(circBufInit,"ramfuncs");
#endif
int circBufInit(Uint16 *mem, unsigned long size)
{
    if ((BuffPtr==NULL) || (mem==NULL) || (size==0))
        return -1;
    BuffPtr->mem=mem;
    BuffPtr->size=size;
    BuffPtr->memEnd= &(mem)[size];
    BuffPtr->head=BuffPtr->tail=mem;
    BuffPtr->count=0;
    BuffPtr->bufFullErr=0;
    return 0;
}

/**
* @fn int circBufGet(CIRCBUF *circBuf, char *d)
*
* This function gets a character from the head of the circular buffer.
*
* @author Eli Schneider
*
* @param circBuf pointer to circular buffer structure
* @param d pointer to destination character
*
* @return 0=Success, -1=Fail.
*
* @date 10.01.2009
*/
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(circBufGet,"ramfuncs");
#endif
int circBufGet(Uint16 *d)
{

    if (BuffPtr->count==0)
        return -1;
    *d= *BuffPtr->head++;
    if (BuffPtr->head==BuffPtr->memEnd)
        BuffPtr->head=BuffPtr->mem;
    BuffPtr->count--;
    return 0;
}
/**
* @fn int circBufPut(CIRCBUF *circBuf, char ch)
*
* This function puts a character into a circular queue.
*
* @author Eli Schneider
*
* @param circBuf pointer to circular buffer structure
* @param ch character
*
* @return 0=Success, -1=Fail.
*
* @date 10.01.2009
*/
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(circBufPut,"ramfuncs");
#endif
int circBufPut(char ch)
{
    if (BuffPtr->size<=BuffPtr->count)
        return -1;
    *BuffPtr->tail++=ch;
    if (BuffPtr->tail==BuffPtr->memEnd)
        BuffPtr->tail=BuffPtr->mem;
    BuffPtr->count++;

    return 0;
}

#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(getData,"ramfuncs");
#endif
Uint16 getData(void)
{
    Uint16 Status;
    int i=0;
    while((i<7)&&(RemainingBytes>0))
    {
        switch(i)
        {
            case 0:
                Status = circBufPut(ECanaMboxes.MBOX1.MDL.byte.BYTE1);
                break;
            case 1:
                Status = circBufPut(ECanaMboxes.MBOX1.MDL.byte.BYTE2);
                break;
            case 2:
                Status = circBufPut(ECanaMboxes.MBOX1.MDL.byte.BYTE3);
                break;
            case 3:
                Status = circBufPut(ECanaMboxes.MBOX1.MDH.byte.BYTE4);
                break;
            case 4:
                Status = circBufPut(ECanaMboxes.MBOX1.MDH.byte.BYTE5);
                break;
            case 5:
                Status = circBufPut(ECanaMboxes.MBOX1.MDH.byte.BYTE6);
                break;
            case 6:
                Status = circBufPut(ECanaMboxes.MBOX1.MDH.byte.BYTE7);
                break;

        }
        if (Status)
            return Status;

        i++;
        RemainingBytes--;
    }
    return Status;

}
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(sdoInitiateDownloadHandle,"ramfuncs");
#endif

Uint16 sdoInitiateDownloadHandle()
{
    Uint16 SDO_ACK[8]={0};
    while (!ECanaRegs.CANRMP.bit.RMP1){ } //if not ready
    if (ECanaMboxes.MBOX1.MDL.byte.BYTE0 == 0x21) //initiate download
    {
        RemainingBytes=0;
        RemainingBytes1=0;
        RemainingBytes = (unsigned long)ECanaMboxes.MBOX1.MDH.byte.BYTE4+256*((unsigned long)ECanaMboxes.MBOX1.MDH.byte.BYTE5);
        RemainingBytes1 = (unsigned long)ECanaMboxes.MBOX1.MDH.byte.BYTE6+256*((unsigned long)ECanaMboxes.MBOX1.MDH.byte.BYTE7);
        RemainingBytes = (RemainingBytes1 << 16) | RemainingBytes;
        EALLOW;     // EALLOW enables access to protected bits
        ECanaRegs.CANRMP.all = 0x00000002;
        EDIS;
        SDO_ACK[0]= 0x60;
        SDO_ACK[1]= 0x20;
        canSendMailBox0(SDO_ACK,8);
        return 0;
    }
    else
      //  canSendMailBox0(SDO_ABORT,8);
        return 1;
}

#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(sdoSegmentAck,"ramfuncs");
#endif

Uint16 sdoSegmentAck()
{
    Uint16 SDO_ACK[8]={0};

    SDO_ACK[0]= 0x20;

    if(toggleBit)
        SDO_ACK[0]= 0x30;

    toggleBit = ~toggleBit;
    toggleBit &= 0x0001;
    EALLOW;     // EALLOW enables access to protected bits
    ECanaRegs.CANRMP.all = 0x00000002;
    EDIS;
    canSendMailBox0(SDO_ACK,8);
    return 0;
}
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(sdoSegmentGetData,"ramfuncs");
#endif

Uint16 sdoSegmentGetData()
{
    while (!ECanaRegs.CANRMP.bit.RMP1){ } //if not ready
    if (((toggleBit && (ECanaMboxes.MBOX1.MDL.byte.BYTE0 == 0x10))||
       (!toggleBit && !ECanaMboxes.MBOX1.MDL.byte.BYTE0))
       ||(ECanaMboxes.MBOX1.MDL.byte.BYTE0 == 0x3))
    {
        getData();
        return 0;
    }
    else
      //  canSendMailBox0(SDO_ABORT,8);
        return 1;
}

#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(getWordCanMailBox1Data,"ramfuncs");
#endif

Uint16 getWordCanMailBox1Data()
{
    Uint16 wordData;
    Uint16 tempData1;
    Uint16 tempData2;

    if (!RemainingBytes)
        sdoInitiateDownloadHandle(); //wait for new packet
    if (BuffPtr->count<2)
        sdoSegmentGetData(); //wait for new packet
    if (BuffPtr->count<4)
        sdoSegmentAck();

    circBufGet(&tempData1);
    circBufGet(&tempData2);
    // wordData = ECanaMboxes.MBOX1.MDL.word.HI_WORD;
    wordData = (tempData1|(tempData2<<8));

    return wordData;
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


#ifdef CAN
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(communicationLock, "ramfuncs");
#endif

/*
 *
 *
 * 1.1.10.3 Autobaud-Detect Sequence
 * Bits ABD and CDC in SCIFFCT control the autobaud logic. The SCIRST bit should be enabled to make
 * autobaud logic work.
 * If ABD is set while CDC is 1, which indicates auto-baud alignment, SCI transmit FIFO interrupt will occur
 * (TXINT). After the interrupt service CDC bit has to be cleared by software. If CDC remains set even after
 * interrupt service, there should be no repeat interrupts.
 * 1. Enable autobaud-detect mode for the SCI by setting the CDC bit (bit 13) in SCIFFCT and clearing the
 * ABD bit (Bit 15) by writing a 1 to ABDCLR bit (bit 14).
 * 2. Initialize the baud register to be 1 or less than a baud rate limit of 500 Kbps.
 * 3. Allow SCI to receive either character "A" or "a" from a host at the desired baud rate. If the first
 * character is either "A" or "a". the autobaud- detect hardware will detect the incoming baud rate and set
 * the ABD bit.
 * 4. The auto-detect hardware will update the baud rate register with the equivalent baud value hex. The
 * logic will also generate an interrupt to the CPU.
 * 5. Respond to the interrupt clear ADB bit by writing a 1 to ABD CLR (bit 14) of SCIFFCT register and
 * disable further autobaud locking by clearing CDC bit by writing a 0.
 * 6. Read the receive buffer for character "A" or "a" to empty the buffer and buffer status.
 * 7. If ABD is set while CDC is 1, which indicates autobaud alignment, the SCI transmit FIFO interrupt will
 * occur (TXINT). After the interrupt service CDC bit must be cleared by software.
 * NOTE: At higher baud rates, the slew rate of the incoming data bits can be affected by transceiver
 * and connector performance. While normal serial communications may work well, this slew
 * rate may limit reliable autobaud detection at higher baud rates (typically beyond 100k baud)
 * and cause the auto-baudlock feature to fail.
 * To avoid this, the followng is recommended:
 * • Achieve a baud-lock between the host and 28x SCI boot loader using a lower baud rate.
 * • The host may then handshake with the loaded 28x application to set the SCI baud rate
 * register to the desired higher baud rate.
 *
 *
 */
inline void communicationLock()
{
    Uint16 byteData;
    Uint16 TxData[8]={0};

    /*Set SCIA_AutobaudLock */
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
    for(;;)
    {
        /* Serial Section */
        if (UART_REG.SCIFFCT.bit.ABD == 1) //add sci A/B automatic detection and fixed baud at 19200
        {
            timoutReset();

            // After autobaud lock, clear the ABD and CDC bits
            UART_REG.SCIFFCT.bit.ABDCLR = 1;
            UART_REG.SCIFFCT.bit.CDC = 0;
            while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
            byteData = UART_REG.SCIRXBUF.bit.RXDT;
            UART_REG.SCITXBUF = byteData;
            //set SCIA get/Send pointers
            GetOnlyWordData = SCIA_GetOnlyWordData;
            SendCheckSum = SendCheckSumSci;
            break;
        }
        else if (UART_REG.SCIRXEMU == 69 || UART_REG.SCIRXEMU == 101){// E || e - Exit boot mode
            while(UART_REG.SCIRXST.bit.RXRDY != 1) { }
            byteData = UART_REG.SCIRXBUF.bit.RXDT;
            UART_REG.SCITXBUF = byteData;
            DELAY_US(1000L);       // 1mS delay to ensure can send ack
            ResetDog(); // Return to FW is exist
        }
        /* CAN Section */
        else if (ECanaRegs.CANRMP.all)
        {
            if ((ECanaMboxes.MBOX1.MDL.byte.BYTE1 == 0x20)&&
                (ECanaMboxes.MBOX1.MDL.byte.BYTE2 == 0x00))
            {
                if(ECanaMboxes.MBOX1.MDL.byte.BYTE3 == 0x00){
                    TxData[0]= 0x4F;
                    TxData[1]= 0x20;
                    TxData[4]=1;
                    canSendMailBox0(&TxData[0],8); //Echo
                    //set CAN get/Send pointers
                    //set get/Send pointers
                    GetOnlyWordData = getWordCanMailBox1Data;
                    SendCheckSum = SendCheckSumCAN;
                    EALLOW;     // EALLOW enables access to protected bits
                    ECanaRegs.CANRMP.all = 0x00000002;
                    EDIS;
                    break;
                }
                else if(ECanaMboxes.MBOX1.MDL.byte.BYTE3 == 0x01){
                    DELAY_US(1000L);                           // 1mS delay to ensure can send ack
                    ResetDog();//callMain();
                }
             }
         }
    }
    return;
}
#else
#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(SCIA_AutobaudLock, "ramfuncs");
#endif
inline void SCIA_AutobaudLock()
{

    SendCheckSum = SendCheckSumSci;
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
#endif
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
extern unsigned long serialCounter;

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

