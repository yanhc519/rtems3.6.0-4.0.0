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
 
rtems_asr Process_asr(
  rtems_signal_set signal_set
);
 
rtems_task Task_1(
  rtems_task_argument argument
);
 
rtems_task Task_2(
  rtems_task_argument argument
);

/* configuration information */

#define CONFIGURE_SPTEST

#define CONFIGURE_TEST_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_TEST_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK   RTEMS_MILLISECONDS_TO_MICROSECONDS(25)
#define CONFIGURE_TICKS_PER_TIMESLICE     1000

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <confdefs.h>

/* global variables */

TEST_EXTERN rtems_id   Task_id[ 4 ];         /* array of task ids */
TEST_EXTERN rtems_name Task_name[ 4 ];       /* array of task names */

TEST_EXTERN rtems_unsigned32 Task_2_preempted;

/* end of include file */
