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
#ifndef _EDUBFM_COMMON_H_
#define _EDUBFM_COMMON_H_


#include <stdio.h>
#include "EduBfM_basictypes.h"
#include "EduBfM_error.h"

#define BEGIN_MACRO do {
#define END_MACRO } while(0)

/* NULL vs NIL:
   	- NULL, a C language predefined keyword, can be assigned to a pointer variable representing that the variable has a ¡°null pointer¡± as its value.
    - NIL, a COSMOS predefined keyword, can be assigned to a non-pointer variable representing that the variable has a ¡°null value¡± as its value. */
#undef NIL
#define NIL -1

/*
 * Configuration Parameters
 */
typedef struct CfgParams_T_tag {
	char*   logVolumeDeviceList;    /* log volume device list */ /* YKL13AUG1998-1 */
    Boolean useDeadlockAvoidance;   /* use deadlock avoidance */
    Boolean useBulkFlush;       /* use bulkflush */
} CfgParams_T;

/*
** Type Definition of PageID
*/
typedef Four PageNo;
typedef Two VolNo;

typedef struct {
    PageNo pageNo;		/* a PageNo */
    VolNo volNo;		/* a VolNo */
} PageID;

#define PAGESIZE      4096      /* NOTE: PAGESIZE must be a multiple of read/write buffer align size */

/* Macro: SET_NILPAGEID(x)
 * Description: set pageNo of the page ID to NIL
 * Parameter:
 *  PageID x    : page ID
 */
#define SET_NILPAGEID(x)   ((x).pageNo = NIL)

/* Macro: IS_NILPAGEID(x)
 * Description: check whether pageNo of the page ID is NIL
 * Parameter:
 *  PageID x    : page ID
 * Returns: TRUE(1) if pageNo of the page ID is NIL, otherwise FALSE(0)
 */
#define IS_NILPAGEID(x)    (((x).pageNo == NIL) ? TRUE:FALSE)

/* Macro: PRINT_TRAINID(x,y)
 * Description: print the train ID with its additional information
 * Parameters:
 *  char *x     : string that represents the additional information of the train ID
 *  TrainID y   : train ID
 */
#define PRINT_PAGEID(x, y)	\
    (y == NULL) ? printf("%s = NULL", (x)) :	\
    printf("%s = {%-2ld, %4ld}\n", (x), (y)->volNo, (y)->pageNo )

/*
** Type Definition for Train
*/
typedef PageID TrainID;		/* use its first page's PageID as the TrainID */

#define PRINT_TRAINID(x,y) PRINT_PAGEID(x,y)

/*
 * Error Handling
 */
/* Error Number Indicating NO ERROR */
#define eNOERROR 0


#endif /* _EDUBFM_COMMON_H_ */
