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

void get_time_yymmdd(char *time_yymmdd)
{
	char timstr[100];

	get_detail_currenttime_for_bcd(timstr);
	strcpy(time_yymmdd, &timstr[0]);
	time_yymmdd[6] = '\0';
}

void get_time_yymmdd_tomorrow(char *time_yymmdd_tomorrow)
{
	char   st[200];
	char   st_year[100];
	char   st_month[100];
	char   st_day[100];
	char   st_h[100];
	char   st_m[100];
	char   st_s[100];

	time_t currenttime;
	time(&currenttime);
	currenttime += 86400;
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

	sprintf(time_yymmdd_tomorrow, "%s%s%02d", st_year, st_month, atoi(st_day));
}

void mutex_lock(TASK_MUTEX *task_mutex)
{
	pthread_mutex_lock(task_mutex);
}

void mutex_unlock(TASK_MUTEX *task_mutex)
{
	pthread_mutex_unlock(task_mutex);
}

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

int find_path_allfiles(char *pathname, char *filelist)
{
	int			n;
	int			numOfFileFound = 0;
	char		search_filename[300];
	char		filename[300];
	char		*ptr;

	sprintf(search_filename, "%s/*", pathname);

	struct dirent **namelist;
	n = scandir(pathname, &namelist, 0, alphasort);
	if (n < 0) return 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(namelist[i]->d_name, ".") == 0 || strcmp(namelist[i]->d_name, "..") == 0) {
			free(namelist[i]);
			continue;
		}
		strcpy(&filelist[numOfFileFound * 200], namelist[i]->d_name);
		numOfFileFound++;
		free(namelist[i]);
	}
	free(namelist);
	return(numOfFileFound);
}

bool check_file_exist(char *FullPathFileName)
{
	bool status = false;
	struct stat	filestatus;

	int exist = stat(FullPathFileName, &filestatus);
	if (exist == 0) status = true;
	return(status);
}

bool check_remote_file_exist(char *ip, char *FullPathFileName)
{
	char ssh_cmd[300];

	sprintf(ssh_cmd, "ssh %s test -d %s", ip, FullPathFileName);
	int ssh_ret = system(ssh_cmd);
	if (ssh_ret == 0) return true;
	return false;
}

bool create_json_format(vector<string>key, vector<string>val, char *json_out)
{
	CkStringBuilder sbJson;

	if (key.size() != val.size()) return false;
	sbJson.Append("{");
	for (int i = 0; i < key.size(); i++) {
		sbJson.Append("\"");
		sbJson.Append(key[i].c_str());
		sbJson.Append("\"");
		sbJson.Append(":");
		sbJson.Append("\"");
		sbJson.Append(val[i].c_str());
		sbJson.Append("\"");
		if(i != key.size()-1) sbJson.Append(",");
	}
	sbJson.Append("}");
	strcpy(json_out, sbJson.getAsString());
	return true;
}

void create_datecode_path(char *pathname, char *out_datecodepathname)
{
	char timestr_yymmdd[20];
	char timestr_yymmdd_tomorrow[20];
	char system_cmd[300];
	char log_msg[4096];

	get_time_yymmdd(timestr_yymmdd);
	sprintf(out_datecodepathname, "%s/%s", pathname, timestr_yymmdd);

	bool status = check_file_exist(out_datecodepathname);
	if (status == false) {
		sprintf(system_cmd, "sudo mkdir %s", out_datecodepathname); system(system_cmd);
		sprintf(system_cmd, "sudo chmod 755 %s", out_datecodepathname); system(system_cmd);
		sprintf(log_msg, "create folder %s\n", out_datecodepathname); write_log(log_msg);
	}

	char tomorrow_path[300];
	get_time_yymmdd_tomorrow(timestr_yymmdd_tomorrow);
	sprintf(tomorrow_path, "%s/%s", pathname, timestr_yymmdd_tomorrow);
	status = check_file_exist(tomorrow_path);
	if (status == false) {
		sprintf(system_cmd, "sudo mkdir %s", tomorrow_path); system(system_cmd);
		sprintf(system_cmd, "sudo chmod 755 %s", tomorrow_path); system(system_cmd);
		sprintf(log_msg, "create folder %s\n", tomorrow_path); write_log(log_msg);
	}
}

void create_remote_datecode_path(char *remote_ip, char *pathname, char *out_datecodepathname)
{
	char ssh_cmd[300];
	char ssh_cmd2[300];
	char timestr_yymmdd[20];
	char log_msg[4096];

	sprintf(ssh_cmd2, "ssh %s sync;sync;sync", remote_ip);

	get_time_yymmdd(timestr_yymmdd);
	sprintf(out_datecodepathname, "%s/%s", pathname, timestr_yymmdd);

	sprintf(ssh_cmd, "ssh %s test -d %s", remote_ip, out_datecodepathname);
	int ssh_ret = system(ssh_cmd);
	if (ssh_ret != 0) {
		sprintf(ssh_cmd, "ssh %s mkdir %s", remote_ip, out_datecodepathname);
		ssh_ret = system(ssh_cmd);
		if (ssh_ret != 0) {
			system(ssh_cmd2); // sync
			Sleep(500);
			ssh_ret = system(ssh_cmd);
			if (ssh_ret != 0) {
				sprintf(log_msg, "[E]: ssh_cmd: %s error\n", ssh_cmd); write_log(log_msg);
				return;
			}
		}
	}
}

bool xfer_file(char *src_ip, char *src_fullfilename, char *des_pathname, char *out_fullfilename)
{
	char filename[200];
	char des_datecodepathname[300];
	char ssh_cmd[300];
	char log_msg[4096];

	strcpy(out_fullfilename, "");

	// create datefolder & get path with datecode
	mutex_lock(&dir_mutex);
		create_datecode_path(des_pathname, des_datecodepathname);
	mutex_unlock(&dir_mutex);

	// extract filename from fullfilename
	char tmpstr[300];
	strcpy(tmpstr, src_fullfilename);
	int n = strlen(tmpstr);
	int p = -1;
	for (int i = n - 1; i >= 0; i--) {
		if (tmpstr[i] == '/') {
			p = i + 1;
			break;
		}
	}
	if (p <= 0) return false;
	strcpy(filename, &tmpstr[p]);
	sprintf(out_fullfilename, "%s/%s", des_datecodepathname, filename);

	// check whether file had been existing
	bool status = check_file_exist(out_fullfilename);
	if (status) return true;

	// copy from remote to local
	sprintf(ssh_cmd, "scp root@%s:%s %s", src_ip, src_fullfilename, des_datecodepathname);
	int ssh_ret = system(ssh_cmd);	
	Sleep(100);
	if (ssh_ret != 0) {
		ssh_ret = system(ssh_cmd);
		Sleep(500);
		if (ssh_ret != 0) {
			ssh_ret = system(ssh_cmd);
			if (ssh_ret != 0) {
				sprintf(log_msg, "[N]: ssh_cmd: ip:%s filename:%s error\n", src_ip, filename); write_log(log_msg);
				mutex_lock(&xfer_mutex);					
					string cmdstr = string(ssh_cmd);
					xfer_cmd_queue.push_back(cmdstr);
				mutex_unlock(&xfer_mutex);
				return false;
			}
		}
	}
	return true;
}

bool xfer_remote_file(char *remote_ip, char *src_fullfilename, char *des_pathname)
{
	char filename[200];
	char des_datecodepathname[300];
	char ssh_cmd[300];
	char log_msg[4096];

	// create datefolder & get path with datecode
	mutex_lock(&remote_dir_mutex);
		create_remote_datecode_path(remote_ip, des_pathname, des_datecodepathname);
	mutex_unlock(&remote_dir_mutex);

	// check whether file had been existing
	bool status = check_remote_file_exist(remote_ip, src_fullfilename);
	if (status) return true;

	// copy from remote to local
	sprintf(ssh_cmd, "scp %s root@%s:%s", src_fullfilename, remote_ip, des_datecodepathname);
	int ssh_ret = system(ssh_cmd);
	Sleep(100);
	if (ssh_ret != 0) {
		ssh_ret = system(ssh_cmd);
		Sleep(500);
		if (ssh_ret != 0) {
			ssh_ret = system(ssh_cmd);
			if (ssh_ret != 0) {
				sprintf(log_msg, "[N]: ssh_cmd(remote): remote_ip:%s filename:%s error\n", remote_ip, filename); write_log(log_msg);
				mutex_lock(&xfer_mutex);
					string cmdstr = string(ssh_cmd);
					xfer_cmd_queue.push_back(cmdstr);
				mutex_unlock(&xfer_mutex);
				return false;
			}
		}
	}
	return true;
}

void show_led(int led_index, int count)
{
	reset_led(led_index, 600);

	char led_msg[20];
	sprintf(led_msg, "%d", count);
	led_display(led_index, 0, led_msg);

	// send led zmq queue
	char zmq_str[1000];
	int unique_page_id = MODE_LED_ID + config_led[led_index].floor_id*100;
	sprintf(zmq_str, "{\"Flag\":\"LED\",\"LedID\":\"%s\",\"EmptyCount\":\"%d\",\"PageID\":\"%d\",\"Mode\":\"LED\"}", config_led[led_index].name, count, unique_page_id);
	struct udp_q_content_type zmq_q;
	strcpy(zmq_q.udp_cmd, zmq_str);
	zmq_q.udp_cmd_len = strlen(zmq_str);
	for (int i = 0; i < config_panel_count; i++) {
		mutex_lock(&send_panel_mutex[i]);
			panel_queue[i].push_back(zmq_q);
		mutex_unlock(&send_panel_mutex[i]);
	}
}