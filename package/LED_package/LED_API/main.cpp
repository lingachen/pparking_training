#include "pparking.h"
#include "main.h"

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
		config_led[i].arrow = atoi(valstr2);
	}
	fclose(fp);
}

int main()
{
	read_config_led();
	for (int i = 0; i < config_led_count; i++) {
		init_led(i);
		show_led(i, 999);
	}
}