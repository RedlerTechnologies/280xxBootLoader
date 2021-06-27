/**
* @file SCI_Boot.h
* @brief C2000 Resident bootloader SCI boot driver
*
* @author Eli Schneider
*
* @version 0.0.1
* @date 04.04.2011
*/
#ifndef _SCI_BOOT_H
#define _SCI_BOOT_H

#include <stdint.h>

Uint16 sdoSegmentAck(void);
void SCI_Re_Init(volatile struct SCI_REGS *regs, uint32_t baudRate);

unsigned long lspClkRate(void);

typedef enum
{
     Rate_4800=0,
     Rate_9600=1,
     Rate_19200=2,
     Rate_38400=3,
     Rate_57600=4,
     Rate_115200=5,
     Rate_230400=6,
     Rate_460800=7,
     Rate_921600=8
}baudRate;

#ifdef KUKU


inline void SCIA_Init(void)
{
	// Enable the SCI-A clocks
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
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
	// Enable pull-ups on SCI-A pins
	// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
	// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
	GpioCtrlRegs.GPAPUD.all &= 0xCFFFFFFF;
	// Enable the SCI-A pins
	// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
	// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
	GpioCtrlRegs.GPAMUX2.all |= 0x05000000;
	// Input qual for SCI-A RX is asynch
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
	EDIS;
}

inline void SCIA_BaudSet(Uint32 baud)
{
	Uint16 brr;

	if (baud)
		brr=(3125000UL/(baud))+((((3125000UL%(baud))*2)<baud)?0:1)-1;
	else
		brr=0;

	UART_REG.SCIHBAUD = brr>>8;
	UART_REG.SCILBAUD = brr&0xff;
}

inline void SCIA_AutobaudLockStart(void)
{
    // Must prime baud register with >= 1
    UART_REG.SCILBAUD = 1;
    // Prepare for autobaud detection
    // Set the CDC bit to enable autobaud detection
    // and clear the ABD bit
    UART_REG.SCIFFCT.bit.CDC = 1;
    UART_REG.SCIFFCT.bit.ABDCLR = 1;
}

inline int SCIA_AutobaudLockPoll(void)
{
    // Wait until we correctly read an
    // 'A' or 'a' and lock

    if(UART_REG.SCIFFCT.bit.ABD != 1)
		return 0;
    // After autobaud lock, clear the CDC bit
    UART_REG.SCIFFCT.bit.CDC = 0;
	return 1;
}

inline int SCIA_AutobaudLockRxPoll(void)
{
    Uint16 byteData;


	if (UART_REG.SCIRXST.bit.RXRDY != 1)
		return 0;
	byteData = UART_REG.SCIRXBUF.bit.RXDT;
	UART_REG.SCITXBUF = byteData;

	return 1;
}

inline int SCIA_RxRdy(void)
{
	return UART_REG.SCIRXST.bit.RXRDY;
}

inline int SCIA_RxEchoChar(void)
{
    Uint16 byteData;

	byteData = UART_REG.SCIRXBUF.bit.RXDT;
	UART_REG.SCITXBUF = byteData;
	return byteData;
}

inline int SCIA_RxChar(void)
{
    Uint16 byteData;

	byteData = UART_REG.SCIRXBUF.bit.RXDT;
	return byteData;
}

inline void SCIA_TxChar(Uint16 byteData)
{
	while (!UART_REG.SCICTL2.bit.TXRDY);
	UART_REG.SCITXBUF = byteData;
}

Uint16 SCIA_GetWordData();

#endif //KUKU
#endif // _SCI_BOOT_H
