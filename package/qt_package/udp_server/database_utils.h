#pragma once

bool check_database_connect(int taskID, PGconn *postgresDB);
void read_pgs_database(PGconn *postgresDB, vector<struct pgs_lot_type>*pgs_lot_data);
void copy_pgs_database(PGconn *postgresDB);
void update_pgs_database(PGconn *postgresDB, char *lotid, char *image_fullfilename, char *plate_no, char *result);
void update_lpr_database(PGconn *postgresDB, char *stationid, char *image_fullfilename, char *plate_no, char *entrytime, char *exittime, char *confidentstr, char *checksumstr, char *stationip);
void update_enf_database(PGconn *postgresDB, char *image_fullfilename, char *plate_no);
int  get_led_list(char *inpstr, char ledlist[][50]);
int  get_led_index(char *led_idstr);
int  get_emptylot_count(PGconn *postgresDB, char *led_idstr);