/*  Shared Memory Lock Routines
 *
 *  This shared memory locked queue support routine need to be
 *  able to lock the specified locked queue.  Interrupts are
 *  disabled while the queue is locked to prevent preemption
 *  and deadlock when two tasks poll for the same lock.
 *  previous level.
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

#include <rtems.h>
#include <bsp.h>
#include <shm.h>

/*
 *  Shm_Initialize_lock
 *
 *  Initialize the lock for the specified locked queue.
 */

void Shm_Initialize_lock(
  Shm_Locked_queue_Control *lq_cb
)
{
  lq_cb->lock = LQ_UNLOCKED;
}

/*  void _Shm_Lock( &lq_cb )
 *
 *  This shared memory locked queue support routine locks the
 *  specified locked queue.  It disables interrupts to prevent
 *  a deadlock condition.
 */

void Shm_Lock(
  Shm_Locked_queue_Control *lq_cb
)
{
  rtems_unsigned32 isr_level, oldlock;

  rtems_interrupt_disable( isr_level );
    Shm_isrstat = isr_level;
    while ( 1 ) {
      atomic_modify( SHM_LOCK_VALUE, &lq_cb->lock, oldlock );
      if ( !(oldlock & SHM_LOCK_VALUE) )
        return;
      delay( 28 );        /* delay 28 microseconds */
    }
}

/*
 *  Shm_Unlock
 *
 *  Unlock the lock for the specified locked queue.
 */

void Shm_Unlock(
  Shm_Locked_queue_Control *lq_cb
)
{
  rtems_unsigned32 isr_level;

  lq_cb->lock = SHM_UNLOCK_VALUE;
  isr_level = Shm_isrstat;
  rtems_interrupt_enable( isr_level );
}

