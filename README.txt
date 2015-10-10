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

+-----------------------------------+
| Introduction - ODYSSEUS/EduCOSMOS |
+-----------------------------------+
ODYSSEUS/EduCOSMOS is a project for educational purposes to implement a part
of the storage system of ODYSSEUS(*) named ODYSSEUS/COSMOS. It consists of the
following three projects:
   - EduBfM project : We implement the operations of the buffer manager
	 consisting of only a very limited subset of the ODYSSEUS Buffer Manager
	 (BfM) functionality.
   - EduOM project : We implement the operations of page-related structures
	 consisting of only a very limited subset of the ODYSSEUS Object Manager
	 (OM) functionality.
   - EduBtM project : We implement the operations of the B+tree index manager
	 consisting of only a very limited subset of the ODYSSEUS B+tree Manager
	 (BtM) functionality.
To help implement each module, students are provided with the project manual,
which contains the base information of the project, the procedure to follow,
and the header/object files containing data structures and useful APIs.
Students are also provided with the test module to test the functions that
they implement and the executable solution file showing the correct test
result.
Students can learn about the structures and functionality of major modules
of a DBMS through each project manual provided and can learn the DBMS system
programming skill by implementing and testing these modules.
------------------------------
(*)ODYSSEUS
ODYSSEUS is an object-relational DBMS developed by Kyu-Young Whang et al. at 
Advanced Information Technology Research Center (AITrc) / Computer Science 
Department of KAIST. ODYSSEUS has been being developed since 1990. Some
useful references are as listed below.
[1] Whang, K., Lee, J., Lee, M., Han, W., Kim, M., and Kim, J., "DB-IR
    Integration Using Tight-Coupling in the Odysseus DBMS," World Wide Web,
	Vol. 18, No. 3, pp. 491-520, May 2015.
[2] Whang, K., Lee, M., Lee, J., Kim, M., and Han, W., "Odysseus: a
    High-Performance ORDBMS Tightly-Coupled with IR Features," In Proc. IEEE
	21st Int'l Conf. on Data Engineering (ICDE), pp. 1104-1105 (demo), Tokyo,
	Japan, April 5-8, 2005. This paper received the Best Demonstration Award.
[3] Whang, K., Park, B., Han, W., and Lee, Y., "An Inverted Index Storage
    Structure Using Subindexes and Large Objects for Tight Coupling of
	Information Retrieval with Database Management Systems," U.S. Patent No.
	6,349,308 (2002) (Appl. No. 09/250,487 (1999)).
[4] Whang, K., Lee, J., Kim, M., Lee, M., Lee, K., Han, W., and Kim, J.,
    "Tightly-Coupled Spatial Database Features in the Odysseus/OpenGIS DBMS for
    High-Performance," GeoInformatica, Vol. 14, No. 4, pp. 425-446, Oct. 2010.
[5] Whang, K., Lee, J., Kim, M., Lee, M., and Lee, K., "Odysseus: a
    High-Performance ORDBMS Tightly-Coupled with Spatial Database Features," In
    Proc. 23rd IEEE Int'l Conf. on Data Engineering (ICDE), pp. 1493-1494
	(demo), Istanbul, Turkey, Apr. 16-20, 2007.

+---------------------------+
| Compilation and Execution |
+---------------------------+
ODYSSEUS/EduCOSMOS is to be compiled and run on Linux (Red Hat).
The recommended environment for compiling and running ODYSSEUS/EduCOSMOS is as
follows:
   - Platform
      - 32bit: Linux version 2.6.18-308.el5PAE
	  - 64bit: Linux version 2.6.32-431.el6.x86_64
   - Compiler
      - 32bit: gcc version 4.1.2
	  - 64bit: gcc version 4.4.7

+---------------------+
| Directory Structure |
+---------------------+
./Doc
	/ProjectManagementManuals: (for TA) project management manuals for TA's
	/ProjectManuals: (for student) project manuals for students
./Projects
	/EduBfM: (for student) project files for the EduBfM project
	/EduBtM: (for student) project files for the EduBtM project
	/EduOM: (for student) project files for the EduOM project
./QnA: (for student) a collection of Q&A's
./Tools: (for TA) tools to manage the projects
