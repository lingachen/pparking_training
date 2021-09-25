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
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <pthread.h>

#include "chilkat/CkCrypt2.h"
#include "chilkat/CkByteData.h"
#include "chilkat/CkSFtp.h"
#include "chilkat/CkSshKey.h"
#include "chilkat/CkHttp.h"
#include "chilkat/CkXml.h"
#include "chilkat/CkHttpResponse.h"
#include "chilkat/CkStringBuilder.h"
#include "chilkat/CkJsonObject.h"
#include "chilkat/CkJsonArray.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvaux.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

#include "defines2.h"
#include "externals.h"