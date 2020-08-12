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

Four edubtm_CheckOnePage(
        PageID      *pid,
		Two			type,
		FILE		*fp,
		bool		*pass)
{
    Four e;         /* error number */
    BtreePage *apage;       /* page to dump */

    e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
    if (e < 0)  ERR(e);

	if (apage->any.hdr.type & INTERNAL){
		edubtm_DumpInternalPage(&(apage->bi), pid, type);
		edubtm_CheckInternalPage(&(apage->bi), pid, type, fp, pass);
	}
	else if (apage->any.hdr.type & LEAF){
		edubtm_DumpLeafPage(&(apage->bl), pid, type);
		edubtm_CheckLeafPage(&(apage->bl), pid, type, fp, pass);

	}
	else
		ERRB1(eBADBTREEPAGE_BTM, pid, PAGE_BUF);

    e = BfM_FreeTrain(pid, PAGE_BUF);
    if (e < 0) ERR(e);
    return(eNOERROR);
}

Four edubtm_CheckFPages(
    PageID              *pid,
    Two                 type,
	FILE				*fp,
	bool				*pass)
{
    BtreePage           *apage;
    btm_InternalEntry   *entry;         /* IN an internal entry */
    PageID              childPid;
    Four                i;
    Four                e;

    e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
    if (e < eNOERROR) ERR(e);

    if (apage->any.hdr.type & INTERNAL){
        edubtm_DumpInternalPage(&(apage->bl), pid, type);
		edubtm_CheckInternalPage(&(apage->bi), pid, type, fp, pass);

        childPid.volNo = pid->volNo;
        childPid.pageNo = apage->bi.hdr.p0;
        edubtm_CheckFPages(&childPid, type, fp, pass);
		
        if (e < eNOERROR) ERR(e);

    }
    else if (apage->any.hdr.type & LEAF){
        edubtm_DumpLeafPage(&(apage->bl), pid, type);
		edubtm_CheckLeafPage(&(apage->bl), pid, type, fp, pass);
    }

    e = BfM_FreeTrain(pid, PAGE_BUF);
    if (e < eNOERROR) ERR(e);

	return eNOERROR;
}


void edubtm_CheckInternalPage(
	BtreeInternal       *internal,      /* IN pointer to buffer of internal page */
    PageID              *pid,           /* IN page identifier */
    Two                 type,           /* IN type for key value */
	FILE				*fp,
	bool				*pass
)
{
	Four				volNo;
	Four				pageNo;
	char				pageType[100];
	Four				free;
	Four				unused;
	Four				nSlots;
	Four				p0;
	Four 				kLen;
	Four				kValInt;
	char				kValVarchar[MAXPLAYERNAME];
	Four				sPid;
	char				str[100];

    Two                 i;              /* index variable */
    Two                 entryOffset;    /* starting offset of an internal entry */
    btm_InternalEntry   *entry;         /* IN an internal entry */
    Two                 j;              /* index variable */
    Two                 len;            /* key value length */
    char        playerName[MAXPLAYERNAME];  /* data of the key value */
    int                 tempKval;


	fgets(str, 100, fp);
    fscanf(fp, "|=========================================================|\n");
    fscanf(fp, "|    PageID = (%d,%d)     type = %s      |\n", &volNo, &pageNo, pageType);
    fscanf(fp, "|=========================================================|\n");
    fscanf(fp, "| free = %d  unused = %d    nSlots = %d		p0 = %d  |\n", &free, &unused, &nSlots, &p0);
    fscanf(fp, "|---------------------------------------------------------|\n");

	if (pid->volNo != volNo || pid->pageNo != pageNo || (strcmp(pageType, "INTERNAL") && strcmp(pageType, "INTERNAL|ROOT")) ||
		internal->hdr.free != free || internal->hdr.unused != unused || internal->hdr.nSlots != nSlots || internal->hdr.p0 != p0)
	{
		*pass = false;
	} 


	for (i = 0; i < nSlots; i++) {
		entryOffset = internal->slot[-i];
		entry = (btm_InternalEntry*)&(internal->data[entryOffset]);
		fscanf(fp, "| ");
		if (type == SM_INT)
		{
			fscanf(fp, "        klen = %d :  Key = %d  : spid = %d        |\n", &kLen, &kValInt, &sPid);
			memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */

			if (kLen != entry->klen || kValInt != tempKval || sPid != entry->spid)
			{
				*pass = false;
				break;
			}
		}
		else if (type == SM_VARSTRING)
		{            
			fscanf(fp, "    klen = %d : Key = %[^:] : spid = %d |\n", &kLen, kValVarchar, &sPid);
			kValVarchar[strlen(kValVarchar) - 1] = '\0';

			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);


			if (kLen != len || strcmp(kValVarchar, playerName) || sPid != entry->spid)
			{
				*pass = false;
				break;
			}
		}
	}

    fscanf(fp, "|---------------------------------------------------------|\n");
}  

void edubtm_CheckLeafPage(
    BtreeLeaf           *leaf,          /* IN pointer to buffer of Leaf page */
    PageID              *pid,           /* IN pointer to leaf PageID */
	Two                 type,           /* IN type for key value */
	FILE				*fp,
	bool				*pass
)
{
    Four                volNo;
    Four                pageNo;
    char                pageType[100];
    Four                free;
    Four                unused;
    Four                nSlots;
	Four				nextPage;
	Four				prevPage;
    Four                kLen;
    Four                kValInt;
    char                kValVarchar[MAXPLAYERNAME];
	Four				nObjs;
	Four				overPid;
	ObjectID			tempOid;
	char				str[100];

    Two                 entryOffset;    /* starting offset of a leaf entry */
    btm_LeafEntry       *entry;         /* a leaf entry */
    ObjectID            *oid;           /* an object identifier */
    Two                 i;              /* index variable */
    Two                 j;              /* index variable */
    Two                 alignedKlen;    /* aligned length of the key length */
    Two                 len;            /* length of the key value */
    char        playerName[MAXPLAYERNAME];  /* data of the key value */
    Four                tempKval;

	fgets(str, 100, fp);
	fscanf(fp, "|===============================================================================|\n");
    fscanf(fp, "|               PageID = (%d, %d)            type = %s                |\n", &volNo, &pageNo, pageType);
    fscanf(fp, "|===============================================================================|\n");
    fscanf(fp, "|             free = %d  unused = %d	 nSlots = %d                      |\n", &free, &unused, &nSlots);       
    fscanf(fp, "|             nextPage = %d  prevPage = %d                     |\n",
            &nextPage, &prevPage );
    fscanf(fp, "|-------------------------------------------------------------------------------|\n");

	if (volNo != pid->volNo || pageNo != pid->pageNo || (strcmp(pageType, "LEAF") && strcmp(pageType, "LEAF|ROOT")) ||
		free != leaf->hdr.free || unused != leaf->hdr.unused || nSlots != leaf->hdr.nSlots || 
		nextPage != leaf->hdr.nextPage || prevPage != leaf->hdr.prevPage ){
		*pass = false;
	}

	for (i = 0; i < leaf->hdr.nSlots; i++) {
		entryOffset = leaf->slot[-i];
		entry = (btm_LeafEntry*)&(leaf->data[entryOffset]);
		
		fscanf(fp, "| ");
		if (type == SM_INT)
		{
			fscanf(fp, "klen = %d : Key = %d", &kLen, &kValInt);
            memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */

            if (kLen != entry->klen || kValInt != tempKval) {
                *pass = false;
                break;
            }
		}
		else if (type == SM_VARSTRING)
		{
			fscanf(fp, "    klen = %4d : Key = %[^:]", &kLen, kValVarchar);
            kValVarchar[strlen(kValVarchar) - 1] = '\0';

			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);

			if (kLen != len || strcmp(kValVarchar, playerName)){
				*pass = false;
				break;
			}
		}
		fscanf(fp, " : nObjects = %d : ", &nObjs);
		if (nObjs != entry->nObjects)
		{
			*pass = false;
			break;
		}
		
		alignedKlen = ALIGNED_LENGTH(entry->klen);
		if (entry->nObjects < 0) { 
			fscanf(fp, " OverPID = %d ", &overPid);
			if (overPid != *((ShortPageID*)&(entry->kval[alignedKlen]))){
				*pass = false;
				break;
			}	
		}
		else {          
			oid = (ObjectID *)&(entry->kval[alignedKlen]);
			fscanf(fp, " ObjectID = (%4d, %4d, %4d, %4d) |\n", &(tempOid.volNo), &(tempOid.pageNo), &(tempOid.slotNo), &(tempOid.unique));
			if(tempOid.volNo != oid->volNo || tempOid.pageNo != oid->pageNo || tempOid.slotNo != oid->slotNo || tempOid.unique != oid->unique){
				*pass = false;
				break;
			}
		}           
		
	}
	fscanf(fp, "|-------------------------------------------------------------------------------|\n");
}      

void edubtm_CheckObject(
	ObjectID 			*oid, 
	FILE 				*fp, 
	bool 				*pass
)
{
	ObjectID			tempOid;

    fscanf(fp, "OID: (%d, %d, %d, %d)\n", &(tempOid.volNo), &(tempOid.pageNo), &(tempOid.slotNo), &(tempOid.unique));
	if (tempOid.volNo != oid->volNo || tempOid.pageNo != oid->pageNo || 
		tempOid.slotNo != oid->slotNo || tempOid.unique != oid->unique)
	{
		*pass = false;
	}
}

