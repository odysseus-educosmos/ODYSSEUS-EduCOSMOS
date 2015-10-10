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
 * Module: edubtm_InitPage.c
 *
 * Description :
 *  This file has three functions which initialize Btree pages.  A Btree page
 *  should be initialized by one of these functions before it is used.
 *
 * Exports:
 *  Four edubtm_InitInternal(PageID*, Boolean)
 *  Four edubtm_InitLeaf(PageID*, Boolean)
 */


#include "EduBtM_common.h"
#include "BfM.h"
#include "EduBtM_Internal.h"



/*@================================
 * edubtm_InitInternal()
 *================================*/
/*
 * Function: Four edubtm_InitInternal(PageID*, Boolean)
 *
 * Description:
 * (Following description is for original ODYSSEUS/COSMOS BtM.
 *  For ODYSSEUS/EduCOSMOS EduBtM, refer to the EduBtM project manual.)
 *
 *  Initialize as an internal page.  If 'root' is TRUE, this page may be
 *  initialized as a root.
 *
 * Returns:
 *  Error code
 *    some errors caused by function calls
 */
Four edubtm_InitInternal(
    PageID  *internal,		/* IN the PageID to be initialized */
    Boolean root,		/* IN Is it root ? */
    Boolean isTmp)              /* IN Is it temporary ? - COOKIE12FEB98 */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four e;			/* error number */
    BtreeInternal *page;	/* a page pointer */


    
    return(eNOERROR);
    
}  /* edubtm_InitInternal() */



/*@================================
 * edubtm_InitLeaf()
 *================================*/
/*
 * Function: Four edubtm_InitLeaf(PageID*, Boolean)
 *
 * Description:
 * (Following description is for original ODYSSEUS/COSMOS BtM.
 *  For ODYSSEUS/EduCOSMOS EduBtM, refer to the EduBtM project manual.)
 *
 *  Initialize as a leaf page. If 'root' is TRUE, this page may be initialize
 *  as a root.
 *
 * Returns:
 *  Error code
 *    some errors caused by function calls
 */
Four edubtm_InitLeaf(
    PageID *leaf,		/* IN the PageID to be initialized */
    Boolean root,		/* IN Is it root ? */
    Boolean isTmp)              /* IN Is it temporary ? */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four e;			/* error number */
    BtreeLeaf *page;		/* a page pointer */


    
    return(eNOERROR);
    
}  /* edubtm_InitLeaf() */
