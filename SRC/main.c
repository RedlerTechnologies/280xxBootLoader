//###########################################################################
//
//!  \addtogroup f2803x_example_list
//!  <h1>F28035 Flash Kernel (f2803x_flash_kernel)</h1>
//!
//!   This example is for use with the SerialLoader2000 utility.  This
//!   application is intended to be loaded into the device's RAM via the
//!   SCI boot mode.  After successfully loaded this program implements a
//!   modified version of the SCI boot protocol that allows a user application
//!   to be programmed into flash.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

/****************************************************************************
 * Redler modifications:
 * **************************************************************************
 *  Version: xx.xx.xx.xx , see "descriptor.h"
 *  Dedicated Rayon_Serial_programmer PC-SW needed
 *
 * 1. Loader positioned in Flash A
 * 2. Checksum Test:
         Fail - Enter Loader mode
         Success - Run Main software
         (User can skip test if CHECKSUM==0)
 * 3. SCI port selection
 * 4. Bootloader Descriptor - Main software can read BootLoader VER etc.
 * 5. Reserved function selected by modifying words (2 to 10) inside HEX File
 * Reserved[WORD] - FUNCTION
 *           [0]  - Sectors to erase
 *           [1]  - Enable KEY Sector For A Erase
 *           [3]  - Sector Erase report
 * 6. Reset timer,After 1 sec Without activity - Reset software back to Loader mode.
 * 7. Load main software at success
 * 8. Ability to call Loader from main program
 * 9. TBD  - Before entering main program. wait 1-3 sec for loader command.
 * 10. TBD  - Write unit serial number (at sector A).
 *
 * Shlomi Dar 20/02/2018
 ****************************************************************************/

#include "board.h"
#include "DSP28x_Project.h"
#include "descriptor.h"
#include "boot.h"
#include "SCI_Boot.h"
#ifdef CAN
#include "ecan.h"
#endif

extern Uint16 sectorMask;

// Prototype statements for functions found within this file.
extern Uint32 SCI_Boot();
void (*ApplicationPtr) (void);
__interrupt void cpu_timer0_isr(void);
void initTimersInterupt();

void memCopy(Uint16 *srcStartAddr,Uint16 *srcEndAddr,Uint16 *dstAddr)
{

  while(srcStartAddr <= srcEndAddr)
  {
      *dstAddr++ = *srcStartAddr++;
  }

  return;
} // end of memCopy() function

void initTimersInterupt(){

    DINT;

    IER &= ~M_INT1;  /* Since the PIE passes Timer0 int to CPU INT1 */
    asm("       NOP");  /* takes about 3 cycles to ensure a pending interrupt */
    asm("       NOP");  /* prior to disabling is serviced before entering */
    asm("       NOP");  /* critical code */

    /*timeout*/
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 60, 1000);//1ms interrupt
    timoutReset();

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS; // This is needed to disable write to EALLOW protected registers

    // Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    // Enable CPU INT1 which is connected to CPU-Timer 0:
    IER |= M_INT1;
    asm("       NOP");                    // Wait one cycle
    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM

    ERTM;   // Enable Global realtime interrupt DBGM
    DRTM;   // enable DebugInt

    CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
}

Uint32 main(void)
{
	Uint32 EntryPoint;

    DINT;	// Disable Global interrupt INTM => INTM = 1
    InitPieCtrl();
    InitPieVectTable();
    IER=0;
    IFR=0;
    PieCtrlRegs.PIEACK.all = 0;

    gpioInit();
    DisableDog();
	IntOsc1Sel();
	InitPll(DSP28_PLLCR,DSP28_DIVSEL);

	Uint16 txMem[8] = {0};
	/* Copy data to RAM */
	memCopy((Uint16 *)&RamfuncsLoadStart,(Uint16 *)&RamfuncsLoadEnd,(Uint16 *)&RamfuncsRunStart);

#ifdef CAN
	Uint32 SDO_RX = 0x600;
	Uint32 SDO_TX = 0x580;
	Uint32 HB_COB_ID = 0x700;   // Heartbeat  COB-ID
	Uint16 NMT_State[1] = { 0x7F };    // Pre-operational
#define UNIT_ID_DFLT 127

	Uint32* nodeIDptr =  (Uint32*)CAN_NODEID_FLASH;
	int nodeID = (*nodeIDptr);
	if(nodeID < 0 || nodeID > 127)
	    nodeID = UNIT_ID_DFLT;
	SDO_RX += nodeID;
	SDO_TX += nodeID;
	HB_COB_ID += nodeID;
    Uint32* canBaudRateptr =  (Uint32*)CAN_BAUDRATE_FLASH;
	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=1;   // eCAN-A
	int baudRate = (*canBaudRateptr);
	if(baudRate >= 0 && baudRate <= 8)
	    InitECanA(SelectCANBaudRate((*canBaudRateptr)));
	else
        InitECanA(SelectCANBaudRate(0));

	Ecan_set_tx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX, SDO_TX, 0);
	Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX + 1, SDO_RX, 0xFFFFFFFF, 0); // NODEID = 0
	circBufInit(txMem,sizeof(txMem));

    Ecan_set_tx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX + 2, HB_COB_ID, 0);
    canSendMailBox(&NMT_State[0], 1, &ECanaMboxes.MBOX2, 2); // Heartbeat

#endif

    initTimersInterupt();

	EntryPoint=SCI_Boot();

	//force reset
	return EntryPoint;
}//Returning from main calls _ExitBoot in Exit_Boot.asm.


#ifdef RUN_FROM_RAM
#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs");
#endif
__interrupt void cpu_timer0_isr(void)
{
    #ifdef DRV_LED_TOGGLE
    if(CpuTimer1.InterruptCount == 100){
        DRV_LED_TOGGLE;
        CpuTimer1.InterruptCount = 0;
    }
    CpuTimer1.InterruptCount++;
    #endif

   CpuTimer0.InterruptCount++;
   if (CpuTimer0.InterruptCount>2000) //2 SEC TIMOUT
   {
	   callBootLoader();
   }
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
