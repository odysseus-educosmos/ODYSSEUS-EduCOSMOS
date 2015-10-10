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
#ifndef _EDUBFM_INTERNAL_H_
#define _EDUBFM_INTERNAL_H_


/*@
 * Constant Definitions
 */ 
/* number of buffer types : number of buffer pools used */
#define NUM_BUF_TYPES 2

/* Buffer Types */
#define PAGE_BUF     0
#define LOT_LEAF_BUF 1

/* Macro: IS_BAD_BUFFERTYPE(type)
 * Description: check whether the buffer type is invalid
 * Parameter:
 *  Four type       : buffer type
 * Returns: TRUE(1) if the buffer type is invalid, otherwise FALSE(0)
 */
#define IS_BAD_BUFFERTYPE(type) (type < 0 || type >= NUM_BUF_TYPES)

/* The structure of key type used at hashing in buffer manager */
/* same as "typedef BfMHashKey PageID; */
typedef struct {
    PageNo pageNo;		/* a PageNo */
    VolNo volNo;		/* a volumeNo */
} BfMHashKey;

/* Macro: SET_NILBFMHASHKEY(key)
 * Description: set pageNo of the hash key to NIL
 * Parameter:
 *  BfMHashKey key  : hash key
 */
#define SET_NILBFMHASHKEY(key) (SET_NILPAGEID(key))

/* Macro: IS_NILBFMHASHKEY(key)
 * Description: check whether pageNo of the hash key is NIL
 * Parameter:
 *  BfMHashKey key  : hash key
 * Returns: TRUE(1) if pageNo of the hash key is NIL, otherwise FALSE(0)
 */
#define IS_NILBFMHASHKEY(key)  (IS_NILPAGEID(key))

/* Macro: CHECKKEY(k)
 * Description: check whether the hash key is invalid
 * Parameter:
 *  BfMHashKey *k    : pointer to the hash key
 */
#define CHECKKEY(k)  \
	        { if( ((k)->volNo < 0) || ((k)->pageNo < 0) )  \
				              return( eBADHASHKEY_BFM ); }

/* Macro: EQUALKEY(k1, k2)
 * Description: check whether the two hash keys are equal
 * Parameters:
 *  BfMHashKey *k1   : pointer to the hash key
 *  BfMHashKey *k2   : pointer to the hash key
 * Returns: TRUE(1) if k1 is equal to k2, otherwise FALSE(0)
 */
#define EQUALKEY(k1, k2) \
          (((k1)->volNo == (k2)->volNo) && ((k1)->pageNo == (k2)->pageNo))

/* The structure of BufferTable which is used in buffer replacement algo. */
typedef struct {
    BfMHashKey 	key;		/* identify a page */
    Two    	fixed;		/* fixed count */
    One    	bits;		/* bit 1 : DIRTY, bit 2 : VALID, bit 3 : REFER, bit 4 : NEW */
    Two    	nextHashEntry;
} BufferTable;

#define DIRTY  0x01
#define VALID  0x02
#define REFER  0x04
#define ALL_0  0x00
#define ALL_1  ((sizeof(One) == 1) ? (0xff) : (0xffff))

/* type definition for buffer pool information */
typedef struct {
    Two                 bufSize;        /* size of a buffer in page size */
    UTwo                nextVictim;     /* starting point for searching a next victim */
    Two                 nBufs;          /* # of buffers in this buffer pool */
    BufferTable*	 	bufTable;
    char*		 		bufferPool;	/* a set of buffers */
    Two*       		 	hashTable;	/* hash table */
} BufferInfo;

/* Macro: BI_BUFSIZE(type)
 * Description: return the size of a buffer element of a buffer pool (unit: # of pages)
 * Parameter:
 *  Four type       : buffer type
 * Returns: (Two) size of a buffer element
 */
#define BI_BUFSIZE(type)	     (bufInfo[type].bufSize)

/* Macro: BI_NBUFS(type)
 * Description: return the number of buffer elements of a buffer pool
 * Parameter:
 *  Four type       : buffer type
 * Returns: (Two) the number of buffer elements
*/
#define BI_NBUFS(type)           (bufInfo[type].nBufs)

/* Macro: BI_NEXTVICTIM(type)
 * Description: return an array index of the next buffer element(next victim) to be visited to determine whether or not to replace the buffer element by the buffer replacement algorithm
 * Parameter:
 *  Four type       : buffer type
 * Returns: (UTwo) an array index of the next victim
 */
#define BI_NEXTVICTIM(type)	     (bufInfo[type].nextVictim)

/* Macro: BI_KEY(type, idx)
 * Description: return the hash key of the page/train residing in the buffer element
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer element
 * Returns: (BfMHashKey) hash key
 */
#define BI_KEY(type, idx)	     (((BufferTable*)bufInfo[type].bufTable)[idx].key)

/* Macro: BI_FIXED(type, idx)
 * Description: return the number of transactions fixing (accessing) the page/train residing in the buffer element
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer element
 * Returns: (Two) number of transactions
 */
#define BI_FIXED(type, idx)	     (((BufferTable*)bufInfo[type].bufTable)[idx].fixed)

/* Macro: BI_BITS(type, idx)
 * Description: return a set of bits indicating the state of the buffer element
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer element
 * Returns: (One) set of bits
 */
#define BI_BITS(type, idx)	     (((BufferTable*)bufInfo[type].bufTable)[idx].bits)

/* Macro: BI_NEXTHASHENTRY(type, idx)
 * Description: return the array index of the buffer element containing the next page/train having the identical hash key value
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer element containing the current page/train
 * Returns: (Two) array index of the buffer element containing the next page/train
 */
#define BI_NEXTHASHENTRY(type, idx)  (((BufferTable*)bufInfo[type].bufTable)[idx].nextHashEntry)

/* Macro: BI_BUFFERPOOL(type)
 * Description: return the buffer pool
 * Parameter:
 *  Four type       : buffer type
 * Returns: (char *) pointer to the buffer pool
 */
#define BI_BUFFERPOOL(type)	     (bufInfo[type].bufferPool)

/* Macro: BI_BUFFER(type, idx)
 * Description: return the idx-th element of the buffer pool
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer element
 * Returns: (char *) pointer to the idx-th element
 */
#define BI_BUFFER(type, idx)	     ((char*)BI_BUFFERPOOL(type)+PAGESIZE*BI_BUFSIZE(type)*idx)

/* Macro: BI_HASHTABLE(type)
 * Description: return the hash table
 * Parameter:
 *  Four type       : buffer type
 * Returns: (Two*) pointer to the hash table
 */
#define BI_HASHTABLE(type)	     (bufInfo[type].hashTable)

/* Macro: BI_HASHTABLEENTRY(type,idx)
 * Description: return the idx-th element of the buffer table
 * Parameters:
 *  Four type       : buffer type
 *  Four idx        : array index of the buffer table element
 * Returns: (Two) idx-th element
 */
#define BI_HASHTABLEENTRY(type,idx)  (*(BI_HASHTABLE(type) + idx))

/* The size of the hash table is three times of the size of the buffer pool
 * in order to minimize the rate of collisions.
 * Each entry of the hash table corresponds to an index of the buffer pool
 * as well as the buffer table.
 */

/* Macro: HASHTABLESIZE_TO_NBUFS(_x)
 * Description: return the size of the hash table (unit: # of elements)
 * Parameter:
 *  Two _x          : size of the buffer pool (unit: # of elements)
 * Returns: (Two) size of the hash table
 */
#define HASHTABLESIZE_TO_NBUFS(_x)   	((_x) * 3 - 1) 	

/* Macro: HASHTABLESIZE(type)
 * Description: return the size of the hash table
 * Parameter:
 *  Four type       : buffer type
 * Returns: (Two) size of the hash table
 */
#define HASHTABLESIZE(type) 	     	(HASHTABLESIZE_TO_NBUFS(BI_NBUFS(type))) 

/* constant definition: The BfMHashKey don't exist in the hash table. */
#define NOTFOUND_IN_HTABLE  -1

extern BufferInfo bufInfo[];

/*@
 * Function Prototypes
 */
/* internal function prototypes */
Four edubfm_AllocTrain(Four);
Four edubfm_Delete(BfMHashKey *, Four);
Four edubfm_DeleteAll(void);
Four edubfm_FlushTrain(TrainID *, Four);
Four edubfm_Insert(BfMHashKey *, Two, Four); 
Four edubfm_LookUp(BfMHashKey *, Four);
Four edubfm_ReadTrain(TrainID *, char *, Four);


#endif /* _EDUBFM_INTERNAL_H_ */
