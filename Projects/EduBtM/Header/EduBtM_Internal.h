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
#ifndef _EDUBTM_INTERNAL_H_
#define _EDUBTM_INTERNAL_H_


#include "Util_pool.h"


/*@
 * Constant Definitions
 */
#ifndef MAXKEYLEN
#define MAXKEYLEN   256
#endif


#define OBJECTID_SIZE   sizeof(ObjectID)


/*
 * Comparison result
 */
#define EQUAL 0
#define GREAT 1
#define LESS  2
#define GREATER 1	/* added only for ODYSSEUS/EduCOSMOS */


/*@
 * Type Definitions
 */
/*************************************************************
 * The structure of Btree Pages - Internal / Leaf / Overflow *
 *************************************************************/

/*
 * BtreeAny Page:
 *  All pages in B+ tree files have some common fields in the same place.
 *  Any Page describe the common fields.
 */
typedef struct {
	PageID pid;                 /* page id of this page, should be located on the beginning */
	Four flags;                 /* flag to store page information */
	Four reserved;              /* reserved space to store page information */
	One    type;        /* Internal, Leaf, or Overflow */
} BtreeAnyHdr;

#define BANY_FIXED  (sizeof(BtreeAnyHdr))

typedef struct { /* Any Page */
	BtreeAnyHdr hdr;            /* header of pages */
	char    data[PAGESIZE-BANY_FIXED]; /* data area */
} BtreeAny;


/*
 * BtreeInternal Page:
 *  Page for the internal node of B+ tree.
 */
typedef struct {
	PageID pid;                 /* page id of this page, should be located on the beginning */
	Four flags;                 /* flag to store page information */
	Four reserved;              /* reserved space to store page information */
	One     type;       /* Internal, Leaf, or Overflow */
	ShortPageID p0;     /* the first pointer */
	Two     nSlots;     /* # of entries in this page */
	Two     free;       /* starting point of the free space */
	Two         unused;     /* number of unused bytes which are not */
	            /* part of the contiguous freespace */
} BtreeInternalHdr;

#define BI_FIXED  (sizeof(BtreeInternalHdr) + sizeof(Two))

typedef struct {   /* Internal (Nonleaf) Page */
	BtreeInternalHdr    hdr;       /* header of the slotted page */
	char            data[PAGESIZE-BI_FIXED];  /* data area */
	Two             slot[1];    /* the first slot */
} BtreeInternal;

/* Macro: BI_FREE(p)
 * Description: return the size of total free area of the internal page given as a parameter
 * Parameter:
 *  BtreeInternal *p      : pointer to the internal page
 * Returns: (Four) size of total free area
 */
#define BI_FREE(p)    ((p)->hdr.unused + BI_CFREE(p))

/* Macro: BI_CFREE(p)
 * Description: return the size of contiguous free area of the internal page given as a parameter
 * Parameter:
 *  BtreeInternal *p      : pointer to the internal page
 * Returns: (Four) size of contiguous free area
 */
#define BI_CFREE(p)   (PAGESIZE - BI_FIXED - (p)->hdr.free - ((p)->hdr.nSlots-1)*((CONSTANT_CASTING_TYPE)sizeof(Two)))
#define BI_HALF       ((CONSTANT_CASTING_TYPE)((PAGESIZE-BI_FIXED)/2))


/*
 * BtreeLeaf:
 *  Page for the leaf node of a B+ tree
 */
typedef struct {
	PageID pid;                 /* page id of this page, should be located on the beginning */
	Four flags;                 /* flag to store page information */
	Four reserved;              /* reserved space to store page information */
	One     type;            /* Internal, Leaf, or Overflow */
	Two     nSlots;          /* # of entries in this page */
	Two     free;            /* starting point of the free space */
	ShortPageID prevPage;        /* Previous page */
	ShortPageID nextPage;        /* Next page */
	Two     unused;          /* number of unused bytes which are not part of the contiguous freespace */
} BtreeLeafHdr;

#define BL_FIXED  (sizeof(BtreeLeafHdr) + sizeof(Two))

typedef struct {   /* Leaf Page */
	BtreeLeafHdr hdr;           /* header of btree leaf page */
	char     data[PAGESIZE-BL_FIXED]; /* data area */
	Two      slot[1];        /* the first slot */
} BtreeLeaf;

/* Macro: BL_FREE(p)
 * Description: return the size of total free area of the leaf page given as a parameter
 * Parameter:
 *  BtreeLeaf *p      : pointer to the leaf page
 * Returns: (Four) size of total free area
 */
#define BL_FREE(p)    ((p)->hdr.unused + BL_CFREE(p))

/* Macro: BL_CFREE(p)
 * Description: return the size of contiguous free area of the leaf page given as a parameter
 * Parameter:
 *  BtreeLeaf *p      : pointer to the leaf page
 * Returns: (Four) size of contiguous free area
 */
#define BL_CFREE(p)    (PAGESIZE - BL_FIXED - (p)->hdr.free - ((p)->hdr.nSlots-1)*((CONSTANT_CASTING_TYPE)sizeof(Two)))
#define BL_HALF        ((CONSTANT_CASTING_TYPE)((PAGESIZE-BL_FIXED)/2))
#define OVERFLOW_SPLIT ((CONSTANT_CASTING_TYPE)(PAGESIZE-BL_FIXED)/3)


/*
 * BteeOverflow:
 *  overflow page of a B+ tree
 */
typedef struct {
	PageID pid;                 /* YKL24MAR97: page id of this page, should be located on the beginning */
	Four flags;                 /* flag to store page information */
	Four reserved;              /* reserved space to store page information */
	One     type;             /* Internal, Leaf, or Overflow */
	ShortPageID nextPage;         /* Next Page */
	ShortPageID prevPage;         /* Previous Page */
	Two     nObjects;         /* # of ObjectIDs in this page */
} BtreeOverflowHdr;

#define BO_FIXED  sizeof(BtreeOverflowHdr)
#define BO_MAXOBJECTIDS ((PAGESIZE-BO_FIXED)/sizeof(ObjectID))
#define BO_DUMMY (PAGESIZE-BO_FIXED-BO_MAXOBJECTIDS*sizeof(ObjectID))

typedef struct {   /* Overflow page */
	BtreeOverflowHdr    hdr;       /* header of the btree overflow page */
	ObjectID            oid[BO_MAXOBJECTIDS]; /* ObjectID area */
#if !defined(SUPPORT_LARGE_DATABASE2)
	char            dummy_fill[BO_DUMMY]; /* dummy fill area */
#endif
} BtreeOverflow;

#define NO_OF_OBJECTS   BO_MAXOBJECTIDS
#define HALF_OF_OBJECTS         ((CONSTANT_CASTING_TYPE)(NO_OF_OBJECTS/2))
#define A_FOURTH_OF_OBJECTS     ((CONSTANT_CASTING_TYPE)(NO_OF_OBJECTS/4))


/*
 * BtreePage:
 *  Page type contains all page types
 */
typedef union {
	/*
	 * Object Manager & B+ Tree Manager Page Types
	 */
	BtreeAny      any;      /* btree any page */
	BtreeInternal bi;       /* btree internal page */
	BtreeLeaf     bl;       /* btree leaf page */
	BtreeOverflow bo;       /* btree overflow page */
} BtreePage;

/* Btree Page Type */
#define ROOT        0x01
#define INTERNAL    0x02
#define LEAF        0x04
#define OVERFLOW    0x08
#define FREEPAGE    0x10


/****************************************************************
 * Entry Types of a B+ tree
 ****************************************************************/

/*
 * The data types 'btm_InternalEntry' and 'btm_LeafEntry' are used to access
 * the entries directly in the buffer of the page. Whereas the data types
 * 'InternalItem' and 'LeafItem' are used to pass the entry value between
 * two functions.
 */

/* Data type of Internal Entry */
typedef struct {
	ShortPageID spid;       /* pointer to the child page */
				/* The child has key values greater than or */
				/* equal to 'kval' of this entry. */
	/* 'klen' and 'kval' should be attached in this order */
	/* to cast this variables the type KeyVlaue. */
	Two  klen;          /* key length */
	char kval[1];       /* key value */
} btm_InternalEntry;

/* Data type of Leaf Entry */
#define BTM_LEAFENTRY_FIXED OFFSET_OF(btm_LeafEntry, kval[0])

/* Data type of Leaf Entry */
typedef struct {
	Two nObjects;       /* # of ObjectIDs */
	/* 'klen' and 'kval' should be attached in this order */
	/* to cast this variables the type KeyVlaue. */
	Two klen;           /* key length */
				/* From this point, alignment is counted. */
	char kval[1];       /* key value and (ObjectID array or overflow PageID) */
} btm_LeafEntry;

/* Data type for representing an internal item */
typedef struct {
	ShortPageID spid;       /* points to the child page */
	Two         klen;       /* key length */
	char        kval[MAXKEYLEN]; /* key value */
} InternalItem;

/* Data type for representing a leaf item */
typedef struct {
	ObjectID oid;       /* an ObjectID */
	Two nObjects;       /* # of ObjectIDs */
	Two  klen;          /* key length */
	char kval[MAXKEYLEN];   /* key value */
} LeafItem;


/*@
** Macro Definitions
*/

/* Macro: GET_PTR_TO_CATENTRY_FOR_BTREE(catObjForFile, catPage, catEntry)
 * Description: get the information about the index file(sm_CatOverlayForBtree) residing in the catalog object for index file
 * Parameters:
 *  ObjectID *catObjForFile         : pointer to the object ID of the catalog object
 *  SlottedPage *catPage            : pointer to the page storing the catalog object
 *  sm_CatOverlayForBtree *catEntry  : (OUT) pointer to the information about the index file
 */
#define GET_PTR_TO_CATENTRY_FOR_BTREE(catObjForFile, catPage, catEntry) \
BEGIN_MACRO \
    sm_CatOverlayForSysTables *smSysTables; \
    Object *obj = (Object*)&(catPage->data[catPage->slot[-catObjForFile->slotNo].offset]); \
    catEntry = &(((sm_CatOverlayForSysTables*)&(obj->data))->btree);\
END_MACRO


/*@
 * Function Prototypes
 */
/*
** B+tree Manager Internal function prototypes
*/
Boolean edubtm_BinarySearchInternal(BtreeInternal*, KeyDesc*, KeyValue*, Two*);
Boolean edubtm_BinarySearchLeaf(BtreeLeaf*, KeyDesc*, KeyValue*, Two*);
void edubtm_CompactInternalPage(BtreeInternal*, Two);
void edubtm_CompactLeafPage(BtreeLeaf*, Two);
Four edubtm_KeyCompare(KeyDesc*, KeyValue*, KeyValue*);
Four edubtm_Delete(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Boolean*, Boolean*, InternalItem*, Pool*, DeallocListElem*);
Four edubtm_Insert(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Boolean*, Boolean*, InternalItem*, Pool*, DeallocListElem*);
Four edubtm_InsertLeaf(ObjectID*, PageID*, BtreeLeaf*, KeyDesc*, KeyValue*, ObjectID*, Boolean*, Boolean*, InternalItem*);
Four edubtm_InsertInternal(ObjectID*, BtreeInternal*, InternalItem*, Two, Boolean*, InternalItem*);
Four edubtm_FirstObject(PageID*, KeyDesc*, KeyValue*, Four, BtreeCursor*);
Four edubtm_FreePages(PhysicalFileID*, PageID*, Pool*, DeallocListElem*);
Four edubtm_InitInternal(PageID*, Boolean, Boolean);
Four edubtm_InitLeaf(PageID*, Boolean, Boolean);
Four edubtm_LastObject(PageID*, KeyDesc*, KeyValue*, Four, BtreeCursor*);
Four edubtm_SplitInternal(ObjectID*, BtreeInternal*, Two, InternalItem*, InternalItem*);
Four edubtm_SplitLeaf(ObjectID*, PageID*, BtreeLeaf*, Two, LeafItem*, InternalItem*);
Four edubtm_get_objectid_from_leaf(BtreeCursor*);
Four edubtm_root_insert(ObjectID*, PageID*, InternalItem*);

Four btm_AllocPage(ObjectID*, PageID*, PageID*);
Boolean btm_BinarySearchOidArray(ObjectID[], ObjectID*, Two, Two*);
Four btm_ObjectIdComp(ObjectID*, ObjectID*);
Four btm_CreateOverflow(ObjectID*, BtreeLeaf*, Two, ObjectID*);
Four btm_InsertOverflow(ObjectID*, PageID*, ObjectID*);
Four btm_DeleteOverflow(PhysicalFileID*, PageID*, ObjectID*, Two*, Pool*, DeallocListElem*);
Four btm_Underflow(PhysicalFileID*, BtreePage*, PageID*, Two, Boolean*,
		           Boolean*, InternalItem*, Pool*, DeallocListElem*);
Four btm_get_objectid_from_overflow(BtreeCursor*);
Four btm_root_delete(PhysicalFileID*, PageID*, Pool*, DeallocListElem*);
Four btm_IsTemporary(ObjectID*, Boolean*);


/*
 * B+tree Manager Interface function prototypes
 */
/*
Four EduBtM_CreateIndex(ObjectID*, PageID*);
Four EduBtM_DeleteObject(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Pool*, DeallocListElem*);
Four EduBtM_DropIndex(PhysicalFileID*, PageID*, Pool*, DeallocListElem*);
Four EduBtM_Fetch(PageID*, KeyDesc*, KeyValue*, Four, KeyValue*, Four, BtreeCursor*);
Four EduBtM_FetchNext(PageID*, KeyDesc*, KeyValue*, Four, BtreeCursor*, BtreeCursor*);
Four EduBtM_InsertObject(ObjectID*, PageID*, KeyDesc*, KeyValue*, ObjectID*, Pool*, DeallocListElem*);
*/


#endif /* _EDUBTM_INTERNAL_H_ */
