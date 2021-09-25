#include "declaration.h"
#include "tcp.h"

SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr)
{
	SOCKET sockfd;
	struct sockaddr_in address;

	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_report);

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, ip_report, &serv_addr.sin_addr) <= 0) {
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		return -1;
	}

	int flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	return sockfd;
}

int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client)
{
	int lenword;
	if (p == NULL) {
		return -1;
	}
	send(sockfd, p, len, 0);
	return lenword;
}

int tcp_read(int sockfd, char *buffer)
{
	int n;

	bzero(buffer, 4096);

	n = recv(sockfd, buffer, 4095, 0);

	if (n < 0) return -1;
	return n;
}