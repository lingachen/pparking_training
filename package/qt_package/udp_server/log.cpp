#include "declaration.h"
#include "log.h"

void init_log()
{
	FILE *fp;
	char timestr_log[100];

	get_detail_currenttime_for_bcd(timestr_log);
	sprintf(log_filename, "/lpr_data/log/log_%s_udp.dat", timestr_log);
	fp = fopen(log_filename, "w");
	if (fp != NULL) {
		fclose(fp);
	}	
}

void write_log(char *msg)
{
	char timestr_log[100];
	char log_msg[4096];

	mutex_lock(&log_mutex);
		get_detail_currenttime(timestr_log);
		sprintf(log_msg, "[%s]: %s", timestr_log, msg);
		printf("%s", log_msg);
		std::string log_str(log_msg);
		log_data.push_back(log_str);
	mutex_unlock(&log_mutex);
}

void print_log(char *msg)
{
	char timestr_log[100];

	get_detail_currenttime(timestr_log);
	printf("[%s]: %s", timestr_log, msg);
}

TASK_FUNC write_log_task(void *)
{
	char log_msg[4096];

	sprintf(log_msg, "[U], write_log_task Ok\n"); write_log(log_msg);

	while (1) {
		char *ptr;
		char date1[100];
		char date2[100];
		char tmpstr1[100];
		char tmpstr2[100];
		char timestr_log[100];
		char tmp_log_filename[300];

		// step1: check whether date code change?
		ptr = strstr(log_filename, "log_");
		if (ptr == NULL) {
			Sleep(20);
			continue;
		}
		strcpy(tmp_log_filename, ptr);
		get_detail_currenttime_for_bcd(timestr_log);
		strcpy(tmpstr1, &tmp_log_filename[4]); tmpstr1[6] = '\0'; strcpy(date1, tmpstr1);
		strcpy(tmpstr2, timestr_log); tmpstr2[6] = '\0'; strcpy(date2, tmpstr2);
		if (strcmp(date1, date2) != 0) {
			sprintf(log_filename, "/lpr_data/log/log_%s000000000_udp.dat", date2);
		}

		// step2: open log file
		FILE *fp;
		fp = fopen(log_filename, "a+");
		if (fp == NULL) {
			Sleep(20);
			continue;
		}

		// step3: write log file
		mutex_lock(&log_mutex);
		vector<string>::iterator it = log_data.begin();
			while (it != log_data.end()) {
				fprintf(fp, "%s", it->c_str());
				it = log_data.erase(it);
			}
		mutex_unlock(&log_mutex);

		// step4: close log file
		fclose(fp);
		Sleep(50);
	}
}