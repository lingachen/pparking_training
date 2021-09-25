#pragma once

void read_cfg_floorplan(char *raw, struct cfg_floorplan_rec *floorplan);
void read_cfg_floormap(char *raw, struct cfg_floormap_rec *floormap);
void read_data_lpr(char *raw, struct data_lpr_rec *data_lpr);
void read_data_pgs(char *raw, struct data_pgs_rec *data_pgs);
void read_data_enf(char *raw, struct data_enf_rec *data_enf);
void read_log_enforcement(char *raw, struct log_enforcement_rec *log_enforcement);
void read_data_blk(char *raw, struct data_blk_rec *data_blk);
void read_log_lpr_movement(char *raw, struct log_lpr_movement_rec *log_lpr_movement);
void read_log_pgs_movement(char *raw, struct log_pgs_movement_rec *log_pgs_movement);
void read_log_pgs_occupancy(char *raw, struct log_pgs_occupancy_rec *log_pgs_occupancy);


void read_movement(char *raw, struct movement_rec *movement);
void read_login_account(char *raw, struct login_account_rec *login_account_rec_local);
void read_station_information(char *raw, struct station_information_lot_type *station_information_lot_local);
void read_information(char *raw, struct information_lot_type *information_lot_local);
void read_enforcement(char *raw, struct enforcement_init_info_rec *enforcement);
void read_floorplan(char *raw, struct cfg_floorplan_rec *floorplan);
void read_data_alarm(char *raw, struct data_alarm_rec *data_alarm);

void read_season(char *raw, struct season_rec *season);
void read_availablelot(char *raw, struct available_lot_type *available_lot_local);
void read_config_cp(char *raw, struct config_cp_type *config_cp_local);
void read_tariff(char *raw, struct tariff_rec *tariff);
void read_parkingfee(char *raw, struct parkingfee_rec *parkingfee);
void read_receipt_data(char *raw, struct receipt_data_rec *receipt_data);
void read_receipt_setting(char *raw, struct receipt_setting_rec *receipt_setting_local);
void read_payment_login(char *raw, struct payment_login_rec *payment_login_local);
void read_hopper(char *raw, struct hopper_rec *hopper);
void read_status(char *raw, struct status_type *status_local);
void read_log_movement(char *raw, struct log_movement_rec *log_movement);
void read_log_payment(char *raw, struct log_payment_rec *log_payment);
void read_lot(char *raw, struct lot_rec *lot);
void read_lot2(char *raw, struct twlot2_rec *lot2);