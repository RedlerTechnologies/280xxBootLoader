/**
* @file descriptor.h
* @brief Brief description
*        Brief description continued
* 
* Detailed description starts here
*
** @author Shlomi Dar
* @author Eli Schneider
*
* @version Version number
* @date 6 באפר׳ 2017
* @copyright (C)2017 Redler Technologies Ltd.
*
*
*
*/

/* Includes --------------------------------------------------------------------------------------*/
#ifdef F2803x_PRE_DEF
#include "DSP2803x_Device.h"
#endif

#ifdef F2806x_PRE_DEF
#include "F2806x_Device.h"
#endif


/* Private variables -----------------------------------------------------------------------------*/


/*typedefs -------------------------------------------------------------------------------------- */


/* defines ---------------------------------------------------------------------------------------*/
/***********Software Rev***************/
#define SW_MAJOR	 00
#define SW_MINOR	 02
#define SW_SUBMINOR	 01
#define SW_PATCH 	 26

#define LOADER_VER (SW_MAJOR*1000000L+SW_MINOR*10000L+SW_SUBMINOR*100L+SW_PATCH)


/***********HW Rev***************/
#define HW_MAJOR     00
#define HW_MINOR     01
#define HW_SUBMINOR  01
#define HW_PATCH     01

#define HW_REV (HW_MAJOR*1000000L+HW_MINOR*10000L+HW_SUBMINOR*100L+HW_PATCH)

/***********Serial Number***************/
#define DEF_SERIAL 0x00000000



/* macros ----------------------------------------------------------------------------------------*/


/* function prototypes --------------------------------------------------------------------------*/
void InitBootLoader(); //asm function
Uint32 LoaderBoot();


/* variable prototypes --------------------- -----------------------------------------------------*/


extern volatile struct sAppInterfaceTable appDesc;
extern volatile const struct sLoaderInterfaceTable loaderDesc;


#ifndef APPLICATIONDESC_H_
#define APPLICATIONDESC_H_


struct sHwParameters //size 16bit x 16
{
    float Rsense;
    float maxContCurrent;
    float maxPeakCurrent;
    float maxPeakTime;
    float maxUartBaud;
    float maxSsiBaud;
    Uint32 reserved[10];
    //float gainIb;
    //float gainIc;
};

struct sLoaderInterfaceTable //size 16bit x 64
{
    Uint32 version;        /* loader version */
    Uint32 loaderChecksum; /* Loader program checksum */
    void (*entry)();       /* Loader entry point */
    Uint32 hw_rev;         /* hardware version */
    Uint32 serial;         /* unit serial number */
    Uint32 partNamber;     /* unit part number */
    Uint32 productionDate; /* production date week year WWYYYY*/
    Uint32 LOT;            /* LOT number */
    Uint16 techCode;       /* Technician code*/
    Uint16 FactoryCode;    /* Factory code*/
    Uint32 reserved[7];
    struct sHwParameters hwParams;
};



struct sAppInterfaceTable
{
	Uint32 version; 		/* application version */
	Uint32 programChecksum;	/* application program checksum */
	void (*entry)();		/* application entry point */
};

Uint32 checkAppBoot();
void callBootLoader();
void callMain();
void InitBoot();

#ifdef __cplusplus
extern "C" {
#endif
 

#ifdef __cplusplus
}
#endif

#endif /* APPLICATIONLOAD_H_ */
