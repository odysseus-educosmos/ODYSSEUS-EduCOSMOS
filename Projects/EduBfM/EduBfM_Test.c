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
/*
 * Module: EduBfM_Test.c
 *
 * Description : 
 *  Test the EduBfM and show the result of test.
 *
 * Exports:
 *  Four EduBfM_Test(Four)
 */

#include <string.h>
#include "EduBfM_common.h"
#include "EduBfM.h"
#include "EduBfM_Internal.h"
#include "EduBfM_basictypes.h"
#include "EduBfM_TestModule.h"


void edubfm_dump_buffertable(Four);
void edubfm_dump_hashtable(Four);


/*@================================
 * EduBfM_Test()
 *================================*/
/*
 * Function: EduBfM_Test(Four volId)
 *
 * Description : 
 *  Show a result of a test of EduBfM.
 *  EduBfM is module which is implemented for operation 
 *  related to page buffer structure. The page buffer 
 *  strucutre is composed of hash table, buffer table, 
 *  and buffer pool. There are five operations in EduBfM.
 *  EduBfM_Test() test these below operations in EduBfM.
 *  EduBfM_GetTrain(), EduBfM_FreeTrain(), EduBfM_SetDirty(),
 *  EduBfM_FlushAll(), EduBfM_DiscardAll().
 *
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four EduBfM_Test(Four volId)
{
	Four 			e;						/* for errors */
    Four   		 	i, j;					/* loop index */
	Four 			index;					/* an index of the buffer table & pool */
	Four    		firstExtNo; 			/* first extent number */
	Page 			*apage;					/* pointer to buffer holding a page */
    PageID  		pageID[3*NUM_PAGE_BUFS];/* PageID of new page to be allocated */
	PageID  		nearPid;  	  			/* near pageID */

	printf("\nLoading EduBfM_Test() complete...\n");
	
	/* Alloc new pages for test */
	e = RDsM_CreateSegment(volId, &firstExtNo);
	if (e < eNOERROR) ERR(e);
	e = RDsM_ExtNoToPageId(volId, firstExtNo, &nearPid);
	if (e < eNOERROR) ERR(e);
	
	for ( i = 0 ; i < NUM_PAGE_BUFS * 3 ; i++ )
	{
		e = RDsM_AllocTrains(volId, firstExtNo, (PageID *)&nearPid, 100, 1, PAGESIZE2, &pageID[i]);
		if (e < eNOERROR) ERR(e);
	}

    /* Show the initial page buffer state*/
	printf("****************************** The initial state of buffer page. ******************************\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	/* #1 Start test for EduBfM_GetTrain and EduBfM_FreeTrain */
	printf("****************************** TEST#1, EduBfM_GetTrain and EduBfM_FreeTrain. ******************************\n");
	
	
	/* Test for EduBfM_GetTrain() when a inserting page is a new page */
	printf("*Test 1_1 : Test for EduBfM_GetTrain() when a inserted page is a new page\n");
	printf("->Insert ten new pages into empty buffer\n\n"); 
	for (i = 0; i < NUM_PAGE_BUFS; i++)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("pageNo %d is inserted into buffer using GetTrain()\n", pageID[i].pageNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
	printf("Press enter key to continue...");
	getchar();
    printf("\n\n");

	/* Test for EduBfM_GetTrain() when a inserting  page is a existent page */
	printf("*Test 1_2 : Test for EduBfM_GetTrain() when a inserted  page is a existent page\n");
	printf("->Insert five existent pages into full buffer\n\n");
	for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("pageNo %d is inserted into buffer using GetTrain()\n", pageID[i].pageNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Test for EduBfM_FreeTrain() when fixed bit of freed pages is bigger than 0 */
	printf("*Test 1_3 : Test for EduBfM_FreeTrain() when fixed bit of freed pages is bigger than 0\n");
	printf("->Free five pages whose fixed bit is bigger than 0\n\n");
	for(i = 1; i < NUM_PAGE_BUFS; i = i + 2)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
    printf("Press enter key to continue...");
	getchar();   
	printf("\n\n");

    /* Test for EduBfM_FreeTrain() when fixed bit of freeed existent pages is 0 */
	printf("*Test 1_4 :  Test for EduBfM_FreeTrain() when fixed bit of freeed existent pages is 0\n");
	printf("->Free five pages whose fixed bit is 0\n\n");
	for(i = 1; i < NUM_PAGE_BUFS; i = i + 2)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	/* Test for EduBfM_GetTrain() when inserted page makes collision in hash function */
	printf("*Test 1_5 : Test for EduBfM_GetTrain() when inserted page makes collision in hash function\n");
	printf("->Insert a new page which has page number makes collision in hash function \n\n");
	
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBfM_GetTrain(&pageID[LAST_PAGE_NUM], (char **)&apage, PAGE_BUF);
	if (e < eNOERROR) ERR(e);
	printf("pageNo %d is inserted into buffer using GetTrain()\n", pageID[LAST_PAGE_NUM].pageNo);  
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Test for EduBfM_GetTrain() when new pages are inserted into full buffer */
	printf("*Test 1_6 : Test for EduBfM_GetTrain() when new pages are inserted into full buffer\n");
	printf("->Insert four new pages into full buffer and free that pages.\n\n");
	for ( i = NUM_PAGE_BUFS; i < PAGE_BUFS_CLOCKALG ; i++)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		 e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
         if (e < eNOERROR) ERR(e);
		 printf("pageNo %d is inserted into buffer using GetTrain()\n", pageID[i].pageNo);

	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	index = edubfm_LookUp((BfMHashKey *)&pageID[i], PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
    printf("Press enter key to continue...");
	getchar();   
	
	printf("\n\n");


	printf("****************************** TEST#1, EduBfM_GetTrain and EduBfM_FreeTrain. ******************************\n\n\n");
	/* #1 End test */


	/* #2 Start test for EduBfM_SetDirty */
    printf("****************************** TEST#2, EduBfM_SetDirty. ******************************\n");
	/* Test for EduBfM_SetDirty() */
	printf("*Test 2_1 : Test for EduBfM_SetDirty()\n");
	printf("->Set a data value of five pages \"modified\" and set dirty bit for that pages\n\n");
	for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		
		apage->header.flags = i+1;
		printf("The header flags value of pageNo %d is setted \"%d\"\n", pageID[i].pageNo, apage->header.flags);
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_SetDirty(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("Dirty bit of pageNo %d is setted using SetDirty()\n", pageID[i].pageNo);

		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
    printf("Press enter key to continue...");
	getchar();

    printf("****************************** TEST#2, EduBfM_SetDirty. ******************************\n\n\n");	
	/* #2 End test */


	/* #3 Start test for EduBfM_FlushAll and EduBfM_DiscardAll */
	printf("****************************** TEST#3, EduBfM_FlushAll and EduBfM_DiscardAll. ******************************\n");
	//Flush and discard all pages
	/* Test for EduBfM_FlushAll() */
	printf("*Test 3_1 : Test for EduBfM_FlushAll()\n");
	printf("->Flush all pages \n\n");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBfM_FlushAll();	
	if ( e < eNOERROR ) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
    printf("Press enter key to continue...");
	getchar(); 
	printf("\n\n");

	/* Test for EduBfM_DiscardAll() */
	printf("*Test 3_2 : Test for EduBfM_DiscardAll()\n");
	printf("->Free all pages which are on a buffer and discard all pages\ni\n");
	/* Free all pages which ar on a buffer */
	for (i = 0; i < NUM_PAGE_BUFS; i = i + 2){
		for (j = 0; j < 2; j++){
			/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
			e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
			if (e < eNOERROR) ERR(e);
			printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
		}
	}
	
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBfM_FreeTrain(&pageID[LAST_PAGE_NUM], PAGE_BUF);
	if (e < eNOERROR) ERR(e);
	printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
	
	for ( i = NUM_PAGE_BUFS; i < PAGE_BUFS_CLOCKALG ; i++){
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
	}



	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBfM_DiscardAll();
	if ( e < eNOERROR ) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	edubfm_dump_buffertable(PAGE_BUF);
	printf("\t(Buffer Table)\n");
	printf("\n");
	edubfm_dump_hashtable(PAGE_BUF);
	printf("\t(Hash Table)\n");
    printf("Press enter key to continue...");
	getchar();   
	printf("\n\n");

	/* Test for flushing pages which are set dirty bit */
	printf("*Test 3_3 : Test for flushing pages which are set dirty bit\n");
	printf("->Check flush function that modified pages are saved on a disk\n");
	printf("\n---------------------------------- Result ----------------------------------\n");
	for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
		if (e < eNOERROR) ERR(e);
		printf("The header flags value of flushed pageNo %d is %d\n", pageID[i].pageNo, apage->header.flags);
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
		if (e < eNOERROR) ERR(e);
	}
	printf("Press enter key to continue...");
	getchar();    
	printf("\n\n");
	printf("****************************** TEST#3, EduBfM_FlushAll and EduBfM_DiscardAll. ******************************\n");
	/* #3 End test */

	return ( eNOERROR );
}


/*@ Macro definition */
#define BUFT(i) (BI_BUFTABLE_ENTRY(type,i))
/*@================================
 * edubfm_dump_buffertable()
 *================================*/
/*
 * Function: void edubfm_dump_buffertable(Four)
 *
 * Description:
 *  Dump the buffer table.
 *
 * Returns:
 *  None
 */
void edubfm_dump_buffertable(
		Four    type)           /* IN buffer type */
{
	Two         i;
	
			    
	printf("\n\t|=================================================================|\n");
	printf("\t|                      Buffer Table                               |\n");
	printf("\t|-------------+-------------+-------------+--------+--------------|\n");
	printf("\t|%10s   |%10s   |%10s   |  bits  |%s |\n", "volNo", "pageNo", "fixed","nextHashEntry");
	printf("\t|-------------+-------------+-------------+--------+--------------|\n");
	for( i = 0; i < BI_NBUFS(type); i++ )
		printf("\t|%10d   |%10d   |%10d   |   0x%x  |%10d    |\n", BUFT(i).key.volNo,
				BUFT(i).key.pageNo, BUFT(i).fixed, (CONSTANT_CASTING_TYPE)BUFT(i).bits, BUFT(i).nextHashEntry );
	printf("\t|=================================================================|\n");
	
} /* edubfm_dump_buffertable() */


/*@================================
 * edubfm_dump_hashtable()
 *================================*/
/*
 * Function: void edubfm_dump_hashtable(Four)
 *
 * Description:
 *  Dump the hash table.
 *
 * Returns:
 *  None
 */
void edubfm_dump_hashtable(
		Four        type)           /* IN buffer type */
{
	Two                  i;
	Four                 j;
	
	
	printf("\n\t|===============================|\n");
	printf("\t|          Hash Table           |\n");
	printf("\t|=============|=================|\n");
	printf("\t|  hashValue  |  hashTableEntry |\n");
	printf("\t|=============|=================|\n");
	for( i = 0; i <= (CONSTANT_CASTING_TYPE)HASHTABLESIZE(type);i++ ) {
		if(i < HASHTABLESIZE(type))
			printf("\t|%10d   |     %10d  |\n", i, BI_HASHTABLEENTRY(type, i));
	}
    printf("\t|=============|=================|\n");
	
} /* edubfm_dump_hashtable() */
