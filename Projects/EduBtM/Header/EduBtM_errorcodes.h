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
 * Macro Definitions
 */
#define ERR_ENCODE_ERROR_CODE(base,no)      ( -1 * (((base) << 16) | no) )

/*
 * Error Base Definitions
 */
#define GENERAL_ERR_BASE                         1
#define BTM_ERR_BASE                             7

/*
 * Error Definitions for GENERAL_ERR_BASE
 */
#define eBADCURSOR                               ERR_ENCODE_ERROR_CODE(GENERAL_ERR_BASE,9)

/*
 * Error Definitions for OM_ERR_BASE
 */
#define eBADPARAMETER_BTM                        ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,0)
#define eBADBTREEPAGE_BTM                        ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,1)
#define eBADPAGE_BTM                             ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,2)
#define eNOTFOUND_BTM                            ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,3)
#define eDUPLICATEDOBJECTID_BTM                  ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,4)
#define eBADCOMPOP_BTM                           ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,5)
#define eDUPLICATEDKEY_BTM                       ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,6)
#define eBADPAGETYPE_BTM                         ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,7)
#define eEXCEEDMAXDEPTHOFBTREE_BTM               ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,8)
#define eTRAVERSEPATH_BTM                        ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,9)
#define eNOSUCHTREELATCH_BTM                     ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,10)
#define eDELETEOBJECTFAILED_BTM                  ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,11)
#define eBADCACHETREELATCHCELLPTR_BTM            ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,12)
#define NUM_ERRORS_BTM_ERR_BASE                  13
#define eNOTSUPPORTED_EDUBTM                     ERR_ENCODE_ERROR_CODE(BTM_ERR_BASE,14)
