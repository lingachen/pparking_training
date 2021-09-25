#include "declaration.h"
#include "log.h"

void init_log()
{
	FILE *fp;

	char timestr_log[100];
	get_detail_currenttime_for_bcd(timestr_log);
	sprintf(log_filename, "/lpr_data/log/log_%s.dat", timestr_log);
	fp = fopen(log_filename, "w");
	if (fp != NULL) {
		fclose(fp);
	}
}

void write_log(char *msg)
{
	char timestr_log[100];
	char log_msg[4096];

	pthread_mutex_lock(&log_mutex);
	get_detail_currenttime(timestr_log);
	sprintf(log_msg, "[%s]: %s", timestr_log, msg);
	printf("%s", log_msg);
	std::string log_str(log_msg);
	log_data.push_back(log_str);
	pthread_mutex_unlock(&log_mutex);
}

void print_log(char *msg)
{
	char timestr_log[100];

	get_detail_currenttime(timestr_log);
	printf("[%s]: %s", timestr_log, msg);
}

void *write_log_task(void *)
{
	char log_msg[4096];

	sprintf(log_msg, "[U], write_log_task Ok\n"); write_log(log_msg);

	while (1) {
		// step1: open log file
		FILE *fp;
		fp = fopen(log_filename, "a+");
		if (fp == NULL) {
			usleep(20);
			continue;
		}

		// step2: write log file
		pthread_mutex_lock(&log_mutex);
		vector<string>::iterator it = log_data.begin();
		while (it != log_data.end()) {
			fprintf(fp, "%s", it->c_str());
			it = log_data.erase(it);
		}
		pthread_mutex_unlock(&log_mutex);

		// step3: close log file
		fclose(fp);

		usleep(50000);
	}
}