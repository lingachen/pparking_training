#pragma once

void	init_camera();
bool	snapshot(Mat &out);
void	mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename);
int		getHeaderLength(char *content);
SOCKET	connectToServer(char *szServerName, WORD portNum);
char	*readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut);
void get_detail_currenttime(char *timestr);
void convert_jpeg_buf_to_mat(char *jpeg_buf, int size, Mat &result);