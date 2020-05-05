/*  Test_task
 *
 *  This task tests the rtems_task_set_note directive on a remote task and that
 *  errors are returned when attempting to delete, start, or restart
 *  a remote task.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
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

#include "system.h"

extern rtems_multiprocessing_table Multiprocessing_configuration;

rtems_task Test_task(
  rtems_task_argument argument
)
{
  rtems_id          tid;
  rtems_status_code status;
  rtems_unsigned32  remote_node;
  rtems_id          remote_tid;
  rtems_id          test_tid;
  rtems_unsigned32  note;

  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

  remote_node = (Multiprocessing_configuration.node == 1) ? 2 : 1;
  printf( "Remote task's name is : " );
  put_name( Task_name[ remote_node ], TRUE );

  puts( "Getting TID of remote task (all nodes)" );
  do {
      status = rtems_task_ident(
          Task_name[ remote_node ],
          RTEMS_SEARCH_ALL_NODES,
          &remote_tid
          );
  } while ( status != RTEMS_SUCCESSFUL );

  directive_failed( status, "rtems_task_ident" );

  puts( "Getting TID of remote task (1 node)" );
  status = rtems_task_ident( Task_name[ remote_node ], remote_node, &test_tid );
  directive_failed( status, "rtems_task_ident" );

  if ( test_tid != remote_tid ) {
    puts( "rtems_task_ident tid's do not match!!" );
    rtems_fatal_error_occurred( status );
  }

  status = rtems_task_delete( remote_tid );
  fatal_directive_status(
    status,
    RTEMS_ILLEGAL_ON_REMOTE_OBJECT,
    "rtems_task_delete of remote task"
  );
  puts( "rtems_task_delete of remote task returned the correct error" );

  status = rtems_task_start( remote_tid, Test_task, 0 );
  fatal_directive_status(
    status,
    RTEMS_ILLEGAL_ON_REMOTE_OBJECT,
    "rtems_task_start of remote task"
  );
  puts( "rtems_task_start of remote task returned the correct error" );

  status = rtems_task_restart( remote_tid, 0 );
  fatal_directive_status(
    status,
    RTEMS_ILLEGAL_ON_REMOTE_OBJECT,
    "rtems_task_restart of remote task"
  );
  puts( "rtems_task_restart of remote task returned the correct error" );

  printf(
   "Setting notepad %d of the remote task to %d\n",
   rtems_get_node(tid),
   rtems_get_node(tid)
  );
  status = rtems_task_set_note(
    remote_tid,
    rtems_get_node(tid),
    rtems_get_node(tid)
  );
  directive_failed( status, "rtems_task_set_note" );

  puts( "Getting a notepad of the remote task" );
  status = rtems_task_get_note( remote_tid, rtems_get_node(tid), &note );
  directive_failed( status, "rtems_task_get_note" );

  if ( note == rtems_get_node(tid) )
    puts( "Remote notepad set and read correctly" );
  else
    printf(
      "FAILURE!! Remote notepad was not set and read correctly (%d, %d)\n",
      note,
      rtems_get_node( tid )
    );

  status = rtems_task_wake_after( TICKS_PER_SECOND );
  directive_failed( status, "rtems_task_wake_after" );

  puts( "*** END OF TEST 2 ***" );
  exit( 0 );
}