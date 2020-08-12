/******************************************************************************/
/*                                                                            */
/*    ODYSSEUS/EduCOSMOS Educational-Purpose Object Storage System            */
/*                                                                            */
/*    Developed by Professor Kyu-Young Whang et al.                           */
/*                                                                            */
/*    Database and Multimedia Laboratory                                      */
/*                                                                            */
/*    Computer Science Department and                                         */
/*    Advanced Information Technology Research Center (AITrc)                 */
/*    Korea Advanced Institute of Science and Technology (KAIST)              */
/*                                                                            */
/*    e-mail: kywhang@cs.kaist.ac.kr                                          */
/*    phone: +82-42-350-7722                                                  */
/*    fax: +82-42-350-8380                                                    */
/*                                                                            */
/*    Copyright (c) 1995-2013 by Kyu-Young Whang                              */
/*                                                                            */
/*    All rights reserved. No part of this software may be reproduced,        */
/*    stored in a retrieval system, or transmitted, in any form or by any     */
/*    means, electronic, mechanical, photocopying, recording, or otherwise,   */
/*    without prior written permission of the copyright owner.                */
/*                                                                            */
/******************************************************************************/
#ifndef _EDUBFM_TESTMODULE_H_
#define _EDUBFM_TESTMODULE_H_


/*
 * Common Definition
 */
#define PAGESIZE2 1
#define CONSTANT_CASTING_TYPE int


/*
 * Definition for EduBfM Test Module
 */
#define NUM_PAGE_BUFS 10
#define LAST_PAGE_NUM 29
#define PAGE_BUFS_CLOCKALG 14
#define MAX_DEVICES_IN_VOLUME 20

#define BUFT(i) (BI_BUFTABLE_ENTRY(type,i))
#define BI_BUFTABLE_ENTRY(type, idx) (((BufferTable*)bufInfo[type].bufTable)[idx]) 


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

Four edubfm_Test_1_1(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_1_2(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_1_3(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_1_4(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_1_5(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_1_6(PageID *, Page *, Four, FILE *, bool *);

Four edubfm_Test_2_1(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_2_2(PageID *, Page *, Four, FILE *, bool *);

Four edubfm_Test_3_1(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_3_2(PageID *, Page *, Four, FILE *, bool *);
Four edubfm_Test_3_3(PageID *, Page *, FILE *, bool *);

void edubfm_Dump_BufTable(Four);
void edubfm_Dump_HashTable(Four);
Four edubfm_Check_BufTable(FILE*);
Four edubfm_Check_HashTable(FILE*);


#endif /* _EDUBFM_TESTMODULE_H_ */
