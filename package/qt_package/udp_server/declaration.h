#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#include <fcntl.h>
#include <dirent.h> 
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <sched.h>
#include <string.h>
#include <vector>
#include <poll.h>
#include <errno.h>
#include <iosfwd>
#include <memory>
#include <utility>
#include <iconv.h>

#include "chilkat/CkStringBuilder.h"
#include "chilkat/CkJsonObject.h"
#include "chilkat/CkJsonArray.h"

#include <libpq-fe.h>
#include <zmq.hpp>

using namespace std;
using std::string;

#include "defines.h"
#include "external_vars.h"
#include "external_func.h"
