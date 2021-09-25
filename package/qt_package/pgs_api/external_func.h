#pragma once

// database.cpp
extern bool CheckDatabaseConnection(PGconn *conn);
extern PGconn *ConnectDatabase(char *connection_str);
extern PGresult *SendSql(PGconn  *conn, char *SqlCmd);
extern int  QueryDatabase(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data);
extern int  QueryDatabase2(PGconn *conn, char *fieldname, char *tablename, char *query_str, int query_mode, char *rec_data);
extern int  QueryDatabase3(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data);
extern int  ClearDatabase(PGconn *conn, char *tablename);
extern bool InsertDatabase(PGconn *conn, char *tablename, char *header_str, char *rec_data);
extern bool UpdateDatabase(PGconn *conn, char *tablename, char *set_str, char *query_str);
extern bool DeletetDatabase(PGconn *conn, char *tablename, char *query_str);
extern bool Deletet_All_Database(PGconn *conn, char *tablename);
extern void GetSingleRecordData(PGresult *res, int query_mode, char *result);
extern void read_record_str(PGresult *res, int iRecord, char *result);
extern int  check_id_or_modified_time_index(PGresult *res);
extern bool verify_database_connection();

// ipcam.cpp
extern void   mParseUrl(char *mUrl, string &serverName, string &filepath, string &filename);
extern int    getHeaderLength(char *content);
extern SOCKET connectToServer(char *szServerName, WORD portNum);
extern char   *readUrl2(char *szUrl, long &bytesReturnedOut, char **headerOut);
extern void   convert_jpeg_buf_to_mat(char *jpeg_buf, int size, Mat &result);

// log.cpp
extern void init_log();
extern void write_log(char *msg);
extern void print_log(char *msg);
extern void *write_log_task(void *);

// led.cpp
extern void init_led(int led_index);
extern void send_led(int led_index, char *led_data, int len);
extern void reset_led(int led_index, int time_val);
extern void led_display(int led_index, int zone, char *msg);
extern void led_display_image(int led_index, int zone, int img_len, unsigned char *imgdata);

// read_data.cpp
extern void read_data_lpr(char *raw, struct data_lpr_rec *data_lpr);
extern void read_data_pgs(char *raw, struct data_pgs_rec *data_pgs);
extern void read_data_enf(char *raw, struct data_enf_rec *data_enf);
extern void read_log_enforcement(char *raw, struct log_enforcement_rec *log_enforcement);
extern void read_data_blk(char *raw, struct data_blk_rec *data_blk);
extern void read_log_lpr_movement(char *raw, struct log_lpr_movement_rec *log_lpr_movement);
extern void read_log_pgs_movement(char *raw, struct log_pgs_movement_rec *log_pgs_movement);
extern void read_log_pgs_occupancy(char *raw, struct log_pgs_occupancy_rec *log_pgs_occupancy);


extern void read_cfg_floormap(char *raw, struct cfg_floormap_rec *floormap);
extern void read_cfg_floorplan(char *raw, struct cfg_floorplan_rec *floorplan);
extern void read_lot(char *raw, struct lot_rec *lot);
extern void read_lot2(char *raw, struct twlot2_rec *lot2);
extern void read_login_account(char *raw, struct login_account_rec *login_account_rec_local);
extern void read_movement(char *raw, struct movement_rec *movement);
extern void read_station_information(char *raw, struct station_information_lot_type *station_information_lot_local);
extern void read_season(char *raw, struct season_rec *season);
extern void read_availablelot(char *raw, struct available_lot_type *available_lot_local);
extern void read_config_cp(char *raw, struct config_cp_type *config_cp_local);
extern void read_tariff(char *raw, struct tariff_rec *tariff);
extern void read_parkingfee(char *raw, struct parkingfee_rec *parkingfee);
extern void read_receipt_data(char *raw, struct receipt_data_rec *receipt_data);
extern void read_receipt_setting(char *raw, struct receipt_setting_rec *receipt_setting_local);
extern void read_payment_login(char *raw, struct payment_login_rec *payment_login_local);
extern void read_hopper(char *raw, struct hopper_rec *hopper);
extern void read_status(char *raw, struct status_type *status_local);
extern void read_log_movement(char *raw, struct log_movement_rec *log_movement);
extern void read_log_payment(char *raw, struct log_payment_rec *log_payment);
extern void read_information(char *raw, struct information_lot_type *information_lot_local);
extern void read_floorplan(char *raw, struct cfg_floorplan_rec *floorplan);
extern void read_enforcement(char *raw, struct enforcement_init_info_rec *enforcement);
extern void read_data_alarm(char *raw, struct data_alarm_rec *data_alarm);

// utils.cpp
extern int  splitstr(char *readin, int len, char split, char ignchar1, char ignchar2, char ignchar3, char ignchar4, char *token, int token_len);
extern void get_currenttime(char *timestr);
extern void get_currenttime_for_bcd(time_t currenttime, char *bcd_str);
extern void get_detail_currenttime(char *timestr);
extern void get_detail_currenttime_for_bcd(char *timestr);
extern void convert_bcdtimestr(char *bcdtimestr, char *stdtimestr);
extern time_t get_time_mins_long_value(char *timestr);
extern void get_validtime(char *monthid, char *validstart, char *validend);
extern long get_time_difference_secs(char *time1, char *time2);
extern SOCKET udp_server_init(char *ip_server, u16 port_server);
extern bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
extern int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
extern bool init_udp();
extern bool check_file_exist(char *FullPathFileName);
extern void get_time_yymmdd(char *time_yymmdd);
extern void get_datecode_path_name(char *pathname, char *out_pathname);
extern bool copy_file_remote(char *remote_ip, char *img_pathstr, char *img_filename);
extern void *monitor_task(void *);
extern void b2u(char src[], char tar[]);
extern void u2b(char src[], char tar[]);
extern void Ucase(char *sPtr, char *outstr);
extern SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
extern int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
extern int tcp_read(int sockfd, char *buffer);
extern bool open_apm_lock(int apmid, int eio_numb);