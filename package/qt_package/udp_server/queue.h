#pragma once

bool read_udp_queue(struct udp_q_content_type *qdata);
bool read_panel_queue(vector<struct udp_q_content_type> *panel_queue_ptr, struct udp_q_content_type *qdata);
bool read_xfer_queue(struct udp_q_content_type *qdata);