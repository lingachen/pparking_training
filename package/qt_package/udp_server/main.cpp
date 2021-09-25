#include "declaration.h"
#include "main.h"

// test program (receive udp from pgs)
int main(int argc, char *argv[])
{
	char log_msg[4096];

	// step1: initialization
  	init_vars();
	init_log();
	init_database();
	read_config_panel();
	init_udp();
	init_threads();
	
	// step2: initial led
	read_config_led();
	for (int i = 0; i < config_led_count; i++) {
		init_led(i);
		int led_count = get_emptylot_count(postgresDB_master, config_led[i].name);
		show_led(i, led_count);
	}
	sprintf(log_msg, "LED init .... \n"); write_log(log_msg);

	// step3: wait for UDP data
	char udprcv[1024];
	char udpsen[1024];
	char udpcmd[1024];
	char udptmp[10000];
	char udpdat[10000];
	SOCKADDR_IN	client_from;
	strcpy(udpdat, "");
	int display_count = 0; 
	while (1) {
		char timestr_log[100];
		get_detail_currenttime(timestr_log);
		//if (display_count % 250 == 0) printf("[%s]: UDP Server Running (Ver:%s)\n", timestr_log, (char *)PROGRAM_VER);
		display_count++;

		//{'Flag':'Result', 'Lotid' : '12', 'CapturedImg' : '//10.0.0.100/210520/plateimage_CT210520013020_1_96.jpg', 'VehiclePlateNo' : 'ABC1234G', 'ResultType' : '0', 'Mode' : 'PGS'}
		//{'Flag':'Result', 'StationID' : 'E1', 'CameraName' : 'E1', 'CapturedImg' : '//10.0.0.100/210520/plateimage_ET_XT210520013020_1__cE1_ABC1234G.jpg', 'VehiclePlateNo' : 'ABC1234G', 'CashCardNoIU' : '0123456789', 'EntryTime' : '210520013020', 'ExitTime' : '210520013020', 'PacketCommand' : 'None', 'ConfidenceLevel' : '98.5', 'CheckSum' : '0', 'ProcessTime' : '0', 'StationIP' : '10.0.0.100', 'Mode' : 'LPR'}
		//{'Flag':'Result','Lotid':'0','CapturedImg':'%s','VehiclePlateNo':'%s','ResultType':'0','Mode':'ENF'}

		int len = udp_recv(udp_svr_socket_handle, &udprcv[0], 1000, &client_from);
		if (len > 0) {
			if (udprcv[len - 1] == 0x0a || udprcv[len - 1] == 0x0d) udprcv[len - 1] = '\0';
			strcat(udpdat, udprcv);
			char *ptr1 = strstr(udpdat, "{");
			if (ptr1 == NULL) {
				strcpy(udpdat, "");
				continue;
			}			
			char *ptr2 = strstr(ptr1, "}");
			if (ptr2 == NULL) {
				strcpy(udpdat, ptr1);
				continue;
			}
			strcpy(udptmp, ptr2 + 1);
			*(ptr2 + 1) = '\0';
			strcpy(udpcmd, ptr1);
			strcpy(udpdat, udptmp);

			// wirte into udp queue
			bool display_flag = check_file_exist("/tmp/enable_udp_display");
			if (display_flag) {
				sprintf(log_msg, "[U]: (%d) UDP CMD: %s\n", udp_queue.size(), udpcmd);
				write_log(log_msg);
			}
			struct udp_q_content_type udp_q;
			strcpy(udp_q.udp_cmd, udpcmd);
			udp_q.udp_cmd_len = strlen(udpcmd);
			mutex_lock(&udp_mutex);
				udp_queue.push_back(udp_q);
			mutex_unlock(&udp_mutex);			
		}
		Sleep(20);
	} // while(1)
	return 0;
}