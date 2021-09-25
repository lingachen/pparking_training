#include "declaration.h"
#include "udp.h"

SOCKET udp_server_init(char *ip_server, u16 port_server)
{
	char   mesg[1000];
	SOCKET sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) return sockfd;

	int flags = fcntl(sockfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sockfd, F_SETFL, flags);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port_server);
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return sockfd;
}

bool udp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr)
{
	bzero(sockaddr, sizeof(*sockaddr));
	sockaddr->sin_addr.s_addr = inet_addr(ip_report);
	sockaddr->sin_port = htons(port_report);
	sockaddr->sin_family = AF_INET;
	return true;
}

int udp_recv(int sockfd, char *buf, int len, SOCKADDR_IN *client)
{
	socklen_t sockaddr_len = sizeof(SOCKADDR);
	int len_r = -1;
	if ((buf == NULL) || (client == NULL)) {
		return -1;
	}
	len_r = recvfrom(sockfd,
		buf,
		len,
		0,
		(sockaddr *)client,
		&sockaddr_len);
	return len_r;
}

int udp_send(int sockfd, char *p, int len, SOCKADDR_IN *client)
{
	int lenword;
	if (p == NULL) {
		return -1;
	}
	lenword = sendto(sockfd,
		p,
		len,
		0,
		(sockaddr *)client,
		sizeof(sockaddr));
	return lenword;
}

bool init_udp()
{
	bool status;
	char log_msg[4096];

	udp_svr_socket_handle = udp_server_init("127.0.0.1", udp_server_portnum);
	if (udp_svr_socket_handle <= 0) return false;

	sprintf(log_msg, "SVR: Portnum = %d\n", udp_server_portnum); write_log(log_msg);

	return true;
}

bool read_pgs_udp(char *raw, struct pgs_udp_data_type *pgs_udp_data)
{
	char *ptr, *ptr1;
	int   i, len, pno;
	char  tmpstr[500];
	char  fieldname[500], valstr[500];

	memset((struct pgs_udp_data_type *)pgs_udp_data, 0, sizeof(pgs_udp_data_type));

	ptr = (char *)malloc(200 * 500);

	len = strlen(raw);
	pno = splitstr(raw, len, ',', '{', ' ', '}', '=', ptr, 500);
	if (pno != 6) return false;
	for (i = 0; i < pno; i++) {
		strcpy(tmpstr, &ptr[i * 500]);
		ptr1 = strstr(tmpstr, ":");
		*ptr1 = '\0';
		strcpy(fieldname, tmpstr);
		strcpy(valstr, &ptr1[1]);

			 if (strcmp(fieldname, "Lotid") == 0)			strcpy(pgs_udp_data->Lotid, valstr);
		else if (strcmp(fieldname, "CapturedImg") == 0)		strcpy(pgs_udp_data->CapturedImg, valstr);
		else if (strcmp(fieldname, "VehiclePlateNo") == 0)	strcpy(pgs_udp_data->VehiclePlateNo, valstr);
		else if (strcmp(fieldname, "ResultType") == 0)		strcpy(pgs_udp_data->ResultType, valstr);
		else {
		}
	} // end pno
	if (ptr != NULL) free(ptr);
	return true;
}