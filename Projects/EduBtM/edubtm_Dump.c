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

#include <string.h>
#include "EduBtM_common.h"
#include "EduBtM_basictypes.h"
#include "EduBtM.h"
#include "EduBtM_TestModule.h"
#include "OM_Internal.h"

Four edubtm_DumpBtreePage(
        PageID      *pid,
        KeyDesc     kdesc)
{
    Four e;         /* error number */
    BtreePage *apage;       /* page to dump */

    e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
    if (e < 0)  ERR(e);

	if (apage->any.hdr.type & INTERNAL)
		edubtm_DumpInternalPage(&(apage->bi), pid, kdesc.kpart[0].type);
	else if (apage->any.hdr.type & LEAF)
		edubtm_DumpLeafPage(&(apage->bl), pid, kdesc.kpart[0].type);
	else
		ERRB1(eBADBTREEPAGE_BTM, pid, PAGE_BUF);

    e = BfM_FreeTrain(pid, PAGE_BUF);
    if (e < 0) ERR(e);
    return(eNOERROR);
}


Four edubtm_DumpFPages(
    PageID              *rootPid,
    Two                 type
)
{
    BtreePage           *apage;
    btm_InternalEntry   *entry;         /* IN an internal entry */
    PageID              childPid;
    Four                i;
    Four                e;

    e = BfM_GetTrain(rootPid, (char **)&apage, PAGE_BUF);
    if (e < eNOERROR) ERR(e);

    if (apage->any.hdr.type & INTERNAL){
        edubtm_DumpInternalPage(&(apage->bl), rootPid, type);

        childPid.volNo = rootPid->volNo;
        childPid.pageNo = apage->bi.hdr.p0;
        edubtm_DumpFPages(&childPid, type);
        if (e < eNOERROR) ERR(e);

    }
    else if (apage->any.hdr.type & LEAF){
        edubtm_DumpLeafPage(&(apage->bl), rootPid, type);
    }

    e = BfM_FreeTrain(rootPid, PAGE_BUF);
    if (e < eNOERROR) ERR(e);

}


Four edubtm_DumpAllPages(
	PageID				*rootPid,
	Two					type
)
{
	BtreePage			*apage;
	btm_InternalEntry   *entry;         /* IN an internal entry */
	PageID				childPid;
	Four				i;
	Four				e;

	e = BfM_GetTrain(rootPid, (char **)&apage, PAGE_BUF);
	if (e < eNOERROR) ERR(e);

	if (apage->any.hdr.type & INTERNAL){
		edubtm_DumpInternalPage(&(apage->bl), rootPid, type);	

		childPid.volNo = rootPid->volNo;
		childPid.pageNo = apage->bi.hdr.p0;
		edubtm_DumpAllPages(&childPid, type);
		if (e < eNOERROR) ERR(e);

		for (i = 0; i < apage->bi.hdr.nSlots; i++)
		{
			entry = (btm_InternalEntry*)&(apage->bi.data[apage->bi.slot[-i]]);
			childPid.pageNo = entry->spid;
			e = edubtm_DumpAllPages(&childPid, type);
			if (e < eNOERROR) ERR(e);
		}

	}
	else if (apage->any.hdr.type & LEAF){
		edubtm_DumpLeafPage(&(apage->bl), rootPid, type);
	}
	
	e = BfM_FreeTrain(rootPid, PAGE_BUF);
	if (e < eNOERROR) ERR(e);

}

void edubtm_DumpInternalPage(
        BtreeInternal       *internal,      /* IN pointer to buffer of internal page */
        PageID              *pid,           /* IN page identifier */
        Two                 type            /* IN type for key value */
        )
{
    Two                 i;              /* index variable */
    Two                 entryOffset;    /* starting offset of an internal entry */
    btm_InternalEntry   *entry;         /* IN an internal entry */
    Two                 j;              /* index variable */
    Two                 len;            /* key value length */
    char        playerName[MAXPLAYERNAME];  /* data of the key value */
    int                 tempKval;

    printf("\n\t|=========================================================|\n");
    printf("\t|    PageID = (%4d,%6d)     type = INTERNAL%s      |\n",
            pid->volNo, pid->pageNo, (internal->hdr.type & ROOT) ? "|ROOT":"     ");
    printf("\t|=========================================================|\n");
    printf("\t| free = %-5d  unused = %-5d", internal->hdr.free, internal->hdr.unused);
    printf("nSlots = %-5d  p0 = %-5d  |\n", internal->hdr.nSlots, internal->hdr.p0 );
    printf("\t|---------------------------------------------------------|\n");
	for (i = 0; i < internal->hdr.nSlots; i++) {
		entryOffset = internal->slot[-i];
		entry = (btm_InternalEntry*)&(internal->data[entryOffset]);
		printf("\t| ");
		if (type == SM_INT)
		{
			memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */
			printf("        klen = %4d :  Key = %4d  : spid = %4d        |\n", entry->klen, tempKval, entry->spid);
		}
		else if (type == SM_VARSTRING)
		{
			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);
			printf("    klen = %4d : Key = %s", len, playerName);
			printf(" : spid = %5d |\n", entry->spid);
		}
	}

    printf("\t|---------------------------------------------------------|\n");

}  

void edubtm_DumpLeafPage(
        BtreeLeaf           *leaf,          /* IN pointer to buffer of Leaf page */
        PageID              *pid,           /* IN pointer to leaf PageID */
        Two                 type            /* IN type for key value */
        )
{
    Two                 entryOffset;    /* starting offset of a leaf entry */
    btm_LeafEntry       *entry;         /* a leaf entry */
    ObjectID            *oid;           /* an object identifier */
    Two                 i;              /* index variable */
    Two                 j;              /* index variable */
    Two                 alignedKlen;    /* aligned length of the key length */
    Two                 len;            /* length of the key value */
    char        playerName[MAXPLAYERNAME];  /* data of the key value */
    Four                tempKval;


    printf("\n\t|===============================================================================|\n");
    printf("\t|               PageID = (%4d,%4d)            type = LEAF%s                |\n",
            pid->volNo, pid->pageNo, (leaf->hdr.type & ROOT) ? "|ROOT":"     ");
    printf("\t|===============================================================================|\n");
    printf("\t|             free = %-5d  unused = %-5d", leaf->hdr.free, leaf->hdr.unused);                                          
    printf("  nSlots = %-5d                      |\n", leaf->hdr.nSlots);
    printf("\t|             nextPage = %-10d   prevPage = %-10d                     |\n",
            leaf->hdr.nextPage, leaf->hdr.prevPage );
    printf("\t|-------------------------------------------------------------------------------|\n");

     
	for (i = 0; i < leaf->hdr.nSlots; i++) {
		entryOffset = leaf->slot[-i];
		entry = (btm_LeafEntry*)&(leaf->data[entryOffset]);
		
		printf("\t| ");
		if (type == SM_INT)
		{
			memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */
			printf("klen = %3d : Key = %-4d", entry->klen, tempKval);
			
			
		}
		else if (type == SM_VARSTRING)
		{
			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);
			printf("klen = %3d : Key = %s", len, playerName);
		}
		printf(" : nObjects = %d : ", entry->nObjects);
		
		alignedKlen = ALIGNED_LENGTH(entry->klen);
		if (entry->nObjects < 0)        
			printf(" OverPID = %d ", *((ShortPageID*)&(entry->kval[alignedKlen])));
		else {          
			oid = (ObjectID *)&(entry->kval[alignedKlen]);
			printf(" ObjectID = (%4d, %4d, %4d, %4d) |\n", oid->volNo, oid->pageNo, oid->slotNo, oid->unique);
		}           
		
	}
	printf("\t|-------------------------------------------------------------------------------|\n");
	
}   
