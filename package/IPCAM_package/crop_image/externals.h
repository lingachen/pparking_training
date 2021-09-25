#pragma once

extern void	init_camera();
extern bool	snapshot(Mat &out);
extern void	mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename);
extern int		getHeaderLength(char *content);
extern SOCKET	connectToServer(char *szServerName, WORD portNum);
extern char	*readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut);
extern void get_detail_currenttime(char *timestr);
extern void convert_jpeg_buf_to_mat(char *jpeg_buf, int size, Mat &result);