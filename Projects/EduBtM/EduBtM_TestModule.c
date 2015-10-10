/******************************************************************************/
/*                                                                            */
/*    Copyright (c) 2013-2015, Kyu-Young Whang, KAIST                         */
/*    All rights reserved.                                                    */
/*                                                                            */
/*    Redistribution and use in source and binary forms, with or without      */
/*    modification, are permitted provided that the following conditions      */
/*    are met:                                                                */
/*                                                                            */
/*    1. Redistributions of source code must retain the above copyright       */
/*       notice, this list of conditions and the following disclaimer.        */
/*                                                                            */
/*    2. Redistributions in binary form must reproduce the above copyright    */
/*       notice, this list of conditions and the following disclaimer in      */
/*       the documentation and/or other materials provided with the           */
/*       distribution.                                                        */
/*                                                                            */
/*    3. Neither the name of the copyright holder nor the names of its        */
/*       contributors may be used to endorse or promote products derived      */
/*       from this software without specific prior written permission.        */
/*                                                                            */
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     */
/*    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       */
/*    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       */
/*    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          */
/*    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,    */
/*    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;        */
/*    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER        */
/*    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT      */
/*    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN       */
/*    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE         */
/*    POSSIBILITY OF SUCH DAMAGE.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*    ODYSSEUS/EduCOSMOS Educational Purpose Object Storage System            */
/*    (Version 1.0)                                                           */
/*                                                                            */
/*    Developed by Professor Kyu-Young Whang et al.                           */
/*                                                                            */
/*    Advanced Information Technology Research Center (AITrc)                 */
/*    Korea Advanced Institute of Science and Technology (KAIST)              */
/*                                                                            */
/*    e-mail: odysseus.educosmos@gmail.com                                    */
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
	numPagesInDevices[0] = 500;
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
		printf("EduBtM_Test failed!!!\n");
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
