#pragma once

void init_led(int led_index);
void send_led(int led_index, char *led_data, int len);
void reset_led(int led_index, int time_val);
void led_display(int led_index, int zone, char *msg);
void led_display_image(int led_index, int zone, int img_len, unsigned char *imgdata);