#include "pparking.h"
#include "main.h"

int main()
{
	init_camera();

	Mat frame;
	snapshot(frame);
	imshow("frame", frame);
	waitKey(0);

	return 0;
}