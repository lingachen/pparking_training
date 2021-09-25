#include "pparking.h"
#include "utils.h"

void Sleep(int val)
{
	int dat;
	if (val % 1000 == 0) {
		dat = val / 1000;
		sleep(dat);
	}
	else {
		dat = val * 1000;
		usleep(dat);
	}
}