#pragma once

extern PGconn  *postgresDB_master;

extern struct receipt_setting_rec	receipt_setting[4];
extern struct config_cp_type		config_cp;

extern SOCKET			server_sockfd;
extern SOCKADDR_IN		send_to_apm[4];
extern SOCKADDR_IN		send_to_e[4];
extern SOCKADDR_IN		send_to_x[4];

extern SOCKET			eio_server_sockfd;
extern SOCKADDR_IN		send_to_eio;

extern pthread_t			monitor_handle;
extern pthread_t			write_log_handle;
extern pthread_mutex_t		log_mutex;				// for datalog write to file
extern char   log_filename[300];
extern vector <string> log_data;

extern int total_receipt_setting_count;

// led variables
extern SOCKET led_sockfd[10];
extern SOCKET led2_sockfd;
extern SOCKADDR_IN	send_to_led;
extern time_t prev_led_reset_time[10];
extern char led_ipaddress[][30];