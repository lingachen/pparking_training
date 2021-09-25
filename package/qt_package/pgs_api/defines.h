#pragma once

#define MDB_IP		(char *)"127.0.0.1"

#define ENABLE_LED		true
#define LED_COUNT		2

#define RESULT_GOOD		 0
#define RESULT_FAIL		-1
#define SYSTEM_FAIL		-9

#define QUERY_MODE_ALL			0
#define QUERY_MODE_FIRST		1
#define QUERY_MODE_LATEST		2

#define MAX_RECORDS				1024
#define MAX_DATA_LEN		    512

#define ENFORCEMENT_HEADER  "\"modified_time\",\"platenum\",\"car_image\",\"comments\""
#define FLOORPLANE_HEADER	"\"floor_id\",\"floor_name\",\"image\",\"comments\""
#define FLOORMAP_HEADER		"\"modified_time\",\"lot_id\",\"floor_id\",\"location_x\",\"location_y\",\"block_w\",\"block_h\",\"comments\""
#define LOT_HEADER			"\"lot_id\",\"lot_name\",\"plate_no\",\"carera_ip\",\"controller_id\",\"indicator_ip\",\"indicator_port_no\",\"occupancy_typeid\",\"floor_id\",\"location_x\",\"location_y\",\"direction\",\"status\",\"image_path\",\"lastupdatedtime\",\"indicator_status\",\"seq_no\",\"zone_id\",\"comments\",\"block_w\",\"block_h\""
#define MOVEMENT_HEADER		"\"carpark_id\",\"modified_time\",\"platenum\",\"etagnum\",\"entry_station\",\"exit_station\",\"entry_time\",\"exit_time\",\"parked_type\",\"paid_time\",\"parked_time_mins\",\"parked_time_hours\",\"parked_fee\",\"paid_fee\",\"paid_status\",\"complimentary_fee\",\"car_image\",\"comments\""
#define SEASON_HEADER		"\"carpark_id\",\"modified_time\",\"season_type\",\"platenum\",\"etagnum\",\"phonenum\",\"monthid\",\"validstart\",\"validend\",\"monthly_fee\",\"comments\""
#define OPERATIONLOG_HEADER "\"user_id\",\"modified_time\",\"log_type\",\"log_message\",\"comments\""
#define TARIFF_HEADER		"\"carpark_id\",\"modified_time\",\"season_fee\",\"hourly_fee\",\"first_duration\",\"second_duration\",\"daily_max\",\"comments\""
#define PARKINGFEE_HEADER	"\"carpark_id\",\"modified_time\",\"weekday_index\",\"starttime_hhmmss\",\"endtime_hhmmss\",\"hourly_fee\",\"comments\""
#define RECEIPT_HEADER		"\"carpark_id\",\"modified_time\",\"receiptid\",\"flag\",\"months\",\"random_code\",\"barcode\",\"qrcode1\",\"qrcode2\",\"receipt_time\",\"receipt_fee\",\"notax_fee\",\"vat_fee\",\"seller_taxnum\",\"buyer_taxnum\",\"comments\""
#define LOG_PAYMENT_HEADER	"\"carpark_id\",\"modified_time\",\"paymentid\",\"platenum\",\"type\",\"paid_fee\",\"paid_time\",\"d1000\",\"d500\",\"d200\",\"d100\",\"d50\",\"d10\",\"d5\",\"h50\",\"h10\",\"flag\",\"comments\""
#define LOG_HOPPER_HEADER	"\"carpark_id\",\"modified_time\",\"ip\",\"h50\",\"h10\",\"h5\",\"receipt\",\"comments\""
#define EXITPASS_HEADER		"\"carpark_id\",\"modified_time\",\"platenum\",\"etagnum\",\"paidtime\",\"movementrid\",\"comments\""
#define LED_HEADER			"\"id\",\"carpark_id\",\"modified_time\",\"ledid\",\"message\",\"comments\""
#define ALARM_HEADER		"\"modified_time\",\"lot_id\",\"watchdog_time\",\"pageindex\",\"status\",\"comments\""
#define BLACKLIST_HEADER	"\"modified_time\",\"stn_id\",\"movement_time\",\"platestr\",\"pageindex\",\"status\",\"car_image\",\"comments\""

#define ID_HOPPER50				0
#define ID_HOPPER10A			1
#define ID_HOPPER10B			2

#define ID_PMS_REBOOT			0
#define ID_APM1_REBOOT			1
#define ID_E1_OPEN				2
#define ID_E1_LOCK				3
#define ID_E1_UNLOCK			4
#define ID_E1_REBOOT			5
#define ID_X1_OPEN				6
#define ID_X1_LOCK				7
#define ID_X1_UNLOCK			8
#define ID_X1_REBOOT			9
#define ID_APM2_REBOOT			11
#define ID_E2_OPEN				12
#define ID_E2_LOCK				13
#define ID_E2_UNLOCK			14
#define ID_E2_REBOOT			15
#define ID_X2_OPEN				16
#define ID_X2_LOCK				17
#define ID_X2_UNLOCK			18
#define ID_X2_REBOOT			19
#define ID_APM3_REBOOT			21
#define ID_E3_OPEN				22
#define ID_E3_LOCK				23
#define ID_E3_UNLOCK			24
#define ID_E3_REBOOT			25
#define ID_X3_OPEN				26
#define ID_X3_LOCK				27
#define ID_X3_UNLOCK			28
#define ID_X3_REBOOT			29
#define ID_APM4_REBOOT			31
#define ID_E4_OPEN				32
#define ID_E4_LOCK				33
#define ID_E4_UNLOCK			34
#define ID_E4_REBOOT			35
#define ID_X4_OPEN				36
#define ID_X4_LOCK				37
#define ID_X4_UNLOCK			38
#define ID_X4_REBOOT			39

#define ID_APM1_OPEN_A			0
#define ID_APM1_OPEN_B			1
#define ID_APM2_OPEN_A			2
#define ID_APM2_OPEN_B			3
#define ID_APM3_OPEN_A			4
#define ID_APM3_OPEN_B			5
#define ID_APM4_OPEN_A			6
#define ID_APM4_OPEN_B			7

#define APM1_ID					0
#define APM2_ID					1
#define APM3_ID					2
#define APM4_ID					3

#define APM_DISP_IO				0
#define APM_CASH_IO				1

#define Account_pw_error		0
#define User_mode				1
#define control_mode			2


#define io_close			close
#define u16					unsigned int

typedef unsigned long		DWORD;
typedef unsigned short		WORD;
typedef unsigned char		BYTE;
typedef unsigned int		UNINT32;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef sockaddr			SOCKADDR;
typedef int					SOCKET;

//------------new------------------
struct log_lpr_movement_rec {
	long id;
	char modified_time[50];
	char station_id[50];
	char platenum[50];
	char ptype[50];
	char movement_time[50];
	char car_image[255];	
	char comments[255];
};
struct log_pgs_movement_rec {
	long id;
	char modified_time[50];
	char lot_id[50];
	char platenum[50];
	char ptype[50];
	char movement_time[50];
	char status[50];
	char car_image[255];
	char comments[255];
};
struct log_pgs_occupancy_rec {
	long id;
	char modified_time[50];
	char led_id[50];
	char count[50];
	char movement_time[50];
	char comments[255];
};
struct log_enforcement_rec {
	long id;
	char modified_time[50];
	char lot_id[50];
	char platenum[50];	
	char car_image[255];
	char comments[255];
};

struct data_enf_rec
{
	long id;
	char modified_time[50];	
	char platenum[50];
	char car_image[255];
	char pageindex[50];
	char comments[255];
};

struct data_pgs_rec {
	long id;
	char modified_time[50];
	char lot_id[50];
	char plate_no[50];
	char camera_ip[50];
	char led_id[50];
	char controller_ip[50];
	char pageindex[50];
	char floor_id[50];
	char status[50];
	char image_path[255];
	char comments[255];
};
struct data_lpr_rec {
	long id;
	char modified_time[50];
	char lot_id[50];
	char plate_no[50];
	char camera_ip[50];
	char led_id[50];
	char controller_ip[50];
	char pageindex[50];
	char floor_id[50];
	char status[50];
	char image_path[255];	
	char comments[255];
};

struct cfg_floorplan_rec {
	long id;
	char floor_id[50];
	char floor_name[50];
	char Image[255];
	char comments[255];
};

struct cfg_floormap_rec
{
	long id;
	char modified_time[50];
	char lot_id[50];
	char floor_id[255];
	char location_x[50];
	char location_y[50];
	char block_w[50];
	char block_h[50];
	char comments[255];
};

struct data_alarm_rec {
	long id;
	char modified_time[50];
	char lot_id[50];
	char watchdog_time[50];
	char pageindex[50];
	char status[50];
	char comments[255];
};

struct data_blk_rec {
	long id;
	char modified_time[50];
	char platestr[50];
	char stn_id[50];
	char movement_time[50];
	char pageindex[50];
	char status[50];
	char car_image[255];
	char comments[255];
};

//-------------new------------------

















struct enforcement_init_info_rec {
	long id;	
	char modified_time[50];	
	char platenum[50];
	char car_image[255];	
	char comments[255];
};

struct lot_init_info_rec {
	long floor_id;
	long Max_lot;
	long lot_id;
	long page_index;
	long display_index;	
};

struct index_rec {	
	long lot_id;
	long index;
	char floor_id[20];	
	char page_no[20];	
};

struct floorplan_rec {
	long id;
	char floor_id[50];
	char floor_name[50];
	char Image[255];
	char comments[255];	
};

struct information_lot_type
{
	long id;	
	char floor_id[50];
	char camera_ip[50];
	char platenum[50];
	char last_updatetime[50];
	char status[50];
	char direction[50];
	char locationx[50];
	char locationy[50];
	char image_path[255];
	char comments[255];
};
struct information_value_type {
	long id;
	char floor_id[50];
	char camera_ip[50];
	char platenum[50];
	char last_updatetime[50];
	char status[50];
	char direction[50];
	char locationx[50];
	char locationy[50];
	char image_path[255];
	char comments[255];
};
struct station_information_lot_type {
	long id;
	int  total_entry;
	int  total_exit;
	char E1_block[10];
	char E2_block[10];
	char E3_block[10];
	char E4_block[10];
	char X1_block[10];
	char X2_block[10];
	char X3_block[10];
	char X4_block[10];
};
struct station_information_value_type {
	long id;
	int  total_entry;
	int  total_exit;
	char E1_block[10];
	char E2_block[10];
	char E3_block[10];
	char E4_block[10];
	char X1_block[10];
	char X2_block[10];
	char X3_block[10];
	char X4_block[10];
};
struct login_account_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char userid[50];
	char passcode[50];	
	char validstart[50];
	char validend[50];	
	char comments[255];
};

struct lot_rec {
	long id;
	long lot_id;
	char lot_name[50];
	char plate_no[50];
	char carera_ip[255];
	char controller_id[50];
	char indicator_ip[50];
	char indicator_port_no[50];
	char occupancy_typeid[50];
	char floor_id[50];
	char location_x[50];
	char location_y[50];
	char direction[50];
	char status[50];
	char image_path[255];
	char lastupdatedtime[50];
	char indicator_status[50];
	char seq_no[50];
	char zone_id[50];	
	char comments[255];
	char block_w[50];
	char block_h[50];
};
struct twlot2_rec {
	long id;
	char modified_time[50];
	char lot_id[50];	
	char plate_no[50];
	char camera_ip[50];
	char led_id[50];
	char controller_ip[50];
	char pageindex[50];
	char floor_id[50];
	char floormap_title[50];	
	char location_x[50];
	char location_y[50];
	char block_w[50];
	char block_h[50];	
	char status[50];
	char image_path[255];
	char comments[255];	
};

struct movement_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char platenum[50];
	char etagnum[50];
	char entry_station[50];
	char exit_station[50];
	char entry_time[50];
	char exit_time[50];
	char parked_type[50];
	char paid_time[50];
	char parked_time_mins[50];
	char parked_time_hours[50];
	char parked_fee[50];
	char paid_fee[50];
	char paid_status[50];
	char complimentary_fee[50];
	char car_image[255];
	char comments[255];
};
struct operation_log {
	long id;
	char user_id[50];
	char modified_time[50];
	char log_type[50];
	char log_message[255];
	char comments[255];
};
struct season_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char season_type[50];
	char platenum[50];
	char etagnum[50];
	char phonenum[50];
	char monthid[50];
	char validstart[50];
	char validend[50];
	char monthly_fee[50];
	char comments[255];
};

struct availablelot_value_type {	
	char carpark_id[50];
	int  totallot;
	int  total_occupied;
	int  season_reserved;
	int  season_occupied;
	int  hourly_occupied;	
};

struct available_lot_type {
	long id;
	char carpark_id[50];
	char modified_time[50];
	int  totallot;
	int  season_reserved;
	int  total_occupied;
	int  season_occupied;
	int  hourly_occupied;
	char comments[255];
};

struct status_type {
	long id;
	char carparkid[50];
	char modified_time[50];
	char apm[50];
	char e1[50];
	char x1[50];
	char fullcontrol[50];
	char printer[50];
	char bill[50];
	char coin[50];
	char hopper50[50];
	char hopper10a[50];
	char hopper10b[50];
	char comments[255];
};

struct tariff_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char season_fee[50];
	char hourly_fee[50];
	char first_duration[50];
	char second_duration[50];
	char daily_max[50];
	char grace_duration[50];
	char comments[255];
};

struct tariff_value_rec {
	double season_fee_val;
	double hourly_fee_val;
	double first_duration_val;
	double second_duration_val;	
	double daily_max_val;
	double grace_duration_val;
};

struct parkingfee_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char weekday_index[50];
	char starttime_hhmmss[50];
	char endtime_hhmmss[50];
	char hourly_fee[50];
	char comments[255];
};

struct hopper_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char ip[50];
	char h50[50];
	char h10[50];
	char h5[50];
	char receipt[50];
	char comments[255];
};

struct receipt_data_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char receiptid[50];
	char flag[50];
	char months[50];
	char random_code[50];
	char barcode[100];
	char qrcode1[200];
	char qrcode2[200];
	char receipt_time[50];
	char receipt_fee[50];
	char notax_fee[50];
	char vat_fee[50];
	char seller_taxnum[50];
	char buyer_taxnum[50];
	char comments[255];
};

struct receipt_setting_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char seller_taxnum[50];
	char invoicetitle[100];
	char itemname[50];
	char shopname[50];
	char machineid[50];
	char ip[50];
	char receiptid_start[50];
	char ether_io[50];
	char comments[255];
};

struct payment_login_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char userid[50];
	char passcode[50];
	char validstart[50];
	char validend[50];
	char comments[255];
};

struct exitpass_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char platenum[50];
	char etagnum[50];
	char paidtime[50];
	char comments[255];
};

struct log_movement_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char platenum[50];
	char etagnum[50];
	char station_name[50];
	char station_time[50];
	char parked_type[50];
	char car_image[300];
	char comments[50];
};

struct log_payment_rec {
	long id;
	char carparkid[50];
	char modified_time[50];
	char paymentid[50];
	char platenum[50];
	char type[50];
	char paid_fee[50];
	char paid_time[50];
	char d1000[50];
	char d500[50];
	char d200[50];
	char d100[50];
	char d50[50];
	char d10[50];
	char d5[50];
	char h50[50];
	char h10[50];
	char flag[50];
	char comments[50];
};

struct disp_availablelot_type {
	char total_lots[50];
	char total_occupies[50];
	char season_occupies[50];
	char hourly_occupies[50];
	char empty_lots[50];
};

struct disp_check_rec {
	int  id;
	char platenum[50];
	char car_image[300]; 
};

struct disp_hopper_rec {
	int h50;
	int h10;
	int h5;
	int receipt;
};

struct init_rec {
	int  ecount;
	int  xcount;
	int  acount;
	char apm_ip[4][50];
};

struct disp_finance_summary_rec {
	int total_revenue;
	int d1000;
	int d500;
	int d200;
	int d100;
	int d50;
	int d10;
	int d5;
	int h50;
	int h10;
};

struct disp_finance_detail_rec {
	int  id;
	char receiptid[50];
	char receipt_time[50];
	int  receipt_fee;
	char buyer_taxnum[50];
	int  notax_fee;
	int  vat_fee;
};

struct config_cp_type {
	long id;
	char carparkid[50];
	char modified_time[50];
	char dbs[50];
	char pms[50];
	char acount[50];
	char apm[4][50];
	char ecount[50];
	char e[4][50];
	char xcount[50];
	char x[4][50];
	char eipcamcount[4][50];
	char eipcam[4][3][50];
	char xipcamcount[4][50];
	char xipcam[4][3][50];
	char eipcam_mon[4][50];
	char xipcam_mon[4][50];
	char eipcam_mon_type[4][50];
	char xipcam_mon_type[4][50];
	char comments[255];
};

