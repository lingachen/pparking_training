#pragma once

int  splitstr(char *readin, int len, char split, char ignchar1, char ignchar2, char ignchar3, char ignchar4, char *token, int token_len);
void get_currenttime(char *timestr);
void get_currenttime_for_bcd(time_t currenttime, char *bcd_str);
void get_detail_currenttime(char *timestr);
void get_detail_currenttime_for_bcd(char *timestr);
void convert_bcdtimestr(char *bcdtimestr, char *stdtimestr);
time_t get_time_mins_long_value(char *timestr);
void get_validtime(char *monthid, char *validstart, char *validend);
long get_time_difference_secs(char *time1, char *time2);
SOCKET udp_server_init(char *ip_server, u16 port_server);
bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
bool init_udp();
bool check_file_exist(char *FullPathFileName);
void get_time_yymmdd(char *time_yymmdd);
void get_datecode_path_name(char *pathname, char *out_pathname);
bool copy_file_remote(char *remote_ip, char *img_pathstr, char *img_filename);
void *monitor_task(void *);
void b2u(char src[], char tar[]);
void u2b(char src[], char tar[]);
void Ucase(char *sPtr, char *outstr);
SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
int tcp_read(int sockfd, char *buffer);
bool open_apm_lock(int apmid, int eio_numb);