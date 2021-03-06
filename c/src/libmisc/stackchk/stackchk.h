/*  stackchk.h
 *
 *  This include file contains information necessary to utilize
 *  and install the stack checker mechanism.
 *
 *  COPYRIGHT (c) 1989, 1990, 1991, 1992, 1993, 1994.
 *  On-Line Applications Research Corporation (OAR).
 *  All rights assigned to U.S. Government, 1994.
 *
 *  This material may be reproduced by or for the U.S. Government pursuant
 *  to the copyright license under the clause at DFARS 252.227-7013.  This
 *  notice must appear in all copies of this file and its derivatives.
 *
 *  $Id$
 */

#ifndef __STACK_CHECK_h
#define __STACK_CHECK_h

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Stack_check_Initialize
 */

void Stack_check_Initialize( void );

/*
 *  Stack_check_Dump_usage
 */

void Stack_check_Dump_usage( void );

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
