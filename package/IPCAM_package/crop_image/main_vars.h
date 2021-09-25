#pragma once

PGconn  *postgresDB_master;

struct receipt_setting_rec	receipt_setting[4];
struct config_cp_type		config_cp;

SOCKET			server_sockfd;
SOCKADDR_IN		send_to_apm[4];
SOCKADDR_IN		send_to_e[4];
SOCKADDR_IN		send_to_x[4];

SOCKET			eio_server_sockfd;
SOCKADDR_IN		send_to_eio;

pthread_t			monitor_handle;
pthread_t			write_log_handle;
pthread_mutex_t		log_mutex;				// for datalog write to file
char   log_filename[300];
vector <string> log_data;

int total_receipt_setting_count;

// led variables
SOCKET led_sockfd[10];
SOCKADDR_IN	send_to_led;
time_t prev_led_reset_time[10];
char led_ipaddress[][30] = { "192.168.2.211", "192.168.2.212" };
