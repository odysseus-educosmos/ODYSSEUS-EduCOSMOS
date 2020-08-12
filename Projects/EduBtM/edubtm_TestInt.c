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
 * Module: EduBtM_TestInt.c
 *
 * Description : 
 * Test the EduBtM where the data type is integer.
 *
 * Exports:
 *  Four EduBtM_TestInt(ObjectID *)
 */

#include <string.h>
#include "EduBtM_common.h"
#include "EduBtM_basictypes.h"
#include "EduBtM.h"
#include "EduBtM_TestModule.h"
#include "OM_Internal.h"

/*@================================
 * edubtm_TestInt()
 *================================*/
/*
 * Function: EduBtM_TestInt(ObjectID *catalogEntry)
 *
 * Description : 
 *  EduBtM_TestInt() tests EduBtM where the data type is integer.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt(ObjectID *catalogEntry, FILE *fp, Four *score, Four *scoreOpt)
{
	PageID				rootPid;	    				/* root page identifier */
    KeyValue    		kval;                           /* value of the key */
	KeyDesc				kdesc;
	Four				i;
	Four				e;								/* error log */

	bool                pass;
	bool                passCoarse;

	printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");

	pass = true;
	e = edubtm_TestInt_1_1(catalogEntry, &rootPid, &kdesc, fp, &pass);
	if (e < eNOERROR) {
		printf("Total score: %d / 100 + %d / 30\n", *score, *scoreOpt);
		ERR(e);
	}
    if (pass == true)
    {
        printf("\n\tTest 1_1 has passed. \n");
        *score += 10;
    }
    else printf("\n\tTest 1_1 has failed. \n");

    printf("Press enter key to continue...");
    getchar();
    printf("\n\n");

	printf("Current score: %d / 10\n", *score);
    printf("Press enter key to continue...");
    getchar();
    printf("\n\n");
    printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");

	printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");

	passCoarse = true;
	for (i = 1; i <= 2; i ++)
	{	
		pass = true;
		switch (i) {
			case 1: 
				e = edubtm_TestInt_2_1(catalogEntry, &rootPid, &kdesc, fp, &pass);
				break;
			case 2:	
				e = edubtm_TestInt_2_2(catalogEntry, &rootPid, &kdesc, fp, &pass);
				break;
		}
		if (e < eNOERROR) {
			printf("Total score: %d / 100 + %d / 30\n", *score, *scoreOpt);
			ERR(e);
		} 
        if (pass == true) printf("\n\tTest 2_%d has passed.\n", i);
        else
        {
            printf("\n\tTest 2_%d has failed. \n", i);
            passCoarse = false;
        }
        printf("Press enter key to continue...");
        getchar();
        printf("\n\n");
	}
	
	if (passCoarse == true) *score += 15;
	printf("Current score: %d / 25\n", *score);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
    printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");

    printf("****************************** TEST#3, EduBtM_Fetch and EduBtM_FetchNext. ******************************\n");
	passCoarse = true;
	for (i = 1; i <= 2; i++)
	{
		pass = true;
		switch (i) {
			case 1:
				e = edubtm_TestInt_3_1(catalogEntry, &rootPid, &kdesc, fp, &pass);
				break;
			case 2:
				e = edubtm_TestInt_3_2(catalogEntry, &rootPid, &kdesc, fp, &pass);
				break;
		}
	    if (e < eNOERROR) {
			printf("Total score: %d / 100 + %d / 30\n", *score, *scoreOpt);
			ERR(e);
		} 
		if (pass == true) printf("\n\tTest 3_%d has passed.\n", i);
		else
		{			
			printf("\n\tTest 3_%d has failed. \n", i);
			passCoarse = false;
		}

		printf("Press enter key to continue...");       
		getchar();          
		printf("\n\n");

	}

	if (passCoarse == true) *score += 15;
	printf("Current score: %d / 40\n", *score);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
    printf("****************************** TEST#3, EduBtM_Fetch and EduBtM_FetchNext. ******************************\n");

    printf("****************************** TEST#4, EduBtM_Delete. (Optional)  ******************************\n");
	passCoarse = true;
    for (i = 1; i <= 2; i++)
    {
		pass = true;
        switch (i) {
            case 1:
                e = edubtm_TestInt_4_1(catalogEntry, &rootPid, &kdesc, fp, &pass);
                break;
            case 2:
	            e = edubtm_TestInt_4_2(catalogEntry, &rootPid, &kdesc, fp, &pass);
                break;
        }    
		if (e < eNOERROR) {
			printf("Total score: %d / 100 + %d / 30\n", *score, *scoreOpt);
			ERR(e);
		} 
        if (pass == true) printf("\n\tTest 4_%d has passed.\n", i);
		else
		{
			printf("\n\tTest 4_%d has failed. \n", i);
			passCoarse = false;
		}

        printf("Press enter key to continue...");
        getchar();
        printf("\n\n");
    }
	if (passCoarse == true)
	{
		printf("\n\tTest 4_1 has passed.\n");
		*scoreOpt += 15;
	}
	else printf("\n\tTest 4_1 has failed.\n");

	printf("Current score: %d / 40 + %d / 15\n", *score, *scoreOpt);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
    printf("****************************** TEST#4, EduBtM_Delete. (Optional)  ******************************\n");

    printf("****************************** TEST#5, EduBtM_DropIndex.  ******************************\n");
	pass = true;
	e = edubtm_TestInt_5_1(catalogEntry, &rootPid, &kdesc, fp, &pass);
	if (e < eNOERROR) {
		printf("Total score: %d / 100 + %d / 30\n", *score, *scoreOpt);
		ERR(e);
	} 
	if (pass == true)
	{
		printf("\n\tTest 5_1 has passed. \n");
		*score += 10;
	}
	else printf("\n\tTest 5_1 has failed. \n");

	printf("Current score: %d / 50 + %d / 15\n", *score, *scoreOpt);
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
    printf("****************************** TEST#5, EduBtM_DropIndex.  ******************************\n");

	return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_1_1()
 *================================*/
/*
 * Function: EduBtM_TestInt_1_1(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_1_1() tests EduBtM_CreateIndex() creating a root page.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_1_1(
	ObjectID			*catalogEntry, 
	PageID				*rootPid,
	KeyDesc				*kdesc,
	FILE				*fp,
	bool				*pass
)
{
	
	Four				e;

    printf("Test 1_1 tests EduBtM_CreateIndex() creating a root page.\n");

    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduBtM_CreateIndex(catalogEntry, rootPid);
    if (e < eNOERROR) ERR(e);

    /* Construct Kval and Kdesc */
    kdesc->flag = KEYFLAG_UNIQUE;
    kdesc->nparts = 1;
    kdesc->kpart[0].type = SM_INT;
    kdesc->kpart[0].offset = 0;
    kdesc->kpart[0].length = sizeof(Four);

    printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	e = edubtm_CheckOnePage((PageID*)rootPid, kdesc->kpart[0].type, fp, pass);
	if (e < eNOERROR) ERR(e);

	return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_2_1()
 *================================*/
/*
 * Function: EduBtM_TestInt_2_1(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_2_1() tests EduBtM_InsertObject() inserting the objects before the page is overflowed.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_2_1(
    ObjectID            	*catalogEntry,
    PageID     				*rootPid,
	KeyDesc					*kdesc,
	FILE					*fp,
	bool					*pass
)
{
	char					obj[100];
	ObjectID				oid;
    KeyValue            	kVal;
	Four					i;
    Four                	e;

    printf("Test 2_1 tests EduBtM_InsertObject() inserting the objects before the page is overflowed.\n");

    kVal.len = sizeof(Four_Invariable);

    for (i = 0; i < 184; i++){
		memcpy(&obj, &i, sizeof(Four_Invariable));
		e = OM_CreateObject(catalogEntry, NULL, NULL, strlen(obj), obj, &oid);
		if (e < eNOERROR) ERR(e);

        memcpy(&(kVal.val[0]), &i, sizeof(Four_Invariable));
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBtM_InsertObject(catalogEntry, rootPid, kdesc, &kVal, &oid, NULL, NULL);
        if(e < eNOERROR) ERR(e);
		
		if(i < 5 || i > 178) printf("The object (key: %d , OID: (%4d, %4d, %4d, %4d)) has been inserted into the index.\n", i, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
		else if (i == 5) printf("...\n");

    }

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    e = edubtm_CheckOnePage(rootPid, kdesc->kpart[0].type, fp, pass);
	if (e < eNOERROR) ERR(e);

    return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_2_2()
 *================================*/
/*
 * Function: EduBtM_TestInt_2_2(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_2_2() tests EduBtM_InsertObject() inserting about the 27,000 objects, 
 *  which make the depth of the tree to be three.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_2_2(
    ObjectID                *catalogEntry,
    PageID                  *rootPid,
    KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass
)
{
	char					obj[100];
    ObjectID                oid;
    KeyValue                kVal;
    Four                    i;
    Four                    e;

    printf("Test 2_2 tests EduBtM_InsertObject() inserting about the 27,000 objects, which make the depth of the tree to be three.\n");

    for (i = 184; i < 27200; i++){
        memcpy(&obj, &i, sizeof(Four_Invariable));
		e = OM_CreateObject(catalogEntry, NULL, NULL, strlen(obj), obj, &oid);
		if (e < eNOERROR) ERR(e);

		memcpy(&(kVal.val[0]), &i, sizeof(Four_Invariable));
        /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
        e = EduBtM_InsertObject(catalogEntry, rootPid, kdesc, &kVal, &oid, NULL, NULL);
        if(e < eNOERROR) ERR(e);
		if(i < 189 || i > 27194) printf("The object (key: %d , OID: (%4d, %4d, %4d, %4d)) has been inserted into the index.\n", i, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
		else if (i == 190) printf("...\n");
    }

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    e = edubtm_CheckFPages(rootPid, kdesc->kpart[0].type, fp, pass);
    if (e < eNOERROR) ERR(e);

    return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_3_1()
 *================================*/
/*
 * Function: EduBtM_TestInt_3_1(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_3_1() tests EduBtM_Fetch() where the fetch condition is for an exact match query.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_3_1(
	ObjectID                *catalogEntry,
	PageID                  *rootPid,
	KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass
)
{
	KeyValue				startKVal;
	KeyValue				stopKVal;
	Four					key;
	Four					startCompOp;
	Four					stopCompOp;
	BtreeCursor				cursor;
	Four					e;

	char					str[100];

    printf("Test 3_1 tests EduBtM_Fetch() where the fetch condition is for an exact match query.\n");

	/* Exact Match */
	startKVal.len = sizeof(Four_Invariable);
	stopKVal.len = sizeof(Four_Invariable);

	startCompOp = SM_EQ;
	stopCompOp = SM_EQ;

	key = 1;
	memcpy(&(startKVal.val[0]), &key, sizeof(Four_Invariable));
    memcpy(&(stopKVal.val[0]), &key, sizeof(Four_Invariable));

	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
	if (e < eNOERROR) ERR(e);
	printf("OID: (%d, %d, %d, %d)\n", cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	fgets(str, 100, fp);
	edubtm_CheckObject(&cursor.oid, fp, pass);	

	key = 1000;
	memcpy(&(startKVal.val[0]), &key, sizeof(Four_Invariable));
	memcpy(&(stopKVal.val[0]), &key, sizeof(Four_Invariable));

	
	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
	if (e < eNOERROR) ERR(e);
	printf("OID: (%d, %d, %d, %d)\n", cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	edubtm_CheckObject(&cursor.oid, fp, pass);	

	key = 10000;
	memcpy(&(startKVal.val[0]), &key, sizeof(Four_Invariable));
	memcpy(&(stopKVal.val[0]), &key, sizeof(Four_Invariable));
	
	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
	if (e < eNOERROR) ERR(e);
	printf("OID: (%d, %d, %d, %d)\n", cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	edubtm_CheckObject(&cursor.oid, fp, pass);	

	/* BOF and EOF */
    startCompOp = SM_BOF;
    stopCompOp = SM_BOF;

	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
    if (e < eNOERROR) ERR(e);
	printf("OID: (%d, %d, %d, %d)\n", cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	edubtm_CheckObject(&cursor.oid, fp, pass);	

	startCompOp = SM_EOF;
	stopCompOp = SM_EOF;

	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
	if (e < eNOERROR) ERR(e);
	printf("OID: (%d, %d, %d, %d)\n", cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	edubtm_CheckObject(&cursor.oid, fp, pass);	

	return eNOERROR;

}

/*@================================
 * EduBtM_TestInt_3_2()
 *================================*/
/*
 * Function: EduBtM_TestInt_3_2(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_3_2() tests EduBtM_Fetch() where the fetch condition is for a range query.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_3_2(
    ObjectID                *catalogEntry,
    PageID                  *rootPid,   
    KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass
)       
{   
    KeyValue                startKVal;
    KeyValue                stopKVal;
    Four                    key;
    Four                    startCompOp;
    Four                    stopCompOp;
	Four					i;
    BtreeCursor             cursor;
    BtreeCursor			 	next;                                   /* next object cursor from EduBtM_FetchNext() */
    Four                    e;

	char					str[100];

    printf("Test 3_2 tests EduBtM_Fetch() where the fetch condition is for a range query.\n");
	
    startKVal.len = sizeof(Four_Invariable);
	stopKVal.len = sizeof(Four_Invariable);

	startCompOp = SM_GT;
	stopCompOp = SM_LE;
	 
	key = 90;
    memcpy(&(startKVal.val[0]), &key, sizeof(Four_Invariable));

	key = 95; 
	memcpy(&(stopKVal.val[0]), &key, sizeof(Four_Invariable));

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
	if (e < eNOERROR) ERR(e);
 
	memcpy(&key, &(cursor.key.val[0]), sizeof(Four_Invariable));

	printf("Key: %d, OID: (%d, %d, %d, %d)\n",
			key, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	fgets(str, 100, fp);
	edubtm_CheckObject(&cursor.oid, fp, pass);

	for (i = 1; i < 5; i++)
	{
		 e = EduBtM_FetchNext(rootPid, kdesc, &stopKVal, stopCompOp, &cursor, &next); 
		 if (e < eNOERROR) ERR(e);
		 
		 cursor = next;
		 memcpy(&key, &(cursor.key.val[0]), sizeof(Four_Invariable));

		 printf("Key: %d, OID: (%d, %d, %d, %d)\n", key, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);

	 	 edubtm_CheckObject(&cursor.oid, fp, pass);

	}
	
    startCompOp = SM_LT;
    stopCompOp = SM_GE;

    key = 95;
    memcpy(&(startKVal.val[0]), &key, sizeof(Four_Invariable));

    key = 90;
    memcpy(&(stopKVal.val[0]), &key, sizeof(Four_Invariable));

    /* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
    e = EduBtM_Fetch(rootPid, kdesc, &startKVal, startCompOp, &stopKVal, stopCompOp, &cursor);
    if (e < eNOERROR) ERR(e);
 
	memcpy(&key, &(cursor.key.val[0]), sizeof(Four_Invariable));

    printf("Key: %d, OID: (%d, %d, %d, %d)\n", key, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique); 
	edubtm_CheckObject(&cursor.oid, fp, pass);

    for (i = 1; i < 5; i++)
    {
         e = EduBtM_FetchNext(rootPid, kdesc, &stopKVal, stopCompOp, &cursor, &next);
         if (e < eNOERROR) ERR(e);

         cursor = next;
		 memcpy(&key, &(cursor.key.val[0]), sizeof(Four_Invariable));

         printf("Key: %d, OID: (%d, %d, %d, %d)\n", key, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);
	 	 edubtm_CheckObject(&cursor.oid, fp, pass);

    }
    
	return eNOERROR;

}

/*@================================
 * EduBtM_TestInt_4_1()
 *================================*/
/*
 * Function: EduBtM_TestInt_4_1(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_4_1() tests EduBtM_DeleteObject() deleting the object. It does not need a redistribution.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_4_1(
    ObjectID                *catalogEntry,
    PageID                  *rootPid,
    KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass

)
{
    KeyValue                kVal;
	Four					key;
	BtreeCursor				cursor;
    Four                    e;

    printf("Test 4_1 tests EduBtM_DeleteObject() deleting the object. It does not need a redistribution.\n");

    kVal.len = sizeof(Four_Invariable);

	key = 50;
	  
	memcpy(&(kVal.val[0]), &key, sizeof(Four_Invariable));
	
	e = EduBtM_Fetch(rootPid, kdesc, &kVal, SM_EQ, &kVal, SM_EQ, &cursor);
	if (e < eNOERROR) ERR(e);
	
	e = EduBtM_DeleteObject(catalogEntry, rootPid, kdesc, &kVal, &cursor.oid, &dlPool, &dlHead);
	if (e < eNOERROR) ERR(e);
	
	printf("The object whose key is %d has been deleted.\n", key);

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");


    e = edubtm_CheckFPages(rootPid, kdesc->kpart[0].type, fp, pass);
    if (e < eNOERROR) ERR(e);

	return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_4_2()
 *================================*/
/*
 * Function: EduBtM_TestInt_4_2(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_4_2() tests EduBtM_DeleteObject() deleting the objects until needing a redistribution.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_4_2(
	ObjectID                *catalogEntry,
	PageID                  *rootPid,
	KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass
)
{   
	KeyValue                kVal;
	Four                    key;
	BtreeCursor             cursor;
	Four                    e;
	
    printf("Test 4_2 tests EduBtM_DeleteObject() deleting the objects until needing a redistribution.\n");

	kVal.len = sizeof(Four_Invariable);
	
	for (key = 51; key < 60; key++)
	{
		memcpy(&(kVal.val[0]), &key, sizeof(Four_Invariable));
		
		e = EduBtM_Fetch(rootPid, kdesc, &kVal, SM_EQ, &kVal, SM_EQ, &cursor);
		if (e < eNOERROR) ERR(e);
		
		e = EduBtM_DeleteObject(catalogEntry, rootPid, kdesc, &kVal, &cursor.oid, &dlPool, &dlHead);
		if (e < eNOERROR) ERR(e);
		
		printf("The object whose key is %d has been deleted.\n", key);
		
		 
	}

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    e = edubtm_CheckFPages(rootPid, kdesc->kpart[0].type, fp, pass);
	if (e < eNOERROR) ERR(e);
	
    return eNOERROR;
}

/*@================================
 * EduBtM_TestInt_5_1()
 *================================*/
/*
 * Function: EduBtM_TestInt_5_1(ObjectID *catalogEntry, PageID *rootPid, KeyDesc *kdesc, FILE *fp, bool *pass)
 *
 * Description : 
 *  EduBtM_TestInt_5_1() tests EduBtM_DropIndex() dropping an index.
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */
Four edubtm_TestInt_5_1(
    ObjectID                *catalogEntry,
    PageID                  *rootPid,
    KeyDesc                 *kdesc,
	FILE                    *fp,
	bool                    *pass
)
{
	SlottedPage				*catPage;    
	sm_CatOverlayForBtree 	*catEntry;                    	/* pointer to Btree file catalog information */   
	PhysicalFileID 			pFid;                           /* physical file identifier for EduBtM_DropIndex() */
	DeallocListElem     	*dlElem;        /* an element of dealloc list */
	Four					i;
	Four                    e;

	Four					pageNo;
	char					str[100];

	printf("Test 5_1 tests EduBtM_DropIndex() dropping an index.\n");

	e = BfM_GetTrain((TrainID*)catalogEntry, (char**)&catPage, PAGE_BUF);                
	if (e < 0) ERR(e);
	
	GET_PTR_TO_CATENTRY_FOR_BTREE(catalogEntry, catPage, catEntry);
	
	MAKE_PHYSICALFILEID(pFid, catEntry->fid.volNo, catEntry->firstPage);
	
	e = BfM_FreeTrain((TrainID*)catalogEntry, PAGE_BUF);
	if (e < 0) ERR(e);

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBtM_DropIndex(&pFid, rootPid, &dlPool, &dlHead);
	if (e < eNOERROR) ERR(e);

	dlElem = dlHead.next;
	
	fgets(str, 100, fp);
	printf("str : %s\n\n", str);
	for (dlElem = dlHead.next; dlElem->next; dlElem = dlElem -> next)
	{
		printf("The page whose pageNo is %d has been deallocated.\n", dlElem->elem.pid.pageNo);
		fscanf(fp, "The page whose pageNo is %d has been deallocated.\n", &pageNo);
		if(pageNo != dlElem->elem.pid.pageNo) {
			*pass = false;
		}
	}
 
    return eNOERROR;

}
