/*  Test_task
 *
 *  This task tests global semaphore operations.  It verifies that
 *  global semaphore errors are correctly returned.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
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

#include "system.h"

rtems_task Test_task(
  rtems_task_argument argument
)
{
  rtems_unsigned32  count;
  rtems_status_code status;

  puts( "Getting SMID of semaphore" );

  do {
    status = rtems_semaphore_ident(
      Semaphore_name[ 1 ],
      RTEMS_SEARCH_ALL_NODES,
      &Semaphore_id[ 1 ]
    );
  } while ( !rtems_is_status_successful( status ) );

  if ( Multiprocessing_configuration.node == 2 ) {
    status = rtems_semaphore_delete( Semaphore_id[ 1 ] );
    fatal_directive_status(
      status,
      RTEMS_ILLEGAL_ON_REMOTE_OBJECT,
      "rtems_semaphore_delete did not return RTEMS_ILLEGAL_ON_REMOTE_OBJECT"
    );
    puts(
      "rtems_semaphore_delete correctly returned RTEMS_ILLEGAL_ON_REMOTE_OBJECT"
    );
  }

  count = 0;            /* number of times node 1 releases semaphore */
  while ( FOREVER ) {
    put_dot( 'p' );
    status = rtems_semaphore_obtain(
      Semaphore_id[ 1 ],
      RTEMS_DEFAULT_OPTIONS,
      RTEMS_NO_TIMEOUT
    );
    if ( status != RTEMS_SUCCESSFUL ) {
      fatal_directive_status(
        status,
        RTEMS_OBJECT_WAS_DELETED,
        "rtems_semaphore_obtain"
      );
      puts( "\nGlobal semaphore deleted" );
      puts( "*** END OF TEST 8 ***" );
      exit( 0 );
    }

    if ( Multiprocessing_configuration.node == 1 && ++count == 1000 ) {
      status = rtems_task_wake_after( TICKS_PER_SECOND );
      directive_failed( status, "rtems_task_wake_after" );

      puts( "\nDeleting global semaphore" );
      status = rtems_semaphore_delete( Semaphore_id[ 1 ] );
      directive_failed( status, "rtems_semaphore_delete" );

      puts( "*** END OF TEST 8 ***" );
      exit( 0 );
    }
    else {
      put_dot( 'v' );
      status = rtems_semaphore_release( Semaphore_id[ 1 ] );
      directive_failed( status, "rtems_semaphore_release FAILED!!" );
    }
  }
}
