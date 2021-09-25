#include "pparking.h"
#include "led.h"

void init_led(int led_index)
{
	unsigned char LED_msg[1000];
	unsigned int  ichecksum;
	unsigned char cid = led_index + 1;
	int			  i;
	int			  idx;
	int			  network_data_len;
	int			  packet_data_len;

	// (1) initial variables
	unsigned char LED26_packet16_2windows[] = { 0x01, 0x02,
												0x00, 0x00, 0x00, 0x04, 0x00, 0x28, 0x00, 0x18,		//X,Y,W,H
												0x00, 0x28, 0x00, 0x04, 0x00, 0x18, 0x00, 0x18 };
	unsigned char imgdata[4096];
	int img_len;
	FILE *fp;
	fp = fopen(arrow_filename[config_led[led_index].arrow], "rb");
	img_len = fread(imgdata, 1, 4096, fp);
	fclose(fp);

	// (3) set led windows size
	ichecksum = 0;
	idx = 0;
	packet_data_len = 18;
	network_data_len = packet_data_len + 11;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = network_data_len;	// len (from packet type)
	LED_msg[idx++] = 0x00;				// len
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x68;				// packet type
	LED_msg[idx++] = 0x32;				// card type
	LED_msg[idx++] = cid;				// control card id
	LED_msg[idx++] = 0x7B;
	LED_msg[idx++] = 0x01;				// RR
	LED_msg[idx++] = packet_data_len;	// packet data len
	LED_msg[idx++] = 0x00;				// packet data len
	LED_msg[idx++] = 0x00;
	LED_msg[idx++] = 0x00;
	for (i = 0; i < packet_data_len; i++) LED_msg[idx++] = LED26_packet16_2windows[i];
	for (i = 8; i < idx; i++) ichecksum = ichecksum + LED_msg[i];
	LED_msg[idx++] = ichecksum % 256;
	LED_msg[idx++] = ichecksum >> 8;
	send_led(led_index, (char *)LED_msg, idx);
	Sleep(500);

	// (4) display arrow
	led_display_image(led_index, 1, img_len, imgdata);
	Sleep(100);
}

void send_led(int led_index, char *led_data, int len)
{
	char buf[1024];
	char log_msg[4096];

	// (1) connect LED TCP
	led_sockfd[led_index] = tcp_client_init((char *)config_led[led_index].ip, 5200, &send_to_led[led_index]);
	if (led_sockfd[led_index] < 0) {
		Sleep(5000);
		led_sockfd[led_index] = tcp_client_init((char *)config_led[led_index].ip, 5200, &send_to_led[led_index]);
		return;
	}

	// (2) send LED command
	tcp_send(led_sockfd[led_index], led_data, len, &send_to_led[led_index]);
	int n = tcp_read(led_sockfd[led_index], buf);

	// (3) close LED TCP
	close(led_sockfd[led_index]);
}

void led_display(int led_index, int zone, char *msg)
{
	unsigned char LED_msg[1000];
	unsigned int  ichecksum;
	unsigned char packet_data[500];
	unsigned char cid = led_index + 1;
	int			  i;
	int			  idx;
	int			  packet_data_len;

	// (1) set packet data
	int p = 0;
	packet_data[p++] = 0x12;	// display pure text (for english)
	packet_data[p++] = (char)zone;	// display window number (0: first block)
	packet_data[p++] = 0x00;	// mode:	  0 draw
	packet_data[p++] = 0x01;	// alignment: 1 => horizontal
	packet_data[p++] = 0x01;	// speed:	  1 => faster 
	packet_data[p++] = 0xff;	// stay time: time hi byte
	packet_data[p++] = 0xff;	// stay time: time lo byte
	packet_data[p++] = 0x03;	// font size: 0 => x8 2 => x16
	packet_data[p++] = 0xff;	// color R:   255
	packet_data[p++] = 0xff;	// color G:   255
	packet_data[p++] = 0xff;	// color B:   255
	for (int i = 0; i < strlen(msg); i++) packet_data[p++] = msg[i];
	packet_data[p++] = '\0';
	packet_data_len = p;

	// (2) set entire network packets (header + packet data)
	ichecksum = 0;
	idx = 0;
	int network_data_len = packet_data_len + 11;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = network_data_len;	// len (from packet type)
	LED_msg[idx++] = 0x00;				// len
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x68;				// packet type
	LED_msg[idx++] = 0x32;				// card type
	LED_msg[idx++] = cid;				// control card id
	LED_msg[idx++] = 0x7B;
	LED_msg[idx++] = 0x01;
	LED_msg[idx++] = packet_data_len;	//length(Lbyte)
	LED_msg[idx++] = 0x00;				//length(Hbyte)
	LED_msg[idx++] = 0x00;				// packet number
	LED_msg[idx++] = 0x00;				// total
	for (int i = 0; i < packet_data_len; i++) LED_msg[idx++] = packet_data[i];
	for (i = 8; i < idx; i++) ichecksum = ichecksum + LED_msg[i];
	LED_msg[idx++] = ichecksum % 256;
	LED_msg[idx++] = ichecksum >> 8;

	// (3) send to LED
	send_led(led_index, (char *)LED_msg, idx);
	Sleep(100);
}

void led_display_image(int led_index, int zone, int img_len, unsigned char *imgdata)
{
	unsigned char LED_msg[4096];
	unsigned int  ichecksum;
	unsigned char packet_data[4096];
	unsigned char cid = led_index + 1;
	int			  i;
	int			  idx;
	int			  packet_data_len;

	// (1) set packet data
	int p = 0;
	packet_data[p++] = 0x03;	// display image data
	packet_data[p++] = (char)zone;	// display window number (0: first block)
	packet_data[p++] = 0x00;	// mode:	  0 draw
	packet_data[p++] = 0x01;	// speed:	  1 => faster 
	packet_data[p++] = 0xff;	// stay time: time hi byte
	packet_data[p++] = 0xff;	// stay time: time lo byte
	packet_data[p++] = 0x01;	// GIF image format
	packet_data[p++] = 0x00;	// Image X
	packet_data[p++] = 0x00;	// Image X
	packet_data[p++] = 0x00;	// Image Y
	packet_data[p++] = 0x00;	// Image Y
	for (int i = 0; i < img_len; i++) packet_data[p++] = imgdata[i];
	//packet_data[p++] = '\0';
	packet_data_len = p;

	// (2) set entire network packets (header + packet data)
	ichecksum = 0;
	idx = 0;
	int network_data_len = packet_data_len + 11;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = 0xFF;
	LED_msg[idx++] = network_data_len % 256;	// len (from packet type)
	LED_msg[idx++] = network_data_len / 256;	// len
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x00;				// reserve
	LED_msg[idx++] = 0x68;				// packet type
	LED_msg[idx++] = 0x32;				// card type
	LED_msg[idx++] = cid;				// control card id
	LED_msg[idx++] = 0x7B;
	LED_msg[idx++] = 0x01;
	LED_msg[idx++] = packet_data_len % 256;	//length(Lbyte)
	LED_msg[idx++] = packet_data_len / 256; //length(Hbyte)
	LED_msg[idx++] = 0x00;					// packet number
	LED_msg[idx++] = 0x00;					// total
	for (int i = 0; i < packet_data_len; i++) LED_msg[idx++] = packet_data[i];
	for (i = 8; i < idx; i++) ichecksum = ichecksum + LED_msg[i];
	LED_msg[idx++] = ichecksum % 256;
	LED_msg[idx++] = ichecksum >> 8;

	// (3) send to LED
	send_led(led_index, (char *)LED_msg, idx);
	Sleep(20);
}

void show_led(int led_index, int count)
{
	char led_msg[20];
	sprintf(led_msg, "%d", count);
	led_display(led_index, 0, led_msg);
}
