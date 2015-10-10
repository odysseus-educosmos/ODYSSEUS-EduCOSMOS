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
#define OM_ERR_BASE                              6

/*
 * Error Definitions for OM_ERR_BASE
 */
#define eBADPARAMETER_OM                         ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,0)
#define eBADOBJECTID_OM                          ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,1)
#define eBADCATALOGOBJECT_OM                     ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,2)
#define eBADLENGTH_OM                            ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,3)
#define eBADSTART_OM                             ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,4)
#define eBADFILEID_OM                            ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,5)
#define eBADUSERBUF_OM                           ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,6)
#define eBADPAGEID_OM                            ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,7)
#define eTOOLARGESORTKEY_OM                      ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,8)
#define eCANTALLOCEXTENT_BL_OM                   ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,9)
#define NUM_ERRORS_OM_ERR_BASE                   10
#define eNOTSUPPORTED_EDUOM			             ERR_ENCODE_ERROR_CODE(OM_ERR_BASE,11)
