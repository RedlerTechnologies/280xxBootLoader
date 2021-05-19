/**
* @file ecandrv.c
* @brief driver for ECan
*
* @author Mamtsev Andrei
*
* @version 0.0.1
* @date 18.07.2010
*/


#include "DSP28x_Project.h"    // DSP28 Headerfile Include File
#include "ecan.h"





/**
* @fn void InitECanA(Uint32 canbtc)
*
* @brief Initialize eCAN-A  module
*
* @author Andrei Mamtsev
*
* @param canbtc  baud rate param
*
* @return void 
*
* @date 18.07.2010
*/

void InitECanA(Uint32 canbtc)       // Initialize eCAN-A module
{
    /* Create a shadow register structure for the CAN control registers. This is
    needed, since, only 32-bit access is allowed to these registers. 16-bit access
    to these registers could potentially corrupt the register contents. This is
    especially true while writing to a bit (or group of bits) among bits 16 - 31 */

    struct ECAN_REGS ECanaShadow;

    EALLOW;     // EALLOW enables access to protected bits


    /* Configure eCAN RX and TX pins for CAN operation using eCAN regs*/

        ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
        ECanaShadow.CANTIOC.bit.TXFUNC = 1;
        ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;

        ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
        ECanaShadow.CANRIOC.bit.RXFUNC = 1;
        ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;
    /* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
    // HECC mode also enables time-stamping feature

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.SCB = 1;
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    /* Initialize all bits of 'Master Control Field' to zero */
    // Some bits of MSGCTRL register come up in an unknown state. For proper operation,
    // all bits (including reserved bits) of MSGCTRL must be initialized to zero

    ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX31.MSGCTRL.all = 0x00000000;

    // TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
    //  as a matter of precaution.

    ECanaRegs.CANTA.all = 0xFFFFFFFF;   /* Clear all TAn bits */

    ECanaRegs.CANRMP.all = 0xFFFFFFFF;  /* Clear all RMPn bits */

    ECanaRegs.CANGIF0.all = 0xFFFFFFFF; /* Clear all interrupt flag bits */
    ECanaRegs.CANGIF1.all = 0xFFFFFFFF;


    /* Configure bit timing parameters for eCANA*/
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

//clk must be enable to exit this loop
    do
    {
      ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 1 );       // Wait for CCE bit to be set..
    //while(ECanaRegs.CANES.bit.CCE != 1 ) {}   // Wait for CCE bit to be set..

    ECanaShadow.CANBTC.all = 0;
       /* The following block is for 90 MHz SYSCLKOUT. (45 MHz CAN module clock Bit rate = 1 Mbps
          See Note at end of file. */
    ECanaShadow.CANBTC.all=canbtc;

#ifdef EXPLANATION
       ECanaShadow.CANBTC.bit.BRPREG = 2;
       ECanaShadow.CANBTC.bit.TSEG2REG = 3;
       ECanaShadow.CANBTC.bit.TSEG1REG = 9;
       ECanaShadow.CANBTC.bit.SAM = 1;
#endif
       ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;

       ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
       ECanaShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
       ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

       // Wait until the CPU no longer has permission to change the configuration registers
       do
       {
         ECanaShadow.CANES.all = ECanaRegs.CANES.all;
       } while(ECanaShadow.CANES.bit.CCE != 0 );       // Wait for CCE bit to be  cleared..
    /* Disable all Mailboxes  */
    ECanaRegs.CANME.all = 0;        // Required before writing the MSGIDs

    EDIS;
}


/**
* @fn void Ecan_set_rx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint32 mask, Uint16 ext)
*
* @brief Initialize eCAN receive mail box 
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param mbox_id  mail box ID
* @param MsgId  message ID
* @param mask  mask forLAM register
* @param ext  
*
* @return void 
*
* @date 18.07.2010
*/
//    Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX+6, ((Uint32)DeviceSp->CanNodeID), 0xFF000000, 0);//nodeID+0x300,0xFFF,

void Ecan_set_rx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint32 mask, Uint16 ext)
{
    struct ECAN_REGS ECanShadow;
    union CANMSGID_REG msg_id;

    if (ECAN_CHANNELS<=dev_id)
        return;
    if (32<=mbox_id)
        return;
    if (ext)
    {
        msg_id.all=MsgId&0x1FFFFFFF;
        msg_id.bit.IDE=1;
    }
    else
    {
        msg_id.all=0;
        msg_id.bit.STDMSGID=MsgId;
        msg_id.bit.AME=1;
    }
    {
        // ECAN_A

        EALLOW;     // EALLOW enables access to protected bits

        /*
        ** Disable mailbox
        */
        ECanShadow.CANME.all=ECanaRegs.CANME.all;
        ECanShadow.CANME.all &= (~(1<<mbox_id));
        ECanaRegs.CANME.all = ECanShadow.CANME.all;

        /*
        ** Set rx direction
        */
        ECanShadow.CANMD.all = ECanaRegs.CANMD.all;
        ECanShadow.CANMD.all |= (1<<mbox_id);
        ECanaRegs.CANMD.all = ECanShadow.CANMD.all;

        (&ECanaMboxes.MBOX0)[mbox_id].MSGID.all=msg_id.all;
        (&ECanaLAMRegs.LAM0)[mbox_id].all=mask;

        /*
        ** Enable mailbox
        */
        ECanShadow.CANME.all=ECanaRegs.CANME.all;
        ECanShadow.CANME.all |= (1<<mbox_id);
        ECanaRegs.CANME.all = ECanShadow.CANME.all;

        EDIS;

    }
}

/**
* @fn void Ecan_set_tx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint32 mask, Uint16 ext)
*
* @brief Initialize eCAN transmit mail box 
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param mbox_id  mail box ID
* @param MsgId  message ID
* @param mask  mask forLAM register
* @param ext  
*
* @return void 
*
* @date 18.07.2010
*/
void Ecan_set_tx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint16 ext)
{
    struct ECAN_REGS ECanShadow;
    union CANMSGID_REG msg_id;

    if (ECAN_CHANNELS<=dev_id)
        return;
    if (32<=mbox_id)
        return;
    if (ext)
    {
        msg_id.all=MsgId&0x1FFFFFFF;
        msg_id.bit.IDE=1;
    }
    else
    {
        msg_id.all=0;
        msg_id.bit.STDMSGID=MsgId;
    }

    {
        // ECAN_A
        EALLOW;     // EALLOW enables access to protected bits

        /*
        ** Disable mailbox
        */
        ECanShadow.CANME.all=ECanaRegs.CANME.all;
        ECanShadow.CANME.all &= (~(1<<mbox_id));
        ECanaRegs.CANME.all = ECanShadow.CANME.all;

        /*
        ** Set tx direction
        */

        ECanShadow.CANMD.all = ECanaRegs.CANMD.all;
        ECanShadow.CANMD.all &= (~(1<<mbox_id));
        ECanaRegs.CANMD.all = ECanShadow.CANMD.all;

        (&ECanaMboxes.MBOX0)[mbox_id].MSGID.all=msg_id.all;

        /*
        ** Enable mailbox
        */
        ECanShadow.CANME.all=ECanaRegs.CANME.all;
        ECanShadow.CANME.all |= (1<<mbox_id);
        ECanaRegs.CANME.all = ECanShadow.CANME.all;

        EDIS;
    }
}



void canSendMailBox0(Uint16 data)
{
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 4;
    ECanaMboxes.MBOX0.MDL.word.HI_WORD = 0x2000;
    ECanaMboxes.MBOX0.MDL.word.LOW_WORD = data;
    ECanaRegs.CANTRS.all = (Uint32)BIT0;  // request a transmission for MailBox 0

}

extern unsigned int checksum;

Uint16 getWordCanMailBox1Data()
{
    Uint16 wordData;

    while (!ECanaRegs.CANRMP.bit.RMP1 && ECanaMboxes.MBOX1.MDL.word.HI_WORD != 0x2000){ } //if not ready
    wordData = ECanaMboxes.MBOX1.MDL.word.LOW_WORD;
    ECanaRegs.CANRMP.all = (Uint32)BIT1;
    checksum += ECanaMboxes.MBOX1.MDL.byte.BYTE0 + ECanaMboxes.MBOX1.MDL.byte.BYTE1;

    return wordData;
}

#ifdef KUKU

ECAN_RX_PACKET    ecan_rx_packet;
Uint32 ecan_rx_cnt=0;
ECAN_TX_PACKET    ecan_tx_packet;
Uint32 ecan_tx_cnt=0;
/*Uint8*/char cnt=0;
ECAN_ERROR_COUNT EcanErrorCount;


/**
* @fn void Ecan_set_baud(Uint16 dev_id, Uint32 canbtc)
*
* @brief Set ECan baud rate
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param canbtc  baud rate param
*
* @return void
*
* @date 18.07.2010
*/
void Ecan_set_baud(Uint16 dev_id, Uint32 canbtc)
{
	/* Create a shadow register structure for the CAN control registers. This is
	needed, since, only 32-bit access is allowed to these registers. 16-bit access
	to these registers could potentially corrupt the register contents. This is
	especially true while writing to a bit (or group of bits) among bits 16 - 31 */

	struct ECAN_REGS ECanShadow;

	if (ECAN_CHANNELS<=dev_id)
		return;

	{
		EALLOW;		// EALLOW enables access to protected bits
		// ECAN_A
		ECanShadow.CANMC.all = ECanaRegs.CANMC.all;
		ECanShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
	    ECanaRegs.CANMC.all = ECanShadow.CANMC.all;
	    while(ECanaRegs.CANES.bit.CCE != 1 ) {}   // Wait for CCE bit to be set..
		ECanaRegs.CANBTC.all = canbtc;
		EDIS;
	}
}

/**
* @fn void Ecan_set_lam(Uint16 dev_id, Uint16 mbox_id, Uint32 mask)
*
* @brief Set ECan lam register
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param mbox_id  mail box ID
* @param mask  mask forLAM register
*
* @return void
*
* @date 18.07.2010
*/
void Ecan_set_lam(Uint16 dev_id, Uint16 mbox_id, Uint32 mask)
{
	if (ECAN_CHANNELS<=dev_id)
		return;
	if (32<=mbox_id)
		return;
	{

		(&ECanaLAMRegs.LAM0)[mbox_id].all=mask;
	}
}


/**
* @fn void Ecan_disable_mailbox(Uint16 dev_id, Uint16 mbox_id)
*
* @brief disable ECan mail box 
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param mbox_id  mail box ID
*
* @return void 
*
* @date 18.07.2010
*/
void Ecan_disable_mailbox(Uint16 dev_id, Uint16 mbox_id)
{
	struct ECAN_REGS ECanShadow;
	
	if (ECAN_CHANNELS<=dev_id)
		return;
	if (32<=mbox_id)
		return;

	{
		// ECAN_A
		EALLOW;		// EALLOW enables access to protected bits

		/*
		** Disable mailbox
		*/
		ECanShadow.CANME.all=ECanaRegs.CANME.all;
		ECanShadow.CANME.all &= (~(1<<mbox_id));
		ECanaRegs.CANME.all = ECanShadow.CANME.all; 
  
	    EDIS;
	}
}

/**
* @fn int16 Ecan_getd(Uint16 dev_id, struct sEcanRxPacket *rx_packet)
*
* @brief receive ECan packet
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
* @param rx_packet  pointer to receive packet struct
*
* @return 1-success , 0-fail 
*
* @date 18.07.2010
*/
int16 Ecan_getd(Uint16 dev_id, struct sEcanRxPacket *rx_packet)
{
	Uint32	mb_mask;
	Uint16	mbox_id;
	volatile struct MBOX *mbx;
	
	if (ECAN_CHANNELS<=dev_id)
		return 0;
	{
		// ECAN_A

        // Find a pending rx mailbox starting from the lowest Mailbox
	    for (mbox_id=0, mb_mask=1; mb_mask!=0; mb_mask<<=1, mbox_id++)
		{
			if (ECanaRegs.CANRMP.all & mb_mask)
				break;
 		}
		if (mb_mask)
		{


			// message is pending, get mailbox adderss
			mbx= &(&ECanaMboxes.MBOX0)[mbox_id];
			rx_packet->mbox_id=mbox_id;
			rx_packet->Ctl.all=0;
			rx_packet->Ctl.bit.dlc=mbx->MSGCTRL.bit.DLC;
			rx_packet->Ctl.bit.rtr=mbx->MSGCTRL.bit.RTR;
			rx_packet->Ctl.bit.ext=mbx->MSGID.bit.IDE;
			rx_packet->Ctl.bit.dbo=ECanaRegs.CANMC.bit.DBO;
			rx_packet->TimeStamp=(&ECanaMOTSRegs.MOTS0)[mbox_id];
			if (rx_packet->Ctl.bit.ext)
				rx_packet->MsgId=mbx->MSGID.all & 0x1FFFFFFF;
			else
				rx_packet->MsgId=mbx->MSGID.bit.STDMSGID;
			rx_packet->data.l.MDL=mbx->MDL.all;
			rx_packet->data.l.MDH=mbx->MDH.all;
			ECanaRegs.CANRMP.all=mb_mask;
			rx_packet->Ctl.bit.dev=dev_id;
			return 1;
		}
		
	}
	return 0;
}


void Ecan_set_mailbox_6_7_9()
{
    // Set Mailbox number 6 as Rx Mailbox. The mask 0xFFFFFFFF means that this value is written to the CANLAM register (CAN Local Acceptance Mask).
    // It means that:
    //  CANLAM.31 = LAMI = true -> Standard (11-bit) and extended (29-bit) CAN indentifier can be received.
    //  CANLAM.30:29 = true     -> Those bits have no meaning, they are Reserved and have no impact.
    //  CANLAM.28:0 = true      -> A value of 1 in the bit means that no matter if received identifier at this bit location is true or false, it is accepted.
    //                          -> A value of 0 in the bit would mean, that the received message identifier must match at this bit-position 1:1 the identifier
    //                             that we write to the message ID register, see '&ECanaMboxes.MBOX0)[mbox_id].MSGID.all'.
    Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX+6, ((Uint32)DeviceSp->CanNodeID), 0xFFFFFFFF/*0xFF000000*/, 0);//nodeID+0x300,0xFFF,

    // Take a dedicated Mailbox number 7 for an NMT message.
    // This Rx buffer is only dedicated to an NMT message (CAN-Identifier = 0x000)
    //  CANLAM.31 = LAMI = false -> The identifier extension bit stored inside bit 31 of '&ECanaMboxes.MBOX0)[mbox_id].MSGID.bit.IDE' (bit 31) determines which identifier is allowed.
    //  CANLAM.30:29 = true      -> Those bits have no meaning, they are Reserved and have no impact.
    //  CANLAM.28:0 = false      -> A value of 0 in the bit means, that the received message identifier at this bit location must match 1:1 the identifier that we
    //                              write to the message ID register, see '&ECanaMboxes.MBOX0)[mbox_id].MSGID.all'.
    Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX+7, CMD_NMT, 0x00000000, 0);

    Ecan_set_tx_mailbox(ECAN_A, MSG_GET_DATA_MAILBOX, (Uint32)DeviceSp->CanNodeID+MSG_PDO2_TX, 0);

}

/**
* @fn int16 Ecan_rxmbrdy(Uint16 dev_id)
*
* @brief   Received Message Pending
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
*
* @return 1-success , 0-fail 
*
* @date 18.07.2010
*/
int myErrorCounter=0;
int myErrorCounter1=0;

int16 Ecan_rxmbrdy(Uint16 dev_id)
{


	if (ECAN_CHANNELS<=dev_id)
		return 0;
	    // ECAN_A
        // CANRMP is a bit-wise register and indicates, that a Received Message is Pending in a certain Mailbox
        // CANME  is a bit-wise register and indicates, that a certain Mailbox is Enabled
        // CANMD  is a bit-wise register and indicates, the Mailbox Direction (bit true = receive, bit false = transmit)
        // So what the function returns is, it  returns a true in case that a CAN Message is pending inside an enabled Mailbox,
        // which is configured in receive direction. So basically if the CAN controller has received a telegram.
	if ((ECanaRegs.CANME.all)&(ECanaRegs.CANMD.all))
    {
                if (ECanaRegs.CANRMP.all)

                    return 1;
    }
 // if (ECanaRegs.CANRMP.all & ECanaRegs.CANME.all & ECanaRegs.CANMD.all)

        return 0;
}

/**
* @fn int16 Ecan_error(Uint16 dev_id)
*
* @brief   Received Message Error
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
*
* @return 1-success , 0-fail 
*
* @date 18.07.2010
*/
int16 Ecan_error(Uint16 dev_id)
{

	if (ECAN_CHANNELS<=dev_id)
		return 0;
	{
		// ECAN_A
		return (ECanaRegs.CANES.all>>15)&0x1FF;
	}
}

/**
* @fn int16 Ecan_TimeOut(Uint16 dev_id)
*
* @brief   Received Message Time out
*
* @author Andrei Mamtsev
*
* @param dev_id  device ID
*
* @return 1-success , 0-fail 
*
* @date 18.07.2010
*/

int16 Ecan_TimeOut(Uint16 dev_id)
{
	Uint32		MailboxID;
	Uint32				mask;
    struct ECAN_REGS    ECanShadow; // AviBendor: Local array of 26*4[Byte] = 104[Byte] --> be sensitive for stack overflow
	//struct ECAN_REGS	*ECanRegstem=&ECanaRegs;

	if (ECAN_CHANNELS<=dev_id)
		return 0;
	{
        // ECAN_A
        if(ECanaRegs.CANGIF0.bit.AAIF0) // If bit AAIF0 indicates, that a transmission request has been aborted
        {
            EcanErrorCount.TimeOut++; // Increment a timeout counter
            ECanShadow.CANGIF0.all= ECanaRegs.CANGIF0.all; // Save global interrupt flag 0 register in a local variable
            ECanShadow.CANTOS.all=ECanaRegs.CANTOS.all;    // Save CAN timeout status register in a local variable

            for (mask=1, MailboxID=0;mask!=0;mask<<=1, MailboxID++) // a for loop that goes through all 32 mailbox buffers
            {
                if (ECanShadow.CANTOS.all & mask) // If the CAN timeout status register indicates that Mailbox[n] has timed out
                {
                    ECanaRegs.CANTOS.all=mask; // Set the bit to 0 via writing 1 to the corresponding bit
                    ECanShadow.CANTOC.all=ECanaRegs.CANTOC.all; // Copy the timeout control register into a shadow variable
                    ECanShadow.CANTOC.all &= ~mask;             // Clear the bit of Mailbox[n], which caused a timeout
                    ECanaRegs.CANTOC.all=ECanShadow.CANTOC.all; // Write back the shadow register. Here we disable the timeout functionality of the Mailbox[n], that ran into a timeout.
                    if ((ECanaRegs.CANMD.all & (1<<MailboxID))==0) // If the Mailox that indicated a timeout was configured as a trasmit Mailbox
                    {
                        ECanaRegs.CANTRR.all=mask; // Cancel the Mailbox transmission request
                        break;
                    }
                }
            }
        }
    }
	return 0;
}



extern Uint32 mainIsrtTicker;
// This function is being called to check if somebody re-configured the static Rx & Tx Mailboxes (unexpectedly).
// There was a problem that when connecting a Kvaser to the CAN network, there were garbage telegrams
// on the bus and somehow the CAN controller static (Rx) Mailboxes got re-configured and currently we do not
// know who re-configured the static Mailboxes. The static Mailboxes are set up inside the function 'CanInit'
// via the function call 'Ecan_set_mailbox_6_7_9()'.
void Ecan_Check_And_Repair_Static_MailBoxes(Uint16 dev_id)
{

    static Uint32 previousIsrTicker = 0;
    int32 IsrTickerDifference = 0;
    Uint16 performCheck = 0;
    struct ECAN_REGS ECanaShadow;
    if (ECAN_CHANNELS<=dev_id)
    {
        return ;
    }

    // The following code is implemented to perform certain actions every n[ms]
    IsrTickerDifference = mainIsrtTicker - previousIsrTicker;
    if((IsrTickerDifference > 2000) || (IsrTickerDifference < 0)) // 2000[Isr Ticks] = every 100[ms]
    {
        performCheck = 1;
        previousIsrTicker = mainIsrtTicker;
    }

    if(performCheck != 0)
    {
        if ((ECanaRegs.CANES.bit.ACKE)||(ECanaRegs.CANES.bit.SMA))
        {
            EALLOW; // @Udi: This I believe is not needed because CAN controller datasheet does not say anything about EALLOW for the CANES register

            ECanaShadow.CANES.all = ECanaRegs.CANES.all;
            ECanaShadow.CANES.all &= 0x01BF0000;
            ECanaRegs.CANES.all = ECanaShadow.CANES.all;


            EDIS;  // @Udi: This I believe is not needed because CAN controller datasheet does not say anything about EALLOW for the CANES register
        }
    }


    // If the following condition is true, then the function 'Ecan_rxmbrdy'
    // has not even a chance to return a 1 and process an incoming message.
    // That means we must take some measures to repair the Mailboxes...
    if ( (!((ECanaRegs.CANME.all)&(ECanaRegs.CANMD.all))) || (performCheck != 0) ) // Check if 'Ecan_rxmbrdy' cannot return a true or check also every 100[ms]
    {
        if ( ((ECanaRegs.CANME.all & 0x0000002C) != 0x0000002C) ||
             ((ECanaRegs.CANMD.all & 0x0000002C) != 0x0000000C) )
            //    &&(Ecan_error(ECAN_A))) //Error in tx/rx?
        {

            EALLOW;     // EALLOW enables access to protected bits
            ECanaRegs.CANRMP.all = 0xFFFFFFFF;
            ECanaRegs.CANME.all = 0;
            ECanaRegs.CANMD.all =0;
            EDIS;
            Ecan_set_mailbox_6_7_9();
        }
    }
}








int16 Ecan_TX_Abort(Uint16 dev_id)
{
	Uint32				mask;
	Uint32		MailboxID;
    struct ECAN_REGS    ECanShadow; // AviBendor: Local array of 26*4[Byte] = 104[Byte] --> be sensitive for stack overflow
	struct MBOX mbx;
	ECAN_TX_PACKET	ecan_tx_packet;


	if (ECAN_CHANNELS<=dev_id)
		return 0;
	{
		// ECAN_A
	    // Here we check the CANGIF0 register, which is the Global Interrupt Flag Register 0
	            if(ECanaRegs.CANGIF0.bit.AAIF0) // If bit AAIF0 indicates, that a transmission request has been aborted
	            {
	                EcanErrorCount.TXAbort++; // Increment a Tx Abort Error Counter
	                /*
	                ** Tx mailbox, handle transmission abort
	                */
	                ECanShadow.CANAA.all=ECanaRegs.CANAA.all; // Save the current CAN acknowledge abort register value

	                for (mask=1, MailboxID=0;mask!=0;mask<<=1, MailboxID++) // Go through all Mailboxes
	                {
	                    if (ECanShadow.CANAA.all & mask) // If a certain Tx Mailbox has failed to transmit a telegram
	                    {
	                        ECanaRegs.CANAA.all = mask; // Acknowledge the aborted transmission via writing a 1 to the dedicated Mailbox bit
	                    //  mbx= (&ECanbMboxes.MBOX0)[mask];//anton
	                        mbx= (&ECanaMboxes.MBOX0)[MailboxID];   // Copy the content of the CAN controller mailbox, which is currently processed
	                        ecan_tx_packet.data.l.MDH=mbx.MDH.all;  // Read upper 32-bit data of Tx telegram, which wasn't successfully transmitted
	                        ecan_tx_packet.data.l.MDL=mbx.MDL.all;  // Read lower 32-bit data of Tx telegram, which wasn't successfully transmitted
	                        ecan_tx_packet.MsgId=mbx.MSGID.all;     // Read COB-ID of Tx telegram, which wasn't successfully transmitted
	                        ecan_tx_packet.Ctl.bit.rtr=mbx.MSGCTRL.bit.RTR; // Read RTR bit of telegram, which wasn't successfully transmitted
                            ecan_tx_packet.mbox_id = MailboxID; // Indicate with which Mailbox number of the CAN controller the re-transmission is supposed to be done.
	                        Ecan_putd(ECAN_A, &ecan_tx_packet); // Re-send the telegram
	                        break;
	                    }
	                }
	            }
	}
	return 0;
}






unsigned char canSend1(CAN_PORT notused, Message *m)
{


  ECAN_TX_PACKET  ecan_tx_packet;
  _iq IqFdb;
  IqFdb=_IQ(ClaMsg.IqFdb);


  ecan_tx_packet.mbox_id=-1;
  ecan_tx_packet.Ctl.all=0;
  ecan_tx_packet.Ctl.bit.dlc=m->len;
  ecan_tx_packet.Ctl.bit.rtr=m->rtr;
  ecan_tx_packet.TimeOut=0;/*100*/
  ecan_tx_packet.MsgId=(Uint32)m->cob_id;//MSG_RESET;
  ecan_tx_packet.data.c0.b0='C';//m->data[0];
  ecan_tx_packet.data.c0.b1='C';//m->data[1];
  ecan_tx_packet.data.c0.b2=0x01;
  ecan_tx_packet.data.c0.b3=0x00;

if(valH || valL){
	switch(valH){
	   case  IQFdb:

		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(IqFdb)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);

	   break;

	   case  IQRef:
		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);
	  		   break;

	   /* TO DO MORE STATES... */

	   default:
		   ecan_tx_packet.data.c0.b4= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b5= 0x00;//DataHigh 8ad
	}

	if(valL==valH)
		valL=0;

	switch(valL)
	{
	   case  IQFdb:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(IqFdb)));  // (_IQtoIQ15(IqFdb)>)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   case IQRef:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));  // (_IQtoIQ15(IqFdb)>>8)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   /* TO DO MORE STATES... */



	   default:
		   ecan_tx_packet.data.c0.b6= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b7= 0x00;//DataHigh 8ad
	}
return (unsigned char)Ecan_putd(ECAN_A, &ecan_tx_packet);
}
else if(valH2 || valL2)
{
		switch(valH2){
	   case  IQFdb:

		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(IqFdb)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);

	   break;

	   case  IQRef:
		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);
	  		   break;

	   /* TO DO MORE STATES... */

	   default:
		   ecan_tx_packet.data.c0.b4= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b5= 0x00;//DataHigh 8ad
	}

	//if(valL==valH)
		//valL=0;

	switch(valL2)
	{
	   case  IQFdb:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(IqFdb)));  // (_IQtoIQ15(IqFdb)>)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   case IQRef:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));  // (_IQtoIQ15(IqFdb)>>8)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   /* TO DO MORE STATES... */



	   default:
		   ecan_tx_packet.data.c0.b6= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b7= 0x00;//DataHigh 8ad
	}
	return (unsigned char)Ecan_putd(ECAN_A, &ecan_tx_packet);
}
return 0;
}



unsigned char canSendAB(CAN_PORT notused, Message *m)
{
	  ECAN_TX_PACKET  ecan_tx_packet;
	  _iq IqFdb=_IQ(ClaMsg.IqFdb);

	  ecan_tx_packet.mbox_id=-1;
	  ecan_tx_packet.Ctl.all=0;
	  ecan_tx_packet.Ctl.bit.dlc=m->len;
	  ecan_tx_packet.Ctl.bit.rtr=m->rtr;
	  ecan_tx_packet.TimeOut=0;/*100*/
	  ecan_tx_packet.MsgId=(Uint32)m->cob_id;//MSG_RESET;
	  ecan_tx_packet.data.c0.b0='A';
	  ecan_tx_packet.data.c0.b1='A';
	  ecan_tx_packet.data.c0.b2=0x01;
	  ecan_tx_packet.data.c0.b3=0x00;
	switch(valH){
	   case  IQFdb:

		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(IqFdb)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);

	   break;

	   case  IQRef:
		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);
	  		   break;

	   /* TO DO MORE STATES... */

	   default:
		   ecan_tx_packet.data.c0.b4= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b5= 0x00;//DataHigh 8ad
	}

	if(valL==valH)
		valL=0;

	switch(valL)
	{
	   case  IQFdb:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(IqFdb)));  // (_IQtoIQ15(IqFdb)>)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   case IQRef:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));  // (_IQtoIQ15(IqFdb)>>8)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   /* TO DO MORE STATES... */



	   default:
		   ecan_tx_packet.data.c0.b6= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b7= 0x00;//DataHigh 8ad
	}
return (unsigned char)Ecan_putd(ECAN_A, &ecan_tx_packet);
}


unsigned char canSendCD(CAN_PORT notused, Message *m)
{
	  ECAN_TX_PACKET  ecan_tx_packet;
      _iq IqFdb=_IQ(ClaMsg.IqFdb);

	  ecan_tx_packet.mbox_id=-1;
	  ecan_tx_packet.Ctl.all=0;
	  ecan_tx_packet.Ctl.bit.dlc=m->len;
	  ecan_tx_packet.Ctl.bit.rtr=m->rtr;
	  ecan_tx_packet.TimeOut=0;/*100*/
	  ecan_tx_packet.MsgId=(Uint32)m->cob_id;//MSG_RESET;
	  ecan_tx_packet.data.c0.b0='B';
	  ecan_tx_packet.data.c0.b1='B';
	  ecan_tx_packet.data.c0.b2=0x01;
	  ecan_tx_packet.data.c0.b3=0x00;
switch(valH2){
	   case  IQFdb:

		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(IqFdb)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);

	   break;

	   case  IQRef:
		   ecan_tx_packet.data.c0.b4=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));
		   ecan_tx_packet.data.c0.b5=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);
	  		   break;

	   /* TO DO MORE STATES... */

	   default:
		   ecan_tx_packet.data.c0.b4= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b5= 0x00;//DataHigh 8ad
	}

	if(valL==valH)
		valL=0;

	switch(valL2)
	{
	   case  IQFdb:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(IqFdb)));  // (_IQtoIQ15(IqFdb)>)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(IqFdb)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   case IQRef:
		   ecan_tx_packet.data.c0.b6=  (unsigned int)((_IQtoIQ15(CpuMsg.IqRef)));  // (_IQtoIQ15(IqFdb)>>8)&0xFF;
		   ecan_tx_packet.data.c0.b7=  (unsigned int)(_IQtoIQ15(CpuMsg.IqRef)>>8);  // _IQtoIQ15(IqFdb)&0xFF;    //DataHigh 8ad
	   break;
	   /* TO DO MORE STATES... */



	   default:
		   ecan_tx_packet.data.c0.b6= 0x00;//DataHigh 8
		   ecan_tx_packet.data.c0.b7= 0x00;//DataHigh 8ad
	}
	return (unsigned char)Ecan_putd(ECAN_A, &ecan_tx_packet);
}


unsigned char canSendFT(CAN_PORT notused, Message *m)
{
      ECAN_TX_PACKET  ecan_tx_packet;
   //  _iq ISin=0;
	  ecan_tx_packet.mbox_id=-1;
	  ecan_tx_packet.Ctl.all=0;
	  ecan_tx_packet.Ctl.bit.dlc=8;//m->len;
	  ecan_tx_packet.Ctl.bit.rtr=0;//m->rtr;
	  ecan_tx_packet.TimeOut=0;/*100*/
	  ecan_tx_packet.MsgId=(Uint32)m->cob_id;//MSG_RESET;
	  ecan_tx_packet.data.c0.b0='F';
	  ecan_tx_packet.data.c0.b1='T';
	  ecan_tx_packet.data.c0.b3=0x00;



      ecan_tx_packet.data.c0.b2=0x01;
	  ecan_tx_packet.data.c0.b6=  (unsigned int)(yellowCh);
	  ecan_tx_packet.data.c0.b7=  (unsigned int)(yellowCh>>8);
	  ecan_tx_packet.data.c0.b4=  (unsigned int)(blueCh);
	  ecan_tx_packet.data.c0.b5=  (unsigned int)((blueCh)>>8);

	return (unsigned char)Ecan_putd(ECAN_A, &ecan_tx_packet);
}


/**
* @fn void DataMatch(ECAN_RX_PACKET *ecan_rx_packet,Message *m)
*
* @brief convert receive data
*
* @author Andrei Mamtsev
*
* @param ecan_rx_packet pointer to receive packet
* @param Message *m pointer to message to send
*
* @return void
*
* @date 18.07.2010
*/

void DataMatch(ECAN_RX_PACKET *ecan_rx_packet,Message *m)
{
	m->len=ecan_rx_packet->Ctl.bit.dlc;
	m->rtr=ecan_rx_packet->Ctl.bit.rtr;
	m->cob_id=ecan_rx_packet->MsgId;//MSG_RESET;
	m->data[0]=ecan_rx_packet->data.c0.b0;
	m->data[1]=ecan_rx_packet->data.c0.b1;
	m->data[2]=ecan_rx_packet->data.c0.b2;
	m->data[3]=ecan_rx_packet->data.c0.b3;
    m->data[4]=ecan_rx_packet->data.c0.b4;
    m->data[5]=ecan_rx_packet->data.c0.b5;
    m->data[6]=ecan_rx_packet->data.c0.b6;
    m->data[7]=ecan_rx_packet->data.c0.b7;
#ifdef KUKU
	if(m->len==4)
	{
		m->len=8;
		m->data[3]|=0x40;
		m->data[4]=m->data[5]=m->data[6]=m->data[7]=0;
	}
	else
	{
		m->data[4]=ecan_rx_packet->data.c0.b4;
		m->data[5]=ecan_rx_packet->data.c0.b5;
		m->data[6]=ecan_rx_packet->data.c0.b6;
		m->data[7]=ecan_rx_packet->data.c0.b7;
	}
#endif
}

/**
* @fn UNS8 canChangeBaudRate(CAN_PORT port, char* baud)
*
* @brief Change ECan baud rate 
*
* @author Andrei Mamtsev
*
* @param port  not used
* @param baud  baud rate param
*
* @return 1 
*
* @date 18.07.2010
*/
UNS8 canChangeBaudRate(CAN_PORT port, char* baud)
{

	Uint32 canbaud=ECANBR_1MBPS_VAL;

	if(!strcmp( baud, "1M")) canbaud=ECANBR_1MBPS_VAL;
//	if(!strcmp( baud, "800K")) canbaud=ECANBR_800KBPS_VAL;
	if(!strcmp( baud, "500K")) canbaud=ECANBR_500KBPS_VAL;
	if(!strcmp( baud, "250K")) canbaud=ECANBR_250KBPS_VAL;
	if(!strcmp( baud, "125K")) canbaud=ECANBR_125KBPS_VAL;
	if(!strcmp( baud, "100K")) canbaud=ECANBR_100KBPS_VAL;
	if(!strcmp( baud, "50K")) canbaud=ECANBR_50KBPS_VAL;
	if(!strcmp( baud, "20K")) canbaud=ECANBR_20KBPS_VAL;
	if(!strcmp( baud, "10K")) canbaud=ECANBR_10KBPS_VAL;
		
	Ecan_set_baud(CAN_A,canbaud);

	return 1;
}

/**
* @fn Uint32 SelectCANBaudRate(char baud)
*
* @brief Select ECan baud rate 
*
* @author Andrei Mamtsev
*
* @param baud  baud rate param
*	0: 1,000,000
*	1: 500,000
*	2: 250,000
*	3: 125,000
*	4: 100,000
*	5: 50,000
*	6: 50,000
*	7: 50,000
*	8: 800,000
*
* @return CANBUS Baudrate 
*
* @date 22.12.2010
*/
Uint32 SelectCANBaudRate(long baud)
{

	Uint32 canbaud;

	switch(baud)
	{
        case 0:
            canbaud=ECANBR_1MBPS_VAL;
        	break;
		case 1:
			canbaud=ECANBR_500KBPS_VAL;
			break;
		case 2:
			canbaud=ECANBR_250KBPS_VAL;
			break;
		case 3:
			canbaud=ECANBR_125KBPS_VAL;
			break;
		case 4:
			canbaud=ECANBR_100KBPS_VAL;
			break;
		case 5:
			canbaud=ECANBR_50KBPS_VAL;
			break;
		case 6:
			canbaud=ECANBR_50KBPS_VAL;
			break;
		case 7:
			canbaud=ECANBR_50KBPS_VAL;
			break;
		case 8:
            canbaud=ECANBR_500KBPS_VAL;
            break;

	}
	return canbaud;
}
//Uint32 protocolParams[MAX_PROTOCOL_PARAMS];
void CanInit ()
{
    //CAN init


    // copy pdo objects from flash to object directory

    ObjDict_obj1005 = CanOpenObjectSp->obj1005_sync_cob_id;
    ObjDict_obj1006 = CanOpenObjectSp->obj1006_comm_cycle_period;
    ObjDict_obj1014 = CanOpenObjectSp->obj1014_emergency_cob_id;
    ObjDict_obj1016[0] = CanOpenObjectSp->obj1016_consumer_heartbeat;
    ObjDict_obj1017 = CanOpenObjectSp->obj1017_producer_heartbeat;

    ObjDict_obj1400_COB_ID_used_by_PDO = CanOpenObjectSp->RPdoComParam[0].COB_ID_OF_PDO;
    ObjDict_obj1400_Transmission_Type = CanOpenObjectSp->RPdoComParam[0].Transmission_Type;

    ObjDict_obj1401_COB_ID_used_by_PDO = CanOpenObjectSp->RPdoComParam[1].COB_ID_OF_PDO;
    ObjDict_obj1401_Transmission_Type = CanOpenObjectSp->RPdoComParam[1].Transmission_Type;

    ObjDict_obj1402_COB_ID_used_by_PDO = CanOpenObjectSp->RPdoComParam[2].COB_ID_OF_PDO;
    ObjDict_obj1402_Transmission_Type = CanOpenObjectSp->RPdoComParam[2].Transmission_Type;

    ObjDict_obj1403_COB_ID_used_by_PDO = CanOpenObjectSp->RPdoComParam[3].COB_ID_OF_PDO;
    ObjDict_obj1403_Transmission_Type = CanOpenObjectSp->RPdoComParam[3].Transmission_Type;


    ObjDict_obj1800_COB_ID_used_by_PDO  = CanOpenObjectSp->TPdoComParam[0].COB_ID_OF_PDO;
    ObjDict_obj1800_Compatibility_Entry = CanOpenObjectSp->TPdoComParam[0].Compatibility_Entry;
    ObjDict_obj1800_Inhibit_Time        = CanOpenObjectSp->TPdoComParam[0].Inhibit_Time;
    ObjDict_obj1800_Event_Timer         = CanOpenObjectSp->TPdoComParam[0].Event_Timer;
    ObjDict_obj1800_Transmission_Type   = CanOpenObjectSp->TPdoComParam[0].Transmission_Type;



    ObjDict_obj1801_COB_ID_used_by_PDO  = CanOpenObjectSp->TPdoComParam[1].COB_ID_OF_PDO;
    ObjDict_obj1801_Compatibility_Entry = CanOpenObjectSp->TPdoComParam[1].Compatibility_Entry;
    ObjDict_obj1801_Inhibit_Time        = CanOpenObjectSp->TPdoComParam[1].Inhibit_Time;
    ObjDict_obj1801_Event_Timer         = CanOpenObjectSp->TPdoComParam[1].Event_Timer;
    ObjDict_obj1801_Transmission_Type   = CanOpenObjectSp->TPdoComParam[1].Transmission_Type;



    ObjDict_obj1802_COB_ID_used_by_PDO  = CanOpenObjectSp->TPdoComParam[2].COB_ID_OF_PDO;
    ObjDict_obj1802_Compatibility_Entry = CanOpenObjectSp->TPdoComParam[2].Compatibility_Entry;
    ObjDict_obj1802_Inhibit_Time        = CanOpenObjectSp->TPdoComParam[2].Inhibit_Time;
    ObjDict_obj1802_Event_Timer         = CanOpenObjectSp->TPdoComParam[2].Event_Timer;
    ObjDict_obj1802_Transmission_Type   = CanOpenObjectSp->TPdoComParam[2].Transmission_Type;



    ObjDict_obj1803_COB_ID_used_by_PDO  = CanOpenObjectSp->TPdoComParam[3].COB_ID_OF_PDO;
    ObjDict_obj1803_Compatibility_Entry = CanOpenObjectSp->TPdoComParam[3].Compatibility_Entry;
    ObjDict_obj1803_Inhibit_Time        = CanOpenObjectSp->TPdoComParam[3].Inhibit_Time;
    ObjDict_obj1803_Event_Timer         = CanOpenObjectSp->TPdoComParam[3].Event_Timer;
    ObjDict_obj1803_Transmission_Type   = CanOpenObjectSp->TPdoComParam[3].Transmission_Type;


    ObjDict_highestSubIndex_obj1A00 = CanOpenObjectSp->PdoMappingTx.objEntry[0].highestSubIndex_obj ;
    memcpy(ObjDict_obj1A00,CanOpenObjectSp->PdoMappingTx.objEntry[0].obj,\
              (sizeof(ObjDict_obj1A00[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1A01 = CanOpenObjectSp->PdoMappingTx.objEntry[1].highestSubIndex_obj ;
    memcpy(ObjDict_obj1A01,CanOpenObjectSp->PdoMappingTx.objEntry[1].obj,\
              (sizeof(ObjDict_obj1A01[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1A02 = CanOpenObjectSp->PdoMappingTx.objEntry[2].highestSubIndex_obj ;
    memcpy(ObjDict_obj1A02,CanOpenObjectSp->PdoMappingTx.objEntry[2].obj,\
              (sizeof(ObjDict_obj1A02[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1A03 = CanOpenObjectSp->PdoMappingTx.objEntry[3].highestSubIndex_obj ;
    memcpy(ObjDict_obj1A03,CanOpenObjectSp->PdoMappingTx.objEntry[3].obj,\
              (sizeof(ObjDict_obj1A03[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1600 = CanOpenObjectSp->PdoMappingRx.objEntry[0].highestSubIndex_obj ;
    memcpy(ObjDict_obj1600,CanOpenObjectSp->PdoMappingRx.objEntry[0].obj,\
              (sizeof(ObjDict_obj1600[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1601 = CanOpenObjectSp->PdoMappingRx.objEntry[1].highestSubIndex_obj ;
    memcpy(ObjDict_obj1601,CanOpenObjectSp->PdoMappingRx.objEntry[1].obj,\
              (sizeof(ObjDict_obj1601[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1602 = CanOpenObjectSp->PdoMappingRx.objEntry[2].highestSubIndex_obj ;
    memcpy(ObjDict_obj1602,CanOpenObjectSp->PdoMappingRx.objEntry[2].obj,\
              (sizeof(ObjDict_obj1602[0]) * 4/*max number of entries*/));

    ObjDict_highestSubIndex_obj1603 = CanOpenObjectSp->PdoMappingRx.objEntry[3].highestSubIndex_obj ;
    memcpy(ObjDict_obj1603,CanOpenObjectSp->PdoMappingRx.objEntry[3].obj,\
              (sizeof(ObjDict_obj1603[0]) * 4/*max number of entries*/));
    // copy NMT State after Boot  from flash to object directory
    NMT_State_After_Boot = Param1.canOpen.NmtState;








    //InitECanGpio(ECAN_A);
  //  protocolParams[13]=0;
 //     Ecan_init(ECAN_A,(SelectCANBaudRate(protocolParams[13])) /*ECANBR_1MBPS_VAL*/);
    Ecan_init(ECAN_A,(SelectCANBaudRate(Param1.comm1.CanBaudRate)));
    Ecan_set_mailbox_6_7_9();

    initTimer();                                  // Start timer for the CANopen stack
    initializeTimer();                            // define all timres as free





    setNodeId (&ObjDict_Data,DeviceSp->CanNodeID);
    setState(&ObjDict_Data, Initialisation,No_Error);  // Init the state
    InitCallBackTable(&ObjDict_Data);//Initialize callback table for  objects

}
void canHandle()
{
    if (Ecan_rxmbrdy(ECAN_A)) // If a telegram was received in any of the configured Rx mailboxes
        {
             if (Ecan_getd(ECAN_A, &ecan_rx_packet)) // Read the CAN telegram, if several are pending read the one from the lowest mailbox number
             {
                 //DRV_LED_ON;
                 // Copy the received telegram from 'ecan_rx_packet' into 'm', which simply holds the most mandatory information
                 DataMatch(&ecan_rx_packet,&m);
                 // DRV_LED_ON;
                canDispatch(&ObjDict_Data, &m);         // process the received tgelegram
               // _sendPDOevent(&ObjDict_Data, TX_PDO_EVENT_TYPE_SYNC_TELEGRAM /*isSyncEvent*/ );
              //  DRV_LED_OFF;
             }

        }

        // Check if mailboxes for received were disabled or directed to transmit and clear the situation
        Ecan_Check_And_Repair_Static_MailBoxes(ECAN_A);

        Ecan_TX_Abort(ECAN_A);
        // Check if a message inside a Mailbox Tx buffer ran into a timeout and clear the situation
        // plus deactivate the timeout functionality for that Mailbox via setting the corresponding bit
        // inside the CAN timeout control register (CANTOC) to 0.
        Ecan_TimeOut(ECAN_A);
        // This function checks if a certain timer alarm event occurred and if so, a call-back function is
        // being called plus the follow-up timer event will be set up. The function checks if a TimerCounter
        // variable, which is incremented inside the MTS IRQ, has exceeded the next timer alarm threshold.
        TimerAlarm_Isr();
        //DRV_LED_OFF;
}
#define COMM_PROTECTION_FREQ_Hz 0.5
unsigned char nodeID=1;
#ifdef KUKU
int CAN_Ping_Ticker;
void CAN_Pingf(void)
{
    if (CAN_Ping_Ticker==1)
    {
        CanInit ();
        CAN_Ping_Ticker=0;

    }

    if(CAN_Ping_Ticker> (uint_least32_t)(ISR_FREQ / COMM_PROTECTION_FREQ_Hz))
    {
        CAN_Ping_Ticker=0;
        if(CAN_Ping_Init && ObjDict_Data.nodeState == Operational)
        {
            if(CAN_Ping)
                CAN_Ping&=0x0;
            else
            {
                 InitECanGpio(ECAN_A);
                 Ecan_init(ECAN_A,(SelectCANBaudRate(protocolParams[13])) /*ECANBR_1MBPS_VAL*/);
                 Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX+6, ((Uint32)nodeID), 0xFF000000, 0);//nodeID+0x300,0xFFF,
                 Ecan_set_rx_mailbox(ECAN_A, ECANA_FIRST_RX_MAILBOX+7, CMD_NMT, 0x00000000, 0);
                 Ecan_set_tx_mailbox(ECAN_A, MSG_GET_DATA_MAILBOX, (Uint32)nodeID+MSG_PDO2_TX, 0);

                  initTimer();                                // Start timer for the CANopen stack
                  setNodeId (&ObjDict_Data, nodeID);
                  setState(&ObjDict_Data, Initialisation,No_Error);  // Init the state
                  InitCommTable();

                CAN_Ping=1;
                CAN_Ping_Init=0;
            }
        }
    }

}
#endif
int CAN_Ping_Ticker=0;

void CanPlot()
{
    if (CAN_Ping_Ticker==1)
    {
        CanInit ();
        CAN_Ping_Ticker=0;

    }

    PlotSeqTransmit();
//    CAN_Pingf();
}
#endif
