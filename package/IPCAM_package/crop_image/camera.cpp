#include "pparking.h"
#include "camera.h"

char config_pgs_http_str[200];

void init_camera()
{
	sprintf(config_pgs_http_str, "http://%s/cgi-bin/images_cgi?channel=0&user=%s&pwd=%s", "192.168.2.191", "admin", "PGSadmin");	//user=admin&pwd=PGSadmin
}

bool snapshot(Mat &out)
{
	char timestr[100];

	long fileSize;
	char *memBuffer, *headerBuffer;
	memBuffer = headerBuffer = NULL;
	memBuffer = readUrl2(config_pgs_http_str, fileSize, &headerBuffer);
	if (memBuffer == NULL) {
		get_detail_currenttime(timestr);
		printf("[%s]: Empty Image\n", timestr);
		return false;
	}
	if (fileSize < 10000) {
		get_detail_currenttime(timestr);
		printf("[%s]: Partial Image: filesize=%d\n", timestr, fileSize);
		return false;
	}
	if (fileSize != 0) {
		convert_jpeg_buf_to_mat(memBuffer, fileSize, out);
		delete(memBuffer);
		delete(headerBuffer);
		return true;
	}
	else {
		get_detail_currenttime(timestr);
		printf("[%s]: Empty Image\n", timestr);
		return false;
	}
}

void mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename)
{
	string::size_type n;
	string url = mUrl;

	if (url.substr(0, 7) == "http://")
		url.erase(0, 7);

	if (url.substr(0, 8) == "https://")
		url.erase(0, 8);

	n = url.find('/');
	if (n != string::npos)
	{
		serverName = url.substr(0, n);
		filepath = url.substr(n);
		n = filepath.rfind('/');
		filename = filepath.substr(n + 1);
	}

	else
	{
		serverName = url;
		filepath = "/";
		filename = "";
	}
}

int getHeaderLength(char *content)
{
	const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
	char *findPos;
	int ofset = -1;

	if (content == NULL) return -1;

	findPos = strstr(content, srchStr1);
	if (findPos != NULL)
	{
		ofset = findPos - content;
		ofset += strlen(srchStr1);
	}

	else
	{
		findPos = strstr(content, srchStr2);
		if (findPos != NULL)
		{
			ofset = findPos - content;
			ofset += strlen(srchStr2);
		}
	}
	return ofset;
}

SOCKET connectToServer(char *szServerName, WORD portNum)
{
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET conn;

	conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn == 0)
		return NULL;

	server.sin_addr.s_addr = inet_addr(szServerName); //*((unsigned long*)hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		return NULL;
	}
	return conn;
}

char *readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut)
{
	const int bufSize = 512;
	char readBuffer[bufSize], sendBuffer[bufSize], tmpBuffer[bufSize];
	char *tmpResult = NULL, *result;
	SOCKET conn;
	string server, filepath, filename;
	long totalBytesRead, thisReadSize, headerLen;

	mParseUrl(szUrl, server, filepath, filename);

	///////////// step 1, connect //////////////////////
	char server_str[100];
	strcpy(server_str, server.c_str());
	char *ptr = strstr(server_str, ":");
	if (ptr != NULL) {
		*ptr = '\0';
	}
	conn = connectToServer((char*)server.c_str(), 80);

	///////////// step 2, send GET request /////////////
	sprintf(tmpBuffer, "GET %s HTTP/1.0", filepath.c_str());
	strcpy(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	sprintf(tmpBuffer, "Host: %s", server.c_str());
	strcat(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	sprintf(tmpBuffer, "Authorization: Basic YWRtaW46UEdTYWRtaW4=");
	strcat(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	strcat(sendBuffer, "\r\n");
	send(conn, sendBuffer, strlen(sendBuffer), 0);

	//    SetWindowText(edit3Hwnd, sendBuffer);
		//printf("Buffer being sent:\n%s", sendBuffer);

		///////////// step 3 - get received bytes ////////////////
		// Receive until the peer closes the connection
	totalBytesRead = 0;
	while (1)
	{
		memset(readBuffer, 0, bufSize);
		thisReadSize = recv(conn, readBuffer, bufSize, 0);

		if (thisReadSize <= 0)
			break;

		tmpResult = (char*)realloc(tmpResult, thisReadSize + totalBytesRead);

		memcpy(tmpResult + totalBytesRead, readBuffer, thisReadSize);
		totalBytesRead += thisReadSize;
	}

	if (totalBytesRead == 0) {
		if (conn != NULL) close(conn);
		return NULL;
	}
	headerLen = getHeaderLength(tmpResult);
	if (headerLen < 0) {
		if (conn != NULL) close(conn);
		return NULL;
	}

	long contenLen = totalBytesRead - headerLen;
	result = new char[contenLen + 1];
	memcpy(result, tmpResult + headerLen, contenLen);
	result[contenLen] = 0x0;
	char *myTmp;

	myTmp = new char[headerLen + 1];
	strncpy(myTmp, tmpResult, headerLen);
	myTmp[headerLen] = NULL;
	delete(tmpResult);
	*headerOut = myTmp;

	bytesReturnedOut = contenLen;
	if (conn != NULL) close(conn);
	return (result);
}

void get_detail_currenttime(char *timestr)
{
	char		 st[100];
	char		 st_year[100];
	char		 st_month[100];
	char		 st_day[100];
	char		 st_h[100];
	char		 st_m[100];
	char		 st_s[100];
	struct timeb detail_time;

	ftime(&detail_time);
	strcpy(st, ctime(&detail_time.time));

	st[7] = '\0';
	st[10] = '\0';
	st[13] = '\0';
	st[16] = '\0';
	st[19] = '\0';
	st[24] = '\0';
	strcpy(st_year, &st[20]);
	strcpy(st_month, &st[4]);
	strcpy(st_day, &st[8]);
	strcpy(st_h, &st[11]);
	strcpy(st_m, &st[14]);
	strcpy(st_s, &st[17]);

	if (strcmp(st_month, "Jan") == 0) {
		strcpy(st_month, "01");
	}
	else if (strcmp(st_month, "Feb") == 0) {
		strcpy(st_month, "02");
	}
	else if (strcmp(st_month, "Mar") == 0) {
		strcpy(st_month, "03");
	}
	else if (strcmp(st_month, "Apr") == 0) {
		strcpy(st_month, "04");
	}
	else if (strcmp(st_month, "May") == 0) {
		strcpy(st_month, "05");
	}
	else if (strcmp(st_month, "Jun") == 0) {
		strcpy(st_month, "06");
	}
	else if (strcmp(st_month, "Jul") == 0) {
		strcpy(st_month, "07");
	}
	else if (strcmp(st_month, "Aug") == 0) {
		strcpy(st_month, "08");
	}
	else if (strcmp(st_month, "Sep") == 0) {
		strcpy(st_month, "09");
	}
	else if (strcmp(st_month, "Oct") == 0) {
		strcpy(st_month, "10");
	}
	else if (strcmp(st_month, "Nov") == 0) {
		strcpy(st_month, "11");
	}
	else if (strcmp(st_month, "Dec") == 0) {
		strcpy(st_month, "12");
	}
	else {
	}

	sprintf(timestr, "%s-%s-%02d %s:%s:%s.%03d", st_year, st_month, atoi(st_day), st_h, st_m, st_s, detail_time.millitm);
}

void convert_jpeg_buf_to_mat(char *jpeg_buf, int size, Mat &result)
{
	Mat rawData = Mat(1, size, CV_8UC1, jpeg_buf);
	if (rawData.empty()) return;
	result = imdecode(rawData, CV_LOAD_IMAGE_COLOR).clone();
}
