#/******************************************************************************/
#/*                                                                            */
#/*    Copyright (c) 2013-2015, Kyu-Young Whang, KAIST                         */
#/*    All rights reserved.                                                    */
#/*                                                                            */
#/*    Redistribution and use in source and binary forms, with or without      */
#/*    modification, are permitted provided that the following conditions      */
#/*    are met:                                                                */
#/*                                                                            */
#/*    1. Redistributions of source code must retain the above copyright       */
#/*       notice, this list of conditions and the following disclaimer.        */
#/*                                                                            */
#/*    2. Redistributions in binary form must reproduce the above copyright    */
#/*       notice, this list of conditions and the following disclaimer in      */
#/*       the documentation and/or other materials provided with the           */
#/*       distribution.                                                        */
#/*                                                                            */
#/*    3. Neither the name of the copyright holder nor the names of its        */
#/*       contributors may be used to endorse or promote products derived      */
#/*       from this software without specific prior written permission.        */
#/*                                                                            */
#/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     */
#/*    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       */
#/*    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       */
#/*    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          */
#/*    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,    */
#/*    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,    */
#/*    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;        */
#/*    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER        */
#/*    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT      */
#/*    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN       */
#/*    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE         */
#/*    POSSIBILITY OF SUCH DAMAGE.                                             */
#/*                                                                            */
#/******************************************************************************/
#/******************************************************************************/
#/*                                                                            */
#/*    ODYSSEUS/EduCOSMOS Educational Purpose Object Storage System            */
#/*    (Version 1.0)                                                           */
#/*                                                                            */
#/*    Developed by Professor Kyu-Young Whang et al.                           */
#/*                                                                            */
#/*    Advanced Information Technology Research Center (AITrc)                 */
#/*    Korea Advanced Institute of Science and Technology (KAIST)              */
#/*                                                                            */
#/*    e-mail: odysseus.educosmos@gmail.com                                    */
#/*                                                                            */
#/******************************************************************************/
#
# Makefile for ../EduBfM directory
#

.KEEP_STATE:

RM = /bin/rm

# Use ANSI/C compiler
CC = gcc

# directory of #include files
INCLUDE = ./Header

LIB = -lm

CFLAGS = -w -g -fsigned-char -fPIC -I$(INCLUDE)
#CFLAGS = -w -O2 -fsigned-char -fPIC -I$(INCLUDE)

EXEC = EduBfM_Test
all: $(EXEC)

INTERFACE = EduBfM_DiscardAll.o EduBfM_FlushAll.o EduBfM_FreeTrain.o \
			EduBfM_GetTrain.o EduBfM_SetDirty.o

NONINTERFACE = edubfm_AllocTrain.o edubfm_FlushTrain.o edubfm_Hash.o edubfm_ReadTrain.o

TESTMODULE = EduBfM_Test.o EduBfM_TestModule.o

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	COSMOS_OBJ = cosmos_64bit.o
else
	COSMOS_OBJ = cosmos_32bit.o
endif

EduBfM_Test: $(TESTMODULE) EduBfM.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

EduBfM.o: $(INTERFACE) $(NONINTERFACE)
	@echo ld -r ~~~ -o $@
	@ld -r $^ $(COSMOS_OBJ) -o $@
	chmod -x $@

.c.o:
	$(CC) $(CFLAGS) -c $<

clean: 
	$(RM) -f $(EXEC) $(INTERFACE) $(NONINTERFACE) $(TESTMODULE) EduBfM.o *.vol
