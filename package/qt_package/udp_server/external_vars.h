#pragma once

// for udp
extern int  udp_server_portnum;
extern int  udp_svr_socket_handle;

// for datalog write to file
extern char				log_filename[200];
extern TASK_HANDLE		write_log_handle;
extern TASK_MUTEX		log_mutex;
extern vector <string>  log_data;

// udp queue
extern vector<struct udp_q_content_type> udp_queue;
extern vector<struct udp_q_content_type> panel_queue[MAX_PANELS];
extern vector<string>  xfer_cmd_queue;
extern TASK_HANDLE		panel_task_handle[MAX_TASKS];
extern TASK_HANDLE		xfer_task_handle;
extern TASK_HANDLE		send_panel_task_handle[MAX_PANELS];
extern TASK_MUTEX		udp_mutex;
extern TASK_MUTEX		xfer_mutex;
extern TASK_MUTEX		dir_mutex;
extern TASK_MUTEX		remote_dir_mutex;
extern TASK_MUTEX		send_panel_mutex[MAX_PANELS];
extern TASK_MUTEX		led_mutex;
extern TASK_MUTEX		panel_mutex;

// database
extern PGconn *postgresDB_master;
extern PGconn *postgresDB_task[MAX_TASKS];
extern vector<struct datatable_template_rec> datatable_template;
extern vector<struct pgs_lot_type > pgs_lot_vecs;

// led variables
extern SOCKET led_sockfd[MAX_LEDS];
extern time_t prev_led_reset_time[MAX_LEDS];
extern SOCKADDR_IN	send_to_led[MAX_LEDS];
extern int config_led_count;
extern int prev_led_count[MAX_LEDS];
extern struct config_led_type config_led[MAX_LEDS];
extern char arrow_filename[][100];


// panel variables
extern int config_panel_count;
extern struct config_panel_type config_panel[MAX_PANELS];