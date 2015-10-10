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
 * Module: EduOM_NextObject.c
 *
 * Description:
 *  Return the next Object of the given Current Object. 
 *
 * Export:
 *  Four EduOM_NextObject(ObjectID*, ObjectID*, ObjectID*, ObjectHdr*)
 */


#include "EduOM_common.h"
#include "BfM.h"
#include "EduOM_Internal.h"

/*@================================
 * EduOM_NextObject()
 *================================*/
/*
 * Function: Four EduOM_NextObject(ObjectID*, ObjectID*, ObjectID*, ObjectHdr*)
 *
 * Description:
 * (Following description is for original ODYSSEUS/COSMOS OM.
 *  For ODYSSEUS/EduCOSMOS EduOM, refer to the EduOM project manual.)
 *
 *  Return the next Object of the given Current Object.  Find the Object in the
 *  same page which has the current Object and  if there  is no next Object in
 *  the same page, find it from the next page. If the Current Object is NULL,
 *  return the first Object of the file.
 *
 * Returns:
 *  error code
 *    eBADCATALOGOBJECT_OM
 *    eBADOBJECTID_OM
 *    some errors caused by function calls
 *
 * Side effect:
 *  1) parameter nextOID
 *     nextOID is filled with the next object's identifier
 *  2) parameter objHdr
 *     objHdr is filled with the next object's header
 */
Four EduOM_NextObject(
    ObjectID  *catObjForFile,	/* IN informations about a data file */
    ObjectID  *curOID,		/* IN a ObjectID of the current Object */
    ObjectID  *nextOID,		/* OUT the next Object of a current Object */
    ObjectHdr *objHdr)		/* OUT the object header of next object */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four e;			/* error */
    Two  i;			/* index */
    Four offset;		/* starting offset of object within a page */
    PageID pid;			/* a page identifier */
    PageNo pageNo;		/* a temporary var for next page's PageNo */
    SlottedPage *apage;		/* a pointer to the data page */
    Object *obj;		/* a pointer to the Object */
    PhysicalFileID pFid;	/* file in which the objects are located */
    SlottedPage *catPage;	/* buffer page containing the catalog object */
    sm_CatOverlayForData *catEntry; /* data structure for catalog object access */



    /*@
     * parameter checking
     */
    if (catObjForFile == NULL) ERR(eBADCATALOGOBJECT_OM);
    
    if (nextOID == NULL) ERR(eBADOBJECTID_OM);



    return(EOS);		/* end of scan */
    
} /* EduOM_NextObject() */
