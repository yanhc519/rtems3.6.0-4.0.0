/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *  Copyright assigned to U.S. Government, 1994.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  $Id$
 */

#include <tmacros.h>

/* functions */

rtems_task Init(
  rtems_task_argument argument
);
 
rtems_task Task_1(
  rtems_task_argument argument
);

/* configuration information */

#define CONFIGURE_SPTEST

#define CONFIGURE_TEST_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_TEST_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_PARTITIONS          2
#define CONFIGURE_TICKS_PER_TIMESLICE       100

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <confdefs.h>

/* global variables */

TEST_EXTERN rtems_id   Task_id[ 4 ];         /* array of task ids */
TEST_EXTERN rtems_name Task_name[ 4 ];       /* array of task names */

TEST_EXTERN rtems_name Partition_id[ 4 ];   /* array of partition ids */
TEST_EXTERN rtems_name Partition_name[ 4 ]; /* array of partition names */
 
TEST_EXTERN rtems_unsigned8 Area_1[4096] CPU_STRUCTURE_ALIGNMENT;
TEST_EXTERN rtems_unsigned8 Area_2[274] CPU_STRUCTURE_ALIGNMENT;
 
#define Put_address_from_area_1( _to_be_printed ) \
   printf( "0x%08lx", \
     (unsigned long)((rtems_unsigned8 *)(_to_be_printed) - Area_1 ) )
 
#define Put_address_from_area_2( _to_be_printed ) \
   printf( "0x%08lx", \
     (unsigned long)((rtems_unsigned8 *)(_to_be_printed) - Area_2 ) )
 
/* end of include file */
