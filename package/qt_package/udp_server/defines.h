#pragma once

#define PROGRAM_VER			"VER_1.0.0_PP"

#define UDP_SERVER_PORT		2021

#define MAX_TASKS			10
#define MAX_PANELS			4

#define TASK_FUNC			void *
#define TASK_HANDLE			pthread_t
#define TASK_MUTEX			pthread_mutex_t
#define io_close			close
typedef unsigned long		DWORD;
typedef unsigned short		WORD;
typedef unsigned char		BYTE;
typedef unsigned int		UNINT32;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef sockaddr			SOCKADDR;
typedef int					SOCKET;
typedef time_t				LARGE_INTEGER;
#define u16					unsigned int

#define RESULT_GOOD			0
#define RESULT_FAIL			-1

#define RESULT_PGS_BLOCK			"0"
#define RESULT_PGS_EMPTY			"1"
#define RESULT_PGS_CARS				"2"
#define RESULT_PGS_FAIL				"3"

#define MODE_LPR_ID			0
#define MODE_PGS_ID			1000
#define MODE_ENF_ID			2000
#define MODE_LED_ID			10000

#define QUERY_MODE_ALL			0
#define QUERY_MODE_FIRST		1
#define QUERY_MODE_LATEST		2

#define MAX_RECORDS				1000
#define MAX_DATA_LEN			1000

#define ENABLE_LED		true

#define MAX_LEDS		10

#define ARROW_L			0
#define ARROW_U			1
#define ARROW_R			2

struct config_led_type {
	char name[30];
	char ip[30];
	int  floor_id;
	int  arrow;
};

struct config_panel_type {
	char ip[30];
};

struct field_data_rec {
	char fieldname[50];
	char datatype[50];
	vector<string> value;
};

struct datatable_template_rec {
	char tablename[100];
	vector<struct field_data_rec> fields;
};

struct datatable_record_rec {
	vector<struct field_data_rec> fields;
};

struct pgs_udp_data_type {
	char Flag[30];
	char Lotid[30];	
	char CapturedImg[200];
	char VehiclePlateNo[30];
	char ResultType[30];
	char StationIP[30];
	char Mode[30];
};

struct lpr_udp_data_type {
	char Flag[30];
	char StationID[30];
	char CameraName[30];
	char CapturedImg[200];
	char VehiclePlateNo[30];
	char CashCardNoIU[30];
	char EntryTime[30];
	char ExitTime[30];
	char PacketCommand[30];
	char ConfidenceLevel[30];
	char CheckSum[30];
	char ProcessTime[30];
	char StationIP[30];
	char Mode[30];
};

struct enf_udp_data_type {
	char Flag[30];
	char Lotid[30];
	char CapturedImg[200];
	char VehiclePlateNo[30];
	char ResultType[30];
	char StationIP[30];
	char Mode[30];
};

struct udp_q_content_type {
	int	  udp_cmd_len;
	char  udp_cmd[5000];
};

struct pgs_lot_type {
	int  id;
	char modified_time[50];
	char lot_id[50];
	char plate_no[50];
	char camera_ip[50];
	char led_id[50];
	char controller_ip[50];
	char pageindex[50];
	char floor_id[50];
	char location_x[50];
	char location_y[50];
	char block_w[50];
	char block_h[50];
	char status[50];
	char image_path[300];
	char comments[255];
};
