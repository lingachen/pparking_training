#include "declaration.h"
#include "utils.h"

int splitstr(char *readin, int len, char split, char ignchar1, char ignchar2, char ignchar3, char ignchar4, char *token, int token_len)
{
	int i, j, k;
	char prev;
	int enable = 1;

	j = 0; k = 0; prev = 0;
	for (i = 0; i < len; i++) {
		if (readin[i] == split && prev == split) {
			token[k*token_len + j] = '\0';
			k++;
			j = 0;
			prev = readin[i];
			continue;
		}
		if ((readin[i] == split || readin[i] == 9) && j == 0) {}
		else if (readin[i] == 0x27) {
			enable = enable * (-1);
		}
		else if (readin[i] == ignchar1) {}
		else if (readin[i] == ignchar2) {}
		else if (readin[i] == ignchar3) {}
		else if (readin[i] == ignchar4) {}
		else if (readin[i] == '\t') {}
		else if (readin[i] == 0x0a) {}
		else if (readin[i] == 0x0d) {}
		else if (readin[i] == split && enable == 1) {
			token[k*token_len + j] = '\0';
			k++;
			j = 0;
		}
		else {
			token[k*token_len + j] = readin[i];
			j++;
		}
		prev = readin[i];
	}

	if (j != 0) {
		token[k*token_len + j] = '\0';
		k++;
	}

	return(k);
}

void get_currenttime(char *timestr)
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

	sprintf(timestr, "%s-%s-%02d %s:%s:%s", st_year, st_month, atoi(st_day), st_h, st_m, st_s);
}

void get_currenttime_for_bcd(time_t currenttime, char *bcd_str)
{
	char   st[200];
	char   st_year[100];
	char   st_month[100];
	char   st_day[100];
	char   st_h[100];
	char   st_m[100];
	char   st_s[100];

	strcpy(st, ctime(&currenttime));

	st[7] = '\0';
	st[10] = '\0';
	st[13] = '\0';
	st[16] = '\0';
	st[19] = '\0';
	st[24] = '\0';
	strcpy(st_year, &st[22]);
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

	sprintf(bcd_str, "%s%s%02d%s%s%s", st_year, st_month, atoi(st_day), st_h, st_m, st_s);
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

void get_detail_currenttime_for_bcd(char *timestr)
{
	char		 st[100];
	char		 st_year[100];
	char		 st_month[100];
	char		 st_day[100];
	char		 st_h[100];
	char		 st_m[100];
	char		 st_s[100];
	long		 timeval_ms;
	struct timeb detail_time;

	ftime(&detail_time);

	strcpy(st, ctime(&detail_time.time));
	st[7] = '\0';
	st[10] = '\0';
	st[13] = '\0';
	st[16] = '\0';
	st[19] = '\0';
	st[24] = '\0';
	strcpy(st_year, &st[22]);
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

	timeval_ms = (long)(detail_time.millitm);
	sprintf(timestr, "%s%s%02d%s%s%s%03d", st_year, st_month, atoi(st_day), st_h, st_m, st_s, timeval_ms);
}

// 191211110330123
void convert_bcdtimestr(char *bcdtimestr, char *stdtimestr)
{
	int		year, month, day, hour, min, sec;
	char	st[200];
	char	st_year[100];
	char	st_month[100];
	char	st_day[100];
	char	st_h[100];
	char	st_m[100];
	char	st_s[100];
	time_t	li;

	struct	tm t;

	strcpy(st, bcdtimestr);

	strncpy(st_year, &st[0], 2); st_year[2] = '\0';
	strncpy(st_month, &st[2], 2); st_month[2] = '\0';
	strncpy(st_day, &st[4], 2); st_day[2] = '\0';
	strncpy(st_h, &st[6], 2); st_h[2] = '\0';
	strncpy(st_m, &st[8], 2); st_m[2] = '\0';
	strncpy(st_s, &st[10], 2); st_s[2] = '\0';
	year = atoi(st_year) + 2000;
	month = atoi(st_month);
	day = atoi(st_day);
	hour = atoi(st_h);
	min = atoi(st_m);
	sec = atoi(st_s);

	sprintf(stdtimestr, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
}

// 191211110330123
time_t get_time_mins_long_value(char *timestr)
{
	int		year, month, day, hour, min, sec;
	char	st[200];
	char	st_year[100];
	char	st_month[100];
	char	st_day[100];
	char	st_h[100];
	char	st_m[100];
	char	st_s[100];
	time_t	li;

	struct	tm t;

	strcpy(st, timestr);

	strncpy(st_year, &st[0], 2); st_year[2] = '\0';
	strncpy(st_month, &st[2], 2); st_month[2] = '\0';
	strncpy(st_day, &st[4], 2); st_day[2] = '\0';
	strncpy(st_h, &st[6], 2); st_h[2] = '\0';
	strncpy(st_m, &st[8], 2); st_m[2] = '\0';
	strncpy(st_s, &st[10], 2); st_s[2] = '\0';
	year = atoi(st_year) + 2000;
	month = atoi(st_month);
	day = atoi(st_day);
	hour = atoi(st_h);
	min = atoi(st_m);
	sec = atoi(st_s);

	t.tm_year = year - 1900;
	//t.tm_mon = month;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min = min;
	t.tm_sec = sec;
	li = mktime(&t);
	printf("%s: year=%d timeval=%ld\n", timestr, year, li);

	return(li);
}

void get_validtime(char *monthid, char *validstart, char *validend)
{
	char yearstr[20];
	char monthstr[20];
	int year_val;
	int month_val;

	strncpy(yearstr, monthid, 4); yearstr[4] = '\0';
	strncpy(monthstr, &monthid[4], 2); monthstr[2] = '\0';
	year_val = atoi(yearstr);
	month_val = atoi(monthstr);

	char tmp_validstart[50];
	sprintf(tmp_validstart, "%02d%02d01000000", year_val - 2000, month_val);

	char tmp_validend[50];
	if (month_val == 12) {
		month_val = 1;
		year_val++;
	}
	else month_val++;
	sprintf(tmp_validend, "%02d%02d01000000", year_val - 2000, month_val);

	time_t validstart_val = get_time_mins_long_value(tmp_validstart);
	time_t validend_val = get_time_mins_long_value(tmp_validend) - 1;

	get_currenttime_for_bcd(validstart_val, validstart);
	get_currenttime_for_bcd(validend_val, validend);
}

long get_time_difference_secs(char *time1, char *time2)
{
	time_t m1, m2, m3;
	int			  total_secs;
	char		  time1_20[100];
	char		  time2_20[100];

	sprintf(time1_20, "20%s", time1);
	sprintf(time2_20, "20%s", time2);

	m1 = get_time_mins_long_value(time1_20);
	m2 = get_time_mins_long_value(time2_20);
	m3 = (m2 - m1) / 1;
	total_secs = (int)m3;
	return(total_secs);
}

SOCKET udp_server_init(char *ip_server, u16 port_server)
{
	char   mesg[1000];
	SOCKET sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) return sockfd;

	int flags = fcntl(sockfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sockfd, F_SETFL, flags);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port_server);
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	return sockfd;
}

bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr)
{
	bzero(sockaddr, sizeof(*sockaddr));
	sockaddr->sin_addr.s_addr = inet_addr(ip_report);
	sockaddr->sin_port = htons(port_report);
	sockaddr->sin_family = AF_INET;
	return true;
}

int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client)
{
	int lenword;
	if (p == NULL) {
		return -1;
	}
	lenword = sendto(sockfd,
		p,
		len,
		0,
		(sockaddr *)client,
		sizeof(sockaddr));
	return lenword;
}

bool init_udp()
{
	bool status;
	char log_msg[4096];

	server_sockfd = udp_server_init("127.0.0.1", 2001);
	if (server_sockfd <= 0) return false;
	sprintf(log_msg, "SVR_UDP: Ok\n"); write_log(log_msg);

	for (int i = 0; i < atoi(config_cp.acount); i++) {
		status = udp_client_init(config_cp.apm[i], 3001, (SOCKADDR_IN *)&send_to_apm[i]);
		if (!status) return false;
		sprintf(log_msg, "APM%d_UDP: Ok\n", i+1); write_log(log_msg);
	}

	for (int i = 0; i < atoi(config_cp.ecount); i++) {
		status = udp_client_init(config_cp.e[i], 3001, (SOCKADDR_IN *)&send_to_e[i]);
		if (!status) return false;
		sprintf(log_msg, "E%d_UDP: Ok\n", i+1); write_log(log_msg);
	}

	for (int i = 0; i < atoi(config_cp.xcount); i++) {
		if (strcmp(config_cp.e[i], config_cp.x[i]) == 0) status = udp_client_init(config_cp.x[i], 3002, (SOCKADDR_IN *)&send_to_x[i]);
		else											 status = udp_client_init(config_cp.x[i], 3001, (SOCKADDR_IN *)&send_to_x[i]);
		if (!status) return false;
		sprintf(log_msg, "X%d_UDP: Ok\n", i+1); write_log(log_msg);
	}

	return true;
}

bool check_file_exist(char *FullPathFileName)
{
	bool status = false;
	struct stat	filestatus;

	int exist = stat(FullPathFileName, &filestatus);
	if (exist == 0) status = true;
	return(status);
}

void get_time_yymmdd(char *time_yymmdd)
{
	char timstr[100];

	get_detail_currenttime_for_bcd(timstr);
	strcpy(time_yymmdd, &timstr[0]);
	time_yymmdd[6] = '\0';
}

void get_datecode_path_name(char *pathname, char *out_pathname)
{
	char timestr_yymmdd[20];
	char system_cmd[300];
	char log_msg[4096];

	get_time_yymmdd(timestr_yymmdd);
	sprintf(out_pathname, "%s/%s", pathname, timestr_yymmdd);

	bool status = check_file_exist(out_pathname);
	if (status == false) {
		sprintf(system_cmd, "sudo mkdir %s", out_pathname); system(system_cmd);
		sprintf(system_cmd, "sudo chmod 755 %s", out_pathname); system(system_cmd);
	}
}

bool copy_file_remote(char *remote_ip, char *img_pathstr, char *img_filename)
{
	char log_msg[4096];

	// step1: check remote folder whether exist?
	int  ssh_ret;
	char ssh_cmd[1024];
	sprintf(ssh_cmd, "ssh %s test -d %s", remote_ip, img_pathstr);
	ssh_ret = system(ssh_cmd);
	sprintf(log_msg, "copy_file_remote(test): ssh_ret=%d ssh_cmd=%s\n", ssh_ret, ssh_cmd); write_log(log_msg);
	if (ssh_ret != 0) {
		sprintf(ssh_cmd, "ssh %s mkdir %s", remote_ip, img_pathstr);
		ssh_ret = system(ssh_cmd);
		sprintf(log_msg, "copy_file_remote(mkdir): ssh_ret=%d ssh_cmd=%s\n", ssh_ret, ssh_cmd); write_log(log_msg);
		if (ssh_ret != 0) {
			return false;
		}
	}

	// step2: copy file to remote folder
	sprintf(ssh_cmd, "scp %s/%s root@%s:%s", img_pathstr, img_filename, remote_ip, img_pathstr);
	ssh_ret = system(ssh_cmd);
	sprintf(log_msg, "copy_file_remote(scp): ssh_ret=%d ssh_cmd=%s\n", ssh_ret, ssh_cmd); write_log(log_msg);
	if (ssh_ret != 0) {
		ssh_ret = system(ssh_cmd);
		sprintf(log_msg, "copy_file_remote(scp): ssh_ret=%d ssh_cmd=%s\n", ssh_ret, ssh_cmd); write_log(log_msg);
		if (ssh_ret != 0) {
			return false;
		}
	}
	return true;
}

void *monitor_task(void *)
{
	char log_msg[4096];

	sprintf(log_msg, "[U], monitor_task Ok\n"); write_log(log_msg);

	while (1) {

	}
}

void clean_database()
{
	// (1) check exitpass (by paidtime)

	// (2) check movement (by paid_status)
}

void b2u(char src[], char tar[])
{
	cout << "\nConvert code From big5 to UTF-8...";
	size_t srclen = strlen(src);
	size_t tarlen = srclen / 2 * 3 + 1;
	memset(tar, 0, tarlen);
	iconv_t cd = iconv_open("UTF-8", "big5");
	size_t error = iconv(cd, &src, &srclen, &tar, &tarlen);
	iconv_close(cd);
}
/*----------------
  UTF-8 Тр big5
------------------*/
void u2b(char src[], char tar[]) 
{
	cout << "\nConvert code From UTF-8 to big5...";
	size_t srclen = strlen(src);
	size_t tarlen = srclen / 3 * 2 + 1;
	memset(tar, 0, tarlen);
	iconv_t cd = iconv_open("big5", "UTF-8");
	size_t error = iconv(cd, &src, &srclen, &tar, &tarlen);
	iconv_close(cd);
}

void Ucase(char *sPtr, char *outstr)
{
	char retstr[5000];
	int  i;

	strcpy(retstr, sPtr);

	for (i = 0; i < (int)strlen(retstr); i++) {
		if (islower(retstr[i])) retstr[i] = toupper(retstr[i]);
	}
	strcpy(outstr, retstr);
}

SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr)
{
	SOCKET sockfd;
	struct sockaddr_in address;

	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_report);

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, ip_report, &serv_addr.sin_addr) <= 0) {
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		return -1;
	}

	int flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	return sockfd;
}

int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client)
{
	int lenword;
	if (p == NULL) {
		return -1;
	}
	send(sockfd, p, len, 0);
	return lenword;
}

int tcp_read(int sockfd, char *buffer)
{
	int n;

	bzero(buffer, 256);

	n = recv(sockfd, buffer, 255, 0);

	if (n < 0) return -1;
	return n;
}

bool open_apm_lock(int apmid, int eio_numb)
{
	char ether_io_ip[50];
	char apm_ip[50];

	// step1: find ether_io ip
	strcpy(apm_ip, config_cp.apm[apmid]);
	bool found_apm_flag = false;
	for (int i = 0; i < atoi(config_cp.acount); i++) {
		if (strcmp(apm_ip, receipt_setting[i].ip) == 0) {
			found_apm_flag = true;
			strcpy(ether_io_ip, receipt_setting[i].ether_io);
			break;
		}
	}
	if (found_apm_flag == false) {
		printf("apm not found error\n");
		return false;
	}

	// step2: init tcpip
	eio_server_sockfd = tcp_client_init(ether_io_ip, 24, &send_to_eio);
	if (eio_server_sockfd <= 0) {
		printf("tcp init error\n");
		return false;
	}

	// step4: send TCP to control ethernet IO 
	char tcp_cmd[100];
	tcp_cmd[0] = 0x68;
	tcp_cmd[1] = 0x01;
	tcp_cmd[2] = 0xA2 + 0;	// A2: close relay
	tcp_cmd[3] = 0x01;
	tcp_cmd[4] = 0x01 + eio_numb;
	tcp_cmd[5] = tcp_cmd[1] ^ tcp_cmd[2] ^ tcp_cmd[3] ^ tcp_cmd[4];
	tcp_cmd[6] = 0x16;
	tcp_send(eio_server_sockfd, tcp_cmd, 7, &send_to_eio);

	usleep(100000);

	char buf[1024];
	int n = tcp_read(eio_server_sockfd, buf);
	if (n > 0) {
		printf("TCP: ");
		for (int i = 0; i < n; i++) {
			printf("%02X ", buf[i]);
		}
		printf("\n");
	}

	sleep(1); // keep relay close for 1s

	tcp_cmd[0] = 0x68;
	tcp_cmd[1] = 0x01;
	tcp_cmd[2] = 0xA2 + 1;	// A3: open relay
	tcp_cmd[3] = 0x01;
	tcp_cmd[4] = 0x01 + eio_numb;
	tcp_cmd[5] = tcp_cmd[1] ^ tcp_cmd[2] ^ tcp_cmd[3] ^ tcp_cmd[4];
	tcp_cmd[6] = 0x16;
	tcp_send(eio_server_sockfd, tcp_cmd, 7, &send_to_eio);

	usleep(100000);

	n = tcp_read(eio_server_sockfd, buf);
	if (n > 0) {
		printf("TCP: ");
		for (int i = 0; i < n; i++) {
			printf("%02X ", buf[i]);
		}
		printf("\n");
	}

	close(eio_server_sockfd);
	return true;
}