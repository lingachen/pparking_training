ui_mainwindow *w;

struct cfg_floorplan_rec    cfg_floor_info[MAX_FLOORS];
struct cfg_floormap_rec     cfg_floor_lot[MAX_LOTS];
struct cfg_floormap_rec     cfg_floor_led[MAX_LEDS];
struct data_lpr_rec         out_data_lpr_rec[MAX_STATIONS];
struct data_enf_rec         out_data_enf_rec[MAX_ENFORCEMENTS];
struct data_pgs_rec         out_data_pgs_rec[MAX_LOTS];

int Total_floor_count;
int Total_floormap_count;
int Total_floormap_led_count;
int Total_lpr_data_count;
int Total_enf_data_count;
int Total_data_pgs_count;
int current_led_display_count[MAX_FLOORS][MAX_LEDS];

int max_page_no[MAX_COMBO_INDEX][MAX_PAGES];
int current_page_id;
char display_list[9][30];
struct available_lot_info_rec available_lot_info[MAX_FLOORS];
char prev_pgs_lot_state[MAX_LOTS][30];
