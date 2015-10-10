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
 * Module: EduBtM_InsertObject.c
 *
 * Description :
 *  Insert an ObjectID 'oid' into a Btree whose key value is 'kval'. 
 *
 * Exports:
 *  Four EduBtM_InsertObject(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Pool*, DeallocListElem*)
 */


#include "EduBtM_common.h"
#include "BfM.h"
#include "EduBtM_Internal.h"
#include "OM_Internal.h"



/*@================================
 * EduBtM_InsertObject() 
 *================================*/
/*
 * Function: Four EduBtM_InsertObject(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Pool*, DeallocListElem*)
 * 
 * Description :
 * (Following description is for original ODYSSEUS/COSMOS BtM.
 *  For ODYSSEUS/EduCOSMOS EduBtM, refer to the EduBtM project manual.)
 *
 *  Insert an ObjectID 'oid' into a Btree whose key value is 'kval'. 
 *  If an overflow page is created as the result of the insert, it may occur
 *  merging or redistibuting two leaves and this may affect the root.
 *
 * Returns:
 *  error code
 *    eBADPARAMETER_BTM
 *    some errors caused by function calls
 */
Four EduBtM_InsertObject(
    ObjectID *catObjForFile,	/* IN catalog object of B+ tree file */
    PageID   *root,		/* IN the root of Btree */
    KeyDesc  *kdesc,		/* IN key descriptor */
    KeyValue *kval,		/* IN key value */
    ObjectID *oid,		/* IN ObjectID which will be inserted */
    Pool     *dlPool,		/* INOUT pool of dealloc list */
    DeallocListElem *dlHead) /* INOUT head of the dealloc list */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    int i;
    Four e;			/* error number */
    Boolean lh;			/* for spliting */
    Boolean lf;			/* for merging */
    InternalItem item;		/* Internal Item */
    SlottedPage *catPage;	/* buffer page containing the catalog object */
    sm_CatOverlayForBtree *catEntry; /* pointer to Btree file catalog information */
    PhysicalFileID pFid;	 /* B+-tree file's FileID */

    
    /*@ check parameters */
    
    if (catObjForFile == NULL) ERR(eBADPARAMETER_BTM);
    
    if (root == NULL) ERR(eBADPARAMETER_BTM);

    if (kdesc == NULL) ERR(eBADPARAMETER_BTM);

    if (kval == NULL) ERR(eBADPARAMETER_BTM);

    if (oid == NULL) ERR(eBADPARAMETER_BTM);    

    /* Error check whether using not supported functionality by EduBtM */
    for(i=0; i<kdesc->nparts; i++)
    {
        if(kdesc->kpart[i].type!=SM_INT && kdesc->kpart[i].type!=SM_VARSTRING)
            ERR(eNOTSUPPORTED_EDUBTM);
    }
    
    
    return(eNOERROR);
    
}   /* EduBtM_InsertObject() */
