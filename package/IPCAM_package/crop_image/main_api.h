#pragma once
extern "C" int minc_pgs_query_cfg_floorplan(struct cfg_floorplan_rec *out_cfg_floorplan);
extern "C" int minc_pgs_query_cfg_floorplan2(int rid, struct cfg_floorplan_rec *out_cfg_floorplan);
extern "C" int minc_pgs_query_cfg_floormap(struct cfg_floormap_rec *out_cfg_floormap_rec);
extern "C" int minc_pgs_query_cfg_floormap_Total_LED(char *LED, struct cfg_floormap_rec *out_cfg_floormap);
extern "C" int minc_pgs_query_cfg_floormap_by_floor_id(char *floor_id, struct cfg_floormap_rec *out_cfg_floormap);
extern "C" int minc_pgs_query_data_lpr(struct data_lpr_rec *out_data_lpr_rec);
extern "C" int minc_pgs_query_data_lpr_by_pageindex(char *pageindex, struct data_lpr_rec *out_data_lpr_rec);
extern "C" int minc_pgs_query_data_pgs(struct data_pgs_rec *out_data_pgs_rec);
extern "C" int minc_pgs_query_data_pgs_by_pageindex(char *pageindex, char *floor_id, struct data_pgs_rec *out_data_pgs_rec);
extern "C" int minc_pgs_query_data_pgs_by_floor_id(char *floor_id, struct data_pgs_rec *out_data_pgs_rec);
extern "C" int minc_pgs_query_data_enf(struct data_enf_rec *out_data_enf_rec);
extern "C" int minc_pgs_query_data_enf_by_pageindex(char *pageindex, struct data_enf_rec *out_data_enf_rec);
extern "C" int minc_pgs_upd_data_pgs(struct data_pgs_rec *inp_data_pgs);
extern "C" int minc_pgs_add_floormap(struct cfg_floormap_rec *inp_floormap);
extern "C" int minc_pgs_upd_floormap(struct cfg_floormap_rec *inp_floormap);
extern "C" int minc_pgs_del_floormap(int rid);
extern "C" int minc_pgs_query_log_lpr_movement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, char *station_id, struct log_lpr_movement_rec *out_log_lpr_movement);
extern "C" int minc_pgs_query_log_pgs_movement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, char *inp_lot_no, struct log_pgs_movement_rec *out_log_pgs_movement);
extern "C" int minc_pgs_query_log_enforcement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_enforcement_rec *out_log_enforcement);
extern "C" int minc_pgs_query_log_pgs_occupancy_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_led_id, struct log_pgs_occupancy_rec *out_log_pgs_occupancy);
extern "C" int minc_pgs_write_csv_log_lpr_movement(char *csv_filename, int len, struct log_lpr_movement_rec *inp_log_lpr_movement);
extern "C" int minc_pgs_write_csv_log_pgs_movement(char *csv_filename, int len, struct log_pgs_movement_rec *inp_log_pgs_movement);
extern "C" int minc_pgs_write_csv_log_enforcement(char *csv_filename, int len, struct log_enforcement_rec *inp_log_enforcement);
extern "C" int minc_pgs_write_csv_log_pgs_occupancy(char *csv_filename, int len, struct log_pgs_occupancy_rec *inp_log_pgs_occupancy);


//-----------------test----------------------------------
extern "C" int minc_pgs_upd_data_pgs_test(char *pageindex, int id);
extern "C" int minc_pgs_upd_data_floormap_test(char *id, int old_id);
//-----------------test----------------------------------



//-----------------new---------------
extern "C" int minc_pgs_query_lot_lotid(char *inp_lot_id, struct twlot2_rec *out_lot2);
extern "C" int minc_pgs_query_lot2(char *inp_floor_id, struct twlot2_rec *out_lot2);
extern "C" int minc_pgs_query_lot2_floor_id(char *inp_lot_floor_id, struct twlot2_rec *out_lot2);
extern "C" int minc_pgs_query_lot2_index2(int Max_lot, int total_floor_count, struct cfg_floorplan_rec *inp_floorplan, struct index_rec *out_index);
extern "C" int minc_pgs_query_lot2_controller_id(char *inp_controller_id, struct twlot2_rec *out_lot2);
extern "C" int minc_pgs_query_lot2_led_id(char *inp_led_id, struct twlot2_rec *out_lot2);
extern "C" int minc_pgs_upd_lot2(struct twlot2_rec *inp_lot2);
extern "C" int minc_pgs_add_lot2(struct twlot2_rec *inp_lot2);
extern "C" int minc_pgs_del_lot2(int rid);
extern "C" int minc_pgs_del_all_lot2();

//-----------------old------------------------------
extern "C" int minc_pgs_init_api();
extern "C" int minc_pgs_led_init_api(int led_index);
extern "C" int minc_pgs_led_display_api(int led_index, int count);
extern "C" int minc_pgs_get_program_version(char *version_str);
extern "C" int minc_pgs_query_account(char *inp_userid, char *inp_passcode);
extern "C" int minc_pgs_query_availablelot(struct availablelot_value_type *availablelot_value);
extern "C" int minc_pgs_upd_operation_log(struct operation_log *inp_operation_log);
extern "C" int minc_pgs_query_lot(char *inp_floor_id, struct lot_rec *out_lot);
extern "C" int minc_pgs_query_lot_index2(int Max_lot, int total_floor_count, struct cfg_floorplan_rec *inp_floorplan, struct index_rec *out_index);

extern "C" int minc_pgs_query_lot_controller_id(char *inp_controller_id, struct lot_rec *out_lot);
extern "C" int minc_pgs_query_lot_lotname(char *inp_lot_name, struct lot_rec *out_lot);
extern "C" int minc_pgs_query_lot_seq_no(char *inp_seq_no, struct lot_rec *out_lot);
extern "C" int minc_pgs_query_lot_floor_id(char *inp_lot_floor_id, struct lot_rec *out_lot);
extern "C" int minc_pgs_upd_lot(struct lot_rec *inp_lot);
extern "C" int minc_pgs_add_lot(struct lot_rec *inp_lot);
extern "C" int minc_pgs_del_lot(int rid);
extern "C" int minc_pgs_del_all_lot();
extern "C" int minc_pgs_update_availablelot(struct availablelot_value_type *inp_availablelot_value_local);
extern "C" int minc_pgs_add_floorplan(struct cfg_floorplan_rec *inp_floorplan);
extern "C" int minc_pgs_upd_floorplan(struct cfg_floorplan_rec *inp_floorplan);
extern "C" int minc_pgs_del_floorplan(int rid);
extern "C" int minc_pgs_del_all_floorplan();
extern "C" int minc_pgs_query_station_infomation(struct station_information_value_type *station_information_value);
extern "C" int minc_pgs_query_infomation(char *inp_floor_id, struct information_value_type *information_value);
extern "C" int minc_pgs_query_log_movement(char *station_name, char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_movement_rec *out_log_movement);
extern "C" int minc_pgs_write_csv_log_movement(char *csv_filename, int len, struct log_movement_rec *inp_log_movement);
extern "C" int minc_pgs_get_image(char *ipcam_ip, char *ipcam_type, char *username, char *password);
extern "C" int minc_pgs_clear_db(char *DB_name);
extern "C" int minc_pgs_add_enforcement(struct enforcement_init_info_rec *inp_enforcement);
extern "C" int minc_pgs_query_enforcement(struct enforcement_init_info_rec *out_enforcement);
extern "C" int minc_pgs_upd_enforcement(struct enforcement_init_info_rec *inp_enforcement);






//-----------------------------------------------------------------------------------------------

extern "C" int minc_pms_init_api(struct disp_availablelot_type *disp_availablelot, struct init_rec *init_data);
extern "C" int minc_pms_get_program_version(char *version_str);
extern "C" int minc_pms_query_availablelot(struct availablelot_value_type *availablelot_value);
extern "C" int minc_pms_update_availablelot(struct availablelot_value_type *availablelot_value_local);
extern "C" int minc_pms_query_season(char *inp_datetime_yyyymm_start, char *inp_datetime_yyyymm_stop, char *inp_platenum, char *inp_phonenum, struct season_rec *out_season);
extern "C" int minc_pms_add_season(struct season_rec *inp_season);
extern "C" int minc_pms_del_season(int rid);
extern "C" int minc_pms_upd_season(struct season_rec *inp_season);
extern "C" int minc_pms_query_movement(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct movement_rec *out_movement);
extern "C" int minc_pms_add_movement(char *inp_entry_time, char *inp_platenum, char *inp_comments);
extern "C" int minc_pms_del_movement(int rid);
extern "C" int minc_pms_upd_movement(int rid, char *inp_entry_time, char *inp_platenum, char *inp_comments);
extern "C" int minc_pms_query_check(struct disp_check_rec *out_check);
extern "C" int minc_pms_upd_check(struct disp_check_rec *inp_check);
extern "C" int minc_pms_control(int control_id);
extern "C" int minc_pms_open_apm(char *password, int control_id);
extern "C" int minc_pms_query_hopper(char *apm_ip, struct disp_hopper_rec *out_hopper);
extern "C" int minc_pms_upd_hopper(char *apm_ip, struct disp_hopper_rec *inp_hopper);
extern "C" int minc_pms_query_finance(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, struct disp_finance_summary_rec *disp_finance_summary, struct disp_finance_detail_rec *disp_finance_detail);
extern "C" int minc_pms_query_All_finance(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, struct disp_finance_summary_rec *disp_finance_summary, struct disp_finance_detail_rec *disp_finance_detail);
extern "C" int minc_pms_get_image(char *station_name);
extern "C" int minc_pms_get_valid_date(char *monthid, char *out_valid_start, char *out_valid_end);
extern "C" int minc_pms_write_led_message(int ledid, char *message);
extern "C" int minc_pms_query_log_movement(char *station_name, char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_movement_rec *out_log_movement);
extern "C" int minc_pms_query_log_payment(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_payment_rec *out_log_payment);
extern "C" int minc_pms_write_csv_finance(char *csv_filename, int len, struct disp_finance_detail_rec *inp_disp_finance_detail);
extern "C" int minc_pms_write_csv_log_movement(char *csv_filename, int len, struct log_movement_rec *inp_log_movement);
extern "C" int minc_pms_write_csv_log_payment(char *csv_filename, int len, struct log_payment_rec *inp_log_payment);
extern "C" int minc_pms_query_tariff(struct tariff_value_rec *tariff_value);
extern "C" int minc_pms_update_tariff(struct tariff_value_rec *tariff_value);
extern "C" int minc_pms_query_parkingfee(struct parkingfee_rec *parkingfee_data);
extern "C" int minc_pms_update_parkingfee(int rid, struct parkingfee_rec *parkingfee_data);
extern "C" int minc_pms_del_parkingfee(int rid);
extern "C" int minc_pms_add_parkingfee(struct parkingfee_rec *parkingfee_data);
extern "C" int minc_pms_import_season(char *season_csv_filename);
extern "C" int minc_pms_import_receipt(char *receipt_csv_filename);
extern "C" int minc_pms_query_unused_receipt(char *monthid, struct disp_finance_detail_rec *disp_finance_detail);

// udp command:
// (1) udp1:
// {'flag':'availablelot','total_lots':'50','total_lots':'50','total_occupies':'50','season_occupies':'50','hourly_occupies':'50','empty_lots':'50'}
// (2) udp2:
// {'flag':'status','apm':'0','e1':'0','x1':'1','fullcontrol':'1','printer':'1','bill':'1','coin':'1','hopper50':'1','hopper10a':'1','hopper10b':'1'}
// (3) udp3:
// {'flag':'movement','station_name':'E1','station_time':'200119200000000','platenum':'6795F5','etagnum':'12345678','parked_type':'season','parked_time':'0','parked_fee':'0','comments':''}
