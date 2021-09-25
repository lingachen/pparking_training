#include "declaration.h"
#include "main_vars.h"

#if 0
int main()
{
	int ret = minc_pgs_init_api();

	ret = minc_pgs_del_floorplan(1);

	struct cfg_floorplan_rec inp_floorplan;
	strcpy(inp_floorplan.floor_id, "5");
	strcpy(inp_floorplan.floor_name, "5F");
	strcpy(inp_floorplan.Image, "AA");
	strcpy(inp_floorplan.comments, "");
	ret = minc_pgs_add_floorplan(&inp_floorplan);
	printf("ret=%d\n", ret);
}
#endif


int minc_pgs_init_api()
{
	char filename[100];
	FILE *fp;
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];
	char query_str[256];
	char tmp[50],tmp_db_ip[50],db_ip[50];

	// step1: display version
	sprintf(log_msg, "minc_pgs_init_api: %s\n", VERSION); write_log(log_msg);

	//step1: read config_joyce and setting site ip	
	sprintf(filename, "/lpr_data/config/config_DB_ip.ini");

	//step2: read DB ip
	fp = fopen(filename, "r");
	if (fp == NULL) exit(0);
	
	while (fscanf(fp, "%s %s", tmp, tmp_db_ip) != EOF)	strcpy(db_ip, tmp_db_ip);	

	// step3: connect database
	char cmd[1000];
	char database_init_str[200];
	sprintf(database_init_str, "host=%s port=5435 dbname=pms_db user=cp password=cp123", db_ip);
	sprintf(cmd, database_init_str);
	postgresDB_master = ConnectDatabase(cmd);
	if (postgresDB_master == NULL) {
		sprintf(log_msg, "ConnectDatabase error (Master)\n"); write_log(log_msg);
		free(raw);
		return RESULT_FAIL;
	}
	free(raw);
	fclose(fp);
	return RESULT_GOOD;
}
int minc_pgs_query_cfg_floorplan(struct cfg_floorplan_rec *out_cfg_floorplan)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floorplan with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.cfg_floorplan", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_cfg_floorplan(raw + i * MAX_DATA_LEN, &out_cfg_floorplan[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_cfg_floorplan2(int rid, struct cfg_floorplan_rec *out_cfg_floorplan)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floorplan with assigned condition
	sprintf(query_str, "id=%d", rid);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.cfg_floorplan", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_cfg_floorplan(raw + i * MAX_DATA_LEN, &out_cfg_floorplan[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_cfg_floormap(struct cfg_floormap_rec *out_cfg_floormap_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floormap with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.cfg_floormap", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_cfg_floormap(raw + i * MAX_DATA_LEN, &out_cfg_floormap_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_cfg_floormap_by_floor_id(char *floor_id, struct cfg_floormap_rec *out_cfg_floormap)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s floor_id = '%s' ORDER BY id ASC", query_str, floor_id);
		else							sprintf(query_str, "floor_id = '%s' ORDER BY id ASC", floor_id);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.cfg_floormap", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_cfg_floormap(raw + i * MAX_DATA_LEN, &out_cfg_floormap[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_cfg_floormap_Total_LED(char *LED, struct cfg_floormap_rec *out_cfg_floormap)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	
	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(LED, "") != 0) {
		sprintf(query_str, "lot_id LIKE '%%%s%%'", LED);		
	}
	
	int rec_no = QueryDatabase(postgresDB_master, "pgs.cfg_floormap", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_cfg_floormap(raw + i * MAX_DATA_LEN, &out_cfg_floormap[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_lpr(struct data_lpr_rec *out_data_lpr_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floormap with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_lpr", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_lpr(raw + i * MAX_DATA_LEN, &out_data_lpr_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_lpr_by_pageindex(char *pageindex,struct data_lpr_rec *out_data_lpr_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(pageindex, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and pageindex = '%s' ORDER BY id ASC", query_str, pageindex);
		else							sprintf(query_str, "pageindex = '%s' ORDER BY id ASC", pageindex);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_lpr", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_lpr(raw + i * MAX_DATA_LEN, &out_data_lpr_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_pgs_by_pageindex(char *pageindex, char *floor_id, struct data_pgs_rec *out_data_pgs_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(pageindex, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and pageindex = '%s' and floor_id = '%s' ORDER BY id ASC", query_str, pageindex, floor_id);
		else							sprintf(query_str, "pageindex = '%s' and floor_id = '%s' ORDER BY id ASC", pageindex, floor_id);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_pgs", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_pgs(raw + i * MAX_DATA_LEN, &out_data_pgs_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_enf_by_pageindex(char *pageindex,struct data_enf_rec *out_data_enf_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(pageindex, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and pageindex = '%s' ORDER BY id ASC", query_str, pageindex);
		else							sprintf(query_str, "pageindex = '%s' ORDER BY id ASC", pageindex);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_enf", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_enf(raw + i * MAX_DATA_LEN, &out_data_enf_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_blk_by_pageindex(char *pageindex, struct data_blk_rec *out_data_blk_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(pageindex, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and pageindex = '%s' ORDER BY id ASC", query_str, pageindex);
		else							sprintf(query_str, "pageindex = '%s' ORDER BY id ASC", pageindex);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_blk", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_blk(raw + i * MAX_DATA_LEN, &out_data_blk_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_pgs_by_floor_id(char *floor_id, struct data_pgs_rec *out_data_pgs_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	strcpy(query_str, "");
	// step2: search floormap with assigned condition	
	if (strcmp(floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s floor_id = '%s' ORDER BY id ASC", query_str, floor_id);
		else							sprintf(query_str, "floor_id = '%s' ORDER BY id ASC", floor_id);
	}
	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_pgs", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_pgs(raw + i * MAX_DATA_LEN, &out_data_pgs_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_pgs(struct data_pgs_rec *out_data_pgs_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floormap with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_pgs", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_pgs(raw + i * MAX_DATA_LEN, &out_data_pgs_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_data_enf(struct data_enf_rec *out_data_enf_rec)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search floormap with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_enf", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_enf(raw + i * MAX_DATA_LEN, &out_data_enf_rec[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_upd_data_pgs(struct data_pgs_rec *inp_data_pgs)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database	
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',lot_id='%s',plate_no='%s',camera_ip='%s',led_id='%s',controller_ip='%s',pageindex='%s',floor_id='%s',status='%s',image_path='%s',comments='%s'",
		modified_time,
		inp_data_pgs->lot_id,
		inp_data_pgs->plate_no,
		inp_data_pgs->camera_ip,
		inp_data_pgs->led_id,
		inp_data_pgs->controller_ip,
		inp_data_pgs->pageindex,
		inp_data_pgs->floor_id,		
		inp_data_pgs->status,
		inp_data_pgs->image_path,
		inp_data_pgs->comments);
	sprintf(ask_str, "id=%d", inp_data_pgs->id);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.data_pgs", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_add_floormap(struct cfg_floormap_rec *inp_floormap)
{
	char modified_time[50];
	char dat_lot[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database	
	get_detail_currenttime_for_bcd(modified_time);

	// write floormap records 
	sprintf(dat_lot, "'%s','%s','%s','%s','%s','%s','%s','%s'",
		modified_time,
		inp_floormap->lot_id,
		inp_floormap->floor_id,
		inp_floormap->location_x,
		inp_floormap->location_y,
		inp_floormap->block_w,
		inp_floormap->block_h,
		inp_floormap->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.cfg_floormap", FLOORMAP_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_upd_floormap(struct cfg_floormap_rec *inp_floormap)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database	
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',lot_id='%s',floor_id='%s',location_x='%s',location_y='%s',block_w='%s',block_h='%s',comments='%s'",
		modified_time,
		inp_floormap->lot_id,
		inp_floormap->floor_id,
		inp_floormap->location_x,
		inp_floormap->location_y,
		inp_floormap->block_w,
		inp_floormap->block_h,
		inp_floormap->comments);
	sprintf(ask_str, "id=%d", inp_floormap->id);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.cfg_floormap", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_floormap(int rid)
{
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "pgs.cfg_floormap", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_query_log_lpr_movement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, char *station_id, struct log_lpr_movement_rec *out_log_lpr_movement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN*1000);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];	

	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");	

	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "modified_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s5959999", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and modified_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "modified_time<='%s'", endtime_str);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(station_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and station_id LIKE '%%%s%%'", query_str, station_id);
		else							sprintf(query_str, "station_id LIKE '%%%s%%'", station_id);
	}
	sprintf(query_str, "%s ORDER BY id ASC", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.log_lpr_movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_lpr_movement(raw + i * MAX_DATA_LEN, &out_log_lpr_movement[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_log_pgs_movement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, char *inp_lot_no, struct log_pgs_movement_rec *out_log_pgs_movement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN*1000);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	

	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "modified_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s5959999", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and modified_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "modified_time<='%s'", endtime_str);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum = '%s'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(inp_lot_no, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and lot_id = '%s'", query_str, inp_lot_no);
		else							sprintf(query_str, "lot_id  = '%s'", inp_lot_no);
	}
	sprintf(query_str, "%s ORDER BY id ASC", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.log_pgs_movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_pgs_movement(raw + i * MAX_DATA_LEN, &out_log_pgs_movement[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_log_enforcement_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_enforcement_rec *out_log_enforcement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN*1000);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];

	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "modified_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s5959999", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and modified_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "modified_time<='%s'", endtime_str);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	
	sprintf(query_str, "%s ORDER BY id ASC", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.log_enforcement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_enforcement(raw + i * MAX_DATA_LEN, &out_log_enforcement[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_log_pgs_occupancy_by_report(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_led_id, struct log_pgs_occupancy_rec *out_log_pgs_occupancy)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN*1000);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];

	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");


	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "modified_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s0000000", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and modified_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "modified_time<='%s' ", endtime_str);
	}
	if (strcmp(inp_led_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and led_id LIKE '%%%s%%'", query_str, inp_led_id);
		else							sprintf(query_str, "led_id LIKE '%%%s%%'", inp_led_id);
	}	

	sprintf(query_str, "%s ORDER BY id ASC", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.log_pgs_occupancy", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_pgs_occupancy(raw + i * MAX_DATA_LEN, &out_log_pgs_occupancy[i]);
	}
	free(raw);
	return rec_no;
}

int minc_pgs_write_csv_log_lpr_movement(char *csv_filename, int len, struct log_lpr_movement_rec *inp_log_lpr_movement)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,modified_time,station_id,platenum,ptype,movement_time,car_image,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s,%s,%s\n",
			i,
			inp_log_lpr_movement->modified_time,
			inp_log_lpr_movement->station_id,
			inp_log_lpr_movement->platenum,
			inp_log_lpr_movement->ptype,
			inp_log_lpr_movement->movement_time,
			inp_log_lpr_movement->car_image,			
			inp_log_lpr_movement->comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}
int minc_pgs_write_csv_log_pgs_movement(char *csv_filename, int len, struct log_pgs_movement_rec *inp_log_pgs_movement)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,modified_time,lot_id,plate_no,camera_ip,led_id,controller_ip,pageindex,floor_id,status,image_path,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s,%s,%s,%s\n",
			i,
			inp_log_pgs_movement->modified_time,
			inp_log_pgs_movement->lot_id,
			inp_log_pgs_movement->platenum,
			inp_log_pgs_movement->ptype,
			inp_log_pgs_movement->movement_time,			
			inp_log_pgs_movement->status,
			inp_log_pgs_movement->car_image,
			inp_log_pgs_movement->comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}
int minc_pgs_write_csv_log_enforcement(char *csv_filename, int len, struct log_enforcement_rec *inp_log_enforcement)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,modified_time,platenum,car_image,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s\n",
			i,
			inp_log_enforcement->modified_time,
			inp_log_enforcement->platenum,
			inp_log_enforcement->car_image,
			inp_log_enforcement->comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}
int minc_pgs_write_csv_log_pgs_occupancy(char *csv_filename, int len, struct log_pgs_occupancy_rec *inp_log_pgs_occupancy)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,modified_time,led_id,count,movement_time,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s\n",
			i,
			inp_log_pgs_occupancy->modified_time,
			inp_log_pgs_occupancy->led_id,
			inp_log_pgs_occupancy->count,
			inp_log_pgs_occupancy->movement_time,
			inp_log_pgs_occupancy->comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}






//-----------------test----------------------------------
int minc_pgs_upd_data_pgs_test(char *pageindex,int id)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "pageindex='%s'",pageindex);

	sprintf(ask_str, "id=%d", id);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.data_pgs", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_upd_data_floormap_test(char *id,int old_id)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "id='%s'", id);

	sprintf(ask_str, "id=%d", old_id);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.cfg_floormap", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
//---------------------------------------------------------





int minc_pgs_led_init_api(int led_index)
{
	char log_msg[4096];
	init_led(led_index);
	sprintf(log_msg, "minc_pgs_led_init_api led[%d] init...\n", led_index); write_log(log_msg);
	return RESULT_GOOD;
}

int minc_pgs_led_display_api(int led_index, int count)
{
	char led_msg[20];
	char log_msg[4096];
	sprintf(led_msg, "%d", count);
	led_display(led_index, 0, led_msg);
	sprintf(log_msg, "minc_pgs_led_display_api led[%d] count=%d init...\n", led_index, count); write_log(log_msg);
}

int minc_pgs_get_program_version(char *version_str)
{
	char log_msg[4096];
	strcpy(version_str, VERSION);
	sprintf(log_msg, "pgs_api version: %s login...\n", version_str);
	write_log(log_msg);

	return RESULT_GOOD;
}

int minc_pgs_query_account(char *inp_userid, char *inp_passcodet)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search season with assigned condition
	strcpy(query_str, "");
	bool first_param_flag = false;
	if (strcmp(inp_userid, "") != 0) {
		sprintf(query_str, "userid = '%s'", inp_userid);
		first_param_flag = true;
	}	
	int rec_no = QueryDatabase(postgresDB_master, "pgs.pgs_login", query_str, QUERY_MODE_ALL, raw);	

	struct login_account_rec login_account_rec_local;
	// step3: output data
	if (rec_no > 0) {
		read_login_account(raw, &login_account_rec_local);
		//idenitify user mode or control mode.
		bool mode = false;
		if (strcmp(inp_userid, "admin") == 0 && strcmp(inp_passcodet, "PPadmin") == 0)	mode = true;
		else if (strcmp(inp_userid, "gast") == 0 && strcmp(inp_passcodet, "gast") == 0)		mode = false;

		if (strcmp(inp_userid, login_account_rec_local.userid) != 0 || strcmp(inp_passcodet, login_account_rec_local.passcode) != 0)	rec_no = Account_pw_error;
		else if ((strcmp(inp_userid, login_account_rec_local.userid) == 0 || strcmp(inp_passcodet, login_account_rec_local.passcode) == 0) && mode == false) {
			rec_no = User_mode;
			sprintf(log_msg, "userid: %s login...\n", inp_userid);
			write_log(log_msg);
		}
		else if ((strcmp(inp_userid, login_account_rec_local.userid) == 0 || strcmp(inp_passcodet, login_account_rec_local.passcode) == 0) && mode == true) {
			rec_no = control_mode;
			sprintf(log_msg, "userid: %s login...\n", inp_userid);
			write_log(log_msg);
		}
	}
	free(raw);
	return rec_no;
}

int minc_pgs_query_station_infomation(struct station_information_value_type *station_information_value)
{
	char raw[1024];
	struct station_information_lot_type station_information_lot_local;
	char log_msg[4096];

	// check database connection
	if (verify_database_connection() == false) {
		sprintf(log_msg, "pgs.station_information connection error..\n");
		write_log(log_msg);
		return SYSTEM_FAIL;
	}
	
	int rec_no = QueryDatabase(postgresDB_master, "pgs.station_information", "id=0", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_station_information(raw, &station_information_lot_local);		
		station_information_value->total_entry = station_information_lot_local.total_entry;
		station_information_value->total_exit = station_information_lot_local.total_exit;	
		strcpy(station_information_value->E1_block, station_information_lot_local.E1_block);
		strcpy(station_information_value->E2_block, station_information_lot_local.E2_block);
		strcpy(station_information_value->E3_block, station_information_lot_local.E3_block);
		strcpy(station_information_value->E4_block, station_information_lot_local.E4_block);
		strcpy(station_information_value->X1_block, station_information_lot_local.X1_block);
		strcpy(station_information_value->X2_block, station_information_lot_local.X2_block);
		strcpy(station_information_value->X3_block, station_information_lot_local.X3_block);
		strcpy(station_information_value->X4_block, station_information_lot_local.X4_block);

		sprintf(log_msg, "pgs.station_information get station_information ok..\n");
		write_log(log_msg);
		return RESULT_GOOD;
	}
	return RESULT_FAIL;
}

int minc_pgs_query_infomation(char *inp_floor_id,struct information_value_type *information_value)
{
	char query_str[256];
	char raw[1024];	
	char log_msg[4096];
	struct information_lot_type information_lot_local;

	// check database connection
	if (verify_database_connection() == false) {
		sprintf(log_msg, "pgs.information connection error..\n");
		write_log(log_msg);
		return SYSTEM_FAIL;
	}
	strcmp(query_str, "");
	if (strcmp(inp_floor_id, "") != 0) {
		sprintf(query_str, "floor_id LIKE '%s'", inp_floor_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.information", query_str, QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {	
		read_information(raw, &information_lot_local);
		strcpy(information_value->floor_id, information_lot_local.floor_id);
		strcpy(information_value->camera_ip, information_lot_local.camera_ip);		
		strcpy(information_value->platenum, information_lot_local.platenum);
		strcpy(information_value->last_updatetime, information_lot_local.last_updatetime);
		strcpy(information_value->status, information_lot_local.status);
		strcpy(information_value->direction, information_lot_local.direction);
		strcpy(information_value->locationx, information_lot_local.locationx);
		strcpy(information_value->locationy, information_lot_local.locationy);
		strcpy(information_value->image_path, information_lot_local.image_path);
		strcpy(information_value->comments, information_lot_local.comments);
		
		sprintf(log_msg, "pgs.information get station_information ok..\n");
		write_log(log_msg);
		return RESULT_GOOD;
	}
	return RESULT_FAIL;
}

int minc_pgs_query_availablelot(struct availablelot_value_type *availablelot_value)
{
	char raw[1024];
	struct available_lot_type available_lot_local;
	char log_msg[4096];

	// check database connection
	if (verify_database_connection() == false) {
		sprintf(log_msg, "data.availablelot connection error..\n");
		write_log(log_msg);
		return SYSTEM_FAIL;
	}

	int rec_no = QueryDatabase(postgresDB_master, "data.availablelot", "id=0", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_availablelot(raw, &available_lot_local);
		strcpy(availablelot_value->carpark_id, available_lot_local.carpark_id);		
		availablelot_value->totallot		= available_lot_local.totallot;
		availablelot_value->season_reserved = available_lot_local.season_reserved;
		availablelot_value->total_occupied  = available_lot_local.total_occupied;
		availablelot_value->season_occupied = available_lot_local.season_occupied;
		availablelot_value->hourly_occupied = available_lot_local.hourly_occupied;
		sprintf(log_msg, "data.availablelot get available ok..\n");
		write_log(log_msg);
		return RESULT_GOOD;
	}
	return RESULT_FAIL;
}

int minc_pgs_update_availablelot(struct availablelot_value_type *inp_availablelot_value_local)
{
	char modified_time[50];
	char set_str[255];
	char ask_str[255];
	char raw[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	get_detail_currenttime_for_bcd(modified_time);
	sprintf(ask_str, "id=0");
	sprintf(set_str, "modified_time='%s',total_occupied='%d'", modified_time, inp_availablelot_value_local->total_occupied);

	// write into master database
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "data.availablelot", set_str, ask_str);
		usleep(10000);
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pgs_upd_operation_log(struct operation_log *inp_operation_log)
{
	char modified_time[50];
	char dat_operation_log[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: add database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(dat_operation_log, "'%s','%s','%s','%s','%s'",	
		inp_operation_log->user_id,
		inp_operation_log->modified_time,
		inp_operation_log->log_type,
		inp_operation_log->log_message,
		inp_operation_log->comments);
	 
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "data.operation_log", OPERATIONLOG_HEADER, dat_operation_log);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
//--------------------------Old---------------------------------------------------------
int minc_pgs_query_lot(char *inp_floor_id, struct lot_rec *out_lot)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", query_str, inp_floor_id);
		else							sprintf(query_str, "floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", inp_floor_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct lot_rec lot_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot(raw + i * MAX_DATA_LEN, &lot_local);
			out_lot[i].id = lot_local.id;
			out_lot[i].lot_id = lot_local.lot_id;
			strcpy(out_lot[i].lot_name, lot_local.lot_name);
			strcpy(out_lot[i].plate_no, lot_local.plate_no);
			strcpy(out_lot[i].carera_ip, lot_local.carera_ip);
			strcpy(out_lot[i].controller_id, lot_local.controller_id);
			strcpy(out_lot[i].indicator_ip, lot_local.indicator_ip);
			strcpy(out_lot[i].indicator_port_no, lot_local.indicator_port_no);
			strcpy(out_lot[i].occupancy_typeid, lot_local.occupancy_typeid);
			strcpy(out_lot[i].floor_id, lot_local.floor_id);
			strcpy(out_lot[i].location_x, lot_local.location_x);
			strcpy(out_lot[i].location_y, lot_local.location_y);
			strcpy(out_lot[i].direction, lot_local.direction);
			strcpy(out_lot[i].status, lot_local.status);
			strcpy(out_lot[i].image_path, lot_local.image_path);
			strcpy(out_lot[i].lastupdatedtime, lot_local.lastupdatedtime);
			strcpy(out_lot[i].indicator_status, lot_local.indicator_status);
			strcpy(out_lot[i].seq_no, lot_local.seq_no);
			strcpy(out_lot[i].zone_id, lot_local.zone_id);
			strcpy(out_lot[i].comments, lot_local.comments);
			strcpy(out_lot[i].block_w, lot_local.block_w);
			strcpy(out_lot[i].block_h, lot_local.block_h);
		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot_floor_id(char *inp_lot_floor_id, struct lot_rec *out_lot)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_lot_floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id = '%s' ORDER BY lot_id ASC", query_str, inp_lot_floor_id);
		else							sprintf(query_str, "floor_id = '%s' ORDER BY lot_id ASC", inp_lot_floor_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct lot_rec lot_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot(raw + i * MAX_DATA_LEN, &lot_local);
			out_lot[i].id = lot_local.id;
			out_lot[i].lot_id = lot_local.lot_id;
			strcpy(out_lot[i].lot_name, lot_local.lot_name);
			strcpy(out_lot[i].plate_no, lot_local.plate_no);
			strcpy(out_lot[i].carera_ip, lot_local.carera_ip);
			strcpy(out_lot[i].controller_id, lot_local.controller_id);
			strcpy(out_lot[i].indicator_ip, lot_local.indicator_ip);
			strcpy(out_lot[i].indicator_port_no, lot_local.indicator_port_no);
			strcpy(out_lot[i].occupancy_typeid, lot_local.occupancy_typeid);
			strcpy(out_lot[i].floor_id, lot_local.floor_id);
			strcpy(out_lot[i].location_x, lot_local.location_x);
			strcpy(out_lot[i].location_y, lot_local.location_y);
			strcpy(out_lot[i].direction, lot_local.direction);
			strcpy(out_lot[i].status, lot_local.status);
			strcpy(out_lot[i].image_path, lot_local.image_path);
			strcpy(out_lot[i].lastupdatedtime, lot_local.lastupdatedtime);
			strcpy(out_lot[i].indicator_status, lot_local.indicator_status);
			strcpy(out_lot[i].seq_no, lot_local.seq_no);
			strcpy(out_lot[i].zone_id, lot_local.zone_id);
			strcpy(out_lot[i].comments, lot_local.comments);
			strcpy(out_lot[i].block_w, lot_local.block_w);
			strcpy(out_lot[i].block_h, lot_local.block_h);
		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot_index2(int Max_lot, int total_floor_count, struct cfg_floorplan_rec *inp_floorplan, struct index_rec *out_index)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];
	int count = 0;

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	for (int i = 0; i < total_floor_count; i++) {
		if (strcmp(inp_floorplan[i].floor_id, "") != 0) {
			if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", query_str, inp_floorplan[i].floor_id);
			else							sprintf(query_str, "floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", inp_floorplan[i].floor_id);
		}
		int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);
		// step3: output data
		struct lot_rec lot_local;
		if (rec_no > 0) {
			for (int j = 0; j < rec_no; j++) {
				read_lot(raw + j * MAX_DATA_LEN, &lot_local);
				out_index[j + count].lot_id = lot_local.lot_id;
				strcpy(out_index[j + count].floor_id, lot_local.floor_id);
				sprintf(out_index[j + count].page_no, "%d", j / 9);
				out_index[j + count].index = j % 9 + 1;
			}
		}
		count = count + rec_no;
		strcpy(query_str, "");
	}

	free(raw);
	return RESULT_GOOD;

}
int minc_pgs_query_lot_controller_id(char *inp_controller_id, struct lot_rec *out_lot)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_controller_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and controller_id LIKE '%%s%' and status='non_occupancy'", query_str, inp_controller_id);
		else							sprintf(query_str, "controller_id LIKE '%%%s%%' and status='non_occupancy'", inp_controller_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct lot_rec lot_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot(raw + i * MAX_DATA_LEN, &lot_local);
			out_lot[i].id = lot_local.id;
			out_lot[i].lot_id = lot_local.lot_id;
			strcpy(out_lot[i].lot_name, lot_local.lot_name);
			strcpy(out_lot[i].plate_no, lot_local.plate_no);
			strcpy(out_lot[i].carera_ip, lot_local.carera_ip);
			strcpy(out_lot[i].controller_id, lot_local.controller_id);
			strcpy(out_lot[i].indicator_ip, lot_local.indicator_ip);
			strcpy(out_lot[i].indicator_port_no, lot_local.indicator_port_no);
			strcpy(out_lot[i].occupancy_typeid, lot_local.occupancy_typeid);
			strcpy(out_lot[i].floor_id, lot_local.floor_id);
			strcpy(out_lot[i].location_x, lot_local.location_x);
			strcpy(out_lot[i].location_y, lot_local.location_y);
			strcpy(out_lot[i].direction, lot_local.direction);
			strcpy(out_lot[i].status, lot_local.status);
			strcpy(out_lot[i].image_path, lot_local.image_path);
			strcpy(out_lot[i].lastupdatedtime, lot_local.lastupdatedtime);
			strcpy(out_lot[i].indicator_status, lot_local.indicator_status);
			strcpy(out_lot[i].seq_no, lot_local.seq_no);
			strcpy(out_lot[i].zone_id, lot_local.zone_id);
			strcpy(out_lot[i].comments, lot_local.comments);
			strcpy(out_lot[i].block_w, lot_local.block_w);
			strcpy(out_lot[i].block_h, lot_local.block_h);
		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_upd_lot(struct lot_rec *inp_lot)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "lot_name='%s',plate_no='%s',carera_ip='%s',controller_id='%s',indicator_ip='%s',indicator_port_no='%s',occupancy_typeid='%s',floor_id='%s',location_x='%s',location_y='%s',direction='%s',status='%s',image_path='%s',lastupdatedtime='%s',indicator_status ='%s', seq_no ='%s', zone_id ='%s',comments='%s',block_w='%s',block_h='%s'",
		inp_lot->lot_name,
		inp_lot->plate_no,
		inp_lot->carera_ip,
		inp_lot->controller_id,
		inp_lot->indicator_ip,
		inp_lot->indicator_port_no,
		inp_lot->occupancy_typeid,
		inp_lot->floor_id,
		inp_lot->location_x,
		inp_lot->location_y,
		inp_lot->direction,
		inp_lot->status,
		inp_lot->image_path,
		inp_lot->lastupdatedtime,
		inp_lot->indicator_status,
		inp_lot->seq_no,
		inp_lot->zone_id,
		inp_lot->comments,
		inp_lot->block_w,
		inp_lot->block_h);
	sprintf(ask_str, "lot_id=%d", inp_lot->lot_id);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.twlot", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_add_lot(struct lot_rec *inp_lot)
{
	char dat_lot[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// write movement records 
	sprintf(dat_lot, "'%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'",
		inp_lot->lot_id,
		inp_lot->lot_name,
		inp_lot->plate_no,
		inp_lot->carera_ip,
		inp_lot->controller_id,
		inp_lot->indicator_ip,
		inp_lot->indicator_port_no,
		inp_lot->occupancy_typeid,
		inp_lot->floor_id,
		inp_lot->location_x,
		inp_lot->location_y,
		inp_lot->direction,
		inp_lot->status,
		inp_lot->image_path,
		inp_lot->lastupdatedtime,
		inp_lot->indicator_status,
		inp_lot->seq_no,
		inp_lot->zone_id,
		inp_lot->comments,
		inp_lot->block_w,
		inp_lot->block_h);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.twlot", LOT_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_lot(int rid) {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "pgs.twlot", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_all_lot() {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database	
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = Deletet_All_Database(postgresDB_master, "pgs.twlot");
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_upd_floorplan(struct cfg_floorplan_rec *inp_floorplan)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);

	sprintf(ask_str, "floor_id='%s'", inp_floorplan->floor_id);
	sprintf(ask_str, "floor_name='%s'", inp_floorplan->floor_name);
	sprintf(set_str, "image='%s'", inp_floorplan->Image);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.cfg_floorplan", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_add_floorplan(struct cfg_floorplan_rec *inp_floorplan)
{
	char dat_lot[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// write movement records 
	sprintf(dat_lot, "'%s','%s','%s','%s'",
		inp_floorplan->floor_id,
		inp_floorplan->floor_name,
		inp_floorplan->Image,
		inp_floorplan->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.cfg_floorplan", FLOORPLANE_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_floorplan(int rid) {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "pgs.cfg_floorplan", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_all_floorplan() {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database	
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = Deletet_All_Database(postgresDB_master, "pgs.cfg_floorplan");
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_query_log_movement(char *station_name, char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_movement_rec *out_log_movement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search log_movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "station_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s0000000", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and station_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "entry_time<='%s'", endtime_str);
	}
	if (strcmp(station_name, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and station_name LIKE '%%%s%%'", query_str, station_name);
		else							sprintf(query_str, "station_name LIKE '%%%s%%'", station_name);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	else							sprintf(query_str, "", query_str);
	int rec_no = QueryDatabase(postgresDB_master, "data.log_movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_movement(raw + i * MAX_DATA_LEN, &out_log_movement[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_write_csv_log_movement(char *csv_filename, int len, struct log_movement_rec *inp_log_movement)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,platenum,etagnum,station_name,station_time,parked_type,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s,%s,\n",
			i,
			inp_log_movement[i].platenum,
			inp_log_movement[i].etagnum,
			inp_log_movement[i].station_name,
			inp_log_movement[i].station_time,
			inp_log_movement[i].parked_type,
			inp_log_movement[i].comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}
int minc_pgs_get_image(char *ipcam_ip, char *ipcam_type, char *username, char *password)
{
	char xml_filename[300];
	char device_service_url[1000];
	char media_service_url[1000];
	char http_uri[300];
	char image_filename[100];
	char log_msg[4096];
	CkHttp http;
	CkXml  xml;
	CkHttpResponse *resp = 0;

	strcpy(image_filename, "/tmp/PGS.jpg");

	if (strcmp(ipcam_type, "td") == 0) {
		// set device_service uri
		sprintf(device_service_url, "http://%s:%d/onvif/device_service", ipcam_ip, 80);

		// login td
		bool success = http.UnlockComponent("NGNSYS.CB1122019_TpaAZ8hJo1jq");
		if (success != true) {
			Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
			frame.setTo(cv::Scalar(255, 255, 255));
			cv::putText(frame, "Http err", Point(25, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
			imwrite(image_filename, frame);
			printf("unlock http error: %s\n", ipcam_type);
			return false;
		}
		http.CloseAllConnections();
		http.SetRequestHeader("Content-Type", "text/xml; charset=utf-8");
		http.SetRequestHeader("Authorization", "Digest username=\"admin\", realm=\"gSOAP Web Service\", qop=\"auth\", algorithm=\"MD5\", uri=\"/onvif/media\", nonce=\"4e4467304d6a46424e4551364d54633059544e6d4e6a513d\", nc=00000001, cnonce=\"F12A06A01AF335701B1944D96363AE5F\", response=\"1335d1c59a4b38b115d35544055ab001\"");
		http.put_Login("admin");
		http.put_LoginDomain(device_service_url);
		http.put_Password("PGSadmin");

		// load xml
		strcpy(xml_filename, "/lpr_data/config/td_ipcam.xml");
		success = xml.LoadXmlFile(xml_filename);
		if (success != true) {
			Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
			frame.setTo(cv::Scalar(255, 255, 255));
			cv::putText(frame, "Load Xml err", Point(25, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
			imwrite(image_filename, frame);
			printf("load xml error: %s\n", ipcam_type);
			return false;
		}

		// post xml (reset image)
		sprintf(media_service_url, "http://%s:%d/onvif/media", ipcam_ip, 80);
		const char *strXml = xml.getXml();
		const char *endPoint = media_service_url;
		resp = http.PostXml(endPoint, strXml, "utf-8");
		if (resp == 0) {
			Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
			frame.setTo(cv::Scalar(255, 255, 255));
			cv::putText(frame, "Post Xml err", Point(25, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
			imwrite(image_filename, frame);
			printf("post xml error: %s\n", ipcam_type);
			return false;
		}

		// set http_uri
		sprintf(http_uri, "http://%s/jpeg/trade_ftp/pic_type00_01.jpg", ipcam_ip);

		// grab & store image
		long fileSize;
		char *memBuffer, *headerBuffer;
		memBuffer = headerBuffer = NULL;
		memBuffer = readUrl2(http_uri, fileSize, &headerBuffer);
		if (memBuffer == NULL) return false;
		if (fileSize != 0) {
			Mat frame;
			convert_jpeg_buf_to_mat(memBuffer, fileSize, frame);
			imwrite(image_filename, frame);
			delete(memBuffer);
			delete(headerBuffer);
			return RESULT_GOOD;
		}
		else {
			Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
			frame.setTo(cv::Scalar(255, 255, 255));
			cv::putText(frame, "EMpty Image", Point(75, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
			imwrite(image_filename, frame);
			printf("camera type error: %s\n", ipcam_type);
			return RESULT_FAIL;
		}
	}
	else if (strcmp(ipcam_type, "jvt") == 0) {
		// set device_service uri
		sprintf(device_service_url, "http://%s/cgi-bin/images_cgi?channel=0&user=%s&pwd=%s", ipcam_ip, username, password);

		// login jvt
		http.CloseAllConnections();
		http.SetRequestHeader("Content-Type", "text/xml; charset=utf-8");
		http.SetRequestHeader("Authorization", "Digest username=\"admin\", realm=\"gSOAP Web Service\", qop=\"auth\", algorithm=\"MD5\", uri=\"/onvif/media\", nonce=\"4e4467304d6a46424e4551364d54633059544e6d4e6a513d\", nc=00000001, cnonce=\"F12A06A01AF335701B1944D96363AE5F\", response=\"1335d1c59a4b38b115d35544055ab001\"");
		http.put_Login("admin");
		http.put_LoginDomain(device_service_url);
		http.put_Password(password);

		// set http_uri
		sprintf(http_uri, "http://%s/cgi-bin/images_cgi?channel=0&user=%s&pwd=%s", ipcam_ip, username, password);

		// grab & store image
		long fileSize;
		char *memBuffer, *headerBuffer;
		memBuffer = headerBuffer = NULL;
		memBuffer = readUrl2(http_uri, fileSize, &headerBuffer);
		if (fileSize != 0) {
			Mat frame;
			convert_jpeg_buf_to_mat(memBuffer, fileSize, frame);
			imwrite(image_filename, frame);
			delete(memBuffer);
			delete(headerBuffer);
			return RESULT_GOOD;
		}
		else {
			Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
			frame.setTo(cv::Scalar(255, 255, 255));
			cv::putText(frame, "Empty Image", Point(75, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
			imwrite(image_filename, frame);
			printf("camera type error: %s\n", ipcam_type);
			return RESULT_FAIL;
		}
	}
	else {
		Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
		frame.setTo(cv::Scalar(255, 255, 255));
		cv::putText(frame, "Error Image", Point(75, 125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
		imwrite(image_filename, frame);
		printf("camera type error: %s\n", ipcam_type);
		return RESULT_FAIL;
	}
}
int minc_pgs_clear_db(char *DB_name)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s", DB_name);

	int rec_no = ClearDatabase(postgresDB_master, query_str);

	// step3: output data
	if (rec_no < 0) {
		rec_no = -1;
	}
	free(raw);
	return rec_no;
}
int minc_pgs_add_enforcement(struct enforcement_init_info_rec *inp_enforcement)
{
	char dat_lot[1024];
	char log_msg[4096];
	char modified_time[50];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	get_detail_currenttime_for_bcd(modified_time);

	// write movement records 
	sprintf(dat_lot, "'%s','%s','%s','%s'",
		inp_enforcement->modified_time,
		inp_enforcement->platenum,
		inp_enforcement->car_image,
		inp_enforcement->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.enforcement", ENFORCEMENT_HEADER, dat_lot);
		status = InsertDatabase(postgresDB_master, "pgs.log_enforcement", ENFORCEMENT_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_query_enforcement(struct enforcement_init_info_rec *out_enforcement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.enforcement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_enforcement(raw + i * MAX_DATA_LEN, &out_enforcement[i]);
	}
	free(raw);
	return rec_no;
}
int minc_pgs_upd_enforcement(struct enforcement_init_info_rec *inp_enforcement)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "'%s','%s','%s','%s'",
		inp_enforcement->modified_time,
		inp_enforcement->platenum,
		inp_enforcement->car_image,
		inp_enforcement->comments);

	sprintf(ask_str, "id=%d", inp_enforcement->id);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.twlot", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pgs_add_blacklist(struct data_blk_rec *data_blk)
{
	char dat_lot[1024];
	char log_msg[4096];
	char modified_time[50];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	get_detail_currenttime_for_bcd(modified_time);

	// write movement records 
	sprintf(dat_lot, "'%s','%s','%s','%s','%s','%s','%s','%s'",
		modified_time,
		data_blk->stn_id,
		data_blk->movement_time,
		data_blk->platestr,
		data_blk->pageindex,
		data_blk->status,
		data_blk->car_image,
		data_blk->comments);	

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.data_blk", BLACKLIST_HEADER, dat_lot);
		status = InsertDatabase(postgresDB_master, "pgs.log_blk_movement", BLACKLIST_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_query_blacklist(struct data_blk_rec *out_data_blk)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	strcpy(query_str, "");
	sprintf(query_str, "%s id IS NOT NULL  ORDER BY id ASC ", query_str);

	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_blk", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_data_blk(raw + i * MAX_DATA_LEN, &out_data_blk[i]);
	}
	free(raw);
	return rec_no;
}

//--------------------no used-------------------------------
int minc_pgs_query_lot_lotname(char *inp_lot_name, struct lot_rec *out_lot)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_lot_name, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and lot_name = '%s' ORDER BY lot_id ASC", query_str, inp_lot_name);
		else							sprintf(query_str, "lot_name = '%s' ORDER BY lot_id ASC", inp_lot_name);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct lot_rec lot_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot(raw + i * MAX_DATA_LEN, &lot_local);
			out_lot[i].id = lot_local.id;
			out_lot[i].lot_id = lot_local.lot_id;
			strcpy(out_lot[i].lot_name, lot_local.lot_name);
			strcpy(out_lot[i].plate_no, lot_local.plate_no);
			strcpy(out_lot[i].carera_ip, lot_local.carera_ip);
			strcpy(out_lot[i].controller_id, lot_local.controller_id);
			strcpy(out_lot[i].indicator_ip, lot_local.indicator_ip);
			strcpy(out_lot[i].indicator_port_no, lot_local.indicator_port_no);
			strcpy(out_lot[i].occupancy_typeid, lot_local.occupancy_typeid);
			strcpy(out_lot[i].floor_id, lot_local.floor_id);
			strcpy(out_lot[i].location_x, lot_local.location_x);
			strcpy(out_lot[i].location_y, lot_local.location_y);
			strcpy(out_lot[i].direction, lot_local.direction);
			strcpy(out_lot[i].status, lot_local.status);
			strcpy(out_lot[i].image_path, lot_local.image_path);
			strcpy(out_lot[i].lastupdatedtime, lot_local.lastupdatedtime);
			strcpy(out_lot[i].indicator_status, lot_local.indicator_status);
			strcpy(out_lot[i].seq_no, lot_local.seq_no);
			strcpy(out_lot[i].zone_id, lot_local.zone_id);
			strcpy(out_lot[i].comments, lot_local.comments);
			strcpy(out_lot[i].block_w, lot_local.block_w);
			strcpy(out_lot[i].block_h, lot_local.block_h);
		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot_seq_no(char *inp_seq_no, struct lot_rec *out_lot)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_seq_no, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and seq_no = '%s' ORDER BY lot_id ASC", query_str, inp_seq_no);
		else							sprintf(query_str, "seq_no = '%s' ORDER BY lot_id ASC", inp_seq_no);
	}


	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct lot_rec lot_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot(raw + i * MAX_DATA_LEN, &lot_local);
			out_lot[i].id = lot_local.id;
			out_lot[i].lot_id = lot_local.lot_id;
			strcpy(out_lot[i].lot_name, lot_local.lot_name);
			strcpy(out_lot[i].plate_no, lot_local.plate_no);
			strcpy(out_lot[i].carera_ip, lot_local.carera_ip);
			strcpy(out_lot[i].controller_id, lot_local.controller_id);
			strcpy(out_lot[i].indicator_ip, lot_local.indicator_ip);
			strcpy(out_lot[i].indicator_port_no, lot_local.indicator_port_no);
			strcpy(out_lot[i].occupancy_typeid, lot_local.occupancy_typeid);
			strcpy(out_lot[i].floor_id, lot_local.floor_id);
			strcpy(out_lot[i].location_x, lot_local.location_x);
			strcpy(out_lot[i].location_y, lot_local.location_y);
			strcpy(out_lot[i].direction, lot_local.direction);
			strcpy(out_lot[i].status, lot_local.status);
			strcpy(out_lot[i].image_path, lot_local.image_path);
			strcpy(out_lot[i].lastupdatedtime, lot_local.lastupdatedtime);
			strcpy(out_lot[i].indicator_status, lot_local.indicator_status);
			strcpy(out_lot[i].seq_no, lot_local.seq_no);
			strcpy(out_lot[i].zone_id, lot_local.zone_id);
			strcpy(out_lot[i].comments, lot_local.comments);
			strcpy(out_lot[i].block_w, lot_local.block_w);
			strcpy(out_lot[i].block_h, lot_local.block_h);
		}
	}
	free(raw);
	return rec_no;
}

//--------------------no used-------------------------------


//-------------------------new-----------------------------------------------------------
int minc_pgs_query_lot_lotid(char *inp_lot_id, struct twlot2_rec *out_lot2)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_lot_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and lot_id = '%s' ORDER BY lot_id ASC", query_str, inp_lot_id);
		else							sprintf(query_str, "lot_id = '%s' ORDER BY lot_id ASC", inp_lot_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct twlot2_rec lot2_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot2(raw + i * MAX_DATA_LEN, &lot2_local);
			out_lot2[i].id = lot2_local.id;
			strcpy(out_lot2[i].modified_time, lot2_local.modified_time);
			strcpy(out_lot2[i].lot_id, lot2_local.lot_id);
			strcpy(out_lot2[i].plate_no, lot2_local.plate_no);
			strcpy(out_lot2[i].camera_ip, lot2_local.camera_ip);
			strcpy(out_lot2[i].led_id, lot2_local.led_id);
			strcpy(out_lot2[i].controller_ip, lot2_local.controller_ip);
			strcpy(out_lot2[i].pageindex, lot2_local.pageindex);
			strcpy(out_lot2[i].floor_id, lot2_local.floor_id);
			strcpy(out_lot2[i].floormap_title, lot2_local.floormap_title);
			strcpy(out_lot2[i].location_x, lot2_local.location_x);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].block_w, lot2_local.block_w);
			strcpy(out_lot2[i].block_h, lot2_local.block_h);
			strcpy(out_lot2[i].status, lot2_local.status);
			strcpy(out_lot2[i].image_path, lot2_local.image_path);
			strcpy(out_lot2[i].comments, lot2_local.comments);

		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot2(char *inp_floor_id, struct twlot2_rec *out_lot2)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	 
	if (strcmp(inp_floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id = '%s' ORDER BY id ASC", query_str, inp_floor_id);
		else							sprintf(query_str, "floor_id = '%s' ORDER BY id ASC", inp_floor_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct twlot2_rec lot2_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot2(raw + i * MAX_DATA_LEN, &lot2_local);
			out_lot2[i].id = lot2_local.id;
			strcpy(out_lot2[i].modified_time, lot2_local.modified_time);
			strcpy(out_lot2[i].lot_id, lot2_local.lot_id);
			strcpy(out_lot2[i].plate_no, lot2_local.plate_no);
			strcpy(out_lot2[i].camera_ip, lot2_local.camera_ip);
			strcpy(out_lot2[i].led_id, lot2_local.led_id);
			strcpy(out_lot2[i].controller_ip, lot2_local.controller_ip);
			strcpy(out_lot2[i].pageindex, lot2_local.pageindex);
			strcpy(out_lot2[i].floor_id, lot2_local.floor_id);
			strcpy(out_lot2[i].floormap_title, lot2_local.floormap_title);
			strcpy(out_lot2[i].location_x, lot2_local.location_x);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].block_w, lot2_local.block_w);
			strcpy(out_lot2[i].block_h, lot2_local.block_h);
			strcpy(out_lot2[i].status, lot2_local.status);
			strcpy(out_lot2[i].image_path, lot2_local.image_path);
			strcpy(out_lot2[i].comments, lot2_local.comments);

		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot2_floor_id(char *inp_lot_floor_id, struct twlot2_rec *out_lot2)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_lot_floor_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id = '%s' ORDER BY lot_id ASC", query_str, inp_lot_floor_id);
		else							sprintf(query_str, "floor_id = '%s' ORDER BY lot_id ASC", inp_lot_floor_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct twlot2_rec lot2_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot2(raw + i * MAX_DATA_LEN, &lot2_local);
			out_lot2[i].id = lot2_local.id;
			strcpy(out_lot2[i].modified_time, lot2_local.modified_time);
			strcpy(out_lot2[i].lot_id, lot2_local.lot_id);
			strcpy(out_lot2[i].plate_no, lot2_local.plate_no);
			strcpy(out_lot2[i].camera_ip, lot2_local.camera_ip);
			strcpy(out_lot2[i].led_id, lot2_local.led_id);
			strcpy(out_lot2[i].controller_ip, lot2_local.controller_ip);
			strcpy(out_lot2[i].pageindex, lot2_local.pageindex);
			strcpy(out_lot2[i].floor_id, lot2_local.floor_id);
			strcpy(out_lot2[i].floormap_title, lot2_local.floormap_title);
			strcpy(out_lot2[i].location_x, lot2_local.location_x);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].block_w, lot2_local.block_w);
			strcpy(out_lot2[i].block_h, lot2_local.block_h);
			strcpy(out_lot2[i].status, lot2_local.status);
			strcpy(out_lot2[i].image_path, lot2_local.image_path);
			strcpy(out_lot2[i].comments, lot2_local.comments);

		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot2_index2(int Max_lot, int total_floor_count, struct cfg_floorplan_rec *inp_floorplan, struct index_rec *out_index)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];
	int count = 0;

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	for (int i = 0; i < total_floor_count; i++) {
		if (strcmp(inp_floorplan[i].floor_id, "") != 0) {
			if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", query_str, inp_floorplan[i].floor_id);
			else							sprintf(query_str, "floor_id LIKE '%%%s%%' ORDER BY lot_id ASC", inp_floorplan[i].floor_id);
		}
		int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);
		// step3: output data
	
		struct twlot2_rec lot2_local;
		if (rec_no > 0) {
			for (int j = 0; j < rec_no; j++) {
				read_lot2(raw + j * MAX_DATA_LEN, &lot2_local);
				out_index[j + count].lot_id = atoi(lot2_local.lot_id);
				strcpy(out_index[j + count].floor_id, lot2_local.floor_id);
				sprintf(out_index[j + count].page_no, "%d", j / 9);
				out_index[j + count].index = j % 9 + 1;
			}
		}
		count = count + rec_no;
		strcpy(query_str, "");
	}

	free(raw);
	return RESULT_GOOD;

}
int minc_pgs_query_lot2_controller_id(char *inp_controller_id, struct twlot2_rec *out_lot2)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_controller_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and controller_id LIKE '%%s%' and status='non_occupancy'", query_str, inp_controller_id);
		else							sprintf(query_str, "controller_id LIKE '%%%s%%' and status='non_occupancy'", inp_controller_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct twlot2_rec lot2_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot2(raw + i * MAX_DATA_LEN, &lot2_local);
			out_lot2[i].id = lot2_local.id;
			strcpy(out_lot2[i].modified_time, lot2_local.modified_time);
			strcpy(out_lot2[i].lot_id, lot2_local.lot_id);
			strcpy(out_lot2[i].plate_no, lot2_local.plate_no);
			strcpy(out_lot2[i].camera_ip, lot2_local.camera_ip);
			strcpy(out_lot2[i].led_id, lot2_local.led_id);
			strcpy(out_lot2[i].controller_ip, lot2_local.controller_ip);
			strcpy(out_lot2[i].pageindex, lot2_local.pageindex);
			strcpy(out_lot2[i].floor_id, lot2_local.floor_id);
			strcpy(out_lot2[i].floormap_title, lot2_local.floormap_title);
			strcpy(out_lot2[i].location_x, lot2_local.location_x);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].block_w, lot2_local.block_w);
			strcpy(out_lot2[i].block_h, lot2_local.block_h);
			strcpy(out_lot2[i].status, lot2_local.status);
			strcpy(out_lot2[i].image_path, lot2_local.image_path);
			strcpy(out_lot2[i].comments, lot2_local.comments);

		}
	}
	free(raw);
	return rec_no;
}
int minc_pgs_query_lot2_led_id(char *inp_led_id, struct twlot2_rec *out_lot2)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");

	if (strcmp(inp_led_id, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and led_id LIKE '%%s%' and status='empty'", query_str, inp_led_id);
		else							sprintf(query_str, "led_id LIKE '%%%s%%' and status='empty'", inp_led_id);
	}

	int rec_no = QueryDatabase(postgresDB_master, "pgs.twlot2", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct twlot2_rec lot2_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_lot2(raw + i * MAX_DATA_LEN, &lot2_local);
			out_lot2[i].id = lot2_local.id;
			strcpy(out_lot2[i].modified_time, lot2_local.modified_time);
			strcpy(out_lot2[i].lot_id, lot2_local.lot_id);
			strcpy(out_lot2[i].plate_no, lot2_local.plate_no);
			strcpy(out_lot2[i].camera_ip, lot2_local.camera_ip);
			strcpy(out_lot2[i].led_id, lot2_local.led_id);
			strcpy(out_lot2[i].controller_ip, lot2_local.controller_ip);
			strcpy(out_lot2[i].pageindex, lot2_local.pageindex);
			strcpy(out_lot2[i].floor_id, lot2_local.floor_id);
			strcpy(out_lot2[i].floormap_title, lot2_local.floormap_title);
			strcpy(out_lot2[i].location_x, lot2_local.location_x);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].location_y, lot2_local.location_y);
			strcpy(out_lot2[i].block_w, lot2_local.block_w);
			strcpy(out_lot2[i].block_h, lot2_local.block_h);
			strcpy(out_lot2[i].status, lot2_local.status);
			strcpy(out_lot2[i].image_path, lot2_local.image_path);
			strcpy(out_lot2[i].comments, lot2_local.comments);

		}
	}
	free(raw);
	return rec_no;
}

int minc_pgs_upd_lot2(struct twlot2_rec *inp_lot2)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database	
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',lot_id='%s',plate_no='%s',camera_ip='%s',led_id='%s',controller_ip='%s',pageindex='%s',floor_id='%s',floormap_title='%s',location_x='%s',location_y='%s',block_w='%s',block_h='%s',image_path='%s',comments='%s'",
		modified_time,
		inp_lot2->lot_id,
		inp_lot2->plate_no,
		inp_lot2->camera_ip,
		inp_lot2->led_id,
		inp_lot2->controller_ip,
		inp_lot2->pageindex,
		inp_lot2->floor_id,
		inp_lot2->floormap_title,
		inp_lot2->location_x,
		inp_lot2->location_y,
		inp_lot2->block_w,
		inp_lot2->block_h,
		inp_lot2->status,
		inp_lot2->image_path,
		inp_lot2->comments);
	sprintf(ask_str, "id=%d", inp_lot2->id);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.twlot2", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_add_lot2(struct twlot2_rec *inp_lot2)
{
	char dat_lot[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// write movement records 
	sprintf(dat_lot, "'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'",
		inp_lot2->modified_time,
		inp_lot2->lot_id,
		inp_lot2->plate_no,
		inp_lot2->camera_ip,
		inp_lot2->led_id,
		inp_lot2->controller_ip,
		inp_lot2->pageindex,
		inp_lot2->floor_id,
		inp_lot2->floormap_title,
		inp_lot2->location_x,
		inp_lot2->location_y,
		inp_lot2->block_w,
		inp_lot2->block_h,
		inp_lot2->status,
		inp_lot2->image_path,
		inp_lot2->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "pgs.twlot2", LOT_HEADER, dat_lot);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_lot2(int rid) {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "pgs.twlot2", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}
int minc_pgs_del_all_lot2() {
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database	
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = Deletet_All_Database(postgresDB_master, "pgs.twlot2");
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}



//------------------------------------------------------------------------------------------






















//------------------------------------------------------------------------------------------------------------------------
int minc_pms_init_api(struct disp_availablelot_type *disp_availablelot, struct init_rec *init_data)
{
	int rec_no;
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: display version
	sprintf(log_msg, "minc_pms_init_api: %s\n", VERSION); write_log(log_msg);

	// step2: connect database
	char cmd[1000];
	char database_init_str[200];
	sprintf(database_init_str, "host=%s port=5435 dbname=pms_db user=cp password=cp123", MDB_IP);
	sprintf(cmd, database_init_str);
	postgresDB_master = ConnectDatabase(cmd);
	if (postgresDB_master == NULL) {
		sprintf(log_msg, "ConnectDatabase error (Master)\n"); write_log(log_msg);
		free(raw);
		return RESULT_FAIL;
	}

	// step3: init log & watchdog
	init_log();
	pthread_mutex_init(&log_mutex, NULL);
	pthread_create(&write_log_handle, NULL, &write_log_task, NULL);
	//pthread_create(&monitor_handle, NULL, &monitor_task, NULL);
	write_log("init_log & monitor ok\n");

	// step4: read availablelot database
	struct available_lot_type available_lot_local;
	memset((struct disp_availablelot_type *)disp_availablelot, 0, sizeof(disp_availablelot_type));

	rec_no = QueryDatabase(postgresDB_master, "data.availablelot", "id=0", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_availablelot(raw, &available_lot_local);
		sprintf(disp_availablelot->total_lots, "%d", available_lot_local.totallot);
		sprintf(disp_availablelot->total_occupies, "%d", available_lot_local.total_occupied);
		sprintf(disp_availablelot->season_occupies, "%d", available_lot_local.season_occupied);
		sprintf(disp_availablelot->hourly_occupies, "%d", available_lot_local.hourly_occupied);
		sprintf(disp_availablelot->empty_lots, "%d", available_lot_local.totallot - available_lot_local.total_occupied);
	}
	if (rec_no <= 0) {
		sprintf(log_msg, "Read availablelot error\n"); write_log(log_msg);
		free(raw);
		return RESULT_FAIL;
	}
	sprintf(log_msg, "read availablelot ok\n"); write_log(log_msg);

	// step5: read receipt_setting
	total_receipt_setting_count = 0;
	rec_no = QueryDatabase(postgresDB_master, "cfg.receipt_setting", "", QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_receipt_setting((raw + i * MAX_DATA_LEN), &receipt_setting[i]);
		}
		total_receipt_setting_count = rec_no;
	}
	if (rec_no <= 0) {
		sprintf(log_msg, "Read receipt setting error\n"); write_log(log_msg);
		free(raw);
		return RESULT_FAIL;
	}
	sprintf(log_msg, "read receipt_setting ok\n"); write_log(log_msg);

	// step6: read cp information
	init_data->ecount = 0;
	init_data->xcount = 0;
	init_data->acount = 0;
	rec_no = QueryDatabase(postgresDB_master, "cfg.config_cp", "id=0", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_config_cp(raw, &config_cp);
		init_data->ecount = atoi(config_cp.ecount);
		init_data->xcount = atoi(config_cp.xcount);
		init_data->acount = atoi(config_cp.acount);
		sprintf(log_msg, "config_cp: ok\n"); write_log(log_msg);
		for (int i = 0; i < atoi(config_cp.acount); i++) {
			sprintf(log_msg, "apm%d: %s\n", i + 1, config_cp.apm[i]);
			strcpy(init_data->apm_ip[i], config_cp.apm[i]);
			write_log(log_msg);
		}
		for (int i = 0; i < atoi(config_cp.ecount); i++) {
			sprintf(log_msg, "e%d: %s\n", i + 1, config_cp.e[i]);
			write_log(log_msg);
			for (int k = 0; k < atoi(config_cp.eipcamcount[i]); k++) {
				sprintf(log_msg, "e%d_ipcam%d: %s\n", i + 1, k + 1, config_cp.eipcam[i][k]);
				write_log(log_msg);
			}
		}
		for (int i = 0; i < atoi(config_cp.xcount); i++) {
			sprintf(log_msg, "x%d: %s\n", i + 1, config_cp.x[i]);
			write_log(log_msg);
			for (int k = 0; k < atoi(config_cp.xipcamcount[i]); k++) {
				sprintf(log_msg, "x%d_ipcam%d: %s\n", i + 1, k + 1, config_cp.xipcam[i][k]);
				write_log(log_msg);
			}
		}
	}
	if (rec_no <= 0) {
		sprintf(log_msg, "Read config_cp error\n"); write_log(log_msg);
		free(raw);
		return RESULT_FAIL;
	}

	// step7: initial UDP
	bool udp_status = init_udp();
	if (udp_status == false) {
		sprintf(log_msg, "init_udp: error\n"); write_log(log_msg);
		free(raw);
		exit(-1);
	}
	write_log("init_udp ok\n");

	free(raw);

	return RESULT_GOOD;
}

int minc_pms_get_program_version(char *version_str)
{
	strcpy(version_str, VERSION);
	return RESULT_GOOD;
}

int minc_pms_query_availablelot(struct availablelot_value_type *availablelot_value)
{
	char raw[1024];
	struct available_lot_type available_lot_local;
	char log_msg[4096];

	// check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	int rec_no = QueryDatabase(postgresDB_master, "data.availablelot", "id=0", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_availablelot(raw, &available_lot_local);		
		availablelot_value->totallot = available_lot_local.totallot;
		availablelot_value->season_reserved = available_lot_local.season_reserved;
		availablelot_value->total_occupied = available_lot_local.total_occupied;
		availablelot_value->season_occupied = available_lot_local.season_occupied;
		availablelot_value->hourly_occupied = available_lot_local.hourly_occupied;
		return RESULT_GOOD;
	}
	return RESULT_FAIL;
}

int minc_pms_update_availablelot(struct availablelot_value_type *availablelot_value_local)
{
	char modified_time[50];
	char set_str[255];
	char ask_str[255];
	char raw[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	get_detail_currenttime_for_bcd(modified_time);
	sprintf(ask_str, "id=0");
	sprintf(set_str, "modified_time='%s',total_occupied='%d'", modified_time, availablelot_value_local->total_occupied);

	// write into master database
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "data.availablelot", set_str, ask_str);
		usleep(10000);
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_query_season(char *inp_datetime_yyyymm_start, char *inp_datetime_yyyymm_stop, char *inp_platenum, char *inp_phonenum, struct season_rec *out_season)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search season with assigned condition
	strcpy(query_str, "");
	bool first_param_flag = false;
	if (strcmp(inp_platenum, "") != 0) {
		sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
		first_param_flag = true;
	}
	if (first_param_flag == false) {
		if (strcmp(inp_phonenum, "") != 0) {
			sprintf(query_str, "phonenum='%s'", inp_phonenum);
			first_param_flag = true;
		}
	}
	else {
		if (strcmp(inp_phonenum, "") != 0) sprintf(query_str, "%s and phonenum='%s'", query_str, inp_phonenum);
	}
	if (first_param_flag == false) {
		if (strcmp(inp_datetime_yyyymm_start, "") != 0) {
			sprintf(query_str, "monthid>='%s'", inp_datetime_yyyymm_start);
			first_param_flag = true;
		}
	}
	else {
		if (strcmp(inp_datetime_yyyymm_start, "") != 0) sprintf(query_str, "%s and monthid>='%s'", query_str, inp_datetime_yyyymm_start);
	}
	if (first_param_flag == false) {
		if (strcmp(inp_datetime_yyyymm_stop, "") != 0) sprintf(query_str, "monthid<='%s'", inp_datetime_yyyymm_stop);
		first_param_flag = true;
	}
	else {
		if (strcmp(inp_datetime_yyyymm_stop, "") != 0) sprintf(query_str, "%s and monthid<='%s'", query_str, inp_datetime_yyyymm_stop);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	int rec_no = QueryDatabase(postgresDB_master, "data.season", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_season(raw + i * MAX_DATA_LEN, &out_season[i]);
	}
	free(raw);
	return rec_no;
}

int minc_pms_add_season(struct season_rec *inp_season)
{
	char modified_time[50];
	char dat_season[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: add database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(dat_season, "'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'", 					
					receipt_setting[0].carparkid,
					modified_time,
					inp_season->season_type,
					inp_season->platenum, 
					inp_season->etagnum,
					inp_season->phonenum, 
					inp_season->monthid,
					inp_season->validstart, inp_season->validend,
					inp_season->monthly_fee,
					inp_season->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "data.season", SEASON_HEADER, dat_season);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_del_season(int rid)
{
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "data.season", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_upd_season(struct season_rec *inp_season)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',season_type='%s',platenum='%s',etagnum='%s',phonenum='%s',monthid='%s',validstart='%s',validend='%s',monthly_fee='%s',comments='%s'", 
		modified_time,
		inp_season->season_type,
		inp_season->platenum,
		inp_season->etagnum,
		inp_season->phonenum,
		inp_season->monthid,
		inp_season->validstart,
		inp_season->validend,
		inp_season->monthly_fee,
		inp_season->comments);
	sprintf(ask_str, "id=%d", inp_season->id);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "data.season", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_query_movement(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct movement_rec *out_movement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "entry_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s0000000", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and entry_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "entry_time<='%s'", endtime_str);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and paid_status <> 'out' order by id desc", query_str);
	else							sprintf(query_str, "paid_status <> 'out' order by id desc", query_str);
	int rec_no = QueryDatabase(postgresDB_master, "data.movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_movement(raw + i * MAX_DATA_LEN, &out_movement[i]);
	}
	free(raw);
	return rec_no;
}

int minc_pms_add_movement(char *inp_entry_time, char *inp_platenum, char *inp_comments)
{
	char modified_time[50];
	char dat_movement[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: add database
	char img_pathname[200];
	char img_filename[200];
	char img_filename2[200];
	char pathstr[200];
	get_detail_currenttime_for_bcd(modified_time);	
	get_datecode_path_name((char *)"/lpr_data/data_input", img_pathname);
	Mat frame = Mat::zeros(Size(300, 200), CV_8UC3);
	frame.setTo(cv::Scalar(255, 255, 255));
	cv::putText(frame, inp_platenum, Point(75,125), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 2, 2);
	sprintf(img_filename2, "plateimage_ET%s_XT_c0_0_sE1_tH_%s_.jpg", inp_entry_time, inp_platenum);
	sprintf(img_filename, "%s/%s", img_pathname, img_filename2);
	imwrite(img_filename, frame);
	// copy image file to apm (for new add entry record)
	for (int i = 0; i < atoi(config_cp.acount); i++) {
		copy_file_remote(config_cp.apm[i], img_pathname, img_filename2);
	}
	// write movement records
	sprintf(dat_movement, "'%s','%s','%s','','E1','','%s','','hourly','','','','','','','','%s','%s'",
		receipt_setting[0].carparkid,
		modified_time,		
		inp_platenum,
		inp_entry_time,
		img_filename,
		inp_comments);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "data.movement", MOVEMENT_HEADER, dat_movement);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_del_movement(int rid)
{
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "data.movement", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_upd_movement(int rid, char *inp_entry_time, char *inp_platenum, char *inp_comments)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',entry_time='%s',platenum='%s',comments='%s'",
		modified_time,
		inp_entry_time,
		inp_platenum,
		inp_comments);
	sprintf(ask_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "data.movement", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_query_check(struct disp_check_rec *out_check)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search movement with assigned condition
	strcpy(query_str, "comments <> 'checked' and parked_type='hourly'");
	int rec_no = QueryDatabase(postgresDB_master, "data.movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	struct movement_rec movement_local;
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_movement(raw + i * MAX_DATA_LEN, &movement_local);
			out_check[i].id = movement_local.id;
			strcpy(out_check[i].platenum, movement_local.platenum);
			strcpy(out_check[i].car_image, movement_local.car_image);
		}
	}
	free(raw);
	return rec_no;
}

int minc_pms_upd_check(struct disp_check_rec *inp_check)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update movement
	get_detail_currenttime_for_bcd(modified_time);
	if (strcmp(inp_check->platenum, "ok") == 0) {
		sprintf(set_str, "modified_time='%s',comments='checked'", modified_time);
		sprintf(ask_str, "id=%d", inp_check->id);
		int  cnt = 0;
		bool status = false;
		while (status == false && cnt < 10) {
			status = UpdateDatabase(postgresDB_master, "data.movement", set_str, ask_str);
			usleep(10000);
			cnt++;
		}
		if (status == false) return RESULT_FAIL;
		else				 return RESULT_GOOD;
	}
	else {
		sprintf(set_str, "modified_time='%s',platenum='%s'", modified_time, inp_check->platenum);
		sprintf(ask_str, "id=%d", inp_check->id);
		int  cnt = 0;
		bool status = false;
		while (status == false && cnt < 10) {
			status = UpdateDatabase(postgresDB_master, "data.movement", set_str, ask_str);
			usleep(10000);
			cnt++;
		}
		if (status == false) return RESULT_FAIL;
		else				 return RESULT_GOOD;
	}
	return RESULT_GOOD;
}

int minc_pms_control(int control_id)
{
	int len;
	int stid;
	char udpstr[100];
	char log_msg[4096];

	switch (control_id) {
	case ID_E1_OPEN:
	case ID_E2_OPEN:
	case ID_E3_OPEN:
	case ID_E4_OPEN:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierOpen'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_e[stid]);
		break;

	case ID_X1_OPEN:
	case ID_X2_OPEN:
	case ID_X3_OPEN:
	case ID_X4_OPEN:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierOpen'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_x[stid]);
		break;

	case ID_E1_LOCK:
	case ID_E2_LOCK:
	case ID_E3_LOCK:
	case ID_E4_LOCK:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierLock'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_e[stid]);
		break;

	case ID_X1_LOCK:
	case ID_X2_LOCK:
	case ID_X3_LOCK:
	case ID_X4_LOCK:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierLock'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_x[stid]);
		break;

	case ID_E1_UNLOCK:
	case ID_E2_UNLOCK:
	case ID_E3_UNLOCK:
	case ID_E4_UNLOCK:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierUnLock'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_e[stid]);
		break;

	case ID_X1_UNLOCK:
	case ID_X2_UNLOCK:
	case ID_X3_UNLOCK:
	case ID_X4_UNLOCK:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'BarrierUnLock'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_x[stid]);
		break;

	case ID_E1_REBOOT:
	case ID_E2_REBOOT:
	case ID_E3_REBOOT:
	case ID_E4_REBOOT:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'Reboot'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_e[stid]);
		break;

	case ID_X1_REBOOT:
	case ID_X2_REBOOT:
	case ID_X3_REBOOT:
	case ID_X4_REBOOT:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'Reboot'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_x[stid]);
		break;

	case ID_APM1_REBOOT:
	case ID_APM2_REBOOT:
	case ID_APM3_REBOOT:
	case ID_APM4_REBOOT:
		stid = (int)(control_id / 10);
		strcpy(udpstr, "{'Flag':'Station','Command':'Reboot'}");
		len = strlen(udpstr);
		udp_send(server_sockfd, udpstr, len+1, &send_to_apm[stid]);
		break;

	case ID_PMS_REBOOT:
		strcpy(udpstr, "sudo reboot -f");
		system(udpstr);
		break;
	}
	return RESULT_GOOD;
}

int minc_pms_open_apm(char *password, int control_id)
{
	char raw[4096];
	char log_msg[4096];
	bool status;
	struct payment_login_rec payment_login;

	// step1: verify password
	int rec_no = QueryDatabase(postgresDB_master, "cfg.payment_login", "", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_payment_login(raw, &payment_login);
	}
	if (rec_no <= 0) {
		sprintf(log_msg, "Read payment_login database error\n"); write_log(log_msg);
		return RESULT_FAIL;
	}
	char db_passwd[256];
	sprintf(db_passwd, "%s%s", payment_login.userid, payment_login.passcode);
	if (strcmp(db_passwd, password) != 0) {
		sprintf(log_msg, "Read payment_login password error\n"); write_log(log_msg);
		return RESULT_FAIL;
	}
	sprintf(log_msg, "read payment_login ok\n"); write_log(log_msg);

	// step2: open apm
	switch (control_id) {
	case ID_APM1_OPEN_A:
		status = open_apm_lock(APM1_ID, APM_DISP_IO);
		break;

	case ID_APM1_OPEN_B:
		status = open_apm_lock(APM1_ID, APM_CASH_IO);
		break;

	case ID_APM2_OPEN_A:
		status = open_apm_lock(APM2_ID, APM_DISP_IO);
		break;

	case ID_APM2_OPEN_B:
		status = open_apm_lock(APM2_ID, APM_CASH_IO);
		break;

	case ID_APM3_OPEN_A:
		status = open_apm_lock(APM3_ID, APM_DISP_IO);
		break;

	case ID_APM3_OPEN_B:
		status = open_apm_lock(APM3_ID, APM_CASH_IO);
		break;

	case ID_APM4_OPEN_A:
		status = open_apm_lock(APM4_ID, APM_DISP_IO);
		break;

	case ID_APM4_OPEN_B:
		status = open_apm_lock(APM4_ID, APM_CASH_IO);
		break;
	}
	return status;
}

int minc_pms_query_hopper(char *apm_ip, struct disp_hopper_rec *out_hopper)
{
	char query_str[256];
	char raw [1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search database
	struct hopper_rec hopper_data;
	sprintf(query_str, "ip='%s'", apm_ip);
	int rec_no = QueryDatabase(postgresDB_master, "data.log_hopper", query_str, QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_hopper(raw, &hopper_data);
		out_hopper->h50   = atoi(hopper_data.h50);
		out_hopper->h10   = atoi(hopper_data.h10);
		out_hopper->h5    = atoi(hopper_data.h5);
		out_hopper->receipt = atoi(hopper_data.receipt);
	}
	return RESULT_GOOD;
}

int minc_pms_upd_hopper(char *apm_ip, struct disp_hopper_rec *inp_hopper)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	char h50[50];
	char h10[50];
	char h5[50];
	char receipt[50];

	// step2: update database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',h50='%d',h10='%d',h5='%d',receipt='%d'",
		modified_time,
		inp_hopper->h50,
		inp_hopper->h10,
		inp_hopper->h5,
		inp_hopper->receipt);
	sprintf(ask_str, "ip='%s'", apm_ip);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "data.log_hopper", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_query_finance(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, struct disp_finance_summary_rec *disp_finance_summary, struct disp_finance_detail_rec *disp_finance_detail)
{
	int rec_no;
	char query_str[256];
	char starttime_str[100];
	char endtime_str[100];
	char log_msg[4096];

	memset((struct disp_finance_summary_rec *)disp_finance_summary, 0, sizeof(struct disp_finance_summary_rec));

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	char *raw = (char *)malloc(MAX_RECORDS * 100 * MAX_DATA_LEN);

	// step2: read receipt database
	struct receipt_data_rec receipt_data_local;
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s00000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "receipt_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s00000", inp_datetime_yymmddhh_stop);
		sprintf(query_str, "%s and receipt_time<='%s'", query_str, endtime_str);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and flag='used' order by id desc", query_str);//used
	else							sprintf(query_str, "flag='used' order by id desc");//used
	rec_no = QueryDatabase(postgresDB_master, "data.receipt", query_str, QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_receipt_data(raw + i * MAX_DATA_LEN, &receipt_data_local);
			disp_finance_detail[i].id = receipt_data_local.id;
			strcpy(disp_finance_detail[i].receiptid, receipt_data_local.receiptid);
			strcpy(disp_finance_detail[i].buyer_taxnum, receipt_data_local.buyer_taxnum);
			strcpy(disp_finance_detail[i].receipt_time, receipt_data_local.receipt_time);
			disp_finance_detail[i].receipt_fee = atoi(receipt_data_local.receipt_fee);
			disp_finance_detail[i].notax_fee = atoi(receipt_data_local.notax_fee);
			disp_finance_detail[i].vat_fee = atoi(receipt_data_local.vat_fee);

			disp_finance_summary->total_revenue += atoi(receipt_data_local.receipt_fee);

#if 0
			// query log_payment to get coin count
			struct log_payment_rec log_payment_local;
			sprintf(query_str, "paymentid='%s'", receipt_data_local.receiptid);
			int rec_no2 = QueryDatabase(postgresDB_master, "data.log_payment", query_str, QUERY_MODE_LATEST, raw);
			if (rec_no2 == 1) {
				read_log_payment(raw, &log_payment_local);
				//disp_finance_summary->total_revenue += atoi(log_payment_local.paid_fee);
				disp_finance_summary->d1000 += atoi(log_payment_local.d1000);
				disp_finance_summary->d500 += atoi(log_payment_local.d500);
				disp_finance_summary->d200 += atoi(log_payment_local.d200);
				disp_finance_summary->d100 += atoi(log_payment_local.d100);
				disp_finance_summary->d50 += atoi(log_payment_local.d50);
				disp_finance_summary->d10 += atoi(log_payment_local.d10);
				disp_finance_summary->d5 += atoi(log_payment_local.d5);
				disp_finance_summary->h50 += atoi(log_payment_local.h50);
				disp_finance_summary->h10 += atoi(log_payment_local.h10);
			}
			else {
				sprintf(log_msg, "minc_pms_query_finance: paymentid=%s not found\n", receipt_data_local.receiptid);
				write_log(log_msg);
			}
#endif
		}
	}

	// step3: query log_payment to get coin count
	struct log_payment_rec log_payment_local;
	strcpy(query_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(query_str, "paid_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(query_str, "%s and paid_time<='%s'", query_str, endtime_str);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	else							sprintf(query_str, "order by id desc");
	int rec_no2 = QueryDatabase(postgresDB_master, "data.log_payment", query_str, QUERY_MODE_ALL, raw);
	if (rec_no2 > 0) {
		for (int i = 0; i < rec_no2; i++) {
			read_log_payment(raw + i * MAX_DATA_LEN, &log_payment_local);
			//disp_finance_summary->total_revenue += atoi(log_payment_local.paid_fee);
			disp_finance_summary->d1000 += atoi(log_payment_local.d1000);
			disp_finance_summary->d500 += atoi(log_payment_local.d500);
			disp_finance_summary->d200 += atoi(log_payment_local.d200);
			disp_finance_summary->d100 += atoi(log_payment_local.d100);
			disp_finance_summary->d50 += atoi(log_payment_local.d50);
			disp_finance_summary->d10 += atoi(log_payment_local.d10);
			disp_finance_summary->d5 += atoi(log_payment_local.d5);
			disp_finance_summary->h50 += atoi(log_payment_local.h50);
			disp_finance_summary->h10 += atoi(log_payment_local.h10);
		}
	}

	free(raw);
	return rec_no;
}

int minc_pms_query_All_finance(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, struct disp_finance_summary_rec *disp_finance_summary, struct disp_finance_detail_rec *disp_finance_detail)
{
	int rec_no;
	char query_str[256];
	char starttime_str[100];
	char endtime_str[100];
	char log_msg[4096];

	memset((struct disp_finance_summary_rec *)disp_finance_summary, 0, sizeof(struct disp_finance_summary_rec));

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	char *raw = (char *)malloc(MAX_RECORDS * 100 * MAX_DATA_LEN);

	// step2: read receipt database
	struct receipt_data_rec receipt_data_local;
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s00000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "receipt_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s00000", inp_datetime_yymmddhh_stop);
		sprintf(query_str, "%s and receipt_time<='%s'", query_str, endtime_str);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s flag='used' order by id desc", query_str);//used
	else							sprintf(query_str, "flag='used' order by id desc");//used
	rec_no = QueryDatabase(postgresDB_master, "data.receipt", query_str, QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_receipt_data(raw + i * MAX_DATA_LEN, &receipt_data_local);
			disp_finance_detail[i].id = receipt_data_local.id;
			strcpy(disp_finance_detail[i].receiptid, receipt_data_local.receiptid);
			strcpy(disp_finance_detail[i].buyer_taxnum, receipt_data_local.buyer_taxnum);
			strcpy(disp_finance_detail[i].receipt_time, receipt_data_local.receipt_time);
			disp_finance_detail[i].receipt_fee = atoi(receipt_data_local.receipt_fee);
			disp_finance_detail[i].notax_fee = atoi(receipt_data_local.notax_fee);
			disp_finance_detail[i].vat_fee = atoi(receipt_data_local.vat_fee);

			disp_finance_summary->total_revenue += atoi(receipt_data_local.receipt_fee);

#if 0
			// query log_payment to get coin count
			struct log_payment_rec log_payment_local;
			sprintf(query_str, "paymentid='%s'", receipt_data_local.receiptid);
			int rec_no2 = QueryDatabase(postgresDB_master, "data.log_payment", query_str, QUERY_MODE_LATEST, raw);
			if (rec_no2 == 1) {
				read_log_payment(raw, &log_payment_local);
				//disp_finance_summary->total_revenue += atoi(log_payment_local.paid_fee);
				disp_finance_summary->d1000 += atoi(log_payment_local.d1000);
				disp_finance_summary->d500 += atoi(log_payment_local.d500);
				disp_finance_summary->d200 += atoi(log_payment_local.d200);
				disp_finance_summary->d100 += atoi(log_payment_local.d100);
				disp_finance_summary->d50 += atoi(log_payment_local.d50);
				disp_finance_summary->d10 += atoi(log_payment_local.d10);
				disp_finance_summary->d5 += atoi(log_payment_local.d5);
				disp_finance_summary->h50 += atoi(log_payment_local.h50);
				disp_finance_summary->h10 += atoi(log_payment_local.h10);
			}
			else {
				sprintf(log_msg, "minc_pms_query_finance: paymentid=%s not found\n", receipt_data_local.receiptid);
				write_log(log_msg);
			}
#endif
		}
	}

	// step3: query log_payment to get coin count
	struct log_payment_rec log_payment_local;
	strcpy(query_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(query_str, "paid_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(query_str, "%s and paid_time<='%s'", query_str, endtime_str);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	else							sprintf(query_str, "order by id desc");
	int rec_no2 = QueryDatabase(postgresDB_master, "data.log_payment", query_str, QUERY_MODE_ALL, raw);
	if (rec_no2 > 0) {
		for (int i = 0; i < rec_no2; i++) {
			read_log_payment(raw + i * MAX_DATA_LEN, &log_payment_local);
			//disp_finance_summary->total_revenue += atoi(log_payment_local.paid_fee);
			disp_finance_summary->d1000 += atoi(log_payment_local.d1000);
			disp_finance_summary->d500 += atoi(log_payment_local.d500);
			disp_finance_summary->d200 += atoi(log_payment_local.d200);
			disp_finance_summary->d100 += atoi(log_payment_local.d100);
			disp_finance_summary->d50 += atoi(log_payment_local.d50);
			disp_finance_summary->d10 += atoi(log_payment_local.d10);
			disp_finance_summary->d5 += atoi(log_payment_local.d5);
			disp_finance_summary->h50 += atoi(log_payment_local.h50);
			disp_finance_summary->h10 += atoi(log_payment_local.h10);
		}
	}

	free(raw);
	return rec_no;
}


int minc_pms_get_valid_date(char *monthid, char *out_valid_start, char *out_valid_end)
{
	struct	tm t;
	char tmpstr[100];
	char log_msg[4096];

	strcpy(tmpstr, monthid); tmpstr[4] = '\0';

	int yyyy = atoi(tmpstr);
	int mm   = atoi(&monthid[4]);

	t.tm_year = yyyy - 1900;
	t.tm_mon  = mm-1;
	t.tm_mday = 1;
	t.tm_hour = 0;
	t.tm_min  = 0;
	t.tm_sec  = 0;
	time_t ct1 = mktime(&t);

	t.tm_year = yyyy - 1900;
	t.tm_mon = mm;
	t.tm_mday = 1;
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	time_t ct2 = mktime(&t); ct2--;

	get_currenttime_for_bcd(ct1, out_valid_start);
	get_currenttime_for_bcd(ct2, out_valid_end);

	return RESULT_GOOD;
}

int minc_pms_write_led_message(int ledid, char *message)
{
	int p = 0;
	char textdata[100][30];
	char modified_time[50];
	char dat_led[1024];

	if (ledid == -1) {
		strcpy((char *)textdata[p++], "開始辨識");
		strcpy((char *)textdata[p++], "請關大燈");
		strcpy((char *)textdata[p++], "辨識失敗");
		strcpy((char *)textdata[p++], "再次辨識");
		strcpy((char *)textdata[p++], "歡迎光臨");
		strcpy((char *)textdata[p++], "月票進場");
		strcpy((char *)textdata[p++], "計時進場");
		strcpy((char *)textdata[p++], "月票出場");
		strcpy((char *)textdata[p++], "計時出場");
		strcpy((char *)textdata[p++], "謝謝惠顧");
		strcpy((char *)textdata[p++], "逾時出場");
		strcpy((char *)textdata[p++], "尚未付費");
		strcpy((char *)textdata[p++], "敬請進場");
		strcpy((char *)textdata[p++], "敬請出場");
		strcpy((char *)textdata[p++], "月票過期");
		strcpy((char *)textdata[p++], "車位已滿");
		strcpy((char *)textdata[p++], "敬請等待");
		strcpy((char *)textdata[p++], "系統維護");
		strcpy((char *)textdata[p++], "車頭離柵欄兩公尺");

		get_detail_currenttime_for_bcd(modified_time);
		for (int i = 0; i < p; i++) {
			char utf8_char[100];
			memset(utf8_char, 0, 100);
			b2u(textdata[i], utf8_char);
			sprintf(dat_led, "%d, '','%s','%d','%s',''", i, modified_time, i, utf8_char);
			bool status = InsertDatabase(postgresDB_master, "cfg.led", LED_HEADER, dat_led);
		}
	}
	else {
		get_detail_currenttime_for_bcd(modified_time);
		char utf8_char[100];
		memset(utf8_char, 0, 100);
		b2u(message, utf8_char);
		sprintf(dat_led, "%d, '','%s','%d','%s',''", ledid, modified_time, ledid, utf8_char);
		bool status = InsertDatabase(postgresDB_master, "cfg.led", LED_HEADER, dat_led);
	}

	return RESULT_GOOD;
} 

int minc_pms_query_log_movement(char *station_name, char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_movement_rec *out_log_movement)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: search log_movement with assigned condition
	char starttime_str[100];
	char endtime_str[100];
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s0000000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "station_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s0000000", inp_datetime_yymmddhh_stop);
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and station_time<='%s'", query_str, endtime_str);
		else							sprintf(query_str, "entry_time<='%s'", endtime_str);
	}
	if (strcmp(station_name, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and station_name LIKE '%%%s%%'", query_str, station_name);
		else							sprintf(query_str, "station_name LIKE '%%%s%%'", station_name);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	else							sprintf(query_str, "", query_str);
	int rec_no = QueryDatabase(postgresDB_master, "data.log_movement", query_str, QUERY_MODE_ALL, raw);

	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_movement(raw + i * MAX_DATA_LEN, &out_log_movement[i]);
	}
	free(raw);
	return rec_no;
}

int minc_pms_query_log_payment(char *inp_datetime_yymmddhh_start, char *inp_datetime_yymmddhh_stop, char *inp_platenum, struct log_payment_rec *out_log_payment)
{
	char query_str[256];
	char starttime_str[100];
	char endtime_str[100];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	char *raw = (char *)malloc(MAX_RECORDS * 100 * MAX_DATA_LEN);

	// step2: search log_payment with assigned condition
	struct receipt_data_rec receipt_data_local;
	strcpy(query_str, "");
	strcpy(starttime_str, "");
	strcpy(endtime_str, "");
	if (strcmp(inp_datetime_yymmddhh_start, "") != 0) {
		sprintf(starttime_str, "%s00000", inp_datetime_yymmddhh_start);
		sprintf(query_str, "paid_time>='%s'", starttime_str);
	}
	if (strcmp(inp_datetime_yymmddhh_stop, "") != 0) {
		sprintf(endtime_str, "%s00000", inp_datetime_yymmddhh_stop);
		sprintf(query_str, "%s and paid_time<='%s'", query_str, endtime_str);
	}
	if (strcmp(inp_platenum, "") != 0) {
		if (strcmp(query_str, "") != 0) sprintf(query_str, "%s and platenum LIKE '%%%s%%'", query_str, inp_platenum);
		else							sprintf(query_str, "platenum LIKE '%%%s%%'", inp_platenum);
	}
	if (strcmp(query_str, "") != 0) sprintf(query_str, "%s order by id desc", query_str);
	else							sprintf(query_str, "", query_str);
	int rec_no = QueryDatabase(postgresDB_master, "data.log_payment", query_str, QUERY_MODE_ALL, raw);
	
	// step3: output data
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++)
			read_log_payment(raw + i * MAX_DATA_LEN, &out_log_payment[i]);
	}
	free(raw);
	return rec_no;
}

int minc_pms_write_csv_finance(char *csv_filename, int len, struct disp_finance_detail_rec *inp_disp_finance_detail)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,receiptid,receipt_time,receipt_fee,buyer_taxnum,notax_fee,vat_fee\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%d,%s,%d,%d,\n",
			i,
			inp_disp_finance_detail[i].receiptid,
			inp_disp_finance_detail[i].receipt_time,
			inp_disp_finance_detail[i].receipt_fee,
			inp_disp_finance_detail[i].buyer_taxnum,
			inp_disp_finance_detail[i].notax_fee,
			inp_disp_finance_detail[i].vat_fee);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}

int minc_pms_write_csv_log_movement(char *csv_filename, int len, struct log_movement_rec *inp_log_movement)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,platenum,etagnum,station_name,station_time,parked_type,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s,%s,\n",
			i,
			inp_log_movement[i].platenum,
			inp_log_movement[i].etagnum,
			inp_log_movement[i].station_name,
			inp_log_movement[i].station_time,
			inp_log_movement[i].parked_type,
			inp_log_movement[i].comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}

int minc_pms_write_csv_log_payment(char *csv_filename, int len, struct log_payment_rec *inp_log_payment)
{
	char fullfilename[300];
	char data[1000];

	// step1: open csv filename
	sprintf(fullfilename, "/lpr_data/csv/%s", csv_filename);
	std::ofstream csvfile;
	csvfile.open(fullfilename);

	// step2: write header
	csvfile << "id,paymentid,platenum,type,paid_fee,paid_time,d100,d50,d10,d5,h50,h10,flag,comments\n";

	// step3: write data
	for (int i = 0; i < len; i++) {
		sprintf(data, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n",
			i,
			inp_log_payment[i].paymentid,
			inp_log_payment[i].platenum,
			inp_log_payment[i].type,
			inp_log_payment[i].paid_fee,
			inp_log_payment[i].paid_time,
			inp_log_payment[i].d100,
			inp_log_payment[i].d50,
			inp_log_payment[i].d10,
			inp_log_payment[i].d5,
			inp_log_payment[i].h50,
			inp_log_payment[i].h10,
			inp_log_payment[i].flag,
			inp_log_payment[i].comments);
		csvfile << data;
	}

	csvfile.close();
	return RESULT_GOOD;
}

int minc_pms_query_tariff(struct tariff_value_rec *tariff_value)
{
	char raw[4096];
	char log_msg[4096];
	struct tariff_rec tariff;

	// check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	sprintf(log_msg, "minc_pms_query_tariff: verify_database_connection ok\n"); write_log(log_msg);

	int rec_no = QueryDatabase(postgresDB_master, "cfg.tariff", "", QUERY_MODE_LATEST, raw);
	if (rec_no > 0) {
		read_tariff(raw, &tariff);
		tariff_value->season_fee_val = atof(tariff.season_fee);
		tariff_value->hourly_fee_val = atof(tariff.hourly_fee);
		tariff_value->first_duration_val = atof(tariff.first_duration);
		tariff_value->second_duration_val = atof(tariff.second_duration);
		tariff_value->daily_max_val = atof(tariff.daily_max);
		tariff_value->first_duration_val = tariff_value->first_duration_val / 60.0;
		tariff_value->second_duration_val = tariff_value->second_duration_val / 60.0;
		tariff_value->grace_duration_val = atof(tariff.grace_duration) / 60.0;
	}
	else if (rec_no <= 0) {
		sprintf(log_msg, "minc_pms_query_tariff: error\n"); write_log(log_msg);
		return RESULT_FAIL;
	}
	return RESULT_GOOD;
}

int minc_pms_update_tariff(struct tariff_value_rec *tariff_value)
{
	char modified_time[50];
	char set_str[255];
	char ask_str[255];
	char log_msg[4096];

	tariff_value->first_duration_val = tariff_value->first_duration_val  * 60.0;
	tariff_value->second_duration_val = tariff_value->second_duration_val * 60.0;
	tariff_value->grace_duration_val = tariff_value->grace_duration_val  * 60.0;

	sprintf(log_msg, "minc_update_tariff: season_fee=%d hourly_fee=%d first_duration=%d second_duration=%d daily_max=%d grace_duration=%d\n",
		(int)tariff_value->season_fee_val,
		(int)tariff_value->hourly_fee_val,
		(int)tariff_value->first_duration_val,
		(int)tariff_value->second_duration_val,
		(int)tariff_value->daily_max_val,
		(int)tariff_value->grace_duration_val);
	write_log(log_msg);

	// check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	sprintf(log_msg, "minc_pms_update_tariff: verify_database_connection ok\n"); write_log(log_msg);

	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',season_fee='%d',hourly_fee='%d',first_duration='%d',second_duration='%d',daily_max='%d',grace_duration='%d'",
		modified_time,
		(int)tariff_value->season_fee_val,
		(int)tariff_value->hourly_fee_val,
		(int)tariff_value->first_duration_val,
		(int)tariff_value->second_duration_val,
		(int)tariff_value->daily_max_val,
		(int)tariff_value->grace_duration_val);
	sprintf(ask_str, "id=0");
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "cfg.tariff", set_str, ask_str);
		usleep(10000);
		verify_database_connection();
		cnt++;
	}
	if (status == false) {
		sprintf(log_msg, "minc_pms_update_tariff: cfg.tariff update error\n");
		write_log(log_msg);
		return RESULT_FAIL;
	}
	sprintf(log_msg, "minc_pms_update_tariff: cfg.tariff update success(%d)\n", cnt);
	write_log(log_msg);
	return RESULT_GOOD;
}

int minc_pms_query_parkingfee(struct parkingfee_rec *parkingfee_data)
{
	char log_msg[4096];

	// check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	sprintf(log_msg, "minc_pms_query_parkingfee: verify_database_connection ok\n"); write_log(log_msg);

	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	int rec_no = QueryDatabase(postgresDB_master, "cfg.parkingfee", "", QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_parkingfee((raw + i * MAX_DATA_LEN), &parkingfee_data[i]);
		}
	}
	return rec_no;
}

int minc_pms_update_parkingfee(int rid, struct parkingfee_rec *parkingfee_data)
{
	char modified_time[50];
	char set_str[255];
	char ask_str[255];
	char log_msg[4096];

	// check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	sprintf(log_msg, "minc_pms_update_parkingfee: verify_database_connection ok\n"); write_log(log_msg);

	get_detail_currenttime_for_bcd(modified_time);
	sprintf(set_str, "modified_time='%s',weekday_index='%s',starttime_hhmmss='%s',endtime_hhmmss='%s',hourly_fee='%s'",
		modified_time,
		parkingfee_data->weekday_index,
		parkingfee_data->starttime_hhmmss,
		parkingfee_data->endtime_hhmmss,
		parkingfee_data->hourly_fee);
	sprintf(ask_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "cfg.parkingfee", set_str, ask_str);
		usleep(10000);
		verify_database_connection();
		cnt++;
	}
	if (status == false) {
		sprintf(log_msg, "minc_pms_update_parkingfee: cfg.parkingfee update error\n");
		write_log(log_msg);
		return RESULT_FAIL;
	}
	sprintf(log_msg, "minc_pms_update_parkingfee: cfg.parkingfee update success(%d)\n", cnt);
	write_log(log_msg);
	return RESULT_GOOD;
}

int minc_pms_del_parkingfee(int rid)
{
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database
	sprintf(query_str, "id=%d", rid);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeletetDatabase(postgresDB_master, "cfg.parkingfee", query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_add_parkingfee(struct parkingfee_rec *parkingfee_data)
{
	char modified_time[50];
	char dat_parkingfee[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: add database
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(dat_parkingfee, "'%s','%s','%s','%s','%s','%s','%s'",
		parkingfee_data->carparkid,
		modified_time,
		parkingfee_data->weekday_index,
		parkingfee_data->starttime_hhmmss,
		parkingfee_data->endtime_hhmmss,
		parkingfee_data->hourly_fee,
		parkingfee_data->comments);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB_master, "cfg.parkingfee", PARKINGFEE_HEADER, dat_parkingfee);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pms_import_season(char *season_csv_filename)
{
	FILE *fp;
	char log_msg[4096];

	// read csv file
	fp = fopen(season_csv_filename, "r");
	if (fp == NULL) {
		sprintf(log_msg, "invoice csv file not found\n"); write_log(log_msg);
		return RESULT_FAIL;
	}

	char *ptr = (char *)malloc(200 * 500);

	char tmpstr[5000];
	// read header (dummy)
	fgets(tmpstr, 5000, fp);

	struct season_rec inp_season;

	// read content
	while (!feof(fp)) {
		fgets(tmpstr, 5000, fp);
		int len = strlen(tmpstr);
		int pno = splitstr(tmpstr, len, ',', '{', ';', '}', '=', ptr, 500);

		sprintf(log_msg, "process data: %s\n", tmpstr); write_log(log_msg);

		// check format
		if (pno != 8) {
			sprintf(log_msg, "cvs format error\n"); write_log(log_msg);
			continue;
		}

		// prepare data
		strcpy(inp_season.season_type, ptr);
		strcpy(inp_season.platenum, ptr + 1 * 500);
		strcpy(inp_season.etagnum, ptr + 2 * 500);
		strcpy(inp_season.phonenum, ptr + 3 * 500);
		strcpy(inp_season.monthid, ptr + 4 * 500);
		strcpy(inp_season.validstart, ptr + 5 * 500);
		strcpy(inp_season.validend, ptr + 6 * 500);
		strcpy(inp_season.comments, ptr + 7 * 500);

		bool status = minc_pms_add_season(&inp_season);
		if (status == RESULT_FAIL) {
			sprintf(log_msg, "add season failed\n"); 
			write_log(log_msg);
		}
	}
	return RESULT_GOOD;
}

int minc_pms_import_receipt(char *receipt_csv_filename)
{
	FILE *fp;
	bool receipt_matched_flag;
	char log_msg[4096];
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);

	// read csv file
	fp = fopen(receipt_csv_filename, "r");
	if (fp == NULL) {
		sprintf(log_msg, "invoice csv file not found\n"); write_log(log_msg);
		return RESULT_FAIL;
	}

	char *ptr = (char *)malloc(200 * 500);
	char seller_taxnum[100];
	char datecode[200];
	char invoice_header[100];
	char invoice_stnum[100];
	char invoice_spnum[100];

	//87019370, 07, 一般稅額計算, 109 / 01 ~109 / 02, YW, 43485750, 43486249
	char tmpstr[5000];
	// read header (dummy)
	fgets(tmpstr, 5000, fp);

	// read content
	while (!feof(fp)) {
		fgets(tmpstr, 5000, fp);
		int len = strlen(tmpstr);
		int pno = splitstr(tmpstr, len, ',', '{', ' ', '}', '=', ptr, 500);

		sprintf(log_msg, "process data: %s\n", tmpstr); write_log(log_msg);

		// check format
		if (pno != 7) {
			sprintf(log_msg, "cvs format error\n"); write_log(log_msg);
			continue;
		}

		//extract information: 87019385, 07, 一般稅額計算, 109 / 01 ~109 / 02, YW, 43505750, 43510249
		strcpy(seller_taxnum, ptr);
		strcpy(datecode, ptr + 3 * 500);
		strcpy(invoice_header, ptr + 4 * 500);
		strcpy(invoice_stnum, ptr + 5 * 500);
		strcpy(invoice_spnum, ptr + 6 * 500);

		// check whether tax number matched with receipt_setting database
		receipt_matched_flag = false;
		int  matched_index = 0;
		for (int i = 0; i < total_receipt_setting_count; i++) {
			if (strcmp(seller_taxnum, receipt_setting[i].seller_taxnum) == 0) {
				receipt_matched_flag = true;
				matched_index = i;
				break;
			}
		}
		if (receipt_matched_flag == false) {
			sprintf(log_msg, "seller taxnum error\n"); write_log(log_msg);
			continue;
		}

		// write blank receipts
		char m1[10];
		char m2[10];
		char months[20];
		strncpy(m1, &datecode[4], 2); m1[2] = '\0';
		strncpy(m2, &datecode[11], 2);  m2[2] = '\0';
		sprintf(months, "%s-%s", m1, m2);
		
		//add query invoice_stnum		
		
		sprintf(query_str, "receiptid LIKE '%%%s%%'", invoice_stnum); 
		//sprintf(query_str, "receiptid='%s'", invoice_stnum);
		int rec_no = QueryDatabase(postgresDB_master, "data.receipt", query_str, QUERY_MODE_ALL, raw);

		if (rec_no == 0) {
			int stnum = atoi(invoice_stnum);
			int spnum = atoi(invoice_spnum);
			for (int i = stnum; i <= spnum; i++) {
				char modified_time[50];
				char receiptid[50];
				char dat_receipt[1024];
				sprintf(receiptid, "%s%08d", invoice_header, i);
				get_detail_currenttime_for_bcd(modified_time);
				sprintf(dat_receipt, "'%s','%s','%s','','%s','','','','','','','','','%s','',''",
					receipt_setting[matched_index].carparkid,
					modified_time,
					receiptid,
					months,
					receipt_setting[matched_index].seller_taxnum);
				bool status = InsertDatabase(postgresDB_master, "data.receipt", RECEIPT_HEADER, dat_receipt);
				sprintf(log_msg, "[%d]: %s status=%d\n", i - stnum, receiptid, status); write_log(log_msg);
				if (status == false) {
					fclose(fp);
					free(ptr);
					return RESULT_FAIL;
				}
			}
		

		}
		else
			 continue;
	}
	fclose(fp);
	free(ptr);
	if (receipt_matched_flag == false) return RESULT_FAIL;
	return RESULT_GOOD;
}

int minc_pms_query_unused_receipt(char *monthid, struct disp_finance_detail_rec *disp_finance_detail)
{
	int rec_no;
	char query_str[256];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	char *raw = (char *)malloc(MAX_RECORDS * 100 * MAX_DATA_LEN);

	// step2: read receipt database
	struct receipt_data_rec receipt_data_local;
	sprintf(query_str, "months='%s' and flag <> 'used' order by id desc", monthid);

	rec_no = QueryDatabase(postgresDB_master, "data.receipt", query_str, QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_receipt_data(raw + i * MAX_DATA_LEN, &receipt_data_local);
			disp_finance_detail[i].id = receipt_data_local.id;
			strcpy(disp_finance_detail[i].receiptid, receipt_data_local.receiptid);
			strcpy(disp_finance_detail[i].buyer_taxnum, receipt_data_local.buyer_taxnum);
			strcpy(disp_finance_detail[i].receipt_time, receipt_data_local.receipt_time);
			disp_finance_detail[i].receipt_fee = atoi(receipt_data_local.receipt_fee);
			disp_finance_detail[i].notax_fee = atoi(receipt_data_local.notax_fee);
			disp_finance_detail[i].vat_fee = atoi(receipt_data_local.vat_fee);
		}
	}
	free(raw);
	return rec_no;
}

int minc_pgs_init_alarm(int total_lots, time_t *watchdog_time, struct data_pgs_rec *inp_data_pgs_rec)
{
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: delete database	
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = Deletet_All_Database(postgresDB_master, "pgs.data_alarm");
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;

	// step3: write data_alarm table (for monitoring)
	char dat_lot[1024];
	char modified_time[100];
	get_detail_currenttime_for_bcd(modified_time);
	for (int i = 0; i < total_lots; i++) {
		sprintf(dat_lot, "'%s','%s','%d','0','Fail',''",
			modified_time,
			inp_data_pgs_rec[i].lot_id,
			watchdog_time[i]);

		cnt = 0;
		status = false;
		while (status == false && cnt < 10) {
			status = InsertDatabase(postgresDB_master, "pgs.data_alarm", ALARM_HEADER, dat_lot);
			usleep(10000);
			cnt++;
		}
		if (status == false) return RESULT_FAIL;
	}
	return RESULT_GOOD;
}

int minc_pgs_update_alarm(bool update_watchdog_timer, char *lotid, char *status_str)
{
	char modified_time[50];
	char set_str[1024];
	char ask_str[1024];
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	// step2: update database
	time_t ct;
	time(&ct);
	get_detail_currenttime_for_bcd(modified_time);
	sprintf(ask_str, "lot_id='%s'", lotid);
	if(update_watchdog_timer == true) sprintf(set_str, "modified_time='%s',watchdog_time='%d',status='%s'", modified_time, ct, status_str);
	else                              sprintf(set_str, "modified_time='%s',status='%s'", modified_time, status_str);
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB_master, "pgs.data_alarm", set_str, ask_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int minc_pgs_read_alarm(struct data_alarm_rec *data_alarm)
{
	char query_str[256];
	char *raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);
	char log_msg[4096];

	// step1: check database connection
	if (verify_database_connection() == false) return SYSTEM_FAIL;

	int rec_no = QueryDatabase(postgresDB_master, "pgs.data_alarm", "", QUERY_MODE_ALL, raw);
	if (rec_no > 0) {
		for (int i = 0; i < rec_no; i++) {
			read_data_alarm(raw + i * MAX_DATA_LEN, &data_alarm[i]);
		}
		free(raw);
		return rec_no;
	}
	free(raw);
	return -1;
}