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
#ifndef _EDUOM_COMMON_H_
#define _EDUOM_COMMON_H_


#include <stdio.h>
#include "EduOM_basictypes.h"
#include "EduOM_error.h"



/* Size in PAGESIZE */
#define PAGESIZE    4096      /* NOTE: PAGESIZE must be a multiple of read/write buffer align size */
#define PAGESIZE2	1		  /* The number of page to be allocated and free */


#define BEGIN_MACRO do {
#define END_MACRO } while(0)


/* NULL vs NIL:
    - NULL, a C language predefined keyword, can be assigned to a pointer variable representing that the variable has a ¡°null pointer¡± as its value.
	- NIL, a COSMOS predefined keyword, can be assigned to a non-pointer variable representing that the variable has a ¡°null value¡± as its value. */
#undef NIL
#define NIL -1


/* Return value */
#define EOS    1        /* end of the scan */


/* special parameter values */
#define REMAINDER -1


/*
** Type Definition of PageID
*/
typedef Four PageNo;
typedef Two VolNo;
typedef VolNo VolID;

typedef struct {
	PageNo pageNo;      /* a PageNo */
	VolNo volNo;        /* a VolNo */
} PageID;

/* Macro: EQUAL_PAGEID(x, y)
 * Description: check whether the two page IDs are equal
 * Parameters:
 *  PageID x        : page ID
 *  pageID y        : page ID
 * returns: TRUE(1) if x is equal to y, otherwise FALSE(0)
 */
#define EQUAL_PAGEID(x, y)                  \
	(((x).volNo == (y).volNo && (x).pageNo == (y).pageNo) ? TRUE:FALSE)

/* Macro: MAKE_PAGEID(pid, volume, page)
 * Description: construct the page ID using the given parameters
 * Parameters:
 *  PageID pid      : (OUT) page ID
 *  volNo volume    : volume number
 *  pageNo page     : page number
 */
#define MAKE_PAGEID(pid, volume, page)  \
	(pid).volNo = (volume),         \
    (pid).pageNo = (page)


/*
 * ShortPageID : referenc a page within a given volume
 */
typedef PageNo ShortPageID;


/*
 * Type Definition for Train
 */
typedef PageID TrainID;     /* use its first page's PageID as the TrainID */


/*
** Typedefs for ObjectID
*/
typedef UFour Unique;
typedef Two SlotNo;

typedef struct {        /* ObjectID is used accross the volumes */
	PageNo pageNo;      /* specify the page holding the object */
	VolID  volNo;       /* specify the volume in which object is in */
	SlotNo slotNo;      /* specify the slot within the page */
	Unique unique;      /* Unique No for checking dangling object */
} ObjectID;

/* Macro: MAKE_OBJECTID(oid, v, p, s, u)
 * Description: construct the object ID using the given parameters
 * Parameters:
 *  ObjectID oid	: (OUT) object ID
 *  volNo v         : volume number
 *  pageNo p        : page number
 *  sloNo s         : slot number
 *  unique u        : unique number
 */
#define MAKE_OBJECTID(oid, v, p, s, u) \
	(oid).volNo = (v), (oid).pageNo = (p), (oid).slotNo = (s), (oid).unique = (u)


/*
 * Definition for Logical ID
 */
typedef Four Serial;
typedef struct {
	Serial serial;      /* a logical serial number */
	VolNo volNo;        /* a VolNo */
} LogicalID;

/* Macro: EQUAL_LOGICALID(x, y)
 * Description: check whether the two logical IDs are equal
 * Parameters:
 *  LogicalID x     : logical ID
 *  LogicalID y     : logical ID
 * Returns: TRUE(1) if x is equal to y, otherwise FALSE(0)
 */
#define EQUAL_LOGICALID(x, y)                  \
	(((x).volNo == (y).volNo && (x).serial == (y).serial) ? TRUE:FALSE)


/*
 * Definition for Physical File ID
 */
typedef PageID  PhysicalFileID;     /* use the first Page's PageID as the physical FileID */

/* Macro: MAKE_PHYSICALFILEID(fid,v,p)
 * Description: construct the physical file ID using the given parameters
 * Parameters:
 *  FileID fid      : (OUT) file ID
 *  volNo v         : volume number
 *  pageNo p        : page number
 */
#define MAKE_PHYSICALFILEID(fid,v,p) MAKE_PAGEID(fid,v,p)


/*
 * Definition for File ID
 */
typedef LogicalID FileID;

/* Macro: EQUAL_FILEID(x, y)
 * Description: check whether the two file IDs are equal
 * Parameters:
 *  FileID x     : file ID
 *  FileID y     : file ID
 * Returns: TRUE(1) if x is equal to y, otherwise FALSE(0)
 */
#define EQUAL_FILEID(x,y)    EQUAL_LOGICALID(x, y)


/*
 * log sequence number
 */
typedef struct Lsn_T_tag {
	UFour offset;               /* byte position in a log volume */
	UFour wrapCount;            /* # of wrapping around a log volume */
} Lsn_T;


/*
 * Common Page
 */
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
 * Type Vector indicates page's type
 */

/* Macro: CONSTANT_ALL_BITS_SET(_size)
 * Description: return the value in which all the bits are set to 1
 * Parameter:
 *  Four _size      : byte size
 * Returns: (Four) value in which all the bits are set to 1
 */
#define CONSTANT_ALL_BITS_SET(_size)	((sizeof(_size) == 1) ? (0xff) : \
										((sizeof(_size) == 2) ? (0xffff) : \
										((sizeof(_size) == 4) ? (0xffffffff) : (0xffffffffffffffff)))) 
#define PAGE_TYPE_VECTOR_MASK	0xf
#define PAGE_TYPE_VECTOR_RESET_MASK (CONSTANT_ALL_BITS_SET(Four)-PAGE_TYPE_VECTOR_MASK)

#define SLOTTED_PAGE_TYPE		0x2

/* Macro: RESET_PAGE_TYPE(page)
 * Description: reset the page type
 * Parameter:
 *  SlottedPage *page   : (OUT) pointer to the page
 */
#define RESET_PAGE_TYPE(page)       (((Page *)(page))->header.flags &= PAGE_TYPE_VECTOR_RESET_MASK)

/* Macro: SET_PAGE_TYPE(page, type)
 * Description: set the page type to the type given as a parameter
 * Parameters:
 *  SlottedPage *page   : (OUT) pointer to the page
 *  Four type           : buffer type
 */
#define SET_PAGE_TYPE(page, type)   (RESET_PAGE_TYPE(page), ((Page *)(page))->header.flags |= type)

/*
 * Typedef for generic object header
 *
 * Be CAREFUL: The fields must match the initial fields of
 *             SMALLOBJHDR and LARGEOBJHDR.
 */
typedef struct {
	Two  properties;    /* the properties bit vector */
	Two  tag;           /* the object's tag */
	Four length;        /* the object's data size */
} ObjectHdr;


/*
 *-------------- Type definitions for Storage Objects --------------
 */
/* object length's minimum limit */
#define MIN_OBJECT_DATA_SIZE sizeof(ObjectID)

/*
 * Typedef for Small object
 *
 * Small object is one which can be stored within one page
 */
typedef struct {
	ObjectHdr   header;         /* the object's header */
	char        data[MIN_OBJECT_DATA_SIZE]; /* data area */
} SmallObject;

/*
 * Typedef for generic object.
 * This is used to determine what type of object we are dealing with.
 * Once the object type is determined, then either the SMALLOBJ or
 * LARGEOBJ typedef is used, depending, of course, on whether we are
 * dealing with a large or small object. For now the basic structure
 * of an object is that of a small object. In case of a large object
 * the data area is used to hold control information.
 *
 */
typedef SmallObject             Object;


/*
 * 'properties' bits; only a few now
 *
 * The 'properties' field is used to record the object's properties.
 */
#define P_CLEAR              0x0 /* clear all bits to 0 */
#define P_LRGOBJ         0x1 /* whether this is a large object */
#define P_LRGOBJ_ROOTWITHHDR 0x2 /* large object header is on the page */
#define P_MOVED          0x4 /* object has been moved to a new page */
#define P_FORWARDED      0x8 /* this is the forwarded record */


/*
 * Main Memory Data Structure of Scan Manager Catalog Table SM_SYSTABLES
 */
typedef struct {
	FileID      fid;        /* data file's file identifier */
	Two         eff;            /* data file's extent fill factor */
	ShortPageID firstPage;  /* data file's first page No */
	ShortPageID lastPage;   /* data file's last page No */
	ShortPageID availSpaceList10;
	ShortPageID availSpaceList20;
	ShortPageID availSpaceList30;
	ShortPageID availSpaceList40;
	ShortPageID availSpaceList50;
} sm_CatOverlayForData;


/*
 * Dealloc List
 */
typedef enum { DL_PAGE, DL_TRAIN, DL_FILE } DLType;

struct _DeallocListElem {
	DLType type;
	union{
		PhysicalFileID pFid;    /* file which had the page before deallocation */
		PageID pid;             /* page to be deallocated */
	} elem;
	struct _DeallocListElem *next;
};

typedef struct _DeallocListElem DeallocListElem;


/*
 * Error Handling
 */
/* Error Number Indicating NO ERROR */
#define eNOERROR 0


/*
 * Macro Definitions
 */
#undef MAX
#define MAX(a,b) (((a) >= (b)) ? (a):(b))


/*
** Calculate the alignment boundary
*/
#define ALIGN sizeof(ALIGN_TYPE)
#define ALIGNED_LENGTH(l) \
	(((l)%ALIGN) ? ((l) - ((l)%ALIGN) + (((l) < 0) ? (-1 * ((Four)(ALIGN))):ALIGN)) : (l))


#endif /* _EDUOM_COMMON_H_ */
