#pragma once

void init_log();
void write_log(char *msg);
void print_log(char *msg);
void *write_log_task(void *);