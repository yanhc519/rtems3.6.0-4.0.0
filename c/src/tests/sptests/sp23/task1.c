/*  Task_1
 *
 *  This task verifies that the dual ported RAM directives work
 *  correctly by converting external addresses to internal addresses and
 *  internal addresses to external addresses.
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

rtems_task Task_1(
  rtems_task_argument argument
)
{
  rtems_id           dpid;
  void              *to_be_converted;
  void              *converted;
  rtems_status_code  status;

  status = rtems_port_ident( Port_name[ 1 ], &dpid );
  directive_failed( status, "rtems_port_ident" );
  printf( "TA1 - rtems_port_ident - 0x%08x\n", dpid );

  to_be_converted = &External_port_area[ 0xe ];
  status = rtems_port_external_to_internal(
    Port_id[ 1 ],
    to_be_converted,
    &converted
  );
  directive_failed( status, "rtems_port_external_to_internal" );
  printf(
    "TA1 - rtems_port_external_to_internal - %p => %p\n",
    to_be_converted,
    converted
  );

  to_be_converted = &Internal_port_area[ 0xe ];
  status = rtems_port_internal_to_external(
    Port_id[ 1 ],
    to_be_converted,
    &converted
  );
  directive_failed( status, "rtems_port_internal_to_external" );
  printf(
    "TA1 - rtems_port_internal_to_external - %p => %p\n",
    to_be_converted,
    converted
  );

  to_be_converted = &Above_port_area[ 0xe ];
  status = rtems_port_external_to_internal(
    Port_id[ 1 ],
    to_be_converted,
    &converted
  );
  directive_failed( status, "rtems_port_external_to_internal" );
  printf(
    "TA1 - rtems_port_external_to_internal - %p => %p\n",
    to_be_converted,
    converted
  );

  to_be_converted = &Below_port_area[ 0xe ];
  status = rtems_port_internal_to_external(
    Port_id[ 1 ],
    to_be_converted,
    &converted
  );
  directive_failed( status, "rtems_port_internal_to_external" );
  printf(
    "TA1 - rtems_port_internal_to_external - %p => %p\n",
    to_be_converted,
    converted
  );

  status = rtems_port_delete( Port_id[ 1 ] );
  directive_failed( status, "rtems_port_delete" );
  puts( "TA1 - rtems_port_delete - DP1" );

  puts( "*** END OF TEST 23 ***" );
  exit( 0 );
}