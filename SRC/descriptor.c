/**
* @file descriptor.c
* @brief Brief description
*        Brief description continued
* 
* Detailed description starts here
*
* @author Shlomi Dar
*
* @version Version number
* @date 6 באפר׳ 2017
* @copyright (C)2017 Redler Technologies Ltd.
*
*
*	Application descriptor tells loader what is program checksum
*	and what is the application entry point
*/
#include "descriptor.h"
#include "flashcheck.h"


extern void c_int00(void);






Uint32 unit_num1;            /* unit number1 */
Uint32 unit_num2;            /* unit number2 */
Uint32 unit_num3;            /* unit number2 */
/***********Loader descriptor********************/
#pragma DATA_SECTION(loaderDesc, ".loaderDesc");
volatile const struct sLoaderInterfaceTable loaderDesc=
			{
                LOADER_VER,/* loader version */
                0xFFFFFFFF, // loader Checksum
                /*(void (*)())*/c_int00, // /* loader entry point */
			    HW_REV,/* hardware version */
			    DEF_SERIAL,/* unit serial number */
			    DEF_NUM1,/* unit number1 */
			    DEF_NUM2,/* unit number2 */
			    DEF_NUM3/* unit number3 */
			};

/************Main Application descriptor*****************/

#pragma DATA_SECTION(appDesc, ".appDesc");
volatile struct sAppInterfaceTable appDesc;




Uint32 checkAppBoot()
{

	if (overallProgramFlashTest()) //Program corrupted => return loader.
		return (Uint32)loaderDesc.entry;

	if (((Uint32)appDesc.entry)==0xFFFFFFFF) //Application descriptor erased => return loader.
		return (Uint32)loaderDesc.entry;


	return (Uint32)appDesc.entry; //All OK => return application descriptor
}


Uint32 LoaderBoot()
{
	return (Uint32)loaderDesc.entry;
}

void callBootLoader()
{
	InitBootLoader();
}

void callMain()
{
	InitBoot();
}





