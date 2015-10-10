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
 * Module : EduOM_CompactPage.c
 * 
 * Description : 
 *  EduOM_CompactPage() reorganizes the page to make sure the unused bytes
 *  in the page are located contiguously "in the middle", between the tuples
 *  and the slot array. 
 *
 * Exports:
 *  Four EduOM_CompactPage(SlottedPage*, Two)
 */


#include <string.h>
#include "EduOM_common.h"
#include "LOT.h"
#include "EduOM_Internal.h"



/*@================================
 * EduOM_CompactPage()
 *================================*/
/*
 * Function: Four EduOM_CompactPage(SlottedPage*, Two)
 * 
 * Description : 
 * (Following description is for original ODYSSEUS/COSMOS OM.
 *  For ODYSSEUS/EduCOSMOS EduOM, refer to the EduOM project manual.)
 *
 *  (1) What to do?
 *  EduOM_CompactPage() reorganizes the page to make sure the unused bytes
 *  in the page are located contiguously "in the middle", between the tuples
 *  and the slot array. To compress out holes, objects must be moved toward
 *  the beginning of the page.
 *
 *  (2) How to do?
 *  a. Save the given page into the temporary page
 *  b. FOR each nonempty slot DO
 *	Fill the original page by copying the object from the saved page
 *          to the data area of original page pointed by 'apageDataOffset'
 *	Update the slot offset
 *	Get 'apageDataOffet' to point the next moved position
 *     ENDFOR
 *   c. Update the 'freeStart' and 'unused' field of the page
 *   d. Return
 *	
 * Returns:
 *  error code
 *    eNOERROR
 *
 * Side Effects :
 *  The slotted page is reorganized to comact the space.
 */
Four EduOM_CompactPage(
    SlottedPage	*apage,		/* IN slotted page to compact */
    Two         slotNo)		/* IN slotNo to go to the end */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    SlottedPage	tpage;		/* temporay page used to save the given page */
    Object *obj;		/* pointer to the object in the data area */
    Two    apageDataOffset;	/* where the next object is to be moved */
    Four   len;			/* length of object + length of ObjectHdr */
    Two    lastSlot;		/* last non empty slot */
    Two    i;			/* index variable */

    

    return(eNOERROR);
    
} /* EduOM_CompactPage */
