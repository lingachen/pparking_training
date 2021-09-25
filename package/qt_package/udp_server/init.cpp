#include "declaration.h"
#include "init.h"

void init_vars()
{
	udp_server_portnum = UDP_SERVER_PORT;
	for (int i = 0; i<MAX_LEDS; i++) prev_led_count[i] = -1;
}

void init_database()
{
	postgresDB_master = init_database("127.0.0.1");
	database_read_fieldname(postgresDB_master, "data_pgs");
	database_read_fieldname(postgresDB_master, "data_lpr");
	database_read_fieldname(postgresDB_master, "data_enf");	
	database_read_fieldname(postgresDB_master, "log_enforcement");
	database_read_fieldname(postgresDB_master, "log_lpr_movement");
	database_read_fieldname(postgresDB_master, "log_pgs_movement");
	database_read_fieldname(postgresDB_master, "log_pgs_occupancy");

	for (int i = 0; i < MAX_TASKS; i++) {
		postgresDB_task[i] = init_database("127.0.0.1");
	}
}

void read_config_led()
{
	int  n;
	char tmpstr[500];
	char valstr1[500];
	char valstr2[500];
	FILE *fp;

	fp = fopen("/lpr_data/config/config_led.ini", "r");
	if (fp == NULL) {
		printf("config_led.ini not exist\n");
		exit(-1);
	}
	fscanf(fp, "%s %s\n", tmpstr, valstr1); config_led_count = atoi(valstr1);
	for (int i = 0; i < config_led_count; i++) {
		fscanf(fp, "%s %s %s %s %s\n", tmpstr, config_led[i].name, config_led[i].ip, valstr1, valstr2);
		config_led[i].floor_id = atoi(valstr1);
		config_led[i].arrow    = atoi(valstr2);
	}
	fclose(fp);
}

void read_config_panel()
{
	int  n;
	char tmpstr[500];
	char valstr[500];
	FILE *fp;

	fp = fopen("/lpr_data/config/config_panel.ini", "r");
	if (fp == NULL) {
		printf("config_panel.ini not exist\n");
		exit(-1);
	}
	fscanf(fp, "%s %s\n", tmpstr, valstr); config_panel_count = atoi(valstr);
	for (int i = 0; i < config_panel_count; i++) {
		fscanf(fp, "%s %s\n", tmpstr, config_panel[i].ip);
	}
	fclose(fp);
}