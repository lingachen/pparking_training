#pragma once

// for udp
int  udp_server_portnum;
int  udp_svr_socket_handle;

// for datalog write to file
char			log_filename[200];
TASK_HANDLE		write_log_handle;
TASK_MUTEX		log_mutex;
vector <string> log_data;

// udp queue
vector<struct udp_q_content_type> udp_queue;
vector<struct udp_q_content_type> panel_queue[MAX_PANELS];
vector<string>  xfer_cmd_queue;
TASK_HANDLE		panel_task_handle[MAX_TASKS];
TASK_HANDLE		xfer_task_handle;
TASK_HANDLE		send_panel_task_handle[MAX_PANELS];
TASK_MUTEX		udp_mutex;
TASK_MUTEX		xfer_mutex;
TASK_MUTEX		dir_mutex;
TASK_MUTEX		remote_dir_mutex;
TASK_MUTEX		send_panel_mutex[MAX_PANELS];
TASK_MUTEX		led_mutex;
TASK_MUTEX		panel_mutex;

// database
PGconn *postgresDB_master;
PGconn *postgresDB_task[MAX_TASKS];
vector<struct datatable_template_rec> datatable_template;
vector<struct pgs_lot_type > pgs_lot_vecs;

// led variables
SOCKET led_sockfd[MAX_LEDS];
time_t prev_led_reset_time[MAX_LEDS];
int config_led_count;
int prev_led_count[MAX_LEDS];
struct config_led_type config_led[MAX_LEDS];
SOCKADDR_IN	send_to_led[MAX_LEDS];
char arrow_filename[][100] = { "/opt/led/ArrowLeft.gif" , "/opt/led/ArrowUp.gif" , "/opt/led/ArrowRight.gif" };

// panel variables
int config_panel_count;
struct config_panel_type config_panel[MAX_PANELS];