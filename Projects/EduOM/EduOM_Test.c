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
 * Module: EduOM_Test.c
 *
 * Description : 
 *  Test the EduOM.
 *
 * Exports:
 *  Four EduOM_Test(Four, Four)
 */

#include <string.h>
#include <stdbool.h>
#include "EduOM_common.h"
#include "EduOM.h"
#include "EduOM_Internal.h"
#include "EduOM_TestModule.h"

/*@================================
 * EduOM_Test()
 *================================*/
/*
 * Function: EduOM_Test(Four volId, Four handle)
 *
 * Description : 
 * 	EduOM_Test() tests EduOM that implements the operations 
 * 	of the object manager. The data structure is composed of 
 * 	the object header, slot, data. There are the following 
 * 	five APIs in EduOM. EduOM_CreateObject(), EduOM_DestroyObject(), 
 * 	EduOM_ReadObject(), EduOM_PrevObject(), EduOM_NextObject().
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
	char		buffer[32];								/* buffer for reading object */

	FILE 		*fp;
	Four		score;
	bool		pass;
	bool 		passCoarse;

	/* Create File */
    e = SM_CreateFile(volId, &fid, FALSE, NULL);
	if (e < eNOERROR) ERR(e);	

	/* Get catalog entry */
	e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
	if (e < eNOERROR) ERR(e);

    /* Open the test result file of the solution for evaluation */    
	if ((fp = fopen("result.txt", "r")) == NULL){
		fprintf(stderr, "ERROR");
		return -1;
	}


	/* #1 Start the test for EduOM_CreateObject */
	printf("****************************** TEST#1, EduOM_CreateObject and EduOM_DestroyObject ******************************\n");
	passCoarse = true;
	score = 0;
	for (i = 1; i <= 7; i++)
	{
		pass = true;
		switch(i){
			case 1:
				e = eduom_Test_1_1(&catalogEntry, &oid, fp, &pass);
				firstOid = oid;
				break;
			case 2:
				e = eduom_Test_1_2(&catalogEntry, &oid, fp, &pass);
				break;
			case 3:
				e = eduom_Test_1_3(&catalogEntry, &oid, fp, &pass);
				lastOid = oid;
				break;
			case 4:
				oid = firstOid;
				e = eduom_Test_1_4(&catalogEntry, &oid, fp, &pass);
				break;
 			case 5:
				oid = firstOid;
				e = eduom_Test_1_5(&catalogEntry, &oid, fp, &pass);
				break;
			case 6:
				oid = lastOid;
				e = eduom_Test_1_6(&catalogEntry, &oid, fp, &pass);
				break;
			case 7:
				e = eduom_Test_1_7(&catalogEntry, &oid, fp, &pass);
				break;
		}
		if (e < eNOERROR){                      
			printf("Total score: %d / 100\n", score);
			ERR(e);               
		}
		if (pass == true) printf("\n\tTest 1_%d has passed.\n", i);
		else
		{
			printf("\n\tTest 1_%d has failed.\n", i);
			passCoarse = false;
			break;
		}
		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");
		
	}
	
	if (passCoarse == true) score += 40;
	printf("Current score: %d / 40\n", score);
	printf("****************************** TEST#1, EduOM_CreateObject and EduOM_DestroyObject  ******************************\n");
	/* #1 End the test */

	printf("Press enter key to continue...");               
	getchar();                  
	printf("\n\n");

	/* #2 Start the test for EduOM_ReadObject */
	printf("****************************** TEST#2, EduOM_ReadObject. ******************************\n");

    passCoarse = true;
	for (i = 1; i <= 2; i++)
	{
		pass = true;
		switch(i){
			case 1:
				oid = firstOid;
				e = eduom_Test_2_1(&oid, fp, &pass);
				break;
			case 2:
				e = eduom_Test_2_2(&oid, fp, &pass);
				break;
		}
		if (e < eNOERROR){                      
			printf("Total score: %d / 100\n", score);
			ERR(e);
		}
		if (pass == true) printf("\n\tTest 2_%d has passed.\n", i);
		else
		{
			printf("\n\tTest 2_%d has failed.\n", i);
			passCoarse = false;
			break;
		}
		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");
		
	}
	
    if (passCoarse == true) score += 10;
	printf("Current score: %d / 50\n", score);
	printf("****************************** TEST#2, EduOM_ReadObject. ******************************\n");
	/* #2 End the test */
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


	/* #3 Start the test for EduOM_PrevObject */
    printf("****************************** TEST#3, EduOM_PrevObject. ******************************\n");
	passCoarse = true;
	for (i = 1; i <= 3; i++)
	{
		pass = true;
		switch(i){
			case 1:
				oid = firstOid;
				e = eduom_Test_3_1(&catalogEntry, &oid, fp, &pass);
				break;
			case 2:
				e = eduom_Test_3_2(&catalogEntry, &oid, fp, &pass);
				break;
			case 3:
				e = eduom_Test_3_3(&catalogEntry, &oid, fp, &pass);
				break;
		}
		if (e < eNOERROR){                      
			printf("Total score: %d / 100\n", score);
			ERR(e);
		}
		if (pass == true) printf("\n\tTest 3_%d has passed.\n", i);
		else
		{
			printf("\n\tTest 3_%d has failed.\n", i);
			passCoarse = false;
			break;
		}
		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");
	}
	if (passCoarse == true) score += 25;
	printf("Current score: %d / 75\n", score);
	printf("****************************** TEST#3, EduOM_PrevObject. ******************************\n");
	/* #3 End the test */

    printf("Press enter key to continue...");
	getchar();  
	printf("\n\n");

	/* #4 Start the test for EduOM_NextObject */
	printf("****************************** TEST#4, EduOM_NextObject. ******************************\n");
	for (i = 1; i <= 3; i++)
	{
        pass = true;
		switch(i){
			case 1:
				oid = firstOid;
				e = eduom_Test_4_1(&catalogEntry, &oid, fp, &pass);
				break;
			case 2:
				e = eduom_Test_4_2(&catalogEntry, &oid, fp, &pass);
				break;
			case 3:
				e = eduom_Test_4_3(&catalogEntry, &oid, fp, &pass);
				break;
		}
		if (e < eNOERROR){                      
			printf("Total score: %d / 100\n", score);
			ERR(e);
		}
		if (pass == true) printf("\n\tTest 4_%d has passed.\n", i);
		else
		{
			printf("\n\tTest 4_%d has failed.\n", i);
			passCoarse = false;
			break;
		}
		printf("Press enter key to continue...");
		getchar();
		printf("\n\n");
	}

	if (passCoarse == true) score += 25;
    
	printf("Current score: %d / 100\n", score);
	prirntf("****************************** TEST#4, EduOM_NextObject. ******************************\n");

	printf("Total score: %d / 100\n", score);

	fclose(fp);
	
	/* Destroy File */
	e = SM_DestroyFile(&fid, NULL);
	if (e < eNOERROR) ERR(e); 

	return eNOERROR;
}

/*@================================
 * eduom_Test_1_1()
 *================================*/
/*
 * Function: eduom_Test_1_1(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_1() tests EduOM_CreateObject() creating an object 
 *  when the near object in the parameter is NULL.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_1(
    ObjectID    *catalogEntry,							/* catalog object */
	ObjectID    *oid,                                   /* object identifeier */
	FILE		*fp,
	bool		*pass
)
{
	PageID      pid; 		                            /* dump page */
	char		omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";	/* test object */
	Four		i;										/* loop index */
    Four        e;                                      /* for errors */
	
    printf("Test 1_1 tests EduOM_CreateObject() creating an object when the near object in the parameter is NULL.\n");

	strcat(omTestObjectNo, "0");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_CreateObject(catalogEntry, NULL, NULL, strlen(omTestObjectNo), omTestObjectNo , oid);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d ) has been inserted into the page\n", oid->pageNo, oid->slotNo);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;

	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);
}

/*@================================
 * eduom_Test_1_2()
 *================================*/
/*
 * Function: eduom_Test_1_2(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_2() tests EduOM_CreateObject() creating objects 
 *  when the near object in the parameter is not NULL. 
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_2(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                    /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	PageID      pid;                                    /* dump page */
	char		omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";	/* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_2 tests EduOM_CreateObject() creating an object when the near object in the parameter is not NULL.\n");
	
	for (i = 1; i < FIRST_PAGE_OBJECT; i++){
		strcpy(omTestObjectNo, "EduOM_TestModule_OBJECT_NUM_");
		strcat(omTestObjectNo, itoa(i,10));

		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_CreateObject(catalogEntry, oid, NULL, strlen(omTestObjectNo), omTestObjectNo, oid);
		if(e < eNOERROR) ERR(e);
		if (i <= 5 || i >= FIRST_PAGE_OBJECT- 5) printf("The object ( %d, %d ) has been inserted into the page\n", oid->pageNo, oid->slotNo);
		else if (i == 6) printf("...\n");
	}

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;

	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);

	return (eNOERROR);
}

/*@================================
 * eduom_Test_1_3()
 *================================*/
/*
 * Function: eduom_Test_1_3(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_3() tests EduOM_CreateObject() creating objects until a new page is needed.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_3(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                   /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{   
	PageID      pid;                                    /* dump page */
	char		omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";	/* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_3 tests EduOM_CreateObject() creating objects until a new page is needed.\n");

	for (i = FIRST_PAGE_OBJECT; i < THIRD_PAGE_OBJECT; i++){
		strcpy(omTestObjectNo, "EduOM_TestModule_OBJECT_NUM_");
		strcat(omTestObjectNo, itoa(i,10));
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_CreateObject(catalogEntry, oid, NULL, strlen(omTestObjectNo), omTestObjectNo, oid);
		if (e < eNOERROR) ERR(e);

		if (i <= 5 + FIRST_PAGE_OBJECT || i >= THIRD_PAGE_OBJECT - 5) printf("The object ( %d, %d ) has been inserted into the page\n", oid->pageNo, oid->slotNo);
		else if (i == 6 + FIRST_PAGE_OBJECT) printf("...\n");

	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
    pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;


	e = eduom_CheckAllPages(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);

}

/*@================================
 * eduom_Test_1_4()
 *================================*/
/*
 * Function: eduom_Test_1_4(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_4() tests EduOM_DestroyObject() destroying the objects that is not the last object in the pages
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_4(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                   /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
    PageID      pid;                                    /* dump page */
	char        omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";    /* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_4 tests EduOM_DestroyObject() destroying the objects that is not the last object in the pages.\n");

	for (i = 0; i < 10; i++)
	{
		oid->slotNo += 2;
		oid->unique += 2;
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_DestroyObject(catalogEntry, oid, &dlPool, &dlHead);
		printf("The object ( %d, %d ) has been destroyed into the page\n", oid->pageNo, oid->slotNo);
	}
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;
   
	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);

	return (eNOERROR);

}

/*@================================
 * eduom_Test_1_5()
 *================================*/
/*
 * Function: eduom_Test_1_5(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_5() tests EduOM_CreateObject() creating a new object when needing to compact the page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_5(
	ObjectID    *catalogEntry,                     		/* catalog object */
	ObjectID    *oid,                                   	/* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	PageID      pid;                                    /* dump page */
	char        omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";    /* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_5 tests EduOM_CreateObject() creating a new object when needing to compact the page.\n");

	strcpy(omTestObjectNo, "EduOM_OBJECT_FOR_COMPACT_TEST");
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_CreateObject(catalogEntry, oid, NULL, strlen(omTestObjectNo), omTestObjectNo, oid);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d ) has been inserted into the page\n", oid->pageNo, oid->slotNo);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;
	
	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);

}

/*@================================
 * eduom_Test_1_6()
 *================================*/
/*
 * Function: eduom_Test_1_6(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_6() tests EduOM_DestroyObject() destroying the objects that is the last object in the page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_6(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                       /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	PageID      pid;                                    /* dump page */ 
	char        omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";    /* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_6 ts EduOM_DestroyObject() destroying the objects that is the last object in the page.\n");
	
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_DestroyObject(catalogEntry, oid, &dlPool, &dlHead);
	if (e < eNOERROR) ERR(e);
	printf("The object ( %d, %d ) has been destroyed from the page\n", oid->pageNo, oid->slotNo);
	
	oid->slotNo--;
	oid->unique--;
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;
	
	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);

	return (eNOERROR);
}

/*@================================
 * eduom_Test_1_7()
 *================================*/
/*
 * Function: eduom_Test_1_7(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_1_7() tests EduOM_DestroyObject() destroying the object when it is the only object in the page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_1_7(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                       /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	PageID      pid;                                    /* dump page */
	char        omTestObjectNo[32] = "EduOM_TestModule_OBJECT_NUM_";    /* test object */
	Four        i;                                      /* loop index */
	Four        e;                                      /* for errors */

    printf("Test 1_7 tests EduOM_DestroyObject() destroying the object when it is the only object in the page.\n");
	
	do{
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduOM_DestroyObject(catalogEntry, oid, &dlPool, &dlHead);
		if (e < eNOERROR) ERR(e);
		
		printf("The object ( %d, %d ) has been destroyed from the page\n", oid->pageNo, oid->slotNo);
		oid->slotNo--;
		oid->unique--;
		
	}while(oid->slotNo >= 0);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;

	e = eduom_GetPrevPageID(&pid);
	if (e < eNOERROR) ERR(e);
	
	e = eduom_CheckOnePage(&pid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);
}

/*@================================
 * eduom_Test_2_1()
 *================================*/
/*
 * Function: eduom_Test_2_1(ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_2_1() tests EduOM_ReadObject() reading part of the objects in the page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_2_1(
	ObjectID    *oid,                            	/* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
    char        buffer[32];                         /* buffer for reading object */
	char		data[32];							/* buffer for reading ojbect of the solution */
	char		str[100];
	Four		i;
	Four		e;

    printf("Test 2_1 tests EduOM_ReadObject() reading part of the objects in the page.\n");

	memset(buffer, 0, 32);
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_ReadObject(oid, 7, 15, &(buffer[0]));
	if (e < eNOERROR) ERR(e);

	printf("Read part of the first object, from 7th character to 15th character, in the first page.\n");
	printf("---------------------------------- Result ----------------------------------\n");
	printf("%s\n", buffer);

	fgets(str, 100, fp);
	fscanf(fp, "%s\n", data);
	if (strcmp(buffer, data) != 0)	*pass = false;

	return (eNOERROR);
}

/*@================================
 * eduom_Test_2_2()
 *================================*/
/*
 * Function: eduom_Test_2_2(ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_2_2() tests EduOM_ReadObject() reading all objects in the page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_2_2(
	ObjectID    *oid,                               /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	char        buffer[32];                         /* buffer for reading object */
	char        data[32];                           /* buffer for reading ojbect of the solution */
	char		str[100];
	Four		i;
	Four		e;

    printf("Test 2_2 tests EduOM_ReadObject() reading all objects in the page.\n");

	memset(buffer, 0, 32);
	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_ReadObject(oid, 0, REMAINDER, &(buffer[0]));
	if (e < eNOERROR) ERR(e);

	printf("Read all of the first object in the first page\n");
	printf("---------------------------------- Result ----------------------------------\n");
	printf("%s\n", buffer);

    fgets(str, 100, fp);
    fscanf(fp, "%s\n", data);
	if (strcmp(buffer, data) != 0)  *pass = false;

	return (eNOERROR);
}

/*@================================
 * eduom_Test_3_1()
 *================================*/
/*
 * Function: eduom_Test_3_1(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_3_1() tests EduOM_Cts EduOM_PrevObject() when the current object is NULL. 
 *  It has to return the last object among all the objects.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_3_1(
    ObjectID    *catalogEntry,                          /* catalog object */
    ObjectID    *oid,                                   /* object identifeier */
    FILE        *fp,
    bool        *pass
)
{
    SlottedPage     *apage;
	PageID      pid;                                    /* dump page */
	Four		i;
	Four		e;

    /* Test for EduOM_PrevObject() when parameter curOID is NULL */
    printf("Test 3_1 tests EduOM_PrevObject() when the current object is NULL. \nIt has to return the last object among all the objects.\n");
    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduOM_PrevObject(catalogEntry, NULL, oid, NULL);
    if (e < eNOERROR) ERR(e);
    printf("Press enter key to continue...");
    getchar();
    printf("\n\n");

	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;

	e = eduom_CheckObject(oid, fp, pass);
	if (e < eNOERROR) ERR(e);

    return (eNOERROR);
}

/*@================================
 * eduom_Test_3_2()
 *================================*/
/*
 * Function: eduom_Test_3_2(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_3_2() tests EduOM_PevObject() when the current object is not NULL.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_3_2(
	ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                   /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
    SlottedPage     *apage;
	PageID      	pid;                                    /* dump page */
	Four        	i;
	Four        	e;

    printf("Test 3_2 tests EduOM_PevObject() when the current object is not NULL.\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_PrevObject(catalogEntry, oid, oid, NULL);
	if (e < eNOERROR) ERR(e);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;
	
	e = eduom_CheckObject(oid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);
	
}

/*@================================
 * eduom_Test_3_3()
 *================================*/
/*
 * Function: eduom_Test_3_3(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_3_3() tests EduOM_PrevObject() when the current object is the first object in the page. 
 *  It has to return the last object of the previous page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_3_3(
    ObjectID    *catalogEntry,                          /* catalog object */
    ObjectID    *oid,                                   /* object identifeier */
    FILE        *fp,
    bool        *pass
)
{
    PageID          pid;                                    /* dump page */
    Four            i;
    Four            e;

    /* Test for EduOM_PrevObjeect when object whose objectID is parameter curOID is first object in the page */
    printf("Test 3_3 tests EduOM_PrevObject() when the current object is the first object in the page. \nIt has to return the last object of the previous page.\n");
    do
    {
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduOM_PrevObject(catalogEntry, oid, oid, NULL);
        if (e < eNOERROR) ERR(e);
    }while(oid->slotNo != 0);
    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduOM_PrevObject(catalogEntry, oid, oid, NULL);
    if (e < eNOERROR) ERR(e);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;
	
    e = eduom_CheckObject(oid, fp, pass);
    if (e < eNOERROR) ERR(e);
    
    return (eNOERROR);

}

/*@================================
 * eduom_Test_4_1()
 *================================*/
/*
 * Function: eduom_Test_4_1(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_4_1() tests EduOM_NextObject() when the current object is NULL. 
 *  It has to return the first object among all the objects.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_4_1(
    ObjectID    *catalogEntry,                          /* catalog object */
	ObjectID    *oid,                                   /* object identifeier */
	FILE        *fp,
	bool        *pass
)
{
	SlottedPage     *apage;
	PageID          pid;                                    /* dump page */
	Four            i;
	Four            e;

    printf("Test 4_1 tests EduOM_NextObject() when the current object is NULL. \nIt has to return the first object among all the objects.\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduOM_NextObject(catalogEntry, NULL, oid, NULL);
	if (e < eNOERROR) ERR(e);

	printf("Press enter key to continue...");                   
	getchar();                      
	printf("\n\n");
	
    pid.volNo = oid->volNo;
	pid.pageNo = oid->pageNo;

	e = eduom_CheckObject(oid, fp, pass);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);

}

/*@================================
 * eduom_Test_4_2()
 *================================*/
/*
 * Function: eduom_Test_4_2(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_4_2() tests EduOM_NextObject() when the current object is not NULL.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_4_2(
    ObjectID    *catalogEntry,                          /* catalog object */
    ObjectID    *oid,                                   /* object identifeier */
    FILE        *fp,
    bool        *pass
)
{   
    SlottedPage     *apage;                                 
    PageID          pid;                                    /* dump page */
    Four            i;
    Four            e;
    
    printf("Test 4_2 tests EduOM_NextObject() when the current object is not NULL.\n");

    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduOM_NextObject(catalogEntry, oid, oid, NULL);
    if (e < eNOERROR) ERR(e);

    printf("Press enter key to continue...");
    getchar();
    printf("\n\n");

    pid.volNo = oid->volNo;
    pid.pageNo = oid->pageNo;
    
    e = eduom_CheckObject(oid, fp, pass);
    if (e < eNOERROR) ERR(e);
    
    return (eNOERROR);

}

/*@================================
 * eduom_Test_4_3()
 *================================*/
/*
 * Function: eduom_Test_4_3(ObjectID *catalogEntry, ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_Test_4_3() tests EduOM_NextObject() when the current object is the first object in the page. 
 *  It has to return the first object of the next page
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_Test_4_3(
    ObjectID    *catalogEntry,                          /* catalog object */
    ObjectID    *oid,                                   /* object identifeier */
    FILE        *fp,
    bool        *pass
)
{   
    SlottedPage     *apage;                                 
    PageID          pid;                                    /* dump page */
    Four            i;
    Four            e;
    
    printf("Test 4_3 tests EduOM_NextObject() when the current object is the first object in the page. \nIt has to return the first object of the next page.\n");

    do
    {
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduOM_NextObject(catalogEntry, oid, oid, NULL);
        if (e < eNOERROR) ERR(e);
    }while(oid->slotNo != 0);

    printf("Press enter key to continue...");
    getchar();
    printf("\n\n");

    pid.volNo = oid->volNo;
    pid.pageNo = oid->pageNo;
    
    e = eduom_CheckObject(oid, fp, pass);
    if (e < eNOERROR) ERR(e);
    
    return (eNOERROR);

}

/*@================================
 * eduom_CheckOnePage()
 *================================*/
/*
 * Function: eduom_CheckOnePage(PageID *pid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_CheckOnePage() compare the page to that of the solution.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_CheckOnePage(
	PageID			*pid,
	FILE			*fp,
	bool			*pass
)
{
	SlottedPage		*apage;
	Four			i;
	Four			e;

	/*@ read the page into the buffer */
	e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
	if (e < 0) ERR(e);
	

	printf("\n---------------------------------- Result ----------------------------------\n");
	eduom_DumpPage(apage);
	eduom_CheckPage(apage, fp, pass);
	
	/*@ free the buffer */
	e = BfM_FreeTrain(pid, PAGE_BUF);
	if (e < eNOERROR) ERR(e);
	
	return (eNOERROR);

}

/*@================================
 * eduom_CheckAllPages()
 *================================*/
/*
 * Function: eduom_CheckAllPAges(PageID *pid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_CheckAllPages() tests EduOM_CreateObject() creating an object  *  when the near object in the parameter is NULL.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four eduom_CheckAllPages(
	PageID          *pid,
	FILE            *fp,
	bool            *pass
)
{
	SlottedPage     *apage;
	PageID			prevPid;
	Four            e;
	
	/*@ read the page into the buffer */
	e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
	if (e < eNOERROR) ERR(e);
	
	if (apage->header.prevPage != -1) {
		prevPid.volNo = apage->header.pid.volNo;
		prevPid.pageNo = apage->header.prevPage;
		e = eduom_CheckAllPages(&prevPid, fp, pass);
		if (e < eNOERROR) ERR(e);
	}
	eduom_DumpPage(apage);
	
	eduom_CheckPage(apage, fp, pass);
	
	/*@ free the buffer */
	e = BfM_FreeTrain(pid, PAGE_BUF);
	if (e < 0) ERR(e);
	
	return (eNOERROR);

}

/*@================================
 * eduom_CheckPage()
 *================================*/
/*
 * Function: eduom_CheckPage(SlottedPage *apage, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_CheckPage() compare the page to that of the solution.
 *
 * Returns:
 *  NONE
 */
void eduom_CheckPage(SlottedPage *apage, FILE *fp, bool *pass)
{
	Object  				*obj;           /* points to the currently displayed object */
	Four					volNo, pageNo;
	Four					nSlots;
	Four					free;
	Four					unused;
	Four					sp_free, sp_cfree;
	Four					fVolNo, fSerial;
	Four					nextPage, prevPage;
	Four					spaceListPrev, spaceListNext;
	Four					len;	
	Four					obj_idx;
	char					obj_data[32];
	char					str[100];
	Four					i;
	Four					e;

	for (i = 0; i < 2; i++) fgets(str, 100, fp);

	fscanf(fp, "+------------------------------------------------------------+\n");
	fscanf(fp, "|                 PageID = (%d, %d)                      |\n", &volNo, &pageNo);
	fscanf(fp, "+------------------------------------------------------------+\n");
	fscanf(fp, "+------------------------------------------------------------+\n");
	fscanf(fp, "|  nSlots = %d         free = %d          unused = %d   |\n", &nSlots, &free, &unused);
	fscanf(fp, "| FREE = %d           CFREE = %d                         |\n", &sp_free, &sp_cfree);
	fscanf(fp, "+------------------------------------------------------------+\n");
    fscanf(fp, "| fid = (%d, %d)                                         |\n", &fVolNo, &fSerial);
	fscanf(fp, "| nextPage = %d         prevPage = %d        |\n", &nextPage, &prevPage);
	fscanf(fp, "| spaceListPrev = %d    spaceListNext = %d   |\n", &spaceListPrev, &spaceListNext);
	fscanf(fp, "+------------------------------------------------------------+\n");

	if (apage->header.pid.volNo != volNo || apage->header.pid.pageNo != pageNo || apage->header.nSlots != nSlots ||
		apage->header.free != free || apage->header.unused != unused || SP_FREE(apage) != sp_free || SP_CFREE(apage) != sp_cfree ||
		apage->header.fid.volNo != fVolNo || apage->header.fid.serial != fSerial ||  
		apage->header.nextPage != nextPage || apage->header.prevPage != prevPage ||
		apage->header.spaceListPrev != spaceListPrev || apage->header.spaceListNext != spaceListNext)
	{
		*pass = false;
	}


    for (i = 0; i < apage->header.nSlots && *pass == true; i++) {
        if (apage->slot[-i].offset == EMPTYSLOT) continue;
		        
		obj = (Object *)&(apage->data[apage->slot[-i].offset]);

        fscanf(fp, "|%d| %d %s	|\n ", &obj_idx, &len, obj_data);
		if (i != obj_idx || len != obj->header.length || strncmp(obj_data, obj->data, len) != 0)
		{
			*pass = false;
			break;
		}
    }
	
	fscanf(fp, "+------------------------------------------------------------+\n");

}

/*@================================
 * eduom_CheckObject()
 *================================*/
/*
 * Function: eduom_CheckObject(ObjectID *oid, FILE *fp, bool *pass)
 *
 * Description : 
 *  eduom_CheckObject() compare the object to that of the solution.
 *
 * Returns:
 *  NONE
 */
void eduom_CheckObject
(
 	ObjectID		*oid,
	FILE			*fp,
	bool			*pass
)
{
	Four			volNo;
	Four			pageNo;
	Four			slotNo;
	Four			unique;
	char			str[100];
	Four			i;
	Four			e;

	fgets(str, 100, fp);

	fscanf(fp, "[ObjectID] : (%d, %d, %d, %d)\n", &volNo, &pageNo, &slotNo, &unique);
	for (i = 0; i < 5; i++) fgets(str, 100, fp);

	if (oid->volNo != volNo || oid->pageNo != pageNo || oid->slotNo != slotNo || oid->unique != unique)
	{
		*pass = false;
	}

	printf("\n---------------------------------- Result ----------------------------------\n");
	e = OM_DumpObject(oid);
	if (e < eNOERROR) ERR(e);

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
	printf("|                 PageID = (%4d, %4d)                      |\n",
			apage->header.pid.volNo, apage->header.pid.pageNo);
	printf("+------------------------------------------------------------+\n");
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
 * eduom_GetPrevPageID()
 *================================*/
/*
 * Function: Four eduom_GetPrevPageID(PageID*)
 *
 * Description:
 *  Get prev page identifier.
 *
 * Returns:
 *  error code
 *    eBADPAGEID_OM
 *    some errors caused by function calls
 */
Four eduom_GetPrevPageID(
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
	(*pid).pageNo = apage -> header.prevPage;     

	return(eNOERROR);
	
} /* eduom_GetNextPageID() */

char* itoa(Four val, Four base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}
