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
 * Module : EduOM_CreateObject.c
 * 
 * Description :
 *  EduOM_CreateObject() creates a new object near the specified object.
 *
 * Exports:
 *  Four EduOM_CreateObject(ObjectID*, ObjectID*, ObjectHdr*, Four, char*, ObjectID*)
 */


#include "EduOM_common.h"
#include "EduOM_Internal.h"



/*@================================
 * EduOM_CreateObject()
 *================================*/
/*
 * Function: Four EduOM_CreateObject(ObjectID*, ObjectID*, ObjectHdr*, Four, char*, ObjectID*)
 * 
 * Description :
 * (Following description is for original ODYSSEUS/COSMOS OM.
 *  For ODYSSEUS/EduCOSMOS EduOM, refer to the EduOM project manual.)
 *
 * (1) What to do?
 * EduOM_CreateObject() creates a new object near the specified object.
 * If there is no room in the page holding the specified object,
 * it trys to insert into the page in the available space list. If fail, then
 * the new object will be put into the newly allocated page.
 *
 * (2) How to do?
 *	a. Read in the near slotted page
 *	b. See the object header
 *	c. IF large object THEN
 *	       call the large object manager's lom_ReadObject()
 *	   ELSE 
 *		   IF moved object THEN 
 *				call this function recursively
 *		   ELSE 
 *				copy the data into the buffer
 *		   ENDIF
 *	   ENDIF
 *	d. Free the buffer page
 *	e. Return
 *
 * Returns:
 *  error code
 *    eBADCATALOGOBJECT_OM
 *    eBADLENGTH_OM
 *    eBADUSERBUF_OM
 *    some error codes from the lower level
 *
 * Side Effects :
 *  0) A new object is created.
 *  1) parameter oid
 *     'oid' is set to the ObjectID of the newly created object.
 */
Four EduOM_CreateObject(
    ObjectID  *catObjForFile,	/* IN file in which object is to be placed */
    ObjectID  *nearObj,		/* IN create the new object near this object */
    ObjectHdr *objHdr,		/* IN from which tag is to be set */
    Four      length,		/* IN amount of data */
    char      *data,		/* IN the initial data for the object */
    ObjectID  *oid)		/* OUT the object's ObjectID */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four        e;		/* error number */
    ObjectHdr   objectHdr;	/* ObjectHdr with tag set from parameter */


    /*@ parameter checking */
    
    if (catObjForFile == NULL) ERR(eBADCATALOGOBJECT_OM);
    
    if (length < 0) ERR(eBADLENGTH_OM);

    if (length > 0 && data == NULL) return(eBADUSERBUF_OM);

	/* Error check whether using not supported functionality by EduOM */
	if(ALIGNED_LENGTH(length) > LRGOBJ_THRESHOLD) ERR(eNOTSUPPORTED_EDUOM);
    

    
    return(eNOERROR);
}
