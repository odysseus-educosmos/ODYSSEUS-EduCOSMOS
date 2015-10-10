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
#ifndef _EDUOM_TESTMODULE_H_
#define _EDUOM_TESTMODULE_H_


#include "BfM.h"
#include "Util_pool.h"

/*
 * Definition for EduOM Test Module
 */
#define TRUE 1
#define FALSE 0
#define MAX_DEVICES_IN_VOLUME 20
#define FIRST_PAGE_OBJECT 84
#define THIRD_PAGE_OBJECT 170
#define ARRAYINDEX 0
#define SET_DUMP_PAGE(oid)  (dumpPage.volNo = oid.volNo, dumpPage.pageNo = oid.pageNo)

/***************************************************************************/
/* For API function that you want to test, define it TRUE.                 */
/* Otherwise, define it FALSE so that the solution API function is called. */

#define _EDUOM_CREATEOBJECT_ 	TRUE
#define _EDUOM_DESTROYOBJECT_ 	TRUE
#define _EDUOM_COMPACTPAGE_		TRUE
#define _EDUOM_READOBJECT_		TRUE
#define _EDUOM_NEXTOBJECT_		TRUE
#define _EDUOM_PREVOBJECT_		TRUE

/***************************************************************************/

#if !(_EDUOM_CREATEOBJECT_)
#define EduOM_CreateObject(args...) OM_CreateObject(args)
#endif

#if !(_EDUOM_DESTROYOBJECT_)
#define EduOM_DestroyObject(args...) OM_DestroyObject(args)
#endif

#if !(_EDUOM_COMPACTPAGE_)
#define EduOM_CompactPage(args...) OM_CompactPage(args)
#endif

#if !(_EDUOM_READOBJECT_)
#define EduOM_ReadObject(args...) OM_ReadObject(args)
#endif

#if !(_EDUOM_NEXTOBJECT_)
#define EduOM_NextObject(args...) OM_NextObject(args)
#endif

#if !(_EDUOM_PREVOBJECT_)
#define EduOM_PrevObject(args...) OM_PrevObject(args)
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

Four RDsM_AllocTrains(Four, Four, PageID *, Two, Four, Two, PageID *);

Four EduOM_Test(Four, Four);


#endif /* _EDUOM_TESTMODULE_H_ */
