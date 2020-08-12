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
/*
 * Module: EduBfM_Test.c
 *
 * Description : 
 *  Test the EduBfM.
 *
 * Exports:
 *  Four EduBfM_Test(Four)
 */

#include <string.h>
#include <stdbool.h>
#include "EduBfM_common.h"
#include "EduBfM.h"
#include "EduBfM_Internal.h"
#include "EduBfM_basictypes.h"
#include "EduBfM_TestModule.h"


/*@================================
 * EduBfM_Test()
 *================================*/
/*
 * Function: EduBfM_Test(Four volId)
 *
 * Description : 
 *  EduBfM is a module which implements the data structures 
 *  and operations of the buffuer manager. The data strucutre 
 *  is composed of the hash table, the buffer table, and the 
 *  buffer pool. There are five following APIs in EduBfM. 
 *  EduBfM_GetTrain(), EduBfM_FreeTrain(), EduBfM_SetDirty(),
 *  EduBfM_FlushAll(), EduBfM_DiscardAll().
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

	FILE			*fp;
	Four			score = 0;				/* score of the test */
	bool  			pass;			/* for the result of each test */
	bool			passCoarse;

	/* Allocate new pages */
	e = RDsM_CreateSegment(volId, &firstExtNo);
	if (e < eNOERROR) ERR(e);
	e = RDsM_ExtNoToPageId(volId, firstExtNo, &nearPid);
	if (e < eNOERROR) ERR(e);
	
	for ( i = 0 ; i < NUM_PAGE_BUFS * 3 ; i++ )
	{
		e = RDsM_AllocTrains(volId, firstExtNo, (PageID *)&nearPid, 100, 1, PAGESIZE2, &pageID[i]);
		if (e < eNOERROR) ERR(e);
	}

	/* Open the result file of the test for evaluation */
    if ((fp = fopen("result.txt", "r")) == NULL){
		fprintf(stderr, "ERROR");
		return -1;
	}

    /* Show initial state of the page buffer */
	printf("****************************** Initial state of the page buffer. ******************************\n");
	edubfm_Dump_BufTable(PAGE_BUF);
	edubfm_Dump_HashTable(PAGE_BUF);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	
	/* #1 Start test for EduBfM_GetTrain and EduBfM_FreeTrain */
    printf("****************************** TEST#1, EduBfM_GetTrain() and EduBfM_FreeTrain(). ******************************\n\n\n");
	passCoarse = true;
	score = 0;
	for (i = 1; i <= 6; i++)
	{
		pass = true;
		switch(i){
			case 1:
				e = edubfm_Test_1_1(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 2:
				e = edubfm_Test_1_2(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 3:
				e = edubfm_Test_1_3(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 4:
				e = edubfm_Test_1_4(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 5:
				e = edubfm_Test_1_5(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 6:	
				e = edubfm_Test_1_6(pageID, apage, PAGE_BUF, fp, &pass);
				break;
		}
		if (e < eNOERROR) {
			printf("Total score: %d / 100\n", score);
			ERR(e);
		}
		if (pass == true) printf("\n\tTest 1_%d is passed.\n", i);
	    else
	    {
	        printf("\n\tTest 1_%d is failed. \n", i);
	        passCoarse = false;
   		}
    	printf("Press enter key to continue...");
   		getchar();
   		printf("\n\n");		
		
	}

	if (passCoarse == true) score += 40;

	printf("Current score: %d / 40\n", score);
	printf("****************************** TEST#1, EduBfM_GetTrain and EduBfM_FreeTrain. ******************************\n\n\n");
	/* #1 End test */

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	/* #2 Start test for EduBfM_SetDirty */
    printf("****************************** TEST#2, EduBfM_SetDirty. ******************************\n");

	e = edubfm_Test_2_1(pageID, apage, PAGE_BUF, fp, &pass);
	if (e < eNOERROR) {             
		printf("Total score: %d / 100\n", score);
		ERR(e);
	}
	if (pass == true) 
	{ 
	    printf("\n\tTest 2_1 is passed. \n");
		score += 20;
	}
	else printf("\n\tTest 2_1 is failed. \n");

    printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	printf("Current score: %d / 60\n", score);
    printf("****************************** TEST#2, EduBfM_SetDirty. ******************************\n\n\n");	
	/* #2 End test */

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	/* #3 Start test for EduBfM_FlushAll and EduBfM_DiscardAll */
	printf("****************************** TEST#3, EduBfM_FlushAll and EduBfM_DiscardAll. ******************************\n");
	//Flush and discard all pages
	passCoarse = true;
	for (i = 1; i <= 3; i++)
	{
		pass = true;
		switch(i) {
			case 1:
			    e = edubfm_Test_3_1(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 2:
			    e = edubfm_Test_3_2(pageID, apage, PAGE_BUF, fp, &pass);
				break;
			case 3:
				e = edubfm_Test_3_3(pageID, apage, fp, &pass);
				break;
		}
        if (e < eNOERROR) {             
			printf("Total score: %d / 100\n", score);
			ERR(e);
		}
        if (pass == true) printf("\n\tTest 3_%d is passed.\n", i);
        else
        {
            printf("\n\tTest 3_%d is failed. \n", i);
            passCoarse = false;
        }

		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");
	}
	
	if (passCoarse == true)  score += 40;
	
	printf("****************************** TEST#3, EduBfM_FlushAll and EduBfM_DiscardAll. ******************************\n");
	/* #3 End test */

	printf("Total score: %d / 100\n", score);

	fclose(fp);

	return ( eNOERROR );
}

/*@================================
 * edubfm_Test_1_1()
 *================================*/
/*
 * Function: edubfm_Test_1_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_1() tests EduBfm_GetTrain() inserting new pages.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubfm_Test_1_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;

	printf("Test 1_1 tests EduBfM_GetTrain() inserting new pages\n");

    for (i = 0; i < NUM_PAGE_BUFS; i++)
    {
        printf("The page, pageNo is %d, has been inserted into the buffer using EduBfM_GetTrain().\n", pageID[i].pageNo);
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
        if (e < eNOERROR) ERR(e);
    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");


    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);


    return (eNOERROR);
}

/*@================================
 * edubfm_Test_1_2()
 *================================*/
/*
 * Function: edubfm_Test_1_2(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_2() tests EduBfm_GetTrain() inserting the apges that already exist in the buffer page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubfm_Test_1_2(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;


    printf("Test 1_2 tests EduBfM_GetTrain() inserting the pages that already exist in the buffer page.\n");

    for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
    {
		printf("The page, pageNo is %d, has been inserted into the buffer using EduBfM_GetTrain().\n", pageID[i].pageNo);
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
        if (e < eNOERROR) ERR(e);
    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}


/*@================================
 * edubfm_Test_1_3()
 *================================*/
/*
 * Function: edubfm_Test_1_3(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_3() tests EduBfm_FreeTrain() freeing the pages whose fixed bits are not 0.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubfm_Test_1_3(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;


    printf("Test 1_3 tests EduBfm_FreeTrain() freeing the pages whose fixed bits are not 0.\n");
    for(i = 1; i < NUM_PAGE_BUFS; i = i + 2)
    {
        printf("The page whose pageNo is %d is freed from the buffer using FreeTrain().\n", pageID[i].pageNo);
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);
    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}


/*@================================
 * edubfm_Test_1_4()
 *================================*/
/*
 * Function: edubfm_Test_1_4(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_4() tests EduBfm_FreeTrain() freeing the pages whose fixed bits are 0.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubfm_Test_1_4(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;


    printf("Test 1_4 tests EduBfm_FreeTrain() freeing the pages whose fixed bits are 0.\n");
    for(i = 1; i < NUM_PAGE_BUFS; i = i + 2)
    {
        printf("The page whose pageNo is %d is freed from the buffer using FreeTrain().\n", pageID[i].pageNo);
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);
    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}

/*@================================
 * edubfm_Test_1_5()
 *================================*/
/*
 * Function: edubfm_Test_1_5(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_5() tests EduBfm_GetTrain() inserting new pages that occur collision in the hash function.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubfm_Test_1_5(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;


    printf("Test 1_5 tests EduBfm_GetTrain() inserting new pages that occur collision in the hash function.\n");

    printf("The page whose pageNo is %d is inserted into the buffer using GetTrain().\n", pageID[LAST_PAGE_NUM].pageNo);
    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduBfM_GetTrain(&pageID[LAST_PAGE_NUM], (char **)&apage, PAGE_BUF);
    if (e < eNOERROR) ERR(e);

    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}

/*@================================
 * edubfm_Test_1_6()
 *================================*/
/*
 * Function: edubfm_Test_1_6(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_1_6() tests EduBfm_GetTrain() inserting new pages when the buffer table is full.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four edubfm_Test_1_6(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;

    printf("Test 1_6 tests EduBfm_GetTrain() inserting new pages when the buffer table is full.\n");

    for ( i = NUM_PAGE_BUFS; i < PAGE_BUFS_CLOCKALG ; i++)
    {
        printf("The page whose pageNo is %d is inserted into the buffer using GetTrain().)\n", pageID[i].pageNo);
    	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
        if (e < eNOERROR) ERR(e);

    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}

/*@================================
 * edubfm_Test_2_1()
 *================================*/
/*
 * Function: edubfm_Test_2_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 * edubfm_Test_2_1() tests EduBfM_SetDirty() modifying pages and setting their dirty bits.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four edubfm_Test_2_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{
    Four            i;
    Four            e;

    printf("Test 2_1 tests EduBfM_SetDirty() modifying pages and setting their dirty bits.\n");
    for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
    {
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
        if (e < eNOERROR) ERR(e);

        apage->header.flags = i+1;
        printf("The header flags value of pageNo %d has been setted \"%d\"\n", pageID[i].pageNo, apage->header.flags);
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_SetDirty(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);
        printf("Dirty bit of pageNo %d has been setted using SetDirty()\n", pageID[i].pageNo);

        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);
    }
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}


/*@================================
 * edubfm_Test_3_1()
 *================================*/
/*
 * Function: edubfm_Test_3_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 * edubfm_Test_3_1() tests EduBfM_FlushAll() flushing all pages in the buffer table.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four edubfm_Test_3_1(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{   
    Four            i;
    Four            e;
    
    printf("Test 3_1 tests EduBfM_FlushAll() flushing all pages in the buffer table.\n");

    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduBfM_FlushAll();
    if ( e < eNOERROR ) ERR(e);
    printf("Press enter key to continue...");
    getchar();
    printf("\n---------------------------------- Result ----------------------------------\n");

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}

/*@================================
 * edubfm_Test_3_2()
 *================================*/
/*
 * Function: edubfm_Test_3_2(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 * edubfm_Test_3_2() tests EduBfM_DiscardAll() freeing all pages and discarding them.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four edubfm_Test_3_2(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
{   
    Four            i, j;
    Four            e;

    printf("Test 3_2 tests EduBfM_DiscardAll() freeing all pages and discarding them.\n");

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
    printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[LAST_PAGE_NUM].pageNo);

    for ( i = NUM_PAGE_BUFS; i < PAGE_BUFS_CLOCKALG ; i++){
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);
        printf("pageNo %d is freed from buffer using FreeTrain()\n", pageID[i].pageNo);
    }

    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduBfM_DiscardAll();
    if ( e < eNOERROR ) ERR(e);

    edubfm_Dump_BufTable(type);
    edubfm_Dump_HashTable(type);

    edubfm_CheckBufTable(type, fp, pass);
    edubfm_CheckHashTable(type, fp, pass);

    return (eNOERROR);
}

/*@================================
 * edubfm_Test_3_3()
 *================================*/
/*
 * Function: edubfm_Test_3_3(PageID *pageID, Page *apage, Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_Test_3_3() tests EduBfM_FlushAll() checking the modified pages are flusehd on the disk in edubfm_Test_3_1.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four edubfm_Test_3_3(PageID *pageID, Page *apage, FILE *fp, bool *pass)
{
	Four			pageNo;
	Four			headerFlag;
	Four 			i;
	char			str[100];
	Four			e;


    printf("Test 3_3 tests EduBfM_FlushAll() checking the modified pages are flushed on the disk in edubfm_Test_3_1.\n");

    printf("\n---------------------------------- Result ----------------------------------\n");
    for (i = 0; i < NUM_PAGE_BUFS; i = i + 2)
    {
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_GetTrain(&pageID[i], (char **)&apage, PAGE_BUF);
        if (e < eNOERROR) ERR(e);
        printf("The header flag value of the flushed page whose pageNo is %d has been %d.\n", pageID[i].pageNo, apage->header.flags);


        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBfM_FreeTrain(&pageID[i], PAGE_BUF);
        if (e < eNOERROR) ERR(e);

        fscanf(fp, "The header flag value of the flushed page whose pageNo is %d has been %d.\n", &pageNo, &headerFlag);
    	if (pageNo != pageID[i].pageNo || headerFlag != apage->header.flags){
			pass = false;
		}

    }

	return (eNOERROR);

}

/*@================================
 * edubfm_CheckBufTable()
 *================================*/
/*
 * Function: edubfm_CheckBufTabl(Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_CheckBufTable() compare the buffer table to that of the solution.
 *
 * Returns:
 *  NONE
 */

void edubfm_CheckBufTable(Four type, FILE *fp, bool *pass)
{
    Four            pageNo;
    Four            volNo;
    Four            fixed;
    Four            bits;
    Four            nextHashEntry;
	Four			i;
	char			str[100];

    for (i = 0; i < 10; i++) fgets(str, 100, fp);
	
    for (i = 0; i < BI_NBUFS(type); i++)
    {
        fscanf(fp, "\t|%10d   |%10d   |%10d   |   0x%x  |%10d    |\n", &volNo, &pageNo, &fixed, &bits, &nextHashEntry);
		if (volNo != BUFT(i).key.volNo || pageNo != BUFT(i).key.pageNo || fixed != BUFT(i).fixed 
			|| bits != BUFT(i).bits || nextHashEntry != BUFT(i).nextHashEntry)
		{
			*pass = false;
		}
		
    }

	return (eNOERROR);
}


/*@================================
 * edubfm_CheckBufTable()
 *================================*/
/*
 * Function: edubfm_CheckBufTabl(Four type, FILE *fp, bool *pass)
 *
 * Description : 
 *  edubfm_CheckHashTable() compare the hash table to that of the solution.
 *
 * Returns:
 *  NONE
 */
void edubfm_CheckHashTable(Four type, FILE *fp, bool *pass)
{
   	Four            hashValue;
    Four            hashTableEntry;
	Four			i;
    char            str[100];


    for (i = 0; i < 9; i++)    fgets(str, 100, fp);

    for (i = 0; i < 29; i++)
    {
        fscanf(fp, "\t|%10d   |     %10d  |\n", &hashValue, &hashTableEntry);
		if (hashTableEntry !=  BI_HASHTABLEENTRY(type, i))
		{
			*pass = false;	
		}

    }

	return (eNOERROR);
}

/*@================================
 * edubfm_Dump_BufTable()
 *================================*/
/*
 * Function: edubfm_Dump_BufTable(Four)
 *
 * Description:
 *  Dump the buffer table.
 *
 * Returns:
 *  None
 */
void edubfm_Dump_BufTable(
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
	printf("\t(Buffer Table)\n\n");
	
} /* edubfm_Dump_BufTable() */


/*@================================
 * edubfm_Dump_HashTable()
 *================================*/
/*
 * Function: edubfm_Dump_HashTable(Four)
 *
 * Description:
 *  Dump the hash table.
 *
 * Returns:
 *  None
 */
void edubfm_Dump_HashTable(
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
	printf("\t(Hash Table)\n");
	
} /* edubfm_Dump_HashTable() */
