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
 * Module: EduOM_Test.c
 *
 * Description : 
 *  Test the EduOM and show the result of test.
 *
 * Exports:
 *  Four EduOM_Test(Four, Four)
 */
#include <string.h>
#include "EduOM_common.h"
#include "EduOM.h"
#include "EduOM_Internal.h"
#include "EduOM_TestModule.h"


Four eduom_DumpPage(SlottedPage *);
Four eduom_DumpOnePage(PageID *);
Four eduom_DumpAllPage(PageID *);
Four eduom_GetNextPageID(PageID *);
char* itoa(Four val, Four base);


/*@================================
 * EduOM_Test()
 *================================*/
/*
 * Function: EduOM_Test(Four volId, Four handle)
 *
 * Description : 
 *  Show a result of a test of EduOM.
 *  EduOM is module which is implemented for operation 
 *  related to page structure. The page strucutre is 
 *  composed of object header, slot, and data.
 *  There are five operations in EduOM.
 *  EduOM_Test() test these below operations in EduOM.
 *  EduOM_CreateObject(), EduOM_DestroyObject(), EduOM_ReadObject(),
 *  EduOM_PrevObject(), EduOM_NextObject().
 *
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four EduOM_Test(Four volId, Four handle){

	Four 		e;										/* for errors */
	Four		i, j;									/* loop index */
	FileID      fid;									/* file identifier */
	ObjectID    catalogEntry;							/* catalog object */
	ObjectID	oid;									/* object identifeier */	
	ObjectID	firstOid;								/* identifier of first object */
	ObjectID 	lastOid;								/* identifier of last object */
	PageID		dumpPage;								/* dump page */
	char		omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";	/* test object */
	char		buffer[32];							/* buffer for reading object */

	printf("Loading EduOM_Test() complete...\n");

	/* Create File */
    e = SM_CreateFile(volId, &fid, FALSE, NULL);
	if (e < eNOERROR) ERR(e);	
	/* Get catalog entry */
	e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
	if (e < eNOERROR) ERR(e);

	/* #1 Start the test for EduOM_CreateObject */
	printf("****************************** TEST#1, EduOM_CreateObject and EduOM_DestroyObject ******************************\n");
	/* Test for EduOM_CreateObject() when a near object is NULL */
	printf("*Test 1_1 : Test for EduOM_CreateObject() when a near object is NULL\n");
	printf("->Insert a new object into a empty page\n\n");
	strcat(omTestObjectNo, "0");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_CreateObject(&catalogEntry, NULL, NULL, strlen(omTestObjectNo), omTestObjectNo , &oid);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d )  is inserted into the page\n", oid.pageNo, oid.slotNo);
    firstOid = oid;
	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Test for EduOM_CreateObjecT() when a near object is not NULL */
	printf("*Test 1_2 : Test for EduOM_CreateObject() when a near object is not NULL\n");
	printf("->Insert new objects into the page until the page is full\n\n");

	if (e < eNOERROR) ERR(e);
	for (i = 1; i < FIRST_PAGE_OBJECT; i++){
		strcpy(omTestObjectNo, "EduOM_TestModule_OBJECT_NUM_");
		strcat(omTestObjectNo, itoa(i,10));	
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_CreateObject(&catalogEntry, &oid, NULL, strlen(omTestObjectNo), omTestObjectNo, &oid);
		if(e < eNOERROR) ERR(e);		  
		printf("The object ( %d, %d )  is inserted into the page\n", oid.pageNo, oid.slotNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n---------------------------------- Result ----------------------------------\n");
	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	printf("Press enter key to continue...");           
	getchar();              
	printf("\n\n");

	/* Test for EduOM_CreateObeject() until a new page is needed */
	printf("*Test 1_3 : Test for EduOM_CreateObeject() until a new page is needed\n");
	printf("->Insert new objects into the page until the 2nd object of 3rd page is created\n\n");
	for (i = FIRST_PAGE_OBJECT; i < THIRD_PAGE_OBJECT; i++){
        strcpy(omTestObjectNo, "EduOM_TestModule_OBJECT_NUM_");
		strcat(omTestObjectNo, itoa(i,10));
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_CreateObject(&catalogEntry, &oid, NULL, strlen(omTestObjectNo), omTestObjectNo, &oid);
		if (e < eNOERROR) ERR(e);
		printf("The object ( %d, %d )  is inserted into the page\n", oid.pageNo, oid.slotNo);
	}
	lastOid = oid;
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    SET_DUMP_PAGE(firstOid);
    printf("\n---------------------------------- Result ----------------------------------\n");
	eduom_DumpAllPage(&dumpPage);
	
	/* Test for EduOM_DestroyObject() when destroying object is not last object in the page */
	printf("*Test 1_4 : Test for EduOM_DestroyObject() when destroying object is not last object in the page\n");
	printf("->Destroy ten objects from the page.\n\n");
	oid = firstOid;
	for (i = 0; i < 10; i++)
	{
		oid.slotNo += 2;
		oid.unique += 2;
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		EduOM_DestroyObject(&catalogEntry, &oid, &dlPool, &dlHead);
		printf("The object ( %d, %d )  is destroyed from the page\n", oid.pageNo, oid.slotNo);
	}

	 printf("Press enter key to continue...");
	 getchar();
	 printf("\n\n");
	 
	 SET_DUMP_PAGE(firstOid);
	 printf("\n---------------------------------- Result ----------------------------------\n");
	 eduom_DumpOnePage(&dumpPage);

	/*  Test for EduOM_CreateObject() when needing page compact */
	printf("*Test 1_5 : Test for EduOM_CreateObject() when needing page compact\n");
	printf("->Insert a new object into the page which needs page compact\n\n");
	oid = firstOid;
	strcpy(omTestObjectNo, "EduOM_OBJECT_FOR_COMPACT_TEST");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_CreateObject(&catalogEntry, &oid, NULL, strlen(omTestObjectNo), omTestObjectNo, &oid);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d )  is inserted into the page\n", oid.pageNo, oid.slotNo);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	SET_DUMP_PAGE(firstOid);
	printf("\n---------------------------------- Result ----------------------------------\n");
	eduom_DumpOnePage(&dumpPage);

	/* Test for EduOM_DestroyObject() when the object is last object in the page */
	printf("*Test 1_6 : Test for EduOM_DestroyObject() when the object is last object in the page\n");
	printf("->Destroy the last object form the 3rd page\n\n");
	
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_DestroyObject(&catalogEntry, &lastOid, &dlPool, &dlHead);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d )  is destroyed from the page\n", lastOid.pageNo, lastOid.slotNo);

	lastOid.slotNo--;               
	lastOid.unique--;    
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	SET_DUMP_PAGE(lastOid);
    printf("\n---------------------------------- Result ----------------------------------\n");     
	eduom_DumpOnePage(&dumpPage);
	printf("Press enter key to continue...");
	getchar();          
	printf("\n\n");

	/* Test 1_7 : Test for EduOM_DestroyObject() when the object is unique object in the page */
	printf("*Test 1_7 : Test for EduOM_DestroyObject() when the object is unique object in the page\n");
	printf("->Destroy objects until destroying object is last object form the 3rd page\n\n");

	
	do{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_DestroyObject(&catalogEntry, &lastOid, &dlPool, &dlHead);
		if (e < eNOERROR) ERR(e);
		
		printf("The object ( %d, %d )  is destroyed from the page\n", lastOid.pageNo, lastOid.slotNo);
		lastOid.slotNo--;
		lastOid.unique--;

	}while(lastOid.slotNo >= 0);
    printf("Press enter key to continue...");
	getchar();          
	printf("\n\n");
	
	SET_DUMP_PAGE(firstOid);
	eduom_GetNextPageID(&dumpPage);
	printf("\n---------------------------------- Result ----------------------------------\n");
	eduom_DumpOnePage(&dumpPage);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	

	printf("****************************** TEST#1, EduOM_CreateObject and EduOM_DestroyObject  ******************************\n");
/* #1 End the test */



/* #2 Start the test for EduOM_ReadObject */
	printf("****************************** TEST#2, EduOM_ReadObject. ******************************\n");


	/* Test for EduOM_ReadObject() when condition is part */
	printf("*Test 2_1 : Test for EduOM_ReadObject() when condition is part\n");
	printf("->Read object from 7th to 15th\n\n");
	oid = firstOid;
	memset(buffer, 0, 32);
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_ReadObject(&oid, 7, 15, &(buffer[0]));
	if (e < eNOERROR) ERR(e);
	printf("Read data of the first object in the first page from 7th character to 15th character\n"); 
	printf("---------------------------------- Result ----------------------------------\n");
	printf("%s\n", buffer);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	/* Test for EduOM_ReadObject() when condition is full */
	printf("*Test 2_2 : Test for EduOM_ReadObject() when condition is full\n");
	printf("->Read a full data of object\n\n");
	memset(buffer, 0, 32);
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_ReadObject(&oid, 0, REMAINDER, &(buffer[0]));
	if (e < eNOERROR) ERR(e);
    printf("Read full data of the first object in first page\n");
	printf("---------------------------------- Result ----------------------------------\n");
	printf("%s\n", buffer);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	printf("****************************** TEST#2, EduOM_ReadObject. ******************************\n");
/* #2 End the test */

/* #3 Start the test for EduOM_PrevObject */
    printf("****************************** TEST#3, EduOM_PrevObject. ******************************\n");
	/* Test for EduOM_PrevObject() when parameter curOID is NULL */
	printf("*Test 3_1 : Test for EduOM_PrevObject() when parameter curOID is NULL.\n");
	printf("->Get a last object identifier\n\n");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_PrevObject(&catalogEntry, NULL, &oid, NULL);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	printf("---------------------------------- Result ----------------------------------\n");
	
	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	e = OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Test for EduOM_PrevObject() when parameter curOID is not NULL */
	printf("*Test 3_2 : Test for EduOM_PrevObject() when parameter curOID is not NULL.\n");
	printf("->Get a identifier of previous object of a last object\n\n");
	printf("Press enter key to continue...");       
	getchar();      
	printf("\n\n");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_PrevObject(&catalogEntry, &oid, &oid, NULL);
	if (e < eNOERROR) ERR(e);
	printf("---------------------------------- Result ----------------------------------\n");

	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	
	printf("Press enter key to continue...");
	getchar();          
	printf("\n\n");
	
	e = OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	/* Test for EduOM_PrevObjeect when object whose objectID is parameter curOID is first object in the page */	
	printf("*Test 3_3 : Test for EduOM_PrevObjeect when object whose objectID is parameter curOID is first object in the page\n");
	printf("->Get a last object of a previous page of a last page\n\n");
	printf("Press enter key to continue...");       
	getchar();      
	printf("\n\n");
	do
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_PrevObject(&catalogEntry, &oid, &oid, NULL);
		if (e < eNOERROR) ERR(e);
	}while(oid.slotNo != 0);
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_PrevObject(&catalogEntry, &oid, &oid, NULL);
	if (e < eNOERROR) ERR(e);
	printf("---------------------------------- Result ----------------------------------\n");
	
	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	
	printf("Press enter key to continue...");
	getchar();          
	printf("\n\n");
	
	e = OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	printf("****************************** TEST#3, EduOM_PrevObject. ******************************\n");
/* #4 End the test */

/* #5 Start the test for EduOM_NextObject */
	printf("****************************** TEST#4, EduOM_NextObject. ******************************\n");
	/* Test for EduOM_NextObject() when parameter curOID is NULL */
	printf("*Test 4_1 : Test for EduOM_NextObject() when parameter curOID is NULL.\n");
    printf("->Get a first object identifier\n\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_NextObject(&catalogEntry, NULL, &oid, NULL);
	if (e < eNOERROR) ERR(e);

	printf("---------------------------------- Result ----------------------------------\n");
	
	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	printf("Press enter key to continue...");
	getchar();
	
	printf("\n\n");
	e = OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	/* Test for EduOM_NextObject() when parameter curOID is not NULL */
	printf("*Test 4_2 : Test for EduOM_NextObject() when parameter curOID is not NULL.\n");
	printf("->Get a identifier of next object of a first object\n\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduOM_NextObject(&catalogEntry, &oid, &oid, NULL);
	if (e < eNOERROR) ERR(e);
	printf("---------------------------------- Result ----------------------------------\n");

	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	e = OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Test for EduOM_NextObjeect when object whose objectID is parameter curOID is last object in the page */
	printf("*Test 4_3 : Test for EduOM_NextObjeect when object whose objectID is parameter curOID is last object in the page\n");
	printf("->Get a first object of a next page of a first page\n\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	do
	{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_NextObject(&catalogEntry, &oid, &oid, NULL);
		if (e < eNOERROR) ERR(e);
	}while(oid.slotNo != 0);
	printf("---------------------------------- Result ----------------------------------\n");

	SET_DUMP_PAGE(oid);
	eduom_DumpOnePage(&dumpPage);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	OM_DumpObject(&oid);
	if (e < eNOERROR) ERR(e);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	printf("****************************** TEST#4, EduOM_NextObject. ******************************\n");

	
	/* Destroy File */
	e = SM_DestroyFile(&fid, NULL);
	if (e < eNOERROR) ERR(e); 

	return eNOERROR;
}

/*@================================
 * eduom_DumpPage()
 *================================*/
/*
 * Function: Four eduom_DumpPage(SlottedPage *)
 *
 * Description:
 *  Print the all contents of the given slotted page.
 *  The page is specified with the pointer to the buffer holding the page.
 *
 * Returns:
 *  error code
 *     eNOERROR
 */
Four eduom_DumpPage(
		SlottedPage *apage)     /* IN a buffer containning the slotted page */
{
	Object  *obj;    	 	/* points to the currently displayed object */
	ObjectID    movedOID;	/* ObjectID to which the obj was moved */
	Two     i;     			/* index variable */
	Four    j;      		/* index variable */
	
	
	printf("+------------------------------------------------------------+\n");
	printf("|  nSlots = %-3d         free = %-4d          unused = %-4d   |\n",
			apage->header.nSlots, apage->header.free, apage->header.unused);
	printf("| FREE = %-4d           CFREE = %-4d                         |\n",
			SP_FREE(apage), SP_CFREE(apage));
	printf("+------------------------------------------------------------+\n");
	printf("| fid = (%4d, %4d)                                         |\n",
			apage->header.fid.volNo, apage->header.fid.serial);                 /* COOKIE17NOV1999 */
	printf("| nextPage = %-10d         prevPage = %-10d        |\n",
			apage->header.nextPage, apage->header.prevPage);
	printf("| spaceListPrev = %-10d    spaceListNext = %-10d   |\n",
			apage->header.spaceListPrev, apage->header.spaceListNext);
	printf("+------------------------------------------------------------+\n");
	
	for (i = 0; i < apage->header.nSlots; i++) {
		if (apage->slot[-i].offset == EMPTYSLOT) continue;
		
		obj = (Object *)&(apage->data[apage->slot[-i].offset]);
		
		printf("|%3d| ", i);
		printf("%c", (obj->header.properties & P_MOVED) ? 'M':' ');
		printf("%c", (obj->header.properties & P_FORWARDED) ? 'F':' ');
		printf("%c", (obj->header.properties & P_LRGOBJ) ? 'L':' ');
		printf("%c", (obj->header.properties & P_LRGOBJ_ROOTWITHHDR) ? 'R':' ');
		printf(" %4d ", obj->header.length);
		
		if (obj->header.properties & P_MOVED) {
			/* moved object: print the moved ObjectID */
			
			movedOID = *((ObjectID *)(obj->data));
			printf("(%4d, %4d, %4d, %4d)                    ",
					movedOID.volNo, movedOID.pageNo, movedOID.slotNo, movedOID.unique);
			
		} else {
			/* plain data */
			
			if (obj->header.properties & P_LRGOBJ) {
				
				for(j = 0; j < 44; j++) putchar(' ');
				
			} else {
				
				for(j = 0; j < 44 && j < obj->header.length; j++)
					if (isprint(obj->data[j])) putchar(obj->data[j]);
					else putchar('~');
				
				for(; j < 44; j++)
					putchar(' ');
			}
		}
		
		printf(" |\n");
	}
	printf("+------------------------------------------------------------+\n");
	return(eNOERROR);

} /* eduom_DumpPage() */

		

/*@================================
 * eduom_DumpOnePage()
 *================================*/
/*
 * Function: Four eduom_DumpOnePage(PageID*)
 *
 * Description:
 *  Print all the contents of the given slotted page.
 *  The page to be printed is specified with its page identifier.
 *
 * Returns:
 *  error code
 *    eBADPAGEID_OM
 *    some errors caused by function calls
 */
Four eduom_DumpOnePage(
		PageID *pid)        /* IN page to dump */
{
	Four e;         /* error number */
	SlottedPage *apage;     /* pointer to buffer holding the page */
	
	
	/*@ parameter checking */
	if (pid == NULL || pid->pageNo == NIL) ERR(eBADPAGEID_OM);
	
	/*@ read the page into the buffer */
	e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);						   
	if (e < 0) ERR(e);
	
	
	printf("+------------------------------------------------------------+\n");				
	printf("|                 PageID = (%4d, %4d)                      |\n",
														       pid->volNo, pid->pageNo);
	printf("+------------------------------------------------------------+\n");
	
	/* call auxiary function with the pointer to the buffer */
	e = eduom_DumpPage(apage);
	if (e < 0) ERR(e);
	
	/*@ free the buffer */
	e = BfM_FreeTrain(pid, PAGE_BUF);
	if (e < 0) ERR(e);
	
	return(eNOERROR);
	
} /* eduom_DumpOnePage() */

/*@================================
 * eduom_DumpAllPage()
 *================================*/
/*
 * Function: Four eduom_DumpAllPage(PageID*)
 *
 * Description:
 *  Print all the contents of all the slotted page.
 *  The page to be printed is specified with its page identifier.
 *
 * Returns:
 *  error code
 *    eBADPAGEID_OM
 *    some errors caused by function calls
 */

Four eduom_DumpAllPage(
		PageID *pid)        /* IN page to dump */
{
	Four e;         /* error number */
	SlottedPage *apage;     /* pointer to buffer holding the page */
	
	
	/*@ parameter checking */
	if (pid == NULL || pid->pageNo == NIL) ERR(eBADPAGEID_OM);
	
	
	printf("+------------------------------------------------------------+\n");
	printf("|                 PageID = (%4d, %4d)                      |\n",
			pid->volNo, pid->pageNo);
	printf("+------------------------------------------------------------+\n");
	
	/* call auxiary function with the pointer to the buffer */
	do{
		/*@ read the page into the buffer */
		e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
		if (e < 0) ERR(e);
		
		eduom_DumpOnePage(pid);
		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");

		/*@ free the buffer */
		e = BfM_FreeTrain(pid, PAGE_BUF);
		if (e < 0) ERR(e);
		
		/* get page identifier of next page */      
		(*pid).pageNo = apage -> header.nextPage;  

	}while(pid != NULL && pid->pageNo != NIL );

	return(eNOERROR);
	
} /* eduom_DumpAllPage() */


/*@================================
 * eduom_GetNextPageID()
 *================================*/
/*
 * Function: Four eduom_GetNextPageID(PageID*)
 *
 * Description:
 *  Get next page identifier.
 *
 * Returns:
 *  error code
 *    eBADPAGEID_OM
 *    some errors caused by function calls
 */
Four eduom_GetNextPageID(
		PageID *pid)        /* IN page to dump */
{
	Four e;         /* error number */
	SlottedPage *apage;     /* pointer to buffer holding the page */
	
	
	/*@ parameter checking */
	if (pid == NULL || pid->pageNo == NIL) ERR(eBADPAGEID_OM);

	/*@ read the page into the buffer */
	e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
	if (e < 0) ERR(e);
	
	/*@ free the buffer */
	e = BfM_FreeTrain(pid, PAGE_BUF);
	if (e < 0) ERR(e);
	
	/* get page identifier of next page */      
	(*pid).pageNo = apage -> header.nextPage;     

	return(eNOERROR);
	
} /* eduom_GetNextPageID() */

char* itoa(Four val, Four base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}
