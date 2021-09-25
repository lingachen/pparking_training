#pragma once

SOCKET udp_server_init(char *ip_server, u16 port_server);
bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
int udp_recv(int sockfd, char *buf, int len, SOCKADDR_IN *client);
int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
bool init_udp();
bool read_pgs_udp(char *raw, struct pgs_udp_data_type *pgs_udp_data);