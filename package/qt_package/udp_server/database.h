#pragma once

PGconn *init_database(char *ip);
bool CheckDatabaseConnection(PGconn *conn);
PGconn *ConnectDatabase(char *connection_str);
PGresult *SendSql(PGconn  *conn, char *SqlCmd);
int  QueryDatabase(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data);
int  QueryDatabase(PGconn *conn, char *fieldname, char *tablename, char *query_str, int query_mode, char *rec_data);
bool InsertDatabase(PGconn *conn, char *tablename, char *header_str, char *rec_data);
bool UpdateDatabase(PGconn *conn, char *tablename, char *set_str, char *query_str);
bool DeleteDatabase(PGconn *conn, char *tablename, char *query_str);
void GetSingleRecordData(PGresult *res, int query_mode, char *result);
void read_record_str(PGresult *res, int iRecord, char *result);
int  check_id_or_modified_time_index(PGresult *res);