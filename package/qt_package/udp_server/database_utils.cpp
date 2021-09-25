#include "declaration.h"
#include "database_utils.h"

bool check_database_connect(int taskID, PGconn *postgresDB)
{
	bool   db_status;
	char   database_cmd_str[300];
	char   log_msg[4096];

	// check database connection	
	sprintf(database_cmd_str, "host=127.0.0.1 port=5435 dbname=pms_db user=cp password=cp123 connect_timeout=5");
	db_status = CheckDatabaseConnection(postgresDB);
	if (db_status == false) {
		postgresDB = ConnectDatabase(database_cmd_str);
		if (postgresDB == NULL) {
			postgresDB = ConnectDatabase(database_cmd_str);
			if (postgresDB == NULL) {
				sprintf(log_msg, "[%2d]: check_database_connect: ConnectDatabase error (Master)\n", taskID);
				write_log(log_msg);
				return false;
			}
		}
		sprintf(log_msg, "[%2d]: check_database_connect: Re-ConnectDatabase Success (Master)\n", taskID);
		write_log(log_msg);
	}
	return true;
}

void read_pgs_database(PGconn *postgresDB, vector<struct pgs_lot_type>*pgs_lot_data)
{
	// step1: read from datatable
	vector<struct datatable_record_rec> out_record_vecs;
	struct datatable_record_rec datatable_record_data;
	struct field_data_rec field_data;
	int ret = database_record_qry(postgresDB, "pgs.data_pgs", QUERY_MODE_ALL, "", "", &datatable_record_data, &out_record_vecs);
	for (int i = 0; i < out_record_vecs.size(); i++) {
		struct pgs_lot_type pgs_lot;
		int p = 0;
		pgs_lot.id = atoi(out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.modified_time,out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.lot_id,		out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.plate_no,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.camera_ip,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.led_id,		out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.controller_ip, out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.pageindex,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.floor_id,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.location_x,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.location_y,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.block_w,		out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.block_h,		out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.status,		out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.image_path,	out_record_vecs[i].fields[p++].value[0].c_str());
		strcpy(pgs_lot.comments,	out_record_vecs[i].fields[p++].value[0].c_str());
		pgs_lot_data->push_back(pgs_lot);
	}
}

void copy_pgs_database(PGconn *postgresDB)
{
	// step1: read from datatable
	vector<struct datatable_record_rec> out_record_vecs;
	struct datatable_record_rec datatable_record_data;
	struct field_data_rec field_data;
	int ret = database_record_qry(postgresDB, "pgs.data_pgs", QUERY_MODE_ALL, "", "", &datatable_record_data, &out_record_vecs);

	for (int i = 0; i < out_record_vecs.size(); i++) {
		struct datatable_record_rec datatable_record_data;
		struct field_data_rec field_data;
		char timestr[100];
		get_detail_currenttime_for_bcd(timestr);
		field_data.value.push_back(string(timestr)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[2].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[3].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[4].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[5].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[6].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[7].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[8].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[14].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(out_record_vecs[i].fields[15].value[0])); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(""); datatable_record_data.fields.push_back(field_data); field_data.value.clear();		
		int ret = database_record_add(postgresDB, "pgs.data_pgs", &datatable_record_data); 
	}
}

void update_pgs_database(PGconn *postgresDB, char *lotid, char *image_fullfilename, char *plate_no, char *result)
{
	char movement_time[200];
	char modified_time[100];

	// step1: get time information
	get_detail_currenttime_for_bcd(modified_time);
	char *ptr;
	ptr = strstr(image_fullfilename, "PT");
	if (ptr == NULL) ptr = strstr(image_fullfilename, "CT");
	if (ptr == NULL) strcpy(movement_time, modified_time);
	else {
		strcpy(movement_time, ptr + 2);
		movement_time[15] = '\0';
	}

	// step2: initial variables
	vector<struct datatable_record_rec> out_record_vecs;
	struct datatable_record_rec datatable_record_data;
	struct field_data_rec field_data;
	out_record_vecs.clear();
	datatable_record_data.fields.clear();
	field_data.value.clear();

	// step3: read from datatable
	int ret = database_record_qry(postgresDB, "pgs.data_pgs", QUERY_MODE_LATEST, "lot_id", lotid, &datatable_record_data, &out_record_vecs);
	if (ret < 0) return;

	// step4: update main database
	char status_str[30];
		 if (strcmp(result, RESULT_PGS_CARS) == 0)  strcpy(status_str, "car");
	else if (strcmp(result, RESULT_PGS_EMPTY) == 0) strcpy(status_str, "empty");
	else if (strcmp(result, RESULT_PGS_FAIL) == 0)  strcpy(status_str, "fail");
	else											strcpy(status_str, "block");
	strcpy(field_data.fieldname, "modified_time"); field_data.value.push_back(string(modified_time)); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	if (out_record_vecs[0].fields[9].value[0] != "block" && strcmp(status_str, "block") == 0) {
		strcpy(field_data.fieldname, "comments");
		field_data.value.push_back(out_record_vecs[0].fields[9].value[0]);
		datatable_record_data.fields.push_back(field_data);
		field_data.value.clear();
	}
	else if (strcmp(status_str, "block") != 0) {
		strcpy(field_data.fieldname, "comments");
		field_data.value.push_back("");
		datatable_record_data.fields.push_back(field_data);
		field_data.value.clear();
	}
	strcpy(field_data.fieldname, "status");	field_data.value.push_back(string(status_str));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "image_path");	field_data.value.push_back(string(image_fullfilename));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "plate_no"); field_data.value.push_back(string(plate_no)); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	ret = database_record_upd(postgresDB, "pgs.data_pgs", "lot_id", lotid, &datatable_record_data);
	datatable_record_data.fields.clear();

	// step5: write log_pgs_movement	
	char ptype[50];
	char platestr[50];
	bool state_changed = false;
	if ((strcmp(status_str, "empty") == 0 && strcmp(out_record_vecs[0].fields[9].value[0].c_str(), "car") == 0) ||
		(strcmp(status_str, "empty") == 0 && strcmp(out_record_vecs[0].fields[9].value[0].c_str(), "fail") == 0)) {
		strcpy(platestr, out_record_vecs[0].fields[3].value[0].c_str());
		strcpy(ptype, "out");
		state_changed = true;
	}
	else if ((strcmp(status_str, "car") == 0  && strcmp(out_record_vecs[0].fields[9].value[0].c_str(), "empty") == 0) ||
			 (strcmp(status_str, "fail") == 0 && strcmp(out_record_vecs[0].fields[9].value[0].c_str(), "empty") == 0)) {
		strcpy(platestr, plate_no);
		strcpy(ptype, "in");
		state_changed = true;
	}
	else if (strcmp(out_record_vecs[0].fields[9].value[0].c_str(), "block") == 0) {
		if ((strcmp(status_str, "empty") == 0 && strcmp(out_record_vecs[0].fields[11].value[0].c_str(), "car") == 0) ||
			(strcmp(status_str, "empty") == 0 && strcmp(out_record_vecs[0].fields[11].value[0].c_str(), "fail") == 0)) {
			strcpy(platestr, plate_no);
			strcpy(ptype, "out");
			state_changed = true;
		}
		else if ((strcmp(status_str, "car") == 0 && strcmp(out_record_vecs[0].fields[11].value[0].c_str(), "empty") == 0) ||
			(strcmp(status_str, "fail") == 0 && strcmp(out_record_vecs[0].fields[11].value[0].c_str(), "empty") == 0)) {
			strcpy(platestr, plate_no);
			strcpy(ptype, "in");
			state_changed = true;
		}
	}
	if (state_changed == true) {
		field_data.value.push_back(string(modified_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(lotid)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(platestr)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(ptype)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(movement_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(status_str)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string(image_fullfilename)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		field_data.value.push_back(string("")); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
		mutex_lock(&panel_mutex);
			ret = database_record_add(postgresDB, "pgs.log_pgs_movement", &datatable_record_data);
		mutex_unlock(&panel_mutex);
		datatable_record_data.fields.clear();
	}

	// step6: check whether need to update led (result is different and not "fail"(2))
	bool disable_led = check_file_exist("/tmp/disable_led");
	if (strcmp(status_str, out_record_vecs[0].fields[9].value[0].c_str()) != 0 && strcmp(result, RESULT_PGS_BLOCK) != 0 && disable_led == false) {
		char ledlist[MAX_LEDS][50];
		char ledstr[200];
		strcpy(ledstr, out_record_vecs[0].fields[5].value[0].c_str());
		int n = get_led_list(ledstr, ledlist);
		for (int i = 0; i < n; i++) {
			int led_index = get_led_index(ledlist[i]);
			if (led_index >= 0) {
				mutex_lock(&led_mutex);
					int led_count = get_emptylot_count(postgresDB, ledlist[i]);
				mutex_unlock(&led_mutex);
				if (led_count >= 0) {
					char led_count_str[30];
					sprintf(led_count_str, "%d", led_count);
					// write log_pgs_occupancy
					field_data.value.push_back(string(modified_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
					field_data.value.push_back(string(config_led[led_index].name)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
					field_data.value.push_back(string(led_count_str)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
					field_data.value.push_back(string(movement_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
					field_data.value.push_back(string("")); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
					mutex_lock(&panel_mutex);
						ret = database_record_add(postgresDB, "pgs.log_pgs_occupancy", &datatable_record_data);
					mutex_unlock(&panel_mutex);
					datatable_record_data.fields.clear();

					// update LED
					char log_msg[4096];
					sprintf(log_msg, "[LE]: LED%d = %d\n", led_index + 1, led_count); write_log(log_msg);
					mutex_lock(&led_mutex);
						show_led(led_index, led_count);
					mutex_unlock(&led_mutex);
				}
			}
		}
	}

	// step7: send zmq queue
	char zmq_str[1000];
	int page_no  = atoi(out_record_vecs[0].fields[7].value[0].c_str());	// page_no
	int floor_no = atoi(out_record_vecs[0].fields[8].value[0].c_str()); // floor_no
	int unique_page_id = MODE_PGS_ID + floor_no * 100 + page_no;
	sprintf(zmq_str, "{\"Flag\":\"Result\",\"Time\":\"%s\",\"Lotid\":\"%s\",\"CapturedImg\":\"%s\",\"VehiclePlateNo\":\"%s\",\"ResultType\":\"%s\",\"PageID\":\"%d\",\"Mode\":\"PGS\"}", modified_time, lotid, image_fullfilename, plate_no, result, unique_page_id);
	struct udp_q_content_type zmq_q;
	strcpy(zmq_q.udp_cmd, zmq_str);
	zmq_q.udp_cmd_len = strlen(zmq_str);
	for (int i = 0; i < config_panel_count; i++) {
		mutex_lock(&send_panel_mutex[i]);
			panel_queue[i].push_back(zmq_q);
		mutex_unlock(&send_panel_mutex[i]);
	}
}

void update_lpr_database(PGconn *postgresDB, char *stationid, char *image_fullfilename, char *plate_no, char *entrytime, char *exittime, char *confidentstr, char *checksumstr, char *stationip)
{
	char movement_time[200];
	char modified_time[100];

	// step1: get time information
	get_detail_currenttime_for_bcd(modified_time);
	char *ptr;
	if (strstr(image_fullfilename, "_ET_") != NULL) ptr = strstr(image_fullfilename, "_XT");
	else if (strstr(image_fullfilename, "_XT_") != NULL) ptr = strstr(image_fullfilename, "_ET");
	if (ptr == NULL) strcpy(movement_time, modified_time);
	else {
		strcpy(movement_time, ptr + 3);
		movement_time[15] = '\0';
	}

	// step2: read from datatable
	vector<struct datatable_record_rec> out_record_vecs;
	struct datatable_record_rec datatable_record_data;
	struct field_data_rec field_data;
	int ret = database_record_qry(postgresDB, "pgs.data_lpr", QUERY_MODE_LATEST, "lot_id", stationid, &datatable_record_data, &out_record_vecs);
	if (ret < 0) return;

	// step3: update database
	char timestr[30];
	get_detail_currenttime_for_bcd(timestr);
	strcpy(field_data.fieldname, "modified_time"); field_data.value.push_back(string(timestr));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "image_path");	field_data.value.push_back(string(image_fullfilename));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "plate_no"); field_data.value.push_back(string(plate_no)); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	ret = database_record_upd(postgresDB, "pgs.data_lpr", "lot_id", stationid, &datatable_record_data);

	// step4: write log_lpr_movement	
	char ptype[50];
	datatable_record_data.fields.clear();
	if (strstr(image_fullfilename, "_XT_") != NULL) strcpy(ptype, "Entry");
	else if (strstr(image_fullfilename, "_ET_") != NULL) strcpy(ptype, "Exit");
	else strcpy(ptype, "Unknown");
	field_data.value.push_back(string(modified_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string(stationid)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string(plate_no)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string(ptype)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string(movement_time)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string(image_fullfilename)); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	field_data.value.push_back(string("")); datatable_record_data.fields.push_back(field_data); field_data.value.clear();
	mutex_lock(&panel_mutex);
		ret = database_record_add(postgresDB, "pgs.log_lpr_movement", &datatable_record_data);
	mutex_unlock(&panel_mutex);

	// step5: send zmq queue
	char zmq_str[1000];
	int page_no = atoi(out_record_vecs[0].fields[7].value[0].c_str());	// page_no
	int unique_page_id = MODE_LPR_ID + page_no;
	sprintf(zmq_str, "{\"Flag\":\"Result\",\"Time\":\"%s\",\"Lotid\":\"%s\",\"CameraName\":\"%s\",\"CapturedImg\":\"%s\",\"VehiclePlateNo\":\"%s\",\"CashCardNoIU\":\"\",\"EntryTime\":\"%s\",\"ExitTime\":\"%s\",\"PacketCommand\":\"\",\"ConfidenceLevel\":\"%s\",\"CheckSum\":\"%s\",\"ProcessTime\":\"\",\"StationIP\":\"%s\",\"PageID\":\"%d\",\"Mode\":\"LPR\"}", movement_time, stationid, stationid, image_fullfilename, plate_no, entrytime, exittime, confidentstr, checksumstr, stationip, unique_page_id);
	struct udp_q_content_type zmq_q;
	strcpy(zmq_q.udp_cmd, zmq_str);
	zmq_q.udp_cmd_len = strlen(zmq_str);
	for (int i = 0; i < config_panel_count; i++) {
		mutex_lock(&send_panel_mutex[i]);
			panel_queue[i].push_back(zmq_q);
		mutex_unlock(&send_panel_mutex[i]);
	}
}

void update_enf_database(PGconn *postgresDB, char *image_fullfilename, char *plate_no)
{
	char modified_time[100];

	// step1: get time information
	get_detail_currenttime_for_bcd(modified_time);

	// step2: read from datatable
	vector<struct datatable_record_rec> out_record_vecs;
	struct datatable_record_rec datatable_record_data;
	struct field_data_rec field_data;
	int ret = database_record_qry(postgresDB, "pgs.data_enf", QUERY_MODE_ALL, "", "", &datatable_record_data, &out_record_vecs);
	//if (ret < 0) return;

	// step3: write data_enf database
	int  pageindex = (int)(out_record_vecs.size() / 9);
	char pageindex_str[50];
	char timestr[30];
	sprintf(pageindex_str, "%d", pageindex);
	get_detail_currenttime_for_bcd(timestr);
	strcpy(field_data.fieldname, "modified_time"); field_data.value.push_back(string(timestr));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "platenum");	field_data.value.push_back(string(plate_no));	datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "car_image"); field_data.value.push_back(string(image_fullfilename)); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "pageindex"); field_data.value.push_back(string(pageindex_str)); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	strcpy(field_data.fieldname, "comments"); field_data.value.push_back(""); datatable_record_data.fields.push_back(field_data);  field_data.value.clear();
	ret = database_record_add(postgresDB, "pgs.data_enf", &datatable_record_data);
	ret = database_record_add(postgresDB, "pgs.log_enforcement", &datatable_record_data);

	// step4: send zmq queue
	char zmq_str[1000];
	int page_no = pageindex;	// page_no
	int unique_page_id = MODE_ENF_ID + page_no;
	sprintf(zmq_str, "{\"Flag\":\"Result\",\"Time\":\"%s\",\"Lotid\":\"0\",\"CapturedImg\":\"%s\",\"VehiclePlateNo\":\"%s\",\"ResultType\":\"0\",\"PageID\":\"%d\",\"Mode\":\"ENF\"}", modified_time, image_fullfilename, plate_no, unique_page_id);
	struct udp_q_content_type zmq_q;
	strcpy(zmq_q.udp_cmd, zmq_str);
	zmq_q.udp_cmd_len = strlen(zmq_str);
	for (int i = 0; i < config_panel_count; i++) {
		mutex_lock(&send_panel_mutex[i]);
			panel_queue[i].push_back(zmq_q);
		mutex_unlock(&send_panel_mutex[i]);
	}
}

int get_led_list(char *inpstr, char ledlist[][50])
{
	char elements[MAX_LEDS][200];
	int len = strlen(inpstr);
	int pno = splitstr(inpstr, len, ',', '{', ' ', '}', '=', &elements[0][0], 200);
	for (int k = 0; k < pno; k++) {
		strcpy(ledlist[k], elements[k]);
	}
	return pno;
}

int get_led_index(char *led_idstr)
{
	int n = -1;
	for (int i = 0; i < config_led_count; i++) {
		if (strcmp(config_led[i].name, led_idstr) == 0) {
			n = i;
			break;
		}
	}
	return n;
}

int get_emptylot_count(PGconn *postgresDB, char *led_idstr)
{
	char *raw;
	char query_str[200];

	sprintf(query_str, "led_id like '%%%s%%' and (status='empty' or (status='block' and comments='empty'))", led_idstr);
	raw = (char *)malloc(MAX_RECORDS*MAX_DATA_LEN);
	int rec_no = QueryDatabase(postgresDB, "pgs.data_pgs", query_str, QUERY_MODE_ALL, raw);
	return rec_no;
	free(raw);
}