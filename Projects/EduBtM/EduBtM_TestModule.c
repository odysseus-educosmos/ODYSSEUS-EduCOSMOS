/******************************************************************************/
/*                                                                            */
/*    ODYSSEUS/EduCOSMOS Educational-Purpose Object Storage System            */
/*                                                                            */
/*    Developed by Professor Kyu-Young Whang et al.                           */
/*                                                                            */
/*    Database and Multimedia Laboratory                                      */
/*                                                                            */
/*    Computer Science Department and                                         */
/*    Advanced Information Technology Research Center (AITrc)                 */
/*    Korea Advanced Institute of Science and Technology (KAIST)              */
/*                                                                            */
/*    e-mail: kywhang@cs.kaist.ac.kr                                          */
/*    phone: +82-42-350-7722                                                  */
/*    fax: +82-42-350-8380                                                    */
/*                                                                            */
/*    Copyright (c) 1995-2013 by Kyu-Young Whang                              */
/*                                                                            */
/*    All rights reserved. No part of this software may be reproduced,        */
/*    stored in a retrieval system, or transmitted, in any form or by any     */
/*    means, electronic, mechanical, photocopying, recording, or otherwise,   */
/*    without prior written permission of the copyright owner.                */
/*                                                                            */
/******************************************************************************/
/*
 * Module: EduBtM_TestModule.c
 *
 * Description : 
 *  Main routine of EduBtM Test Module
 *
 */

#include <stdlib.h>
#include "EduBtM_common.h"
#include "EduBtM_Internal.h"
#include "EduBtM_TestModule.h"


Four main()
{

	Four	e;									/* for errors */
	Four 	i;									/* loop index */
	Four	handle;								/* system handle */
	Four	numDevices = 0;						/* # of devices which consists formated volume */
	char 	*devNames[MAX_DEVICES_IN_VOLUME];	/* device name */
	char 	*title;								/* volume title */
	Four 	volId;								/* volume identifier */
	Two 	extSize;							/* size of an extent */
	Four 	numPagesInDevices[MAX_DEVICES_IN_VOLUME];/* # of pages in the each devices */
	Four 	segmentSize;						/* size of a segment */
	XactID 	xactId;								/* transaction identifier */

	/*
	 *   Initialize the storage system 
	 */
	/* Initialize miniCOSMOS */
	e = LRDS_Init();
	if (e < eNOERROR){
		printf("LRDS_Init failed!!!\n");
		exit(1);
	}
	
	
	/* Allocate handle */
	e = LRDS_AllocHandle(&handle);
	if (e < eNOERROR) {
		printf("LRDS_AllocHandle failed!!!\n");
		LRDS_Final();
		exit(1);
	}
	

	/* Initialize the variable for LRDS_FormatDataVolume */
	numDevices = 1;
	devNames[0] = "testsolution.vol";
	title = "test";
	volId = 1000;
	extSize = 16;
	numPagesInDevices[0] = 5000;
	segmentSize = 16;

	/*
	 *  Format volume
	 */
    e = LRDS_FormatDataVolume(numDevices, devNames, title, volId, extSize, numPagesInDevices, segmentSize);
	if (e < eNOERROR) {
		printf("LRDS_FormatDataVolume failed!!!\n");
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}

	/*  Mount volume */
	e = LRDS_Mount(numDevices, devNames, &volId);
	if (e < eNOERROR){
		printf("LRDS_Mount failed!!!\n");
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}

	
	/* Begin Transaction */
	e = LRDS_BeginTransaction(&xactId, X_RR_RR);
	if (e < eNOERROR){
		LRDS_Dismount(volId);
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}
	
	/* Test miniBtM */
	e = EduBtM_Test(volId, handle);
	if (e < eNOERROR){
		printf("EduBtM_Test failed!!!\n%d\n", e);
		LRDS_AbortTransaction(&xactId);
		LRDS_Dismount(volId);
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}

	/* Commit Transaction */
	e = LRDS_CommitTransaction(&xactId);
	if (e < eNOERROR){
		printf("LRDS_CommitTransaction failed!!!\n");
		LRDS_Dismount(volId);
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}

	/* Dismount volume */
	e= LRDS_Dismount(volId);
	if (e < eNOERROR){
		printf("LRDS_Dismount failed!!!\n");
		LRDS_FreeHandle(handle);
		LRDS_Final();
		exit(1);
	}

	/* Free Handle */
	e = LRDS_FreeHandle(handle);
	if (e < eNOERROR) {
		printf("LRDS_FreeHandle failed!!!\n");
		LRDS_Final();
		exit(1);
	}

	/* Finalize miniCOSMOS */
	e = LRDS_Final();
	if (e < eNOERROR) {
		printf("LRDS_Final failed!!!\n");
		exit(1);
	}
	
	return 0;
}
