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
#ifndef _EDUOM_INTERNAL_H_
#define _EDUOM_INTERNAL_H_


/*@
 * Type Definitions
 */

/*
 *----------------- Typedefs for Page Structures --------------------
 */

/*
 * define a type for a slot that includes a unique number
 */
typedef struct {
	Two     offset;     /* points to actual storage area */
	Unique  unique;     /* unique number */
} SlottedPageSlot;


/*
 * Typedef for the header of slotted page
 */
typedef struct {
	PageID pid;         /* page id of this page, should be located on the beginnig */
	Four flags;         /* flag to store page information */
	Four reserved;      /* reserved space to store page information */
	Two nSlots;         /* slots in use on the page */
	Two free;           /* offset of contiguous free area on page */
	Two unused;         /* number of unused bytes which are not part of the contiguous freespace */
	FileID fid;         /* fileID within its volume */
	Unique unique;      /* unique number to allocate */
	Unique uniqueLimit;     /* limit of valid unique numbers */
	ShortPageID nextPage;   /* Next PageID of data file */
	ShortPageID prevPage;   /* Prev PageID of data file */
	ShortPageID spaceListPrev;  /* double linked list of xx% free pages */
	ShortPageID spaceListNext;  /*   within the same file */
} SlottedPageHdr;


/*
 * Typedef for slotted page
 */
#define SP_FIXED (sizeof(SlottedPageHdr) + sizeof(SlottedPageSlot))

typedef struct {
	SlottedPageHdr header;    /* header of the slotted page */
	char data[PAGESIZE-SP_FIXED]; /* data area */
	SlottedPageSlot slot[1];      /* slot arrays, indexes backwards */
} SlottedPage;


/*@
 * Macro Function Definitions
 */
/* useful macros */

/* Macro: SP_FREE(p)
 * Description: return the size of total free area of the page given as a parameter
 * Parameter:
 *  SlottedPage *p      : pointer to the page
 * Returns: (Four) size of total free area
 */
#define SP_FREE(p)  ((p)->header.unused + SP_CFREE(p))

/* Macro: SP_CFREE(p)
 * Description: return the size of contiguous free area of the page given as a parameter
 * Parameter:
 *  SlottedPage *p      : pointer to the page
 * Returns: (Four) size of contiguous free area
 */
#define SP_CFREE(p) \
(PAGESIZE - SP_FIXED - (p)->header.free - ((p)->header.nSlots-1)*((CONSTANT_CASTING_TYPE)sizeof(SlottedPageSlot)))

#define SP_10SIZE       ((CONSTANT_CASTING_TYPE)((PAGESIZE-SP_FIXED)/10))
#define SP_20SIZE       ((CONSTANT_CASTING_TYPE)(((PAGESIZE-SP_FIXED)/10L)*2))
#define SP_30SIZE       ((CONSTANT_CASTING_TYPE)(((PAGESIZE-SP_FIXED)/10L)*3))
#define SP_40SIZE       ((CONSTANT_CASTING_TYPE)(((PAGESIZE-SP_FIXED)/10L)*4))
#define SP_50SIZE       ((CONSTANT_CASTING_TYPE)((PAGESIZE-SP_FIXED)/2))


/* constant macro for the empty slot */
/* The empty slots have EMPTYSLOT with the 'offset' */
#define EMPTYSLOT       -1

/* Macro: IS_VALID_OBJECTID(oid, s_page)
 * Description: check whether the object ID given as a parameter is valid or not
 * Parameters:
 *  ObjectID *oid       : pointer to the object ID
 *  SlottedPage *s_page : pointer to the page storing the object ID given as a parameter
 * Returns: TRUE(1) if oid is valid, otherwise FALSE(0)
 */
#define IS_VALID_OBJECTID(oid, s_page) \
	(((s_page->slot[-(oid)->slotNo].offset == EMPTYSLOT) || \
	  (s_page->slot[-(oid)->slotNo].unique != (oid)->unique)) ? FALSE : TRUE)

#define LRGOBJ_THRESHOLD (PAGESIZE - SP_FIXED - sizeof(ObjectHdr))

/* Macro: GET_PTR_TO_CATENTRY_FOR_DATA(catObjForFile, catPage, catEntry)
 * Description: get the information about the data file(sm_CatOverlayForData) residing in the catalog object for data file
 * Parameters:
 *  ObjectID *catObjForFile         : pointer to the object ID of the catalog object
 *  SlottedPage *catPage            : pointer to the page storing the catalog object
 *  sm_CatOverlayForData *catEntry  : (OUT) pointer to the information about the data file
 */
#define GET_PTR_TO_CATENTRY_FOR_DATA(catObjForFile, catPage, catEntry) \
{   \
	Four offset = catPage->slot[-(catObjForFile->slotNo)].offset; \
	Object *obj = (Object *)&(catPage->data[offset]); \
	catEntry = (sm_CatOverlayForData*)obj->data; \
}


/*@
 * Function Prototypes
 */
/* internal function prototypes */
Four eduom_CreateObject(ObjectID*, ObjectID*, ObjectHdr*, Four, char*, ObjectID*);

Four om_FileMapAddPage(ObjectID*, PageID*, PageID*);
Four om_FileMapDeletePage(ObjectID*, PageID*);
Four om_GetUnique(PageID*, Unique*);
Four om_IsTemporary(FileID*, Boolean*);
Four om_PutInAvailSpaceList(ObjectID*, PageID*, SlottedPage*);
Four om_RemoveFromAvailSpaceList(ObjectID*, PageID*, SlottedPage*);

    
#endif /* _EDUOM_INTERNAL_H_ */
