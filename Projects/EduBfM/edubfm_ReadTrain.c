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
 * Module: edubfm_ReadTrain.c
 *
 * Description : 
 *  Read a train into the buffer.
 *
 * Exports:
 *  edubfm_ReadTrain()
 */


#include "EduBfM_common.h"
#include "RDsM.h"
#include "RM.h"                 /* YKL05MAR97 */
#include "EduBfM_Internal.h"



/*@================================
 * edubfm_ReadTrain()
 *================================*/
/*
 * Function: Four edubfm_ReadTrain(TrainID*, char*, Four)
 *
 * Description:
 * (Following description is for original ODYSSEUS/COSMOS BfM.
 *  For ODYSSEUS/EduCOSMOS EduBfM, refer to the EduBfM project manual.)
 *
 *  Using the given parameters, trainId and type,  read a train from
 *  the disk  and load it into the given buffer.   If the error occurs 
 *  when RDsM_ReadTrain() is called, simply return it.  The function has
 *  no code for checking input parameters since this will be done RDsM,
 *  especially RDsM_ReadTrain().
 *
 * Returns;
 *  error code
 *    some errors caused by RDsM_ReadTrain()
 *
 * Side effects
 *  1) parameter aTrain
 *     a buffer specified by 'aTrain' is filled with a disk content
 */
Four edubfm_ReadTrain(
    TrainID *trainId,		/* IN which train? */
    char    *aTrain,		/* OUT a pointer to buffer */
    Four    type )		/* IN buffer type */
{
	/* These local variables are used in the solution code. However, you don¡¯t have to use all these variables in your code, and you may also declare and use additional local variables if needed. */
    Four e;			/* for error */


	/* Error check whether using not supported functionality by EduBfM */
	if (RM_IS_ROLLBACK_REQUIRED()) ERR(eNOTSUPPORTED_EDUBFM);



    return( eNOERROR );

}  /* edubfm_ReadTrain */
