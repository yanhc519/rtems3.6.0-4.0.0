/*
 * glue.c -- all the code to make GCC and the libraries run on
 *           a target board running RTEMS. These should work with 
 *           any target which conforms to the RTEMS BSP.
 *
 *  $Id$
 */

#ifndef lint
static char _sccsid[] = "@(#)iface.c 04/12/96     1.1\n";
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int
read(int fd,
     char *buf,
     int nbytes)
{
    return __rtems_read(fd, buf, nbytes);
}

int
write(int fd,
      char *buf,
      int nbytes)
{
    return __rtems_write(fd, buf, nbytes);
}

int
open(char *buf,
     int flags,
     int mode)
{
    return __rtems_open(buf, flags, mode);
}

int
close(int fd)
{
    return __rtems_close(fd);
}

/*
 * isatty -- returns 1 if connected to a terminal device,
 *           returns 0 if not.
 */
int
isatty(int fd)
{
    return __rtems_isatty(fd);
}

/*
 * lseek -- move read/write pointer. Since a serial port
 *          is non-seekable, we return an error.
 */
off_t
lseek(int fd,
      off_t offset,
      int whence)
{
    return __rtems_lseek(fd, offset, whence);
}

/*
 * fstat -- get status of a file. Since we have no file
 *          system, we just return an error.
 */
int
fstat(int fd,
      struct stat *buf)
{
    return __rtems_fstat(fd, buf);
}

int
getpid()
{
  return __rtems_getpid();
}

/*
 * kill -- go out via exit...
 */
int
kill(int pid,
     int sig)
{
    return __rtems_kill(pid, sig);
}


