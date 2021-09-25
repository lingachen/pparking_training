#pragma once

int config_led_count;
struct config_led_type config_led[MAX_LEDS];
SOCKET led_sockfd[MAX_LEDS];
SOCKADDR_IN	send_to_led[MAX_LEDS];

char arrow_filename[][100] = { "/opt/led/ArrowLeft.gif" , "/opt/led/ArrowUp.gif" , "/opt/led/ArrowRight.gif" };