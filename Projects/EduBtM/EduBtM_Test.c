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
 * Module: EduBtM_Test.c
 *
 * Description : 
 * Test the EduBtM and show the result of test.
 *
 * Exports:
 *  Four EduBtM_Test(Four, Four)
 */

#include <string.h>
#include "EduBtM_common.h"
#include "EduBtM_basictypes.h"
#include "EduBtM.h"
#include "EduBtM_TestModule.h"
#include "OM_Internal.h"
Four dumpBtreePage(PageID*, KeyDesc);
void dumpInternal(BtreeInternal*, PageID*, Two);
void dumpLeaf(BtreeLeaf*, PageID*, Two);
void dumpOverflow(BtreeOverflow*, PageID*);

/*@================================
 * EduBtM_Test()
 *================================*/
/*
 * Function: EduBtM_Test(Four volId, Four handle)
 *
 * Description : 
 *  Show a result of a test of EduBtM.
 *  EduBtM is module which is implemented for operation 
 *  related to B+ tree structure. The B+ tree strucutre is 
 *  composed of root page, internal page, and leaf page.
 *  There are five operations in EduBtM.
 *  EduBtM_Test() test these below operations in EduBtM.
 *  EduBtM_CreateIndex(), EduBtM_InsertObject(), EduBtM_Fetch(),
 *  EduBtM_FetchNext(), EduBtM_DropIndex().
 *
 *
 * Returns:
 *  error code
 *    some errors caused by function calls
 */

Four EduBtM_Test(Four volId, Four handle){
	
	Four e;												/* for errors */
	Four i;												/* loop index */
    FileID      fid;                                    /* file identifier */
	ObjectID    catalogEntry;                           /* catalog object */
	Four numOfIntegerObject = NUMOFINSERTEDOBJECT;		/* number of integer object */
	Four numOfVariableObject = 0;						/* number of variable object */
	Four operation;										/* operation number */
	Four scanOperation;									/* operation number of scan function */
	IndexID iid;										/* index id */
	ObjectID oid;										/* object id */
	PageID 	dumpPage;									/* page identifier for dump */
	PhysicalFileID pFid;								/* physical file identifier for EduBtM_DropIndex() */ 
	PhysicalIndexID		rootPid;						/* root page identifier */
	KeyValue	kval;									/* value of key */
	KeyValue	startKval;								/* start value of key for EduBtM_FetchNext() */
	KeyValue	stopKval;								/* stop value of key for EduBtM_FetchNext() */
	KeyDesc		kdesc;									/* key descriptor */
	Four		startCompOp;							/* start condition for EduBtM_FetchNext() */
	Four		stopCompOp;								/* stop condition for EduBtM_FetchNext() */
	Four		compOp;									/* conditino for EduBtM_Fetch() */
	Four		keyValueNumber = 0;						/* value of integer key */	
	SlottedPage *catPage;								/* buffer page containing the catalog object */
	sm_CatOverlayForBtree *catEntry;					/* pointer to Btree file catalog information */
	BtreeCursor cursor;									/* cursor for EduBtM_FetchNext() */
	BtreeCursor next;									/* next object cursor from EduBtM_FetchNext() */
    Two 		lengthOfPlayerName;						/* length of variable key */
	char 		playerName[MAXPLAYERNAME];				/* value of  variable key */
	char		*res;									/* string for file input */
	FILE		*fp;

	printf("Loading EduBtM_Test() complete...\n");

	/* Create File */
	e = SM_CreateFile(volId, &fid, FALSE, NULL);
	if (e < eNOERROR) ERR(e);
	/* Get catalog entry */
	e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
	if (e < eNOERROR) ERR(e);
		
/* Start test for integer key value */
	printf("############################## Start EduBtM test for integer key value ##############################\n");
/* #1 Start the test for EduBtM_CreateIndex */
	   
	printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");
	/* Create a root page using EduBtM_CreateIndex */
	printf("*Test1_1 : Test for EduBtM_CreateIndex()\n");
	printf("->Create a root page\n");

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBtM_CreateIndex(&catalogEntry, &rootPid);
	if (e < eNOERROR) ERR(e);

	/* Construct Kval and Kdesc */
	kval.len = sizeof(Four_Invariable);
	memcpy(&(kval.val[0]), &keyValueNumber, sizeof(Four_Invariable));
	
	kdesc.flag = KEYFLAG_UNIQUE;
	kdesc.nparts = 1;
	kdesc.kpart[0].type = SM_INT;
	kdesc.kpart[0].offset = 0;
	kdesc.kpart[0].length = sizeof(Four);
	
	e = dumpBtreePage((PageID*)&rootPid, kdesc);
	if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", rootPid.volNo, rootPid. pageNo);
    else if (e < eNOERROR) ERR(e);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");

/* #1 End the test */



/* #2 Start the test for EduBtM_InsertObject */
	
	printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");
	/* 200 integer objects are inserted into index */
    printf("*Test 2_1 : Test for EduBtM_InsertObject()\n");
	printf("200 integer objects are inserted into the B+ tree index\n");
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Construct oid */
	oid.pageNo = 777;
	oid.volNo = volId;
		        

	for (i = 0; i < NUMOFINSERTEDOBJECT; i++){
	
		keyValueNumber = i;
		memcpy(&(kval.val[0]), &keyValueNumber, sizeof(Four_Invariable));
		oid.slotNo = i;
		oid.unique = i;
		/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
		e = EduBtM_InsertObject(&catalogEntry, &rootPid, &kdesc, &kval, &oid, NULL, NULL);
		if(e < eNOERROR) ERR(e);
		printf("The object (key: %d , OID: (%4d, %4d, %4d, %4d)) is inserted into the index.\n", i, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);

	}
	      
	printf("The objects are inserted into the index\n");
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");

	
/* #2 End the test */


	printf("****************************** Option. ******************************\n");
	do{
		operation = 0;
		printf("(1. Insert Object   2. Delete Object   3. Scan   4. Dump   5. Drop Index and Exit)\t");
		if (scanf("%d",&operation) == 0){ 
			while(getchar() != '\n');
			operation = 0;
		}
		switch(operation){
			case 1:
				
				printf("****************************** EduBtM_InsertObject. ******************************\n");
				
				while (1) {
					printf("Enter the key value : ");
					if (scanf("%d", &keyValueNumber) == 0)
						while(getchar() != '\n');
					else
						break;
					printf("Wrong number!!!\n");
				};
				memcpy(&(kval.val[0]), &keyValueNumber, sizeof(Four_Invariable));
				
				oid.slotNo = numOfIntegerObject;
				oid.unique = numOfIntegerObject++;

				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_InsertObject(&catalogEntry, &rootPid, &kdesc, &kval, &oid, NULL, NULL);
				if (e == eDUPLICATEDKEY_BTM) printf("There is the same key in the B+ tree index.\nEduBtM allows only unique keys\n");
				else if(e < eNOERROR) ERR(e);
				else printf("The object (key: %d, OID: ( %d, %d, %d, %d)) is inserted into the B+ tree index.\n", 
						keyValueNumber, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);

                printf("****************************** EduBtM_InsertObject. ******************************\n");
				break;

			case 2:

				printf("****************************** EduBtM_DeleteObject. ******************************\n");

				while (1) {
					printf("Enter the key value : ");
					if (scanf("%d", &keyValueNumber) == 0)
						while(getchar() != '\n');
					else
						break;
					printf("Wrong number!!!\n");
				};

				memcpy(&(kval.val[0]), &keyValueNumber, sizeof(Four_Invariable));

				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_Fetch(&rootPid, &kdesc, &kval, SM_EQ, &kval, SM_EQ, &cursor);
				if (e < eNOERROR) ERR(e);
				else if (cursor.flag == CURSOR_EOS) {
					printf("There is no object that satisfies the condition.\n");
					break;
				}
				else{
					/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
					e = EduBtM_DeleteObject(&catalogEntry, &rootPid, &kdesc, &kval, &cursor.oid, &dlPool, &dlHead);
					if (e == eNOTSUPPORTED_EDUBTM) printf("Delete operation is not implemented.\n");
					else if (e == eNOTFOUND_BTM) printf("There is no object that statisfies the condition.\n");
					else if (e < eNOERROR) ERR(e);
					else printf("The object (key: %d, OID: ( %d, %d, %d, %d)) is deleted from the B+ tree index.\n", 
							keyValueNumber, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
				}							

				printf("****************************** EduBtM_DeleteObject. ******************************\n");

				break;
			case 3:

				printf("****************************** Scan. ******************************\n");

				printf("****** Comparison operator *****\n");
				printf("1. Equal value\n2. Less value\n3. Less or Equal value\n4. Greater value\n5. Greater or Eqaul value\n6. Greatest value\n7. Least value\n");
				printf("********************************\n");
				
				/* Get start conditions */
				do{
					e = 0;
					printf("Enter the comparison operator of start condition : ");
					if (scanf("%d", &startCompOp) == 0){
						while( getchar() != '\n' );
						startCompOp = 0;
					}
					switch(startCompOp){
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:	
							printf("Entert the start key value : ");
							if (scanf("%d", &keyValueNumber) == 0) 
							{
								while( getchar() != '\n' );
								e = -1;
								printf("Wrong nubmer!!!\n");
								break;
							}
							startKval.len = sizeof(Four_Invariable);
							memcpy(&(startKval.val[0]), &keyValueNumber, sizeof(Four_Invariable));
							break;
						case 6:
							startCompOp = SM_EOF; 
							break;
						case 7:
							startCompOp = SM_BOF;
							break;
						default:
							e = -1;
							printf("Wrong number!!!\n");
							break;
					}
				}while(e == -1);
				

				/* Get stop conditions */
				do{
					e = 0;
					printf("Enter the comparison operator of stop condition : ");                                               
					if (scanf("%d", &stopCompOp) == 0){
						while( getchar() != '\n' );
						stopCompOp = 0;
					}
					switch(stopCompOp){
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
							printf("Entert the stop key value : ");
							if (scanf("%d", &keyValueNumber) == 0) 
							{   
								while( getchar() != '\n' );
								e = -1;
								printf("Wrong nubmer!!!\n");
								break;
							}
							stopKval.len = sizeof(Four_Invariable);
							memcpy(&(stopKval.val[0]), &keyValueNumber, sizeof(Four_Invariable));
							break;
						case 6:
							stopCompOp = SM_EOF;
							break;
						case 7:
							stopCompOp = SM_BOF;
							break;
						default:
							printf("Wrong number!!!\n");
							e = -1;
							break;
					}
				}while (e == -1);


				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_Fetch(&rootPid, &kdesc, &startKval, startCompOp, &stopKval, stopCompOp, &cursor);
                if (e < eNOERROR) ERR(e);
				else if (cursor.flag == CURSOR_EOS) {
					printf("There is no object that satisfies the condition.\n");
					break;
				}
				memcpy(&keyValueNumber, &(cursor.key.val[0]), sizeof(Four_Invariable));
				printf("Cursor points to the %dth slot in the leaf page ( volNo = %d, pageNo = %d )\n",
						cursor.slotNo, cursor.leaf.volNo, cursor.leaf.pageNo);
				printf("Key: %d, OID: (%d, %d, %d, %d)\n",
						keyValueNumber, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);
                
				do{

					printf("(1. FetchNext   2. Dump   3. Quit Scan)\t");
					if (scanf("%d",&scanOperation) == 0){
						while(getchar() != '\n');
						scanOperation = 0;
					}
					switch(scanOperation){
						case 1:
							
							/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
							e = EduBtM_FetchNext(&rootPid, &kdesc, &stopKval, stopCompOp, &cursor, &next);
							if (e < eNOERROR) ERR(e);
							else if (next.flag == CURSOR_EOS) {
								printf("There is no object that satisfies the condition.\n");
								break;
							}   
							cursor = next;	
							memcpy(&keyValueNumber, &(cursor.key.val[0]), sizeof(Four_Invariable));
							printf("Cursor points to the %dth slot in the leaf page ( volNo = %d, pageNo = %d )\n", 
									cursor.slotNo, cursor.leaf.volNo, cursor.leaf.pageNo);
							printf("Key: %d, OID: (%d, %d, %d, %d)\n", 
									keyValueNumber, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);
							break;

						case 2:

							printf("pageNo of rootPid : %d\n", rootPid.pageNo);

							dumpPage.volNo = volId;
							printf("Enter the pageNo : ");
							if (scanf("%d", &(dumpPage.pageNo)) == 0)
							{
								while(getchar() != '\n');
								printf("Wrong number!!!\n");
								break;
							}
						
							e = dumpBtreePage(&dumpPage, kdesc);
							if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", dumpPage.volNo, dumpPage.pageNo);
							else if (e < eNOERROR) ERR(e);
							break;

						case 3:
							printf("Quit scan.\n");
							break;

						default:
							printf("Wrong operation number!!!\n");
					}
				}while(scanOperation != 3);
				printf("****************************** Scan ******************************\n");

				break;
				
			case 4:

				printf("****************************** Dump  ******************************\n");

				printf("pageNo of rootPid : %d\n", rootPid.pageNo);
				dumpPage.volNo = volId;
				printf("Enter the pageNo : ");
				if (scanf("%d", &(dumpPage.pageNo)) == 0)
				{
					while(getchar() != '\n');
					printf("Wrong number!!!\n");
					break;
				}

			    e = dumpBtreePage(&dumpPage, kdesc);
				if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", dumpPage.volNo, dumpPage.pageNo);
				else if (e < eNOERROR) ERR(e);
                printf("****************************** Dump  ******************************\n");
				break;

			case 5:
				printf("****************************** EduBtM_DropIndex. ******************************\n");
				
				/* set pFid */
				/* Get the B+ tree file's FileID from the catalog object */
				e = BfM_GetTrain((TrainID*)&catalogEntry, (char**)&catPage, PAGE_BUF);
				if (e < 0) ERR(e);

				GET_PTR_TO_CATENTRY_FOR_BTREE((&catalogEntry), catPage, catEntry);

				MAKE_PHYSICALFILEID(pFid, catEntry->fid.volNo, catEntry->firstPage);

				e = BfM_FreeTrain((TrainID*)&catalogEntry, PAGE_BUF);
				if (e < 0) ERR(e);
				
				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_DropIndex(&pFid, &rootPid, &dlPool, &dlHead);
				if (e < eNOERROR) ERR(e);
				printf("****************************** EduBtM_DropIndex. ******************************\n");
				break;

			default:
				printf("Wrong number!!!\n");
				break;
		}
	}while(operation != 5);
    printf("****************************** Option. ******************************\n");
    printf("############################## End EduBtM test for integer key value ##############################\n\n\n");
/* End test for integer key value. */


	/* Destroy File */
	e = SM_DestroyFile(&fid, NULL);
	if (e < eNOERROR) ERR(e);
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* Create File */
	e = SM_CreateFile(volId, &fid, FALSE, NULL);
	if (e < eNOERROR) ERR(e);
	/* Get catalog entry */
	e = sm_GetCatalogEntryFromDataFileId(ARRAYINDEX, &fid, &catalogEntry);
	if (e < eNOERROR) ERR(e);


/* Start test for variable key value */
    printf("############################## Start EduBtM test for variable key value ##############################\n");/* #1 Start the test for EduBtM_CreateIndex */

	printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");
	/* Create a root page using EduBtM_CreateIndex */
    printf("*Test1_1 : Test for EduBtM_CreateIndex()\n");
	printf("->Create a root page\n");
	
	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
	e = EduBtM_CreateIndex(&catalogEntry, &rootPid);
	if (e < eNOERROR) ERR(e);
    e = dumpBtreePage((PageID*)&rootPid, kdesc); 
	if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", rootPid.volNo, rootPid. pageNo);
	else if (e < eNOERROR) ERR(e);

    printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

	printf("****************************** TEST#1, EduBtM_CreateIndex. ******************************\n");
	
	
/* #1 End the test */


/* #2 Start the test for EduBtM_InsertObject */

	printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");
	/* 144 variable string objects are inserted into index */
    printf("*Test 2_1 : Test for EduBtM_InsertObject()\n");
    printf("144 variable string objects are inserted into the B+ tree index\n");

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");
	
	/* Construct Kval and Kdesc */

	kval.len = MAXPLAYERNAME;
	
	kdesc.flag = KEYFLAG_UNIQUE;
	kdesc.nparts = 1;
	kdesc.kpart[0].type = SM_VARSTRING;
	kdesc.kpart[0].offset = 0;
	kdesc.kpart[0].length = MAXPLAYERNAME;

	/* Construct oid */
	oid.pageNo = 777;
	oid.volNo = 1000;

	fp = fopen("playerNames.txt", "rt");
	 
	for (numOfVariableObject = 0;!feof(fp) || numOfVariableObject < NUMOFPLAYER; numOfVariableObject++){
		res = fgets(playerName, MAXPLAYERNAME, fp);
		if (res == NULL ) break;
		else
		{
			for (lengthOfPlayerName  = 0; lengthOfPlayerName < MAXPLAYERNAME; lengthOfPlayerName++)
				if (playerName[lengthOfPlayerName] == '\n') break;
			lengthOfPlayerName--;
			playerName[lengthOfPlayerName] = '\0';
			
			memcpy(&(kval.val[0]), &lengthOfPlayerName, sizeof(Two));
			memcpy(&(kval.val[sizeof(Two)]), &playerName, MAXPLAYERNAME);

			oid.slotNo = numOfVariableObject;
			oid.unique = numOfVariableObject;
			/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
			e = EduBtM_InsertObject(&catalogEntry, &rootPid, &kdesc, &kval, &oid, NULL, NULL);
			if(e < eNOERROR) ERR(e);
			else printf("The object (key: %s , OID: (%4d, %4d, %4d, %4d)) is inserted into the index.\n", playerName, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
		}
	}
	fclose(fp);	

	printf("Press enter key to continue...");
	getchar();
	printf("\n\n");

    printf("The objects are inserted into the index\n");
	printf("****************************** TEST#2, EduBtM_InsertObject. ******************************\n");
	
	/* #2 End the test */

	printf("****************************** Option. ******************************\n");
    do{
		operation = 0;
		printf("(1. Insert Object   2. Delete Object   3. Scan   4. Dump   5. Drop Index and Exit)\t");
		if (scanf("%d", &operation)== 0){
			while(getchar() != '\n');
			operation = 0;
		}
		switch(operation){
			case 1:
				
				printf("****************************** EduBtM_InsertObject. ******************************\n");
				
				
				printf("Enter the player name :");
				getchar();
		        fgets(playerName, MAXPLAYERNAME, stdin);
				
				lengthOfPlayerName = strlen(playerName);
				playerName[lengthOfPlayerName-- - 1] = '\0';
				memcpy(&(kval.val[0]), &lengthOfPlayerName, sizeof(Two));
				memcpy(&(kval.val[sizeof(Two)]), &playerName, MAXPLAYERNAME);

				oid.slotNo = numOfVariableObject;
				oid.unique = numOfVariableObject++;

				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_InsertObject(&catalogEntry, &rootPid, &kdesc, &kval, &oid, NULL, NULL);
				if (e == eDUPLICATEDKEY_BTM) printf("There is the same key in the B+ tree index.\nEduBtM allows only unique keys\n");
				else if (e < eNOERROR) ERR(e);
				else printf("The object (key: %s , OID: (%4d, %4d, %4d, %4d)) is inserted into the B+ tree index.\n", playerName, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
				
				printf("****************************** EduBtM_InsertObject. ******************************\n");
				break;

            case 2:
				
				printf("****************************** EduBtM_DeleteObject. ******************************\n");
				
				printf("Enter the player name : ");
				getchar();
		        fgets(playerName, MAXPLAYERNAME, stdin);

				lengthOfPlayerName = strlen(playerName);
				playerName[lengthOfPlayerName-- - 1] = '\0';
				memcpy(&(kval.val[0]), &lengthOfPlayerName, sizeof(Two));
				memcpy(&(kval.val[sizeof(Two)]), &playerName, MAXPLAYERNAME);
				

				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_Fetch(&rootPid, &kdesc, &kval, SM_EQ, &kval, SM_EQ, &cursor);
				if (e < eNOERROR) ERR(e);
				else if (cursor.flag == CURSOR_EOS) {
					printf("There is no object that satisfies the condition.\n");
					break;
				}
				else
				{
					/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
					e = EduBtM_DeleteObject(&catalogEntry, &rootPid, &kdesc, &kval, &cursor.oid, &dlPool, &dlHead);
					if (e == eNOTFOUND_BTM) printf("There is no object that statisfies the condition.\n");
					else if (e < eNOERROR) ERR(e);
					else printf("The object (key: %s, OID: ( %d, %d, %d, %d)) is deleted from the B+ tree index.\n",
							playerName, oid.volNo, oid.pageNo, oid.slotNo, oid.unique);

				}
				printf("****************************** EduBtM_DeleteObject. ******************************\n");
				
				break;

            case 3:
			
				printf("****************************** Scan. ******************************\n");

				printf("****** Comparison operator *****\n");
				printf("1. Equal value\n2. Less value\n3. Less or Equal value\n4. Greater value\n5. Greater or Eqaul value\n6. Greatest value\n7. Least value\n");
				printf("********************************\n");
				
				/* Get start conditions */
				do{
					e = 0;
					printf("Enter the comparison operator of start condition : ");
					if (scanf("%d", &startCompOp) == 0){
						while( getchar() != '\n' );
						startCompOp = 0;
					}
					switch(startCompOp){
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
							printf("Enter the player name of start key value : ");
							getchar();
		        			fgets(playerName, MAXPLAYERNAME, stdin);
							lengthOfPlayerName = strlen(playerName);
							playerName[lengthOfPlayerName-- - 1] = '\0';
							startKval.len = MAXPLAYERNAME;
							memcpy(&(startKval.val[0]), &lengthOfPlayerName, sizeof(Two));
							memcpy(&(startKval.val[sizeof(Two)]), &playerName, MAXPLAYERNAME);
							break;
						case 6:
							startCompOp = SM_EOF;
							break;
						case 7:
							startCompOp = SM_BOF;
							break;
						default:
							printf("Wrong number!!!\n");
							e = -1;
							break;
					}
				}while(e == -1);
				
				
				/* Get stop conditions */
				do{
					e = 0;
					printf("Enter the comparison operator of stop condition : ");
					if (scanf("%d", &stopCompOp) == 0){
						while( getchar() != '\n' );
						stopCompOp = 0;
					}

					switch(stopCompOp){
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
							printf("Entert the player name of stop key value : ");
							getchar();
		        			fgets(playerName, MAXPLAYERNAME, stdin);
							lengthOfPlayerName = strlen(playerName);
							playerName[lengthOfPlayerName-- - 1] = '\0';
							stopKval.len = MAXPLAYERNAME;
							memcpy(&(stopKval.val[0]), &lengthOfPlayerName, sizeof(Two));
							memcpy(&(stopKval.val[sizeof(Two)]), &playerName, MAXPLAYERNAME);
							break;
						case 6:
							stopCompOp = SM_EOF;
							break;
						case 7:
							stopCompOp = SM_BOF;
							break;
						default:
							printf("Wrong number!!!\n");
							e = -1;
							break;
					}
				}while (e == -1);

				

				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_Fetch(&rootPid, &kdesc, &startKval, startCompOp, &stopKval, stopCompOp, &cursor);
				if (e < eNOERROR) ERR(e);
				else if (cursor.flag == CURSOR_EOS) {
					printf("There is no object that satisfies the condition.\n");
					break;
				}   
				memcpy(playerName, &(cursor.key.val[sizeof(Two)]), MAXPLAYERNAME);
				printf("Cursor points to the %dth slot in the leaf page ( volNo = %d, pageNo = %d )\n", 
						cursor.slotNo, cursor.leaf.volNo, cursor.leaf.pageNo);
				printf("Key: %s, OID: (%d, %d, %d, %d)\n",
						playerName, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);
				
				do{
					
					printf("(1. FetchNext   2. Dump   3. Quit Scan)\t");
					if (scanf("%d",&scanOperation) == 0){
						while(getchar() != '\n');
						scanOperation = 0;
					}
					
					switch(scanOperation){
						case 1:
							/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
							e = EduBtM_FetchNext(&rootPid, &kdesc, &stopKval, stopCompOp, &cursor, &next);
							if (e < eNOERROR) ERR(e);
							else if (next.flag == CURSOR_EOS) {
								printf("There is no object that satisfies the condition.\n");
								break;
							}   
							cursor = next;
							memcpy(&playerName, &(cursor.key.val[sizeof(Two)]), MAXPLAYERNAME);
							printf("Cursor points to the %dth slot in the leaf page ( volNo = %d, pageNo = %d )\n", 
									cursor.slotNo, cursor.leaf.volNo, cursor.leaf.pageNo);
							printf("Key: %s, OID: (%d, %d, %d, %d)\n", 
									playerName, cursor.oid.volNo, cursor.oid.pageNo, cursor.oid.slotNo, cursor.oid.unique);
							break;
							
						case 2:
							
							printf("pageNo of rootPid : %d\n", rootPid.pageNo);
							
							dumpPage.volNo = volId;
							printf("Enter the pageNo : ");
							if (scanf("%d", &(dumpPage.pageNo)) == 0)
							{
								while(getchar() != '\n');
								printf("Wrong number!!!\n");
								break;
							}
							
							e = dumpBtreePage(&dumpPage, kdesc);
							if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", dumpPage.volNo, dumpPage. pageNo);
			                else if (e < eNOERROR) ERR(e);
							break;
							
						case 3:
							printf("Quit scan.\n");
							break;
							
						default:
							printf("Wrong operation number!!!\n");
					}
				}while(scanOperation != 3);

				printf("****************************** Scan. ******************************\n");		
				break;
				
			case 4:

				printf("****************************** Dump  ******************************\n");
				printf("pageNo of rootPid : %d\n", rootPid.pageNo);
				dumpPage.volNo = volId;
				printf("Enter the pageNo : ");
				if (scanf("%d", &(dumpPage.pageNo)) == 0)
				{
					while(getchar() != '\n');
					printf("Wrong number!!!\n");
					break;
				}
				
				e = dumpBtreePage(&dumpPage, kdesc);
				if (e == eBADBTREEPAGE_BTM) printf("The page (PID: ( %d, %d )) does not exist in the B+ tree index.\n", dumpPage.volNo, dumpPage. pageNo);
                else if (e < eNOERROR) ERR(e);

				break;
			
			case 5:
				printf("****************************** EduBtM_DropIndex. ******************************\n");

				/* set pFid */
				/* Get the B+ tree file's FileID from the catalog object */
				e = BfM_GetTrain((TrainID*)&catalogEntry, (char**)&catPage, PAGE_BUF);
				if (e < 0) ERR(e);

				GET_PTR_TO_CATENTRY_FOR_BTREE((&catalogEntry), catPage, catEntry);

				MAKE_PHYSICALFILEID(pFid, catEntry->fid.volNo, catEntry->firstPage);

				e = BfM_FreeTrain((TrainID*)&catalogEntry, PAGE_BUF);
				if (e < 0) ERR(e);
				
				/* The successful default solution code is called if "Edu" is omitted from the function name in the following line */
				e = EduBtM_DropIndex(&pFid, &rootPid, &dlPool, &dlHead);
				if (e < eNOERROR) ERR(e);
				printf("****************************** EduBtM_DropIndex. ******************************\n");
				break;

			default:
				printf("Wrong number!!!\n");
				break;
		}
	}while(operation != 5);
    printf("****************************** Option. ******************************\n");			

	/* Destroy File */
	e = SM_DestroyFile(&fid, NULL);
	if (e < eNOERROR) ERR(e);

	return eNOERROR;
}
/* End test for variable key value. */


/*@================================
 * dumpBtreePage()
 *================================*/
/*
 * Function: Four  dumpBtreePage(PageID*)
 *
 * Description:
 *  dump routine.
 *
 * Returns:
 *  Error code
 *    some errors caused by function calls
 */
Four dumpBtreePage(
		PageID		*pid,
		KeyDesc		kdesc)
{
	Four e;         /* error number */
	BtreePage *apage;       /* page to dump */
	
	
	e = BfM_GetTrain(pid, (char **)&apage, PAGE_BUF);
	if (e < 0)  ERR(e);
	
	if (kdesc.kpart[0].type == SM_INT){
		if (apage->any.hdr.type & INTERNAL)
			dumpInternal(&(apage->bi), pid, kdesc.kpart[0].type);
		else if (apage->any.hdr.type & LEAF)
			dumpLeaf(&(apage->bl), pid, kdesc.kpart[0].type);
		else if (apage->bo.hdr.type & OVERFLOW)
			dumpOverflow(&(apage->bo), pid);
		else
			ERRB1(eBADBTREEPAGE_BTM, pid, PAGE_BUF);
	}else if (kdesc.kpart[0].type == SM_VARSTRING){
		if (apage->any.hdr.type & INTERNAL)     
			dumpInternal(&(apage->bi), pid, kdesc.kpart[0].type);  
		else if (apage->any.hdr.type & LEAF)       
			dumpLeaf(&(apage->bl), pid, kdesc.kpart[0].type);  
		
		else if (apage->bo.hdr.type & OVERFLOW)     
			dumpOverflow(&(apage->bo), pid);  
		else        
			ERRB1(eBADBTREEPAGE_BTM, pid, PAGE_BUF);
	}
	e = BfM_FreeTrain(pid, PAGE_BUF);
	if (e < 0) ERR(e);
	return(eNOERROR);
}

/*@================================
 * dumpInternal()
 *================================*/
/* Function: void dumpInternal(BtreeInternal*, PageID*)
 *
 * Description:
 *  Dump an internal page.
 * 
 * Returns:
 *  None
 */
void dumpInternal(
		BtreeInternal       *internal,      /* IN pointer to buffer of internal page */
		PageID              *pid,			/* IN page identifier */
		Two					type            /* IN type for key value */
		) 
{
	Two                 i;              /* index variable */
	Two                 entryOffset;    /* starting offset of an internal entry */
	btm_InternalEntry   *entry;         /* IN an internal entry */
	Two                 j;              /* index variable */
	Two                 len;            /* key value length */
	char        playerName[MAXPLAYERNAME];  /* data of the key value */
	int					tempKval;

	printf("\n\t|=========================================================|\n");
	printf("\t|    PageID = (%4d,%6d)     type = INTERNAL%s      |\n",
			pid->volNo, pid->pageNo, (internal->hdr.type & ROOT) ? "|ROOT":"     ");
	printf("\t|=========================================================|\n");
	printf("\t| free = %-5d, unused = %-5d", internal->hdr.free, internal->hdr.unused);
	printf("nSlots = %-5d, p0 = %-5d  |\n", internal->hdr.nSlots, internal->hdr.p0 );
	printf("\t|---------------------------------------------------------|\n");
	if (type == SM_INT)
		for (i = 0; i < internal->hdr.nSlots; i++) {
			entryOffset = internal->slot[-i];
			entry = (btm_InternalEntry*)&(internal->data[entryOffset]);
			printf("\t| ");
			memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */
			printf("        klen = %4d :  Key = %4d  : spid = %4d        |\n", entry->klen, tempKval, entry->spid);
		}
	else if (type == SM_VARSTRING)
		for (i = 0; i < internal->hdr.nSlots; i++) {
			entryOffset = internal->slot[-i];
			entry = (btm_InternalEntry*)&(internal->data[entryOffset]);
			printf("\t| ");
			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);
			printf("	klen = %4d : Key = %s", len, playerName);
			printf(" : spid = %5d |\n", entry->spid);
		}

	printf("\t|---------------------------------------------------------|\n");
	
}  /* dumpInternal */


/*@================================
 * dumpLeaf()
 *================================*/
/*
 * Function: void dumpLeaf(BtreeLeaf*, PageID*)
 * 
 * Description:
 *  Dump a leaf page.
 *  
 * Returns:
 *  None
 */
void dumpLeaf(
		BtreeLeaf           *leaf,          /* IN pointer to buffer of Leaf page */
		PageID              *pid,			/* IN pointer to leaf PageID */
		Two					type			/* IN type for key value */
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
	Four				tempKval;


	printf("\n\t|===============================================================================|\n");
	printf("\t|               PageID = (%4d,%4d)            type = LEAF%s                |\n",
			pid->volNo, pid->pageNo, (leaf->hdr.type & ROOT) ? "|ROOT":"     ");
	printf("\t|===============================================================================|\n");
	printf("\t|             free = %-5d, unused = %-5d", leaf->hdr.free, leaf->hdr.unused);												   
	printf("  nSlots = %-5d                      |\n", leaf->hdr.nSlots);
	printf("\t|             nextPage = %-10d,  prevPage = %-10d                     |\n",
			leaf->hdr.nextPage, leaf->hdr.prevPage );
	printf("\t|-------------------------------------------------------------------------------|\n");

	if (type == SM_INT) 
		for (i = 0; i < leaf->hdr.nSlots; i++) {
			entryOffset = leaf->slot[-i];
			entry = (btm_LeafEntry*)&(leaf->data[entryOffset]);
			printf("\t| ");
			memcpy((char*)&tempKval, (char*)entry->kval, sizeof(Four_Invariable)); /* YRK07JUL2003 */
			printf("klen = %3d : Key = %-4d", entry->klen, tempKval);
			printf(" : nObjects = %d : ", entry->nObjects);
			
			alignedKlen = ALIGNED_LENGTH(entry->klen);
			if (entry->nObjects < 0)
				printf(" OverPID = %d ", *((ShortPageID*)&(entry->kval[alignedKlen])));
			else {
				oid = (ObjectID *)&(entry->kval[alignedKlen]);
				printf(" ObjectID = (%4d, %4d, %4d, %4d) |\n", oid->volNo, oid->pageNo, oid->slotNo, oid->unique);
			}
		}
	else if (type == SM_VARSTRING)
		for (i = 0; i < leaf->hdr.nSlots; i++) {
			entryOffset = leaf->slot[-i];
			entry = (btm_LeafEntry*)&(leaf->data[entryOffset]);
			
			printf("\t| ");
			memcpy((char*)&len, (char*)&(entry->kval[0]), sizeof(Two));
			memcpy(&playerName, &(entry->kval[sizeof(Two)]), MAXPLAYERNAME);
			printf("klen = %3d : Key = %s", len, playerName);
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
	
}  /* dumpLeaf*/




/*@================================
 * dumpOverflow()
 *================================*/
/*
 * Function: Four dumpOverflow(BtreeOverflow*, PageID*)
 *
 * Description:
 *  Dump the overflow page.
 *
 * Returns:
 *  None
 */
void dumpOverflow(
		BtreeOverflow *overflow,    /* IN pointer to bugffer of Overflow Page */
		PageID        *pid)     /* IN PageID of overflow page */
{
	Two           i;            /* index variable */
	ObjectID      oid;      /* an object identifier */
	
	
	printf("\n\t|===========================================================================|\n");
	printf("\t|          PageID = (%4d,%6d)            type = OVERFLOW            |\n",
			pid->volNo, pid->pageNo);
	printf("\n\t|===========================================================================|\n");
	printf("nextPage = %-5d, prevPage = %-5d       |\n",
			overflow->hdr.nextPage, overflow->hdr.prevPage);
	printf("\t|---------------------------------------------------------------------------|");
	
	for (i = 0; i < overflow->hdr.nObjects; i++) {
		if(i%3 == 0) printf("\n\t| ");
		
		oid = overflow->oid[i];
		printf("  (%-4d, %-4d, %-4d, %-4d) ",
				oid.volNo, oid.pageNo, oid.slotNo, oid.unique);
	}
	printf("\n\t|---------------------------------------------------------------------------|\n");
	
}  /* dumpOverflow() */
