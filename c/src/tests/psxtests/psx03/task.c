/*  Task_1_through_3
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
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
#include <signal.h>

void *Task_1(
  void *argument
)
{
  int status;

  /* send SIGUSR2 to Init which is waiting on SIGUSR1 */

  print_current_time( "Task_1: ", "" );

  puts( "Task_1: pthread_kill - SIGUSR2 to Init" );
  status = pthread_kill( Init_id, SIGUSR2 );
  assert( !status );

  pthread_exit( NULL );

     /* switch to Init */

  return NULL; /* just so the compiler thinks we returned something */
}

void *Task_2(
  void *argument
)
{
  int status;

  /* send SIGUSR1 to Init which is waiting on SIGUSR1 */
 
  print_current_time( "Task_2: ", "" );

  puts( "Task_1: pthread_kill - SIGUSR1 to Init" );
  status = pthread_kill( Init_id, SIGUSR1 );
  assert( !status );
 
  pthread_exit( NULL );

     /* switch to Init */

  return NULL; /* just so the compiler thinks we returned something */
}
