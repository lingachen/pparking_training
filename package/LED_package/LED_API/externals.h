#pragma once

extern int config_led_count;
extern struct config_led_type config_led[MAX_LEDS];
extern SOCKET led_sockfd[MAX_LEDS];
extern SOCKADDR_IN	send_to_led[MAX_LEDS];

extern char arrow_filename[][100];

extern void init_led(int led_index);
extern void send_led(int led_index, char *led_data, int len);
extern void led_display(int led_index, int zone, char *msg);
extern void led_display_image(int led_index, int zone, int img_len, unsigned char *imgdata);
extern void show_led(int led_index, int count);

extern SOCKET tcp_client_init(char *ip_report, u16 port_report, SOCKADDR_IN *sockaddr);
extern int tcp_send(int sockfd, char *p, int len, SOCKADDR_IN *client);
extern int tcp_read(int sockfd, char *buffer);

extern void Sleep(int val);