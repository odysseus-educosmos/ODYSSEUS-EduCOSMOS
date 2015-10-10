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
 * Module : EduOM_ReadObject.c
 * 
 * Description : 
 *  EduOM_ReadObject() causes data to be read from the object identified by 'oid'
 *  into the user specified buffer 'buf'.
 *
 * Exports:
 *  Four EduOM_ReadObject(ObjectID*, Four, Four, char*)
 */


#include <string.h>
#include "EduOM_common.h"
#include "BfM.h"		/* for the buffer manager call */
#include "LOT.h"		/* for the large object manager call */
#include "EduOM_Internal.h"



/*@================================
 * EduOM_ReadObject()
 *================================*/
/*
 * Function: Four EduOM_ReadObject(ObjectID*, Four, Four, char*)
 * 
 * Description : 
 * (Following description is for original ODYSSEUS/COSMOS OM.
 *  For ODYSSEUS/EduCOSMOS EduOM, refer to the EduOM project manual.)
 *
 *  (1) What to do?
 *  EduOM_ReadObject() causes data to be read from the object identified by 'oid'
 *  into the user specified buffer 'buf'. The byte range to be read are
 *  specified by start position 'start' and the number of bytes 'length'.
 *  The 'length' bytes from 'start' are copied from the disk to the user buffer
 *  'buf'. eIf 'length' is REMAINDER, the data from 'start' to end of the
 *  object are to be read(In this case we assume 'buf' can accomadate bytes
 *  to be read).
 *  This routine returns the number of bytes to read.
 *
 *  (2) How to do?
 *  a. Read in the slotted page
 *  b. See the object header
 *  c. IF moved object THEN
 *	   call this routine recursively with the forwarded object's identifier
 *     ELSE 
 *	   IF large object THEN 
 *             call the large object manager's LOT_ReadObject()
 *	   ELSE 
 *	       copy the data into the user buffer 'buf'
 *	   ENDIF
 *     ENDIF
 *  d. Free the buffer page
 *  e. Return
 *
 * Returns:
 *  1) number of bytes actually read (values greater than or equal to 0)
 *  2) Error Code (negative values)
 *    eBADOBJECTID_OM
 *    eBADLENGTH_OM
 *    eBADUSERBUF_OM
 *    eBADSTART_OM
 *    some errors caused by function calls
 */
Four EduOM_ReadObject(
    ObjectID 	*oid,		/* IN object to read */
    Four     	start,		/* IN starting offset of read */
    Four     	length,		/* IN amount of data to read */
    char     	*buf)		/* OUT user buffer to return the read data */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four     	e;              /* error code */
    PageID 	pid;		/* page containing object specified by 'oid' */
    SlottedPage	*apage;		/* pointer to the buffer of the page  */
    Object	*obj;		/* pointer to the object in the slotted page */
    Four	offset;		/* offset of the object in the page */

    
    
    /*@ check parameters */

    if (oid == NULL) ERR(eBADOBJECTID_OM);

    if (length < 0 && length != REMAINDER) ERR(eBADLENGTH_OM);
    
    if (buf == NULL) ERR(eBADUSERBUF_OM);

    

    return(length);
    
} /* EduOM_ReadObject() */
