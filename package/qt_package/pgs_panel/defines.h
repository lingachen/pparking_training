#pragma once

#define PAGE_LOT_MONTIOR        0
#define PAGE_CARPARK_MONITOR    1
#define PAGE_REPORT             2
#define PAGE_SETTING            3
#define PAGE_ALARM              4

#define PAGE_SETTING_FLOOR      0
#define PAGE_SETTING_LOT        1

#define SETTING_TYPE_FLOOR_LOC       0
#define SETTING_TYPE_FLOOR_PARAM     1

#define REPORT_LPR_MOVEMENT     0
#define REPORT_PGS_MOVEMENT     1
#define REPORT_ALL_MOVEMENT     2
#define REPORT_ENFORCEMENT      3
#define REPORT_LOT_OCCUPIED     4

#define LPR_MODE                0
#define PGS_MODE                1
#define ENF_MODE                2
#define BLK_MODE                3

#define RESULT_PGS_BLOCK			"0"
#define RESULT_PGS_EMPTY			"1"
#define RESULT_PGS_CARS				"2"
#define RESULT_PGS_FAIL				"3"

#define MAX_LOTS                1000
#define MAX_FLOORS              100
#define MAX_LEDS                100
#define MAX_STATIONS            100
#define MAX_ENFORCEMENTS        1000
#define MAX_BLACKLIST           1000
#define MAX_PAGES               100
#define MAX_COMBO_INDEX         10

#define SCREEN_WIDTH			1920
#define SCREEN_HEIGTH			1080

struct log_blacklist_rec {
    long id;
    char modified_time[50];
    char lotid[50];
    char platenum[50];
    char car_image[255];
    char timeindex[50];
    char comments[255];
};

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

struct ROI_rec {
    char location_x[50];
    char location_y[50];
    char block_w[50];
    char block_h[50];
};

struct data_enf_rec {
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

struct cfg_floormap_rec {
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

struct available_lot_info_rec {
    int total_lots;
    int total_occupied;
    int total_led[MAX_LEDS];
    int led_occupied[MAX_LEDS];
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
