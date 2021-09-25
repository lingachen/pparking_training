#pragma once

// database.cpp
extern PGconn *init_database(char *ip);
extern bool CheckDatabaseConnection(PGconn *conn);
extern PGconn *ConnectDatabase(char *connection_str);
extern PGresult *SendSql(PGconn  *conn, char *SqlCmd);
extern int  QueryDatabase(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data);
extern int  QueryDatabase(PGconn *conn, char *fieldname, char *tablename, char *query_str, int query_mode, char *rec_data);
extern bool InsertDatabase(PGconn *conn, char *tablename, char *header_str, char *rec_data);
extern bool UpdateDatabase(PGconn *conn, char *tablename, char *set_str, char *query_str);
extern bool DeleteDatabase(PGconn *conn, char *tablename, char *query_str);
extern void GetSingleRecordData(PGresult *res, int query_mode, char *result);
extern void read_record_str(PGresult *res, int iRecord, char *result);
extern int  check_id_or_modified_time_index(PGresult *res);

// database_api.cpp
extern int database_read_fieldname(PGconn *postgresDB, char *tablename);
extern int database_extract_fieldname(char *tablename, char fieldname[][50]);
extern int database_record_add(PGconn *postgresDB, char *tablename, struct datatable_record_rec *datatable_record_data);
extern int database_record_upd(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data);
extern int database_record_qry(PGconn *postgresDB, char *tablename, int query_mode, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data, vector<struct datatable_record_rec>*out_record_vecs);
extern int database_record_del(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value);

// database_utils.cpp
extern bool check_database_connect(int taskID, PGconn *postgresDB);
extern void read_pgs_database(PGconn *postgresDB, vector<struct pgs_lot_type>*pgs_lot_data);
extern void copy_pgs_database(PGconn *postgresDB);
extern void update_pgs_database(PGconn *postgresDB, char *lotid, char *image_fullfilename, char *plate_no, char *result);
extern void update_lpr_database(PGconn *postgresDB, char *stationid, char *image_fullfilename, char *plate_no, char *entrytime, char *exittime, char *confidentstr, char *checksumstr, char *stationip);
extern void update_enf_database(PGconn *postgresDB, char *image_fullfilename, char *plate_no);
extern int  get_led_list(char *inpstr, char ledlist[][50]);
extern int  get_led_index(char *led_idstr);
extern int  get_emptylot_count(PGconn *postgresDB, char *led_idstr);

// init.cpp
extern void init_vars();
extern void init_database();
extern void read_config_led();
extern void read_config_panel();

// led.cpp
extern void init_led(int led_index);
extern void send_led(int led_index, char *led_data, int len);
extern void reset_led(int led_index, int time_val);
extern void led_display(int led_index, int zone, char *msg);
extern void led_display_image(int led_index, int zone, int img_len, unsigned char *imgdata);

// log.cpp
extern void init_log();
extern void write_log(char *msg);
extern void print_log(char *msg);
extern TASK_FUNC write_log_task(void *);

// queue.cpp
extern bool read_udp_queue(struct udp_q_content_type *qdata);
extern bool read_panel_queue(vector<struct udp_q_content_type> *panel_queue_ptr, struct udp_q_content_type *qdata);
extern bool read_xfer_queue(struct udp_q_content_type *qdata);

// tcp.cpp
extern SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
extern int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
extern int tcp_read(int sockfd, char *buffer);

// threads.cpp
extern void init_threads();
extern TASK_FUNC panel_task(void *data);
extern TASK_FUNC xfer_task(void *);
extern TASK_FUNC send_panel_task(void *data);

// udp.cpp
extern SOCKET udp_server_init(char *ip_server, u16 port_server);
extern bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
extern int udp_recv(int sockfd, char *buf, int len, SOCKADDR_IN *client);
extern int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
extern bool init_udp();
extern bool read_pgs_udp(char *raw, struct pgs_udp_data_type *pgs_udp_data);

// utils.cpp
extern void get_detail_currenttime(char *timestr);
extern void get_detail_currenttime_for_bcd(char *timestr);
extern void get_time_yymmdd(char *time_yymmdd);
extern void get_time_yymmdd_tomorrow(char *time_yymmdd_tomorrow);
extern void mutex_lock(TASK_MUTEX *task_mutex);
extern void mutex_unlock(TASK_MUTEX *task_mutex);
extern void Sleep(int val);
extern int  find_path_allfiles(char *pathname, char *filelist);
extern bool check_file_exist(char *FullPathFileName);
extern bool check_remote_file_exist(char *ip, char *FullPathFileName);
extern int  splitstr(char *readin, int len, char split, char ignchar1, char ignchar2, char ignchar3, char ignchar4, char *token, int token_len);
extern bool create_json_format(vector<string>key, vector<string>val, char *json_out);
extern void create_datecode_path(char *pathname, char *out_datecodepathname);
extern void create_remote_datecode_path(char *remote_ip, char *pathname, char *out_datecodepathname);
extern bool xfer_file(char *src_ip, char *src_fullfilename, char *des_pathname, char *out_fullfilename);
extern bool xfer_remote_file(char *remote_ip, char *src_fullfilename, char *des_pathname);
extern void show_led(int led_index, int count);
