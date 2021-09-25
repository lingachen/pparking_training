#pragma once

int  splitstr(char *readin, int len, char split, char ignchar1, char ignchar2, char ignchar3, char ignchar4, char *token, int token_len);
void get_detail_currenttime(char *timestr);
void get_detail_currenttime_for_bcd(char *timestr);
void get_time_yymmdd(char *time_yymmdd);
void get_time_yymmdd_tomorrow(char *time_yymmdd_tomorrow);
void mutex_lock(TASK_MUTEX *task_mutex);
void mutex_unlock(TASK_MUTEX *task_mutex);
void Sleep(int val);
int  find_path_allfiles(char *pathname, char *filelist);
bool check_file_exist(char *FullPathFileName);
bool check_remote_file_exist(char *ip, char *FullPathFileName);
bool create_json_format(vector<string>key, vector<string>val, char *json_out);
bool xfer_file(char *src_ip, char *src_fullfilename, char *des_pathname, char *out_fullfilename);
bool xfer_remote_file(char *remote_ip, char *src_fullfilename, char *des_pathname);
void create_datecode_path(char *pathname, char *out_datecodepathname);
void create_remote_datecode_path(char *remote_ip, char *pathname, char *out_datecodepathname);
void show_led(int led_index, int count);
