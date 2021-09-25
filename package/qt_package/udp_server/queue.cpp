#include "declaration.h"
#include "queue.h"

bool read_udp_queue(struct udp_q_content_type *qdata)
{
	if (udp_queue.size() <= 0) return false;
	// take first data out
	vector<struct udp_q_content_type>::iterator it = udp_queue.begin();
	strcpy(qdata->udp_cmd, it->udp_cmd);
	qdata->udp_cmd_len = it->udp_cmd_len;
	it = udp_queue.erase(it);
	return true;
}

bool read_panel_queue(vector<struct udp_q_content_type> *panel_queue_ptr, struct udp_q_content_type *qdata)
{
	if (panel_queue_ptr->size() <= 0) return false;
	// take first data out
	vector<struct udp_q_content_type>::iterator it = panel_queue_ptr->begin();
	strcpy(qdata->udp_cmd, it->udp_cmd);
	qdata->udp_cmd_len = it->udp_cmd_len;
	it = panel_queue_ptr->erase(it);
	return true;
}

bool read_xfer_queue(struct udp_q_content_type *qdata)
{
	if (xfer_cmd_queue.size() <= 0) return false;
	// take first data out
	vector<string>::iterator it = xfer_cmd_queue.begin();
	strcpy(qdata->udp_cmd, it->c_str());
	qdata->udp_cmd_len = strlen(qdata->udp_cmd);
	it = xfer_cmd_queue.erase(it);
	return true;
}