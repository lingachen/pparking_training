#include "declaration.h"
#include "threads.h"

void init_threads()
{
	pthread_mutex_init(&log_mutex, NULL);
	pthread_mutex_init(&udp_mutex, NULL);
	pthread_mutex_init(&xfer_mutex, NULL);
	pthread_mutex_init(&dir_mutex, NULL);
	pthread_mutex_init(&remote_dir_mutex, NULL);
	pthread_mutex_init(&led_mutex, NULL);
	pthread_mutex_init(&panel_mutex, NULL);
	for (int i = 0; i < config_panel_count; i++) pthread_mutex_init(&send_panel_mutex[i], NULL);

	pthread_create(&write_log_handle, NULL, &write_log_task, NULL);

	// handling udp packet & copy file and write to send_panel queue (copy failed => send to xfer_task for continous copy)
	int taskid[MAX_TASKS];
	int p = 0;
	for (p = 0; p < MAX_TASKS; p++) {
		taskid[p] = p;
		pthread_create(&panel_task_handle[p], NULL, &panel_task, &taskid[p]);
		Sleep(100);
	}

	// copy file if failed in first time copy (in panel_task)
	pthread_create(&xfer_task_handle, NULL, &xfer_task, NULL);

	// send zmq messages to panel
	int panelid[MAX_PANELS];
	for (int i = 0; i < config_panel_count; i++) {
		panelid[i] = i;
		pthread_create(&send_panel_task_handle[i], NULL, &send_panel_task, &panelid[i]);
	}
}

TASK_FUNC panel_task(void *data)
{
	int	 *data_ptr = (int *)data;
	int	 taskID = *data_ptr;
	bool status;
	char log_msg[4096];
	struct udp_q_content_type udp_q;

	if (taskID < 0 || taskID > MAX_TASKS - 1) {
		sprintf(log_msg, "[%d], Initial panel_task Failed\n", taskID); write_log(log_msg);
		return NULL;
	}

	sprintf(log_msg, "[%d], Initial panel_task Ok\n", taskID); write_log(log_msg);

	while (1) {
		// check database
		bool db_status = check_database_connect(taskID, postgresDB_task[taskID]);
		if (db_status == false) {
			Sleep(3000);
			sprintf(log_msg, "[%d]: check_database_connect: Failed\n", taskID); write_log(log_msg);
			continue;
		}

		mutex_lock(&udp_mutex);
			status = read_udp_queue(&udp_q);
		mutex_unlock(&udp_mutex);

		if (status) {
			// extract information
			CkJsonObject json;
			status = json.Load(udp_q.udp_cmd);
			if (status == false) {
				sprintf(log_msg, "[%d], Wrong Format Error: %s\n", taskID, udp_q.udp_cmd); write_log(log_msg);
				continue;
			}

			// base on different type packets (copy files and modified filename)
			char mode[30];
			char img_fullfilename[300];
			strcpy(mode, json.stringOf("Mode"));
				 if (strcmp(mode, "PGS") == 0) {
					struct pgs_udp_data_type pgs_udp_data;
					strcpy(pgs_udp_data.Flag, json.stringOf("Flag"));
					strcpy(pgs_udp_data.Lotid, json.stringOf("Lotid"));
					strcpy(pgs_udp_data.CapturedImg, json.stringOf("CapturedImg"));
					strcpy(pgs_udp_data.VehiclePlateNo, json.stringOf("VehiclePlateNo"));
					strcpy(pgs_udp_data.ResultType, json.stringOf("ResultType"));
					strcpy(pgs_udp_data.StationIP, json.stringOf("StationIP"));
					strcpy(pgs_udp_data.Mode, json.stringOf("Mode"));
					xfer_file(pgs_udp_data.StationIP, pgs_udp_data.CapturedImg, "/lpr_data/panel/pgs", img_fullfilename);
					update_pgs_database(postgresDB_task[taskID], pgs_udp_data.Lotid, img_fullfilename, pgs_udp_data.VehiclePlateNo, pgs_udp_data.ResultType);
					sprintf(log_msg, "[%2d]: (%d) LotID:%3s IP:%s Platenum=%s (%s)\n", taskID, udp_queue.size(), pgs_udp_data.Lotid, pgs_udp_data.StationIP, pgs_udp_data.VehiclePlateNo, img_fullfilename); write_log(log_msg);
			}
			else if (strcmp(mode, "LPR") == 0) {
					 struct lpr_udp_data_type lpr_udp_data;
					 strcpy(lpr_udp_data.Flag, json.stringOf("Flag"));
					 strcpy(lpr_udp_data.StationID, json.stringOf("StationID"));
					 strcpy(lpr_udp_data.CameraName, json.stringOf("CameraName"));
					 strcpy(lpr_udp_data.CapturedImg, json.stringOf("CapturedImg"));
					 strcpy(lpr_udp_data.VehiclePlateNo, json.stringOf("VehiclePlateNo"));
					 strcpy(lpr_udp_data.CashCardNoIU, json.stringOf("CashCardNoIU"));
					 strcpy(lpr_udp_data.EntryTime, json.stringOf("EntryTime"));
					 strcpy(lpr_udp_data.ExitTime, json.stringOf("ExitTime"));
					 strcpy(lpr_udp_data.PacketCommand, json.stringOf("PacketCommand"));
					 strcpy(lpr_udp_data.ConfidenceLevel, json.stringOf("ConfidenceLevel"));
					 strcpy(lpr_udp_data.CheckSum, json.stringOf("CheckSum"));
					 strcpy(lpr_udp_data.ProcessTime, json.stringOf("ProcessTime"));
					 strcpy(lpr_udp_data.StationIP, json.stringOf("StationIP"));
					 strcpy(lpr_udp_data.Mode, json.stringOf("Mode"));
					 xfer_file(lpr_udp_data.StationIP, lpr_udp_data.CapturedImg, "/lpr_data/panel/station", img_fullfilename);
					 update_lpr_database(postgresDB_task[taskID], lpr_udp_data.StationID, img_fullfilename, lpr_udp_data.VehiclePlateNo, lpr_udp_data.EntryTime, lpr_udp_data.ExitTime, lpr_udp_data.ConfidenceLevel, lpr_udp_data.CheckSum, lpr_udp_data.StationIP);
					 sprintf(log_msg, "[%2d]: (%d) StationID:%3s Platenum=%s (%s)\n", taskID, udp_queue.size(), lpr_udp_data.StationID, lpr_udp_data.VehiclePlateNo, img_fullfilename); write_log(log_msg);
			}
			else if (strcmp(mode, "ENF") == 0) {
					 struct enf_udp_data_type enf_udp_data;
					 strcpy(enf_udp_data.Flag, json.stringOf("Flag"));
					 strcpy(enf_udp_data.Lotid, json.stringOf("Lotid"));
					 strcpy(enf_udp_data.CapturedImg, json.stringOf("CapturedImg"));
					 strcpy(enf_udp_data.VehiclePlateNo, json.stringOf("VehiclePlateNo"));
					 strcpy(enf_udp_data.ResultType, json.stringOf("ResultType"));
					 strcpy(enf_udp_data.StationIP, json.stringOf("StationIP"));
					 strcpy(enf_udp_data.Mode, json.stringOf("Mode"));
					 xfer_file(enf_udp_data.StationIP, enf_udp_data.CapturedImg, "/lpr_data/panel/enforcement", img_fullfilename);
					 update_enf_database(postgresDB_task[taskID], img_fullfilename, enf_udp_data.VehiclePlateNo);
					 sprintf(log_msg, "[%2d]: (%d) Enforcements: Platenum=%s (%s)\n", taskID, udp_queue.size(), enf_udp_data.VehiclePlateNo, img_fullfilename); write_log(log_msg);
			}
			else {
					 sprintf(log_msg, "[%2d]: Wrong Mode Error: %s\n", taskID, mode); write_log(log_msg);
			}
		}

		Sleep(20);
	}
}

TASK_FUNC xfer_task(void *)
{
	bool status;
	char ssh_cmd[300];
	char log_msg[4096];
	struct udp_q_content_type udp_q;

	sprintf(log_msg, "[M], Initial xfer_task Ok\n"); write_log(log_msg);

	while (1) {
		mutex_lock(&xfer_mutex);
			status = read_xfer_queue(&udp_q);
		mutex_unlock(&xfer_mutex);

		if (status) {
			strcpy(ssh_cmd, udp_q.udp_cmd);
			int ssh_ret = system(ssh_cmd);			
			if (ssh_ret != 0) {
				Sleep(5000);
				ssh_ret = system(ssh_cmd);
				if (ssh_ret != 0) {
					Sleep(10000);
					sprintf(log_msg, "[M]: xfer_task: ssh_cmd: %s error\n", ssh_cmd); write_log(log_msg);
					continue;
				}
			}
			else {
				sprintf(log_msg, "[M]: xfer_task: OK\n", ssh_cmd); write_log(log_msg);
			}
		}
		Sleep(1000);
	}
}

TASK_FUNC send_panel_task(void *data)
{
	int	 *data_ptr = (int *)data;
	int	 panelID = *data_ptr;
	bool status;
	struct udp_q_content_type zmq_q;
	char log_msg[4096];

#if 0
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	char zmp_socket_str[200];
	sprintf(zmp_socket_str, "tcp://%s:6557", config_panel[panelID].ip);
	socket.connect(zmp_socket_str);
#endif

	SOCKADDR_IN	send_to_panel;
	status = udp_client_init((char *)config_panel[panelID].ip, 2010, &send_to_panel);

	sprintf(log_msg, "[M], Initial send_panel_task[%d] Ok\n", panelID); write_log(log_msg);

	while (1) {
		mutex_lock(&send_panel_mutex[panelID]);
			status = read_panel_queue(&panel_queue[panelID], &zmq_q);
		mutex_unlock(&send_panel_mutex[panelID]);
			
		if (status) {
#if 0
			zmq::message_t request_msg(zmq_q.udp_cmd_len+1);
			memcpy(request_msg.data(), zmq_q.udp_cmd, zmq_q.udp_cmd_len+1);
			socket.send(request_msg);	// ZMQ_NOBLOCK
#endif
			udp_send(udp_svr_socket_handle, zmq_q.udp_cmd, zmq_q.udp_cmd_len, &send_to_panel);
			sprintf(log_msg, "[%2d]: send_msg=%s panel_queue_size=%d\n", panelID, zmq_q.udp_cmd, panel_queue[panelID].size()); write_log(log_msg);
	
#if 0
			// Get the reply
			zmq::message_t recv_msg; 
			socket.recv(&recv_msg);		// ZMQ_DONTWAIT
			char recv_msg_char[1024];
			memset(recv_msg_char, 0, 1024);
			memcpy(recv_msg_char, recv_msg.data(), recv_msg.size());
			sprintf(log_msg, "[%2d]: recv_msg=%s\n", panelID, recv_msg_char); write_log(log_msg);
#endif
			// remove if long time not response
			if (panel_queue[panelID].size() > 100) {
				mutex_lock(&send_panel_mutex[panelID]);
					int n = panel_queue[panelID].size();
					vector<struct udp_q_content_type> panel_queue_buf;
					panel_queue_buf.push_back(panel_queue[panelID][n - 2]);
					panel_queue_buf.push_back(panel_queue[panelID][n - 1]);
					panel_queue[panelID].clear();
					panel_queue[panelID] = panel_queue_buf;
				mutex_unlock(&send_panel_mutex[panelID]);
			}
			Sleep(10);
		}
		else Sleep(20);
	}
	return 0;
}