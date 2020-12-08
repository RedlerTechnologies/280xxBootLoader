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
#define SW_PATCH 	 24

#define LOADER_VER (SW_MAJOR*1000000L+SW_MINOR*10000L+SW_SUBMINOR*100L+SW_PATCH)


/***********HW Rev***************/
#define HW_MAJOR     00
#define HW_MINOR     01
#define HW_SUBMINOR  01
#define HW_PATCH     01

#define HW_REV (HW_MAJOR*1000000L+HW_MINOR*10000L+HW_SUBMINOR*100L+HW_PATCH)

/***********Serial Number***************/
#define DEF_SERIAL 0x00000000

/***********Unit Numbers***************/
#define DEF_NUM1 1
#define DEF_NUM2 2
#define DEF_NUM3 3

/* macros ----------------------------------------------------------------------------------------*/


/* function prototypes --------------------------------------------------------------------------*/
void InitBootLoader(); //asm function
Uint32 LoaderBoot();


/* variable prototypes --------------------- -----------------------------------------------------*/


extern volatile struct sAppInterfaceTable appDesc;
extern volatile const struct sLoaderInterfaceTable loaderDesc;


#ifndef APPLICATIONDESC_H_
#define APPLICATIONDESC_H_



struct sLoaderInterfaceTable
{
    Uint32 version;        /* loader version */
    Uint32 programChecksum;/* application program checksum */
    void (*entry)();       /* Loader entry point */
    Uint32 hw_rev;         /* hardware version */
    Uint32 serial;         /* unit serial number */
    Uint32 unit_num1;            /* unit number1 */
    Uint32 unit_num2;            /* unit number2 */
    Uint32 unit_num3;            /* unit number2 */
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
