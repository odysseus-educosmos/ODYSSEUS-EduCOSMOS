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
#ifndef _EDUBFM_TESTMODULE_H_
#define _EDUBFM_TESTMODULE_H_


/*
 * Common Definition
 */
#define TRUE 1
#define FALSE 0
#define PAGESIZE2 1
#define CONSTANT_CASTING_TYPE int


/*
 * Definition for EduBfM Test Module
 */
#define NUM_PAGE_BUFS 10
#define LAST_PAGE_NUM 29
#define PAGE_BUFS_CLOCKALG 14
#define MAX_DEVICES_IN_VOLUME 20

#define BI_BUFTABLE_ENTRY(type, idx) (((BufferTable*)bufInfo[type].bufTable)[idx]) 

/***************************************************************************/
/* For API function that you want to test, define it TRUE.                 */
/* Otherwise, define it FALSE so that the solution API function is called. */

#define _EDUBFM_GETTRAIN_		TRUE
#define _EDUBFM_FREETRAIN_		TRUE
#define _EDUBFM_SETDIRTY_		TRUE
#define _EDUBFM_FLUSHALL_		TRUE
#define _EDUBFM_DISCARDALL_		TRUE

/***************************************************************************/

#if !(_EDUBFM_GETTRAIN_)
#define EduBfM_GetTrain(args...) BfM_GetTrain(args)
#endif

#if !(_EDUBFM_FREETRAIN_)
#define EduBfM_FreeTrain(args...) BfM_FreeTrain(args)
#endif

#if !(_EDUBFM_SETDIRTY_)
#define EduBfM_SetDirty(args...) BfM_SetDirty(args)
#endif

#if !(_EDUBFM_FLUSHALL_)
#define EduBfM_FlushAll(args...) BfM_FlushAll(args)
#endif

#if !(_EDUBFM_DISCARDALL_)
#define EduBfM_DiscardAll(args...) BfM_DiscardAll(args)
#endif


/*
 * Type Definition of Page
 */
typedef struct Lsn_T_tag {
    UFour offset;               /* byte position in a log volume */
    UFour wrapCount;            /* # of wrapping around a log volume */
} Lsn_T;

typedef struct PageHdr_T_tag {
    PageID pid;                 /* page id of this page */
    Four flags;
    Four reserved;
    PageID fidOrIid;            /* file id or index id containing this page */
    Lsn_T lsn;                  /* page lsn */
    Four logRecLen;             /* log record length */
} PageHdr;

typedef struct Page_tag {
    PageHdr header;
    char data[PAGESIZE-sizeof(PageHdr)];
} Page;


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

Four RDsM_CreateSetment(Four, Four*);
Four RDsM_ExtNoToPageId(Four, Four, PageID*);
Four RDsM_AllocTrains(Four, Four, PageID *, Two, Four, Two, PageID *);

Four EduBfM_Test(Four);


#endif /* _EDUBFM_TESTMODULE_H_ */
