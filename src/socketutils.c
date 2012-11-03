
/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "socketutils.h"

int
socket_wait(Socket *this, time_t seconds )
{
    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(this->fd, &fdset);
    struct timeval tv_timeout = { seconds, 0 };

    if (select((this->fd) + 1, &fdset, NULL, NULL, &tv_timeout) == -1) {
      return -1; // error
    }

    if (FD_ISSET(this->fd, &fdset)) {
      return 1; // found!
    }

    return 0; // timeout
}
