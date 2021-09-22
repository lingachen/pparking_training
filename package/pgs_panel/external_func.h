

// utils.cpp
extern void wait_ms(int timeval_ms);
extern QString toQstring(char *inpstr);
extern string toStdstring(QString *qstr);
extern int toInt(QString qstr);
extern QString get_currenttime();
extern QString get_monthid();
extern QString convert_time_format(char *time_bcd);
extern bool check_file_exist(char *FullPathFileName);
extern int get_pgs_lotid_index(char *lotid);
extern int get_floor_index(char *floor_id);
extern int get_floor_lot_index(char *lotid);
extern int get_display_index(char *lotid);
