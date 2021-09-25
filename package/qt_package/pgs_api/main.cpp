#include "declaration.h"

#if 0
extern int minc_pgs_query_data_pgs(struct data_pgs_rec *out_data_pgs_rec);
extern int minc_pgs_init_alarm(int total_lots, time_t *watchdog_time, struct data_pgs_rec *inp_data_pgs_rec);
extern int minc_pgs_update_alarm(bool update_watchdog_timer, char *lotid, char *status_str);
extern int minc_pgs_read_alarm(struct data_alarm_rec *data_alarm);
extern int minc_pgs_query_data_enf(struct data_enf_rec *out_data_enf_rec);
extern int minc_pgs_add_blacklist(struct data_blk_rec *inp_blacklist);
extern int minc_pgs_query_blacklist(struct data_blk_rec *out_blacklist);

int main()
{
	struct data_blk_rec inp_blacklist;
	int n = minc_pgs_query_blacklist(&inp_blacklist);
	printf("n=%d\n", n);
}
#endif
