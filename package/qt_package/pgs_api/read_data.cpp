#include "declaration.h"
#include "read_data.h"

void read_movement(char *raw, struct movement_rec *movement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct movement_rec *)movement, 0, sizeof(movement_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			movement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(movement->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(movement->modified_time, valstr);
		else if (strcmp(fieldname, "platenum") == 0) strcpy(movement->platenum, valstr);
		else if (strcmp(fieldname, "etagnum") == 0) strcpy(movement->etagnum, valstr);
		else if (strcmp(fieldname, "entry_station") == 0) strcpy(movement->entry_station, valstr);
		else if (strcmp(fieldname, "exit_station") == 0) strcpy(movement->exit_station, valstr);
		else if (strcmp(fieldname, "entry_time") == 0) strcpy(movement->entry_time, valstr);
		else if (strcmp(fieldname, "exit_time") == 0) strcpy(movement->exit_time, valstr);
		else if (strcmp(fieldname, "parked_type") == 0) strcpy(movement->parked_type, valstr);
		else if (strcmp(fieldname, "paid_time") == 0) strcpy(movement->paid_time, valstr);
		else if (strcmp(fieldname, "parked_time_mins") == 0) strcpy(movement->parked_time_mins, valstr);
		else if (strcmp(fieldname, "parked_time_hours") == 0) strcpy(movement->parked_time_hours, valstr);
		else if (strcmp(fieldname, "parked_time_mins") == 0) strcpy(movement->exit_station, valstr);
		else if (strcmp(fieldname, "parked_fee") == 0) strcpy(movement->parked_fee, valstr);
		else if (strcmp(fieldname, "paid_fee") == 0) strcpy(movement->paid_fee, valstr);
		else if (strcmp(fieldname, "paid_status") == 0) strcpy(movement->paid_status, valstr);
		else if (strcmp(fieldname, "complimentary_fee") == 0) strcpy(movement->complimentary_fee, valstr);
		else if (strcmp(fieldname, "car_image") == 0) strcpy(movement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(movement->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}
void read_lot(char *raw, struct lot_rec *lot)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct lot_rec *)lot, 0, sizeof(lot_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			lot->id = atoi(valstr);
		}
		if (strcmp(fieldname, "lot_id") == 0) {
			lot->lot_id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "lot_name")			== 0) strcpy(lot->lot_name, valstr);
		else if (strcmp(fieldname, "plate_no")			== 0) strcpy(lot->plate_no, valstr);
		else if (strcmp(fieldname, "carera_ip")			== 0) strcpy(lot->carera_ip, valstr);
		else if (strcmp(fieldname, "controller_id")		== 0) strcpy(lot->controller_id, valstr);
		else if (strcmp(fieldname, "indicator_ip")		== 0) strcpy(lot->indicator_ip, valstr);
		else if (strcmp(fieldname, "indicator_port_no") == 0) strcpy(lot->indicator_port_no, valstr);
		else if (strcmp(fieldname, "occupancy_typeid")	== 0) strcpy(lot->occupancy_typeid, valstr);
		else if (strcmp(fieldname, "floor_id")			== 0) strcpy(lot->floor_id, valstr);
		else if (strcmp(fieldname, "location_x")		== 0) strcpy(lot->location_x, valstr);
		else if (strcmp(fieldname, "location_y")		== 0) strcpy(lot->location_y, valstr);
		else if (strcmp(fieldname, "direction")			== 0) strcpy(lot->direction, valstr);
		else if (strcmp(fieldname, "status")			== 0) strcpy(lot->status, valstr);
		else if (strcmp(fieldname, "image_path")		== 0) strcpy(lot->image_path, valstr);
		else if (strcmp(fieldname, "lastupdatedtime")	== 0) strcpy(lot->lastupdatedtime, valstr);
		else if (strcmp(fieldname, "indicator_status")	== 0) strcpy(lot->indicator_status, valstr);
		else if (strcmp(fieldname, "seq_no")			== 0) strcpy(lot->seq_no, valstr);
		else if (strcmp(fieldname, "zone_id")			== 0) strcpy(lot->zone_id, valstr);
		else if (strcmp(fieldname, "comments")			== 0) strcpy(lot->comments, valstr);
		else if (strcmp(fieldname, "block_w")			== 0) strcpy(lot->block_w, valstr);
		else if (strcmp(fieldname, "block_h")			== 0) strcpy(lot->block_h, valstr);
		else {
		}
	} // end pno
	free(ptr);
}
void read_lot2(char *raw, struct twlot2_rec *lot2)
{
	char modified_time[50]; 
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	get_detail_currenttime_for_bcd(modified_time);

	memset((struct ltwlot2_rect_rec *)lot2, 0, sizeof(twlot2_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			lot2->id = atoi(valstr);
		}		
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "modified_time") == 0) strcpy(lot2->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0) strcpy(lot2->lot_id, valstr);
		else if (strcmp(fieldname, "plate_no") == 0) strcpy(lot2->plate_no, valstr);
		else if (strcmp(fieldname, "camera_ip") == 0) strcpy(lot2->camera_ip, valstr);
		else if (strcmp(fieldname, "led_id") == 0) strcpy(lot2->led_id, valstr);
		else if (strcmp(fieldname, "controller_ip") == 0) strcpy(lot2->controller_ip, valstr);
		else if (strcmp(fieldname, "pageindex") == 0) strcpy(lot2->pageindex, valstr);
		else if (strcmp(fieldname, "floor_id") == 0) strcpy(lot2->floor_id, valstr);
		else if (strcmp(fieldname, "floormap_title") == 0) strcpy(lot2->floormap_title, valstr);
		else if (strcmp(fieldname, "location_x") == 0) strcpy(lot2->location_x, valstr);
		else if (strcmp(fieldname, "location_y") == 0) strcpy(lot2->location_y, valstr);
		else if (strcmp(fieldname, "block_w") == 0) strcpy(lot2->block_w, valstr);
		else if (strcmp(fieldname, "block_h") == 0) strcpy(lot2->block_h, valstr);
		else if (strcmp(fieldname, "status") == 0) strcpy(lot2->status, valstr);
		else if (strcmp(fieldname, "image_path") == 0) strcpy(lot2->image_path, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(lot2->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_station_information(char *raw, struct station_information_lot_type *station_information_lot_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct station_information_lot_type *)station_information_lot_local, 0, sizeof(station_information_lot_type));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			station_information_lot_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "total_entry") == 0)		station_information_lot_local->total_entry = atoi(valstr);
		else if (strcmp(fieldname, "total_exit") == 0)		station_information_lot_local->total_exit  = atoi(valstr);
		else if (strcmp(fieldname, "E1_block") == 0)		strcpy(station_information_lot_local->E1_block, valstr);
		else if (strcmp(fieldname, "E2_block") == 0)		strcpy(station_information_lot_local->E2_block, valstr);
		else if (strcmp(fieldname, "E3_block") == 0)		strcpy(station_information_lot_local->E3_block, valstr);
		else if (strcmp(fieldname, "E4_block") == 0)		strcpy(station_information_lot_local->E4_block, valstr);
		else if (strcmp(fieldname, "X1_block") == 0)		strcpy(station_information_lot_local->X1_block, valstr);
		else if (strcmp(fieldname, "X2_block") == 0)		strcpy(station_information_lot_local->X2_block, valstr);
		else if (strcmp(fieldname, "X3_block") == 0)		strcpy(station_information_lot_local->X3_block, valstr);
		else if (strcmp(fieldname, "X4_block") == 0)		strcpy(station_information_lot_local->X4_block, valstr);
		else {
		}
	} // end pno
	free(ptr);
}
void read_information(char *raw, struct information_lot_type *information_lot_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct information_lot_type *)information_lot_local, 0, sizeof(information_lot_type *));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);
		
		if (strcmp(fieldname, "id") == 0) {
			information_lot_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");		
		if (strcmp(fieldname, "floor_id") == 0)				strcpy(information_lot_local->floor_id, valstr);
		else if (strcmp(fieldname, "camera_ip") == 0)		strcpy(information_lot_local->camera_ip, valstr);
		else if (strcmp(fieldname, "platenum") == 0)		strcpy(information_lot_local->platenum, valstr);
		else if (strcmp(fieldname, "last_updatetime") == 0)	strcpy(information_lot_local->last_updatetime, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(information_lot_local->status, valstr);
		else if (strcmp(fieldname, "direction") == 0)		strcpy(information_lot_local->direction, valstr);
		else if (strcmp(fieldname, "locationx") == 0)		strcpy(information_lot_local->locationx, valstr);
		else if (strcmp(fieldname, "locationy") == 0)		strcpy(information_lot_local->locationy, valstr);
		else if (strcmp(fieldname, "image_path") == 0)		strcpy(information_lot_local->image_path, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(information_lot_local->comments, valstr);
		else {
		}
		
	} // end pno
	free(ptr);
}

void read_floorplan(char *raw, struct cfg_floorplan_rec *floorplan)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct cfg_floorplan_rec *)floorplan, 0, sizeof(cfg_floorplan_rec));

	
	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);
		
		if (strcmp(fieldname, "id") == 0) {
			floorplan->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "floor_id") == 0)				strcpy(floorplan->floor_id, valstr);
		else if (strcmp(fieldname, "floor_name") == 0)		strcpy(floorplan->floor_name, valstr);
		else if (strcmp(fieldname, "image") == 0)			strcpy(floorplan->Image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(floorplan->comments, valstr);	
		else {
		}
		
	} // end pno
	free(ptr);
	
}
void read_cfg_floorplan(char *raw, struct cfg_floorplan_rec *floorplan)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct cfg_floorplan_rec *)floorplan, 0, sizeof(cfg_floorplan_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			floorplan->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "floor_id") == 0)				strcpy(floorplan->floor_id, valstr);
		else if (strcmp(fieldname, "floor_name") == 0)		strcpy(floorplan->floor_name, valstr);
		else if (strcmp(fieldname, "image") == 0)			strcpy(floorplan->Image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(floorplan->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}
void read_cfg_floormap(char *raw, struct cfg_floormap_rec *floormap)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct cfg_floormap_rec *)floormap, 0, sizeof(cfg_floormap_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			floormap->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "modified_time") == 0)	strcpy(floormap->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0)			strcpy(floormap->lot_id, valstr);
		else if (strcmp(fieldname, "floor_id") == 0)		strcpy(floormap->floor_id, valstr);
		else if (strcmp(fieldname, "location_x") == 0)		strcpy(floormap->location_x, valstr);
		else if (strcmp(fieldname, "location_y") == 0)		strcpy(floormap->location_y, valstr);
		else if (strcmp(fieldname, "block_w") == 0)			strcpy(floormap->block_w, valstr);
		else if (strcmp(fieldname, "block_h") == 0)			strcpy(floormap->block_h, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(floormap->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}
void read_data_lpr(char *raw, struct data_lpr_rec *data_lpr)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct data_lpr_rec *)data_lpr, 0, sizeof(data_lpr_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			data_lpr->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "modified_time") == 0)	strcpy(data_lpr->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0)			strcpy(data_lpr->lot_id, valstr);
		else if (strcmp(fieldname, "plate_no") == 0)		strcpy(data_lpr->plate_no, valstr);
		else if (strcmp(fieldname, "camera_ip") == 0)		strcpy(data_lpr->camera_ip, valstr);
		else if (strcmp(fieldname, "led_id") == 0)			strcpy(data_lpr->led_id, valstr);
		else if (strcmp(fieldname, "controller_ip") == 0)	strcpy(data_lpr->controller_ip, valstr);
		else if (strcmp(fieldname, "pageindex") == 0)		strcpy(data_lpr->pageindex, valstr);
		else if (strcmp(fieldname, "floor_id") == 0)		strcpy(data_lpr->floor_id, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(data_lpr->status, valstr);
		else if (strcmp(fieldname, "image_path") == 0)		strcpy(data_lpr->image_path, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(data_lpr->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}
void read_data_pgs(char *raw, struct data_pgs_rec *data_pgs)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct data_pgs_rec *)data_pgs, 0, sizeof(data_pgs_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			data_pgs->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "modified_time") == 0)	strcpy(data_pgs->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0)			strcpy(data_pgs->lot_id, valstr);
		else if (strcmp(fieldname, "plate_no") == 0)		strcpy(data_pgs->plate_no, valstr);
		else if (strcmp(fieldname, "camera_ip") == 0)		strcpy(data_pgs->camera_ip, valstr);
		else if (strcmp(fieldname, "led_id") == 0)			strcpy(data_pgs->led_id, valstr);
		else if (strcmp(fieldname, "controller_ip") == 0)	strcpy(data_pgs->controller_ip, valstr);
		else if (strcmp(fieldname, "pageindex") == 0)		strcpy(data_pgs->pageindex, valstr);
		else if (strcmp(fieldname, "floor_id") == 0)		strcpy(data_pgs->floor_id, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(data_pgs->status, valstr);
		else if (strcmp(fieldname, "image_path") == 0)		strcpy(data_pgs->image_path, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(data_pgs->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);
}
void read_data_enf(char *raw, struct data_enf_rec *data_enf)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct data_enf_rec *)data_enf, 0, sizeof(data_enf_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			data_enf->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "modified_time") == 0)		strcpy(data_enf->modified_time, valstr);
		else if (strcmp(fieldname, "platenum") == 0)		strcpy(data_enf->platenum, valstr);
		else if (strcmp(fieldname, "pageindex") == 0)		strcpy(data_enf->pageindex, valstr);
		else if (strcmp(fieldname, "car_image") == 0)		strcpy(data_enf->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(data_enf->comments, valstr);		
		else {
		}

	} // end pno
	free(ptr);

}
void read_log_enforcement(char *raw, struct log_enforcement_rec *log_enforcement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_enforcement_rec *)log_enforcement, 0, sizeof(log_enforcement_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_enforcement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "modified_time") == 0)		strcpy(log_enforcement->modified_time, valstr);
		else if (strcmp(fieldname, "platenum") == 0)		strcpy(log_enforcement->platenum, valstr);
		else if (strcmp(fieldname, "car_image") == 0)		strcpy(log_enforcement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(log_enforcement->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}
void read_data_blk(char *raw, struct data_blk_rec *data_blk)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct data_blk_rec *)data_blk, 0, sizeof(data_blk_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			data_blk->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "modified_time") == 0)	strcpy(data_blk->modified_time, valstr);
		else if (strcmp(fieldname, "platestr") == 0)		strcpy(data_blk->platestr, valstr);
		else if (strcmp(fieldname, "stn_id") == 0)			strcpy(data_blk->stn_id, valstr);
		else if (strcmp(fieldname, "movement_time") == 0)	strcpy(data_blk->movement_time, valstr);
		else if (strcmp(fieldname, "pageindex") == 0)		strcpy(data_blk->pageindex, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(data_blk->status, valstr);
		else if (strcmp(fieldname, "car_image") == 0)		strcpy(data_blk->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(data_blk->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);

}
void read_log_lpr_movement(char *raw, struct log_lpr_movement_rec *log_lpr_movement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_lpr_movement_rec *)log_lpr_movement, 0, sizeof(log_lpr_movement_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_lpr_movement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "modified_time") == 0)	strcpy(log_lpr_movement->modified_time, valstr);
		else if (strcmp(fieldname, "station_id") == 0)		strcpy(log_lpr_movement->station_id, valstr);
		else if (strcmp(fieldname, "platenum") == 0)		strcpy(log_lpr_movement->platenum, valstr);
		else if (strcmp(fieldname, "ptype") == 0)			strcpy(log_lpr_movement->ptype, valstr);
		else if (strcmp(fieldname, "movement_time") == 0)	strcpy(log_lpr_movement->movement_time, valstr);
		else if (strcmp(fieldname, "car_image") == 0)		strcpy(log_lpr_movement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(log_lpr_movement->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}
void read_log_pgs_movement(char *raw, struct log_pgs_movement_rec *log_pgs_movement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_pgs_movement_rec *)log_pgs_movement, 0, sizeof(log_pgs_movement_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_pgs_movement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "modified_time") == 0)	strcpy(log_pgs_movement->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0)			strcpy(log_pgs_movement->lot_id, valstr);
		else if (strcmp(fieldname, "platenum") == 0)		strcpy(log_pgs_movement->platenum, valstr);
		else if (strcmp(fieldname, "ptype") == 0)			strcpy(log_pgs_movement->ptype, valstr);
		else if (strcmp(fieldname, "movement_time") == 0)	strcpy(log_pgs_movement->movement_time, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(log_pgs_movement->status, valstr);
		else if (strcmp(fieldname, "car_image") == 0)		strcpy(log_pgs_movement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(log_pgs_movement->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);
}
void read_log_pgs_occupancy(char *raw, struct log_pgs_occupancy_rec *log_pgs_occupancy)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_pgs_occupancy_rec *)log_pgs_occupancy, 0, sizeof(log_pgs_occupancy_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_pgs_occupancy->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "modified_time") == 0)	strcpy(log_pgs_occupancy->modified_time, valstr);
		else if (strcmp(fieldname, "led_id") == 0)			strcpy(log_pgs_occupancy->led_id, valstr);
		else if (strcmp(fieldname, "count") == 0)			strcpy(log_pgs_occupancy->count, valstr);
		else if (strcmp(fieldname, "movement_time") == 0)	strcpy(log_pgs_occupancy->movement_time, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(log_pgs_occupancy->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);
}

void read_enforcement(char *raw, struct enforcement_init_info_rec *enforcement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct enforcement_init_info_rec *)enforcement, 0, sizeof(enforcement_init_info_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			enforcement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "modified_time") == 0)			strcpy(enforcement->modified_time, valstr);
		else if (strcmp(fieldname, "platenum") == 0)			strcpy(enforcement->platenum, valstr);
		else if (strcmp(fieldname, "car_image") == 0)			strcpy(enforcement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0)			strcpy(enforcement->comments, valstr);
		else {
		}

	} // end pno
	free(ptr);

}



void read_season(char *raw, struct season_rec *season)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct season_rec *)season, 0, sizeof(season_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			season->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(season->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(season->modified_time, valstr);
		else if (strcmp(fieldname, "season_type") == 0) strcpy(season->season_type, valstr);
		else if (strcmp(fieldname, "platenum") == 0) strcpy(season->platenum, valstr);
		else if (strcmp(fieldname, "etagnum") == 0) strcpy(season->etagnum, valstr);
		else if (strcmp(fieldname, "phonenum") == 0) strcpy(season->phonenum, valstr);
		else if (strcmp(fieldname, "monthid") == 0) strcpy(season->monthid, valstr);
		else if (strcmp(fieldname, "validstart") == 0) strcpy(season->validstart, valstr);
		else if (strcmp(fieldname, "validend") == 0) strcpy(season->validend, valstr);
		else if (strcmp(fieldname, "monthly_fee") == 0) strcpy(season->monthly_fee, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(season->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_availablelot(char *raw, struct available_lot_type *available_lot_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct available_lot_type *)available_lot_local, 0, sizeof(available_lot_type));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			available_lot_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carpark_id") == 0) strcpy(available_lot_local->carpark_id, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(available_lot_local->modified_time, valstr);
		else if (strcmp(fieldname, "totallot") == 0) available_lot_local->totallot = atoi(valstr);
		else if (strcmp(fieldname, "season_reserved") == 0) available_lot_local->season_reserved = atoi(valstr);
		else if (strcmp(fieldname, "total_occupied") == 0) available_lot_local->total_occupied = atoi(valstr);
		else if (strcmp(fieldname, "season_occupied") == 0) available_lot_local->season_occupied = atoi(valstr);
		else if (strcmp(fieldname, "hourly_occupied") == 0) available_lot_local->hourly_occupied = atoi(valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(available_lot_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}
void read_login_account(char *raw, struct login_account_rec *login_account_rec_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct login_account_rec *)login_account_rec_local, 0, sizeof(login_account_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			login_account_rec_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(login_account_rec_local->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(login_account_rec_local->modified_time, valstr);		
		else if (strcmp(fieldname, "userid") == 0) strcpy(login_account_rec_local->userid, valstr);
		else if (strcmp(fieldname, "passcode") == 0) strcpy(login_account_rec_local->passcode, valstr);
		else if (strcmp(fieldname, "validstart") == 0) strcpy(login_account_rec_local->validstart, valstr);
		else if (strcmp(fieldname, "validend") == 0) strcpy(login_account_rec_local->validend, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(login_account_rec_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_config_cp(char *raw, struct config_cp_type *config_cp_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct config_cp_type *)config_cp_local, 0, sizeof(config_cp_type));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			config_cp_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0)			strcpy(config_cp_local->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0)	strcpy(config_cp_local->modified_time, valstr);
		else if (strcmp(fieldname, "dbs") == 0)				strcpy(config_cp_local->dbs, valstr);
		else if (strcmp(fieldname, "pms") == 0)				strcpy(config_cp_local->pms, valstr);
		else if (strcmp(fieldname, "acount") == 0)			strcpy(config_cp_local->acount, valstr);
		else if (strcmp(fieldname, "apm1") == 0)			strcpy(config_cp_local->apm[0], valstr);
		else if (strcmp(fieldname, "apm2") == 0)			strcpy(config_cp_local->apm[1], valstr);
		else if (strcmp(fieldname, "apm3") == 0)			strcpy(config_cp_local->apm[2], valstr);
		else if (strcmp(fieldname, "apm4") == 0)			strcpy(config_cp_local->apm[3], valstr);
		else if (strcmp(fieldname, "ecount") == 0)			strcpy(config_cp_local->ecount, valstr);
		else if (strcmp(fieldname, "e1") == 0)				strcpy(config_cp_local->e[0], valstr);
		else if (strcmp(fieldname, "e2") == 0)				strcpy(config_cp_local->e[1], valstr);
		else if (strcmp(fieldname, "e3") == 0)				strcpy(config_cp_local->e[2], valstr);
		else if (strcmp(fieldname, "e4") == 0)				strcpy(config_cp_local->e[3], valstr);
		else if (strcmp(fieldname, "xcount") == 0)			strcpy(config_cp_local->xcount, valstr);
		else if (strcmp(fieldname, "x1") == 0)				strcpy(config_cp_local->x[0], valstr);
		else if (strcmp(fieldname, "x2") == 0)				strcpy(config_cp_local->x[1], valstr);
		else if (strcmp(fieldname, "x3") == 0)				strcpy(config_cp_local->x[2], valstr);
		else if (strcmp(fieldname, "x4") == 0)				strcpy(config_cp_local->x[3], valstr);
		else if (strcmp(fieldname, "e1ipcamcount") == 0)	strcpy(config_cp_local->eipcamcount[0], valstr);
		else if (strcmp(fieldname, "e2ipcamcount") == 0)	strcpy(config_cp_local->eipcamcount[1], valstr);
		else if (strcmp(fieldname, "e3ipcamcount") == 0)	strcpy(config_cp_local->eipcamcount[2], valstr);
		else if (strcmp(fieldname, "e4ipcamcount") == 0)	strcpy(config_cp_local->eipcamcount[3], valstr);
		else if (strcmp(fieldname, "e1ipcam1") == 0)		strcpy(config_cp_local->eipcam[0][0], valstr);
		else if (strcmp(fieldname, "e1ipcam2") == 0)		strcpy(config_cp_local->eipcam[0][1], valstr);
		else if (strcmp(fieldname, "e1ipcam3") == 0)		strcpy(config_cp_local->eipcam[0][2], valstr);
		else if (strcmp(fieldname, "e2ipcam1") == 0)		strcpy(config_cp_local->eipcam[1][0], valstr);
		else if (strcmp(fieldname, "e2ipcam2") == 0)		strcpy(config_cp_local->eipcam[1][1], valstr);
		else if (strcmp(fieldname, "e2ipcam3") == 0)		strcpy(config_cp_local->eipcam[1][2], valstr);
		else if (strcmp(fieldname, "e3ipcam1") == 0)		strcpy(config_cp_local->eipcam[2][0], valstr);
		else if (strcmp(fieldname, "e3ipcam2") == 0)		strcpy(config_cp_local->eipcam[2][1], valstr);
		else if (strcmp(fieldname, "e3ipcam3") == 0)		strcpy(config_cp_local->eipcam[2][2], valstr);
		else if (strcmp(fieldname, "e4ipcam1") == 0)		strcpy(config_cp_local->eipcam[3][0], valstr);
		else if (strcmp(fieldname, "e4ipcam2") == 0)		strcpy(config_cp_local->eipcam[3][1], valstr);
		else if (strcmp(fieldname, "e4ipcam3") == 0)		strcpy(config_cp_local->eipcam[3][2], valstr);
		else if (strcmp(fieldname, "x1ipcamcount") == 0)	strcpy(config_cp_local->xipcamcount[0], valstr);
		else if (strcmp(fieldname, "x2ipcamcount") == 0)	strcpy(config_cp_local->xipcamcount[1], valstr);
		else if (strcmp(fieldname, "x3ipcamcount") == 0)	strcpy(config_cp_local->xipcamcount[2], valstr);
		else if (strcmp(fieldname, "x4ipcamcount") == 0)	strcpy(config_cp_local->xipcamcount[3], valstr);
		else if (strcmp(fieldname, "x1ipcam1") == 0)		strcpy(config_cp_local->xipcam[0][0], valstr);
		else if (strcmp(fieldname, "x1ipcam2") == 0)		strcpy(config_cp_local->xipcam[0][1], valstr);
		else if (strcmp(fieldname, "x1ipcam3") == 0)		strcpy(config_cp_local->xipcam[0][2], valstr);
		else if (strcmp(fieldname, "x2ipcam1") == 0)		strcpy(config_cp_local->xipcam[1][0], valstr);
		else if (strcmp(fieldname, "x2ipcam2") == 0)		strcpy(config_cp_local->xipcam[1][1], valstr);
		else if (strcmp(fieldname, "x2ipcam3") == 0)		strcpy(config_cp_local->xipcam[1][2], valstr);
		else if (strcmp(fieldname, "x3ipcam1") == 0)		strcpy(config_cp_local->xipcam[2][0], valstr);
		else if (strcmp(fieldname, "x3ipcam2") == 0)		strcpy(config_cp_local->xipcam[2][1], valstr);
		else if (strcmp(fieldname, "x3ipcam3") == 0)		strcpy(config_cp_local->xipcam[2][2], valstr);
		else if (strcmp(fieldname, "x4ipcam1") == 0)		strcpy(config_cp_local->xipcam[3][0], valstr);
		else if (strcmp(fieldname, "x4ipcam2") == 0)		strcpy(config_cp_local->xipcam[3][1], valstr);
		else if (strcmp(fieldname, "x4ipcam3") == 0)		strcpy(config_cp_local->xipcam[3][2], valstr);
		else if (strcmp(fieldname, "e1ipcam_mon") == 0)		strcpy(config_cp_local->eipcam_mon[0], valstr);
		else if (strcmp(fieldname, "e2ipcam_mon") == 0)		strcpy(config_cp_local->eipcam_mon[1], valstr);
		else if (strcmp(fieldname, "e3ipcam_mon") == 0)		strcpy(config_cp_local->eipcam_mon[2], valstr);
		else if (strcmp(fieldname, "e4ipcam_mon") == 0)		strcpy(config_cp_local->eipcam_mon[3], valstr);
		else if (strcmp(fieldname, "x1ipcam_mon") == 0)		strcpy(config_cp_local->xipcam_mon[0], valstr);
		else if (strcmp(fieldname, "x2ipcam_mon") == 0)		strcpy(config_cp_local->xipcam_mon[1], valstr);
		else if (strcmp(fieldname, "x3ipcam_mon") == 0)		strcpy(config_cp_local->xipcam_mon[2], valstr);
		else if (strcmp(fieldname, "x4ipcam_mon") == 0)		strcpy(config_cp_local->xipcam_mon[3], valstr);
		else if (strcmp(fieldname, "e1ipcam_mon_type") == 0)	strcpy(config_cp_local->eipcam_mon_type[0], valstr);
		else if (strcmp(fieldname, "e2ipcam_mon_type") == 0)	strcpy(config_cp_local->eipcam_mon_type[1], valstr);
		else if (strcmp(fieldname, "e3ipcam_mon_type") == 0)	strcpy(config_cp_local->eipcam_mon_type[2], valstr);
		else if (strcmp(fieldname, "e4ipcam_mon_type") == 0)	strcpy(config_cp_local->eipcam_mon_type[3], valstr);
		else if (strcmp(fieldname, "x1ipcam_mon_type") == 0)	strcpy(config_cp_local->xipcam_mon_type[0], valstr);
		else if (strcmp(fieldname, "x2ipcam_mon_type") == 0)	strcpy(config_cp_local->xipcam_mon_type[1], valstr);
		else if (strcmp(fieldname, "x3ipcam_mon_type") == 0)	strcpy(config_cp_local->xipcam_mon_type[2], valstr);
		else if (strcmp(fieldname, "x4ipcam_mon_type") == 0)	strcpy(config_cp_local->xipcam_mon_type[3], valstr);
		else if (strcmp(fieldname, "comments") == 0)			strcpy(config_cp_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_tariff(char *raw, struct tariff_rec *tariff)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct tariff_rec *)tariff, 0, sizeof(tariff_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			tariff->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(tariff->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(tariff->modified_time, valstr);
		else if (strcmp(fieldname, "season_fee") == 0) strcpy(tariff->season_fee, valstr);
		else if (strcmp(fieldname, "hourly_fee") == 0) strcpy(tariff->hourly_fee, valstr);
		else if (strcmp(fieldname, "first_duration") == 0) strcpy(tariff->first_duration, valstr);
		else if (strcmp(fieldname, "second_duration") == 0) strcpy(tariff->second_duration, valstr);
		else if (strcmp(fieldname, "daily_max") == 0) strcpy(tariff->daily_max, valstr);
		else if (strcmp(fieldname, "grace_duration") == 0) strcpy(tariff->grace_duration, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(tariff->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_parkingfee(char *raw, struct parkingfee_rec *parkingfee)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct parkingfee_rec *)parkingfee, 0, sizeof(parkingfee_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			parkingfee->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0)			strcpy(parkingfee->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0)	strcpy(parkingfee->modified_time, valstr);
		else if (strcmp(fieldname, "weekday_index") == 0)	strcpy(parkingfee->weekday_index, valstr);
		else if (strcmp(fieldname, "starttime_hhmmss") == 0)strcpy(parkingfee->starttime_hhmmss, valstr);
		else if (strcmp(fieldname, "endtime_hhmmss") == 0)	strcpy(parkingfee->endtime_hhmmss, valstr);
		else if (strcmp(fieldname, "hourly_fee") == 0)		strcpy(parkingfee->hourly_fee, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(parkingfee->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_receipt_data(char *raw, struct receipt_data_rec *receipt_data)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct receipt_data_rec *)receipt_data, 0, sizeof(receipt_data_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			receipt_data->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "carparkid") == 0)		strcpy(receipt_data->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0)	strcpy(receipt_data->modified_time, valstr);
		else if (strcmp(fieldname, "receiptid") == 0)		strcpy(receipt_data->receiptid, valstr);
		else if (strcmp(fieldname, "flag") == 0)			strcpy(receipt_data->flag, valstr);
		else if (strcmp(fieldname, "months") == 0)			strcpy(receipt_data->months, valstr);
		else if (strcmp(fieldname, "random_code") == 0)		strcpy(receipt_data->random_code, valstr);
		else if (strcmp(fieldname, "barcode") == 0)			strcpy(receipt_data->barcode, valstr);
		else if (strcmp(fieldname, "qrcode1") == 0)			strcpy(receipt_data->qrcode1, valstr);
		else if (strcmp(fieldname, "qrcode2") == 0)			strcpy(receipt_data->qrcode2, valstr);
		else if (strcmp(fieldname, "receipt_time") == 0)	strcpy(receipt_data->receipt_time, valstr);
		else if (strcmp(fieldname, "receipt_fee") == 0)		strcpy(receipt_data->receipt_fee, valstr);
		else if (strcmp(fieldname, "notax_fee") == 0)		strcpy(receipt_data->notax_fee, valstr);
		else if (strcmp(fieldname, "vat_fee") == 0)			strcpy(receipt_data->vat_fee, valstr);
		else if (strcmp(fieldname, "seller_taxnum") == 0)	strcpy(receipt_data->seller_taxnum, valstr);
		else if (strcmp(fieldname, "buyer_taxnum") == 0)	strcpy(receipt_data->buyer_taxnum, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(receipt_data->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_receipt_setting(char *raw, struct receipt_setting_rec *receipt_setting_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct receipt_setting_rec *)receipt_setting_local, 0, sizeof(receipt_setting_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			receipt_setting_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(receipt_setting_local->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(receipt_setting_local->modified_time, valstr);
		else if (strcmp(fieldname, "seller_taxnum") == 0) strcpy(receipt_setting_local->seller_taxnum, valstr);
		else if (strcmp(fieldname, "invoicetitle") == 0) strcpy(receipt_setting_local->invoicetitle, valstr);
		else if (strcmp(fieldname, "itemname") == 0) strcpy(receipt_setting_local->itemname, valstr);
		else if (strcmp(fieldname, "shopname") == 0) strcpy(receipt_setting_local->shopname, valstr);
		else if (strcmp(fieldname, "machineid") == 0) strcpy(receipt_setting_local->machineid, valstr);
		else if (strcmp(fieldname, "ip") == 0) strcpy(receipt_setting_local->ip, valstr);
		else if (strcmp(fieldname, "receiptid_start") == 0) strcpy(receipt_setting_local->receiptid_start, valstr);
		else if (strcmp(fieldname, "ether_io") == 0) strcpy(receipt_setting_local->ether_io, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(receipt_setting_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_payment_login(char *raw, struct payment_login_rec *payment_login_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct payment_login_rec *)payment_login_local, 0, sizeof(payment_login_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			payment_login_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(payment_login_local->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(payment_login_local->modified_time, valstr);
		else if (strcmp(fieldname, "userid") == 0) strcpy(payment_login_local->userid, valstr);
		else if (strcmp(fieldname, "passcode") == 0) strcpy(payment_login_local->passcode, valstr);
		else if (strcmp(fieldname, "validstart") == 0) strcpy(payment_login_local->validstart, valstr);
		else if (strcmp(fieldname, "validend") == 0) strcpy(payment_login_local->validend, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(payment_login_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_hopper(char *raw, struct hopper_rec *hopper)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct hopper_rec *)hopper, 0, sizeof(hopper_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			hopper->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(hopper->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(hopper->modified_time, valstr);
		else if (strcmp(fieldname, "ip") == 0) strcpy(hopper->ip, valstr);
		else if (strcmp(fieldname, "h50") == 0) strcpy(hopper->h50, valstr);
		else if (strcmp(fieldname, "h10") == 0) strcpy(hopper->h10, valstr);
		else if (strcmp(fieldname, "h5") == 0) strcpy(hopper->h5, valstr);
		else if (strcmp(fieldname, "receipt") == 0) strcpy(hopper->receipt, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(hopper->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_status(char *raw, struct status_type *status_local)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct status_type *)status_local, 0, sizeof(status_type));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			status_local->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		     if (strcmp(fieldname, "carparkid") == 0) strcpy(status_local->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(status_local->modified_time, valstr);
		else if (strcmp(fieldname, "apm") == 0) strcpy(status_local->apm, valstr);
		else if (strcmp(fieldname, "e1") == 0) strcpy(status_local->e1, valstr);
		else if (strcmp(fieldname, "x1") == 0) strcpy(status_local->x1, valstr);
		else if (strcmp(fieldname, "fullcontrol") == 0) strcpy(status_local->fullcontrol, valstr);
		else if (strcmp(fieldname, "printer") == 0) strcpy(status_local->printer, valstr);
		else if (strcmp(fieldname, "bill") == 0) strcpy(status_local->bill, valstr);
		else if (strcmp(fieldname, "coin") == 0) strcpy(status_local->coin, valstr);
		else if (strcmp(fieldname, "hopper50") == 0) strcpy(status_local->hopper50, valstr);
		else if (strcmp(fieldname, "hopper10a") == 0) strcpy(status_local->hopper10a, valstr);
		else if (strcmp(fieldname, "hopper10b") == 0) strcpy(status_local->hopper10b, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(status_local->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_log_movement(char *raw, struct log_movement_rec *log_movement)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_movement_rec *)log_movement, 0, sizeof(log_movement_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_movement->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

		if (strcmp(fieldname, "carparkid") == 0) strcpy(log_movement->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(log_movement->modified_time, valstr);
		else if (strcmp(fieldname, "platenum") == 0) strcpy(log_movement->platenum, valstr);
		else if (strcmp(fieldname, "etagnum") == 0) strcpy(log_movement->etagnum, valstr);
		else if (strcmp(fieldname, "station_name") == 0) strcpy(log_movement->station_name, valstr);
		else if (strcmp(fieldname, "station_time") == 0) strcpy(log_movement->station_time, valstr);
		else if (strcmp(fieldname, "parked_type") == 0) strcpy(log_movement->parked_type, valstr);
		else if (strcmp(fieldname, "car_image") == 0) strcpy(log_movement->car_image, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(log_movement->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_log_payment(char *raw, struct log_payment_rec *log_payment)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct log_payment_rec *)log_payment, 0, sizeof(log_payment_rec));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			log_payment->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "carparkid") == 0) strcpy(log_payment->carparkid, valstr);
		else if (strcmp(fieldname, "modified_time") == 0) strcpy(log_payment->modified_time, valstr);
		else if (strcmp(fieldname, "paymentid") == 0) strcpy(log_payment->paymentid, valstr);
		else if (strcmp(fieldname, "platenum") == 0) strcpy(log_payment->platenum, valstr);
		else if (strcmp(fieldname, "type") == 0) strcpy(log_payment->type, valstr);
		else if (strcmp(fieldname, "paid_fee") == 0) strcpy(log_payment->paid_fee, valstr);
		else if (strcmp(fieldname, "paid_time") == 0) strcpy(log_payment->paid_time, valstr);
		else if (strcmp(fieldname, "d1000") == 0) strcpy(log_payment->d1000, valstr);
		else if (strcmp(fieldname, "d500") == 0) strcpy(log_payment->d500, valstr);
		else if (strcmp(fieldname, "d200") == 0) strcpy(log_payment->d200, valstr);
		else if (strcmp(fieldname, "d100") == 0) strcpy(log_payment->d100, valstr);
		else if (strcmp(fieldname, "d50") == 0) strcpy(log_payment->d50, valstr);
		else if (strcmp(fieldname, "d10") == 0) strcpy(log_payment->d10, valstr);
		else if (strcmp(fieldname, "d5") == 0) strcpy(log_payment->d5, valstr);
		else if (strcmp(fieldname, "h50") == 0) strcpy(log_payment->h50, valstr);
		else if (strcmp(fieldname, "h10") == 0) strcpy(log_payment->h10, valstr);
		else if (strcmp(fieldname, "flag") == 0) strcpy(log_payment->flag, valstr);
		else if (strcmp(fieldname, "comments") == 0) strcpy(log_payment->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}

void read_data_alarm(char *raw, struct data_alarm_rec *data_alarm)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct data_alarm_rec *)data_alarm, 0, sizeof(data_alarm_rec));


	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

		if (strcmp(fieldname, "id") == 0) {
			data_alarm->id = atoi(valstr);
		}
		if (strcmp(valstr, "None") == 0) strcpy(valstr, "");

			 if (strcmp(fieldname, "modified_time") == 0)	strcpy(data_alarm->modified_time, valstr);
		else if (strcmp(fieldname, "lot_id") == 0)			strcpy(data_alarm->lot_id, valstr);
		else if (strcmp(fieldname, "watchdog_time") == 0)	strcpy(data_alarm->watchdog_time, valstr);
		else if (strcmp(fieldname, "pageindex") == 0)		strcpy(data_alarm->pageindex, valstr);
		else if (strcmp(fieldname, "status") == 0)			strcpy(data_alarm->status, valstr);
		else if (strcmp(fieldname, "comments") == 0)		strcpy(data_alarm->comments, valstr);
		else {
		}
	} // end pno
	free(ptr);
}