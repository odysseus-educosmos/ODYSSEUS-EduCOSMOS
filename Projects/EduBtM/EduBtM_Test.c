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
 * Module: EduBtM_Test.c
 *
 * Description : 
 * Test the EduBtM and show the result of test.
 *
 * Exports:
 *  Four EduBtM_Test(Four, Four)
 */

#include <string.h>
#include "EduBtM_common.h"
#include "EduBtM_basictypes.h"
#include "EduBtM.h"
#include "EduBtM_TestModule.h"
#include "OM_Internal.h"


/*@================================
 * EduBtM_Test()
 *================================*/
/*
 * Function: EduBtM_Test(Four volId, Four handle)
 *
 * Description : 
 *  EduBtM_Test() tests EduBtM that implements the data structures 
 *  and operations of the object manager. The data structure is 
 *  composed of the root page, the internal page, and the leaf page. 
 *  There are the following five APIs in EduBtM. EduBtMM_CreateIndex(), 
 *  EduBtM_InsertObject(), EduOM_Fetch(), EduOM_FetchNext(), EduOM_DropIndex().
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four EduBtM_Test(Four volId, Four handle){
    FileID      fid;                                    /* file identifier */
    ObjectID    catalogEntry;                           /* catalog object */
	FILE		*fp;
	Four		score = 0;
	Four		scoreOpt = 0;
	Four		e;

	if ((fp = fopen("result.txt", "r")) == NULL){
		fprintf(stderr, "ERROR");
		return -1;
	}


    /* Create File */
    e = SM_CreateFile(volId, &fid, FALSE, NULL);
    if (e < eNOERROR) ERR(e);
    /* Get catalog entry */
    e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
    if (e < eNOERROR) ERR(e);

    e = edubtm_TestInt(&catalogEntry, fp, &score, &scoreOpt);
	if (e < eNOERROR) ERR(e);

    /* Destroy File */
    e = SM_DestroyFile(&fid, NULL);
    if (e < eNOERROR) ERR(e);

    /* Create File */
	e = SM_CreateFile(volId, &fid, FALSE, NULL);
	if (e < eNOERROR) ERR(e);
	
	/* Get catalog entry */
	e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
	if (e < eNOERROR) ERR(e);

    e = edubtm_TestVarchar(&catalogEntry, fp, &score, &scoreOpt);
	if (e < eNOERROR) ERR(e);

	/* Destroy File */
	e = SM_DestroyFile(&fid, NULL);
	if (e < eNOERROR) ERR(e);

	fclose(fp);

    return eNOERROR;

}

