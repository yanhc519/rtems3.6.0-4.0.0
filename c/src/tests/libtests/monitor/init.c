/*
 *  This is a simple test whose only purpose is to start the Monitor
 *  task.  The Monitor task can be used to obtain information about
 *  a variety of RTEMS objects.  
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

#define TEST_INIT
#include "system.h"

#include <rtems/monitor.h>

rtems_task_priority Priorities[6] = { 0,   1,   1,   3,   4,   5 };

rtems_task Task_1_through_5(
  rtems_unsigned32 argument
)
{
  rtems_status_code status;

  for ( ; ; ) {
    status = rtems_task_wake_after( 100 );
    directive_failed( status, "rtems_task_wake_after" );
  }
}



rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_unsigned32  index;
  rtems_status_code status;

  puts( "\n\n*** MONITOR TASK TEST ***" );

  Task_name[ 1 ] =  rtems_build_name( 'T', 'A', '1', ' ' );
  Task_name[ 2 ] =  rtems_build_name( 'T', 'A', '2', ' ' );
  Task_name[ 3 ] =  rtems_build_name( 'T', 'A', '3', ' ' );
  Task_name[ 4 ] =  rtems_build_name( 'T', 'A', '4', ' ' );
  Task_name[ 5 ] =  rtems_build_name( 'T', 'A', '5', ' ' );

  for ( index = 1 ; index <= 5 ; index++ ) {
    status = rtems_task_create(
      Task_name[ index ],
      Priorities[ index ],
      RTEMS_MINIMUM_STACK_SIZE * 4,
      RTEMS_DEFAULT_MODES,
      (index == 5) ? RTEMS_FLOATING_POINT : RTEMS_DEFAULT_ATTRIBUTES,
      &Task_id[ index ]
    );
    directive_failed( status, "rtems_task_create loop" );
  }

  for ( index = 1 ; index <= 5 ; index++ ) {
    status = rtems_task_start( Task_id[ index ], Task_1_through_5, index );
    directive_failed( status, "rtems_task_start loop" );
  }

  rtems_monitor_init( 0 );

  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}
