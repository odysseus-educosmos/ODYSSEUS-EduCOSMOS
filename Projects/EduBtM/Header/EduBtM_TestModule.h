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
#ifndef _EDUBTM_TESTMODULE_H_
#define _EDUBTM_TESTMODULE_H_


#include "BfM.h"
#include "Util_pool.h"

/*
 * Definition for EduBtM Test Module
 */
#define TRUE 1
#define FALSE 0
#define MAX_DEVICES_IN_VOLUME 20
#define ARRAYINDEX 0
#define NUMOFINSERTEDOBJECT	200
#define NUMOFPLAYER 1000
#define MAXPLAYERNAME 60

/***************************************************************************/
/* For API function that you want to test, define it TRUE.                 */
/* Otherwise, define it FALSE so that the solution API function is called. */

#define _EDUBTM_CREATEINDEX_	TRUE
#define _EDUBTM_DROPINDEX_		TRUE
#define _EDUBTM_INSERTOBJECT_	TRUE
#define _EDUBTM_DELETEOBJECT_	TRUE
#define _EDUBTM_FETCH_			TRUE
#define _EDUBTM_FETCHNEXT_		TRUE

/***************************************************************************/

#if !(_EDUBTM_CREATEINDEX_)
#define EduBtM_CreateIndex(args...) BtM_CreateIndex(args) 
#endif

#if !(_EDUBTM_DROPINDEX_)
#define EduBtM_DropIndex(args...) BtM_DropIndex(args)
#endif

#if !(_EDUBTM_INSERTOBJECT_)
#define EduBtM_InsertObject(args...) BtM_InsertObject(args) 
#endif

#if !(_EDUBTM_DELETEOBJECT_)
#define EduBtM_DeleteObject(args...) BtM_DeleteObject(args) 
#endif

#if !(_EDUBTM_FETCH_)
#define EduBtM_Fetch(args...) BtM_Fetch(args)
#endif

#if !(_EDUBTM_FETCHNEXT_)
#define EduBtM_FetchNext(args...) BtM_FetchNext(args)
#endif


DeallocListElem dlHead;
extern Pool dlPool;


/*
 * Type Definition about transaction
 */
typedef struct {        /* 8 byte unsigned integer */
    UFour high;
    UFour low;
} XactID;

typedef enum { X_BROWSE_BROWSE, X_CS_BROWSE, X_CS_CS, X_RR_BROWSE, X_RR_CS, X_RR_RR } ConcurrencyLevel; /* isolation degree */

/*
 *  Definition for Physical Index ID
 */
typedef PageID  PhysicalIndexID;  /* use the root Page's PageID as the physical IndexID */

/*
** Definition for Index ID
*/
typedef LogicalID IndexID;


/*@
 * Function Prototypes
 */
/* Interface Function Prototypes */
Four LRDS_Init(void);
Four LRDS_AllocHandle(Four*);
Four LRDS_FormatDataVolume(Four, char**, char*, Four, Two, Four*, Four);
Four LRDS_Mount(Four, char**, Four*);
Four LRDS_BeginTransaction(XactID*, ConcurrencyLevel); /* COOKIE09NOV1999 */
Four LRDS_CommitTransaction(XactID*);
Four LRDS_AbortTransaction(XactID*);
Four LRDS_Dismount(Four);
Four LRDS_FreeHandle(Four);
Four LRDS_Final(void);

Four EduBtM_Test(Four, Four);


#endif /* _EDUBTM_TESTMODULE_H_ */
