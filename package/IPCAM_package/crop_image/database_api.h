#pragma once

int database_read_fieldname(PGconn *postgresDB, char *tablename);
int database_extract_fieldname(char *tablename, char fieldname[][50]);
int database_record_add(PGconn *postgresDB, char *tablename, struct datatable_record_rec *datatable_record_data);
int database_record_upd(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data);
int database_record_qry(PGconn *postgresDB, char *tablename, int query_mode, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data, vector<struct datatable_record_rec>*out_record_vecs);
int database_record_del(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value);
