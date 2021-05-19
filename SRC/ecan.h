/**
* @file ecandrv.h
* @brief driver for ECan
*
* @author Mamtsev Andrei
*
* @version 0.0.1
* @date 18.07.2010
*/

#ifndef __ECAN_H
#define __ECAN_H


#define MAX_PROTOCOL_PARAMS             15      /**< Maximum number of communication protocol parameters */

#define ECAN_A	0
#if DSP28_CANB
#define ECAN_B	1
#define ECAN_CHANNELS	2
#else
#define ECAN_CHANNELS	1
#endif

#ifndef ECANA_RX_MAILBOXES
#define ECANA_RX_MAILBOXES	9 //8
#endif

#ifndef ECANA_STATIC_TX_MAILBOXES
#define ECANA_STATIC_TX_MAILBOXES	1 //_1
#endif

#ifndef ECANA_DYNAMIC_TX_MAILBOXES
#define ECANA_DYNAMIC_TX_MAILBOXES	20//10//23
#endif

#define ECANA_FIRST_RX_MAILBOX	0
#define ECANA_FIRST_STATIC_TX_MAILBOX	(ECANA_FIRST_RX_MAILBOX+ECANA_RX_MAILBOXES)
#define	ECANA_FIRST_DYNAMIC_TX_MAILBOX (ECANA_FIRST_STATIC_TX_MAILBOX+ECANA_STATIC_TX_MAILBOXES)

#define ECANA_DYNAMYC_TX_MAILBOX_MASK ((~((0xFFFFFFFFL)<<ECANA_DYNAMIC_TX_MAILBOXES))<<ECANA_FIRST_DYNAMIC_TX_MAILBOX)

/*
** Rx Identifiers
*/
#define CMD_NMT				0x000
#define CMD_SYNC			0x080
#define CMD_TIME_STAMP		0x100
#define CMD_EMERGENCY		0x080
#define CMD_PDO1_RX			0x200
#define CMD_PDO2_RX			0x300
#define CMD_PDO3_RX			0x400
#define CMD_PDO4_RX			0x500
#define CMD_SDO_RX			0x600
#define CMD_ERROR_CONTROL	0x700

/*
** Tx Identifiers
*/
#define MSG_RESET 		0x080
#define MSG_LOGX1_ALL	0x200
#define MSG_LOGX4_CH0	0x300
#define MSG_LOGX4_CH1	0x400
#define MSG_LOGX4_CH2	0x500
#define MSG_LOGX4_CH3	0x600

#define MSG_LOG_READ	0x700
#define MSG_SET_RESP_LOCAL	0x114
#define MSG_SET_RESP_REMOTE	0x115
#define MSG_SET_DATA_ACK 	0x116
#define MSG_GET_DATA	0x117

#define MSG_NMT				0x000
#define MSG_SYNC			0x080
#define MSG_TIME_STAMP		0x100
#define MSG_EMERGENCY		0x080
#define MSG_PDO1_TX			0x180
#define MSG_PDO2_TX			0x280
#define MSG_PDO3_TX			0x380
#define MSG_PDO4_TX			0x480
#define MSG_SDO_TX			0x580
#define MSG_ERROR_CONTROL	0x700


#define MSG_GET_DATA_MAILBOX ECANA_FIRST_STATIC_TX_MAILBOX

struct sEcanLData
{
	Uint32	MDL;
	Uint32	MDH;
};

// applicable when DBO=0
struct sEcanW0Data
{
	Uint16	w23;
	Uint16	w01;
	Uint16	w67;
	Uint16	w45;
};

// applicable when DBO=1
struct sEcanW1Data
{
	Uint16	w10;
	Uint16	w32;
	Uint16	w67;
	Uint16	w45;
};

// applicable when DBO=0
struct sEcanC0Data
{
	Uint16	b3:8;
	Uint16	b2:8;
	Uint16	b1:8;
	Uint16	b0:8;
	Uint16	b7:8;
	Uint16	b6:8;
	Uint16	b5:8;
	Uint16	b4:8;
};

// applicable when DBO=1
struct sEcanC1Data
{
	Uint16	b0:8;
	Uint16	b1:8;
	Uint16	b2:8;
	Uint16	b3:8;
	Uint16	b4:8;
	Uint16	b5:8;
	Uint16	b6:8;
	Uint16	b7:8;
};

union uEcanData
{
	Uint32 all[2];
	struct sEcanLData l;
	struct sEcanW0Data w0;		// for dbo=0
	struct sEcanW1Data w1;		// for dbo=1
	struct sEcanC0Data c0;		// for dbo=0
	struct sEcanC1Data c1;		// for dbo=1
};

struct sEcanMsgCtl
{
	Uint16	dlc:4;			// data length control;
	Uint16	tpl:3;			// transmission priority level - tx only
	Uint16	rtr:1;			// remote frame - tx only
	Uint16	ext:1;			// extended address
	Uint16	dbo:1;			// data byte order in the packet 
	Uint16	moto:1;			// message output timeout - tx only
	Uint16	dev:1;			// source device - rx only		
	Uint16	rsvd:4;		
};

union uEcanMsgCtl
{
	Uint16 all;
	struct sEcanMsgCtl bit;
};

typedef struct sEcanRxPacket
{
	int16	mbox_id;		// 0-31 mailbox id 
	union uEcanMsgCtl Ctl;
	Uint32	TimeStamp;		// message timestamp in bit times
	Uint32	MsgId;
	union uEcanData	data;
} ECAN_RX_PACKET;

typedef struct sEcanTxPacket
{
	int16	mbox_id;		// 0-31 = specific mailbox id, -1 = allocate a mailbbox 
	union uEcanMsgCtl Ctl;
	Uint32	TimeOut;		// message timeout in bit times
	Uint32	MsgId;
	union uEcanData	data;
} ECAN_TX_PACKET;

typedef struct sEcanError
{
	Uint32	TimeOut;		// message timeout in bit times
	Uint32	TXAbort;
} ECAN_ERROR_COUNT;


/**
 * @brief The CAN message structure
 * @ingroup can
 */
typedef struct {
    Uint16 cob_id; /**< message's ID */
    Uint16 rtr:8;     /**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
    Uint16 len:8;     /**< message's length (0 to 8) */
    Uint16 data[8]; /**< message's datas */
} Message;

/*
 *  ECANHW_Handle is an opaque pointer.  Individual implementations of ECANHW
 *  will define ECANHW_Obj differently.  ECANHW_Obj is a private structure and
 *  details are intentionally hidden.
 */
//typedef struct ECANHW_Obj *ECANHW_Handle;       /* opaque pointer */

#ifdef __cplusplus
extern "C" {
#endif

#define ECANBR_1MBPS_VAL	0x000200CBL  //CANTC => (SUSCLK/2)/((BRPreg+1)*(TSeg1+1)+(TSeg2+1))
#define ECANBR_500KBPS_VAL  0x000500CBL  // TSeg1>>TSeg2
#define ECANBR_250KBPS_VAL	0x000B00CBL
#define ECANBR_125KBPS_VAL	0x001700CBL
#define ECANBR_100KBPS_VAL	0x001D00CBL
#define ECANBR_50KBPS_VAL	0x003B00CBL
#define ECANBR_20KBPS_VAL	0x009500CBL
#define ECANBR_10KBPS_VAL	0x002CC0FFL


//void InitECanGpio(Uint16 dev_id);
void InitECanA(Uint32 canbtc);
void Ecan_init(Uint16 dev_id, Uint32 canbtc);
void Ecan_set_baud(Uint16 dev_id, Uint32 canbtc);
void Ecan_set_lam(Uint16 dev_id, Uint16 mbox_id, Uint32 mask);
void Ecan_set_rx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint32 mask, Uint16 ext);
void Ecan_set_tx_mailbox(Uint16 dev_id, Uint16 mbox_id, Uint32 MsgId, Uint16 ext);
void Ecan_disable_mailbox(Uint16 dev_id, Uint16 mbox_id);
int16 Ecan_getd(Uint16 dev_id, struct sEcanRxPacket *rx_packet);
int16 Ecan_putd(Uint16 dev_id, struct sEcanTxPacket *tx_packet);

int16 Ecan_rxmbrdy(Uint16 dev_id);
//unsigned char canSend(CAN_PORT notused, Message *m);
//unsigned char canSend1(CAN_PORT notused, Message *m);
//unsigned char canSendAB(CAN_PORT notused, Message *m);
//unsigned char canSendCD(CAN_PORT notused, Message *m);
//unsigned char canSendFT(CAN_PORT notused, Message *m);
//void DataMatch(ECAN_RX_PACKET *ecan_rx_packet,Message *m);
int16 Ecan_error(Uint16 dev_id);
int16 Ecan_TX_Abort(Uint16 dev_id);
int16 Ecan_TimeOut(Uint16 dev_id);
Uint32 SelectCANBaudRate(long baud);
void CanInit ();
void canHandle();
void CanPlot();
extern ECAN_TX_PACKET	ecan_tx_packet;
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif

