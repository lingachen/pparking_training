#pragma once

SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
int tcp_read(int sockfd, char *buffer);