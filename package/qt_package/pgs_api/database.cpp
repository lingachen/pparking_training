#include "declaration.h"
#include "database.h"

bool CheckDatabaseConnection(PGconn *conn)
{
	if (PQstatus(conn) != CONNECTION_OK) {
		return(false);
	}
	return(true);
}

PGconn *ConnectDatabase(char *connection_str)
{
	PGconn *conn;
	conn = PQconnectdb(connection_str);
	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
		PQfinish(conn);
		return(NULL);
	}
	return(conn);
}

PGresult *SendSql(PGconn  *conn, char *SqlCmd)
{
	PGresult *res;
	res = PQexec(conn, SqlCmd);
	if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return(NULL);
	}
	return(res);
}

int QueryDatabase(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data)
{
	PGresult *res;
	char	  SqlCmd[1000];
	int		  i;
	int		  total_rec = 0;
	bool	  status;

	if (strcmp(query_str, "") == 0) sprintf(SqlCmd, "SELECT * FROM %s", tablename);
	else			                sprintf(SqlCmd, "SELECT * FROM %s WHERE %s", tablename, query_str);

	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(-1);
	}

	switch (query_mode) {
	case QUERY_MODE_ALL:
		total_rec = PQntuples(res);
		for (i = 0; i < total_rec; i++) {
			read_record_str(res, i, rec_data + i * MAX_DATA_LEN);
		}
		break;

	case QUERY_MODE_FIRST:
		GetSingleRecordData(res, QUERY_MODE_FIRST, rec_data);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	case QUERY_MODE_LATEST:
		GetSingleRecordData(res, QUERY_MODE_LATEST, rec_data);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	default:
		break;
	}

	PQclear(res);
	return(total_rec);
}

int QueryDatabase2(PGconn *conn, char *fieldname, char *tablename, char *query_str, int query_mode, char *rec_data)
{
	PGresult *res;
	char	  SqlCmd[5000];
	int		  i;
	int		  total_rec = 0;
	bool	  status;

	if (strcmp(query_str, "") == 0) sprintf(SqlCmd, "SELECT %s FROM %s", fieldname, tablename);
	else			                sprintf(SqlCmd, "SELECT %s FROM %s WHERE %s", fieldname, tablename, query_str);

	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(-1);
	}

	switch (query_mode) {
	case QUERY_MODE_ALL:
		total_rec = PQntuples(res);
		for (i = 0; i < total_rec; i++) {
			read_record_str(res, i, rec_data + i * MAX_DATA_LEN);
		}
		break;

	case QUERY_MODE_FIRST:
		read_record_str(res, 0, rec_data + 0 * MAX_DATA_LEN);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	case QUERY_MODE_LATEST:
		read_record_str(res, total_rec - 1, rec_data + (total_rec - 1) * MAX_DATA_LEN);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	default:
		break;
	}

	PQclear(res);
	return(total_rec);
}

int QueryDatabase3(PGconn *conn, char *tablename, char *query_str, int query_mode, char *rec_data)
{
	PGresult *res;
	char	  SqlCmd[5000];
	int		  i;
	int		  total_rec = 0;
	bool	  status;

	if (strcmp(query_str, "") == 0) sprintf(SqlCmd, "SELECT * FROM %s", tablename);
	else			                sprintf(SqlCmd, "SELECT * FROM %s %s", tablename, query_str);

	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(-1);
	}

	switch (query_mode) {
	case QUERY_MODE_ALL:
		total_rec = PQntuples(res);
		for (i = 0; i < total_rec; i++) {
			read_record_str(res, i, rec_data + i * MAX_DATA_LEN);
		}
		break;

	case QUERY_MODE_FIRST:
		GetSingleRecordData(res, QUERY_MODE_FIRST, rec_data);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	case QUERY_MODE_LATEST:
		GetSingleRecordData(res, QUERY_MODE_LATEST, rec_data);
		if (strcmp(rec_data, "") != 0) total_rec = 1;
		break;

	default:
		break;
	}

	PQclear(res);
	return(total_rec);
}

int ClearDatabase(PGconn *conn, char *tablename)
{
	PGresult *res;
	char	  SqlCmd[5000];
	int		  i;
	int		  total_rec = 0;
	bool	  status;

	sprintf(SqlCmd, "TRUNCATE TABLE %s", tablename);
	
	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(-1);
	}	

	PQclear(res);
	return(0);
}


bool InsertDatabase(PGconn *conn, char *tablename, char *header_str, char *rec_data)
{
	PGresult *res;
	char SqlCmd[5000];

	sprintf(SqlCmd, "INSERT INTO %s(%s) VALUES(%s)", tablename, header_str, rec_data);
	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(false);
	}

	PQclear(res);
	return(true);
}

bool UpdateDatabase(PGconn *conn, char *tablename, char *set_str, char *query_str)
{
	PGresult *res;
	char SqlCmd[5000];

	sprintf(SqlCmd, "UPDATE %s set %s WHERE %s", tablename, set_str, query_str);

	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(false);
	}

	PQclear(res);
	return(true);
}

bool DeletetDatabase(PGconn *conn, char *tablename, char *query_str)
{
	PGresult *res;
	char SqlCmd[5000];

	sprintf(SqlCmd, "DELETE FROM %s WHERE %s", tablename, query_str);
	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(false);
	}

	PQclear(res);
	return(true);
}
bool Deletet_All_Database(PGconn *conn, char *tablename)
{
	PGresult *res;
	char SqlCmd[5000];

	sprintf(SqlCmd, "TRUNCATE TABLE %s", tablename);
	res = SendSql(conn, SqlCmd);
	if (res == NULL) {
		PQclear(res);
		return(false);
	}

	PQclear(res);
	return(true);
}

void GetSingleRecordData(PGresult *res, int query_mode, char *result)
{
	char tmpstr[MAX_DATA_LEN];
	char data_min[MAX_DATA_LEN];
	char data_max[MAX_DATA_LEN];
	char *ptr;
	int  min_index;
	int  max_index;
	int  nFields;
	int  nRecord;
	int  nIndex = -1;
	int  i, j, k;

	strcpy(tmpstr, "");
	nRecord = PQntuples(res);
	if (nRecord == 0) {
		strcpy(result, "");
		return;
	}

	nFields = PQnfields(res);
	nIndex = check_id_or_modified_time_index(res);

	ptr = (char *)malloc(nRecord * MAX_DATA_LEN);

	if (nIndex != -1) {
		if (nIndex >= 1000) k = nIndex / 1000 - 1; else k = nIndex - 1;
		for (i = 0; i < nRecord; i++) {
			strcpy(ptr + i * MAX_DATA_LEN, PQgetvalue(res, i, k));
			if (i == 0) {
				strcpy(data_min, ptr + i * MAX_DATA_LEN); min_index = 0;
				strcpy(data_max, ptr + i * MAX_DATA_LEN); max_index = 0;
			}
			else {
				if (strcmp(ptr + i * MAX_DATA_LEN, data_min) < 0) { strcpy(data_min, ptr + i * MAX_DATA_LEN); min_index = i; }
				if (strcmp(ptr + i * MAX_DATA_LEN, data_max) > 0) { strcpy(data_max, ptr + i * MAX_DATA_LEN); max_index = i; }
			}
		}

		if (query_mode == QUERY_MODE_FIRST) {
			read_record_str(res, min_index, tmpstr);
		}
		else if (query_mode == QUERY_MODE_LATEST) {
			read_record_str(res, max_index, tmpstr);
		}
		else {
		}
	}
	else {
		read_record_str(res, 0, tmpstr);
	}

	free(ptr);
	strcpy(result, tmpstr);
}

void read_record_str(PGresult *res, int iRecord, char *result)
{
	int  j;
	int  nFields;
	char tmpstr[MAX_DATA_LEN];

	strcpy(tmpstr, "");

	nFields = PQnfields(res);

	if (nFields == 0) {
	}
	else if (nFields == 1) {
		sprintf(tmpstr, "{'%s':'%s'}", PQfname(res, nFields - 1), PQgetvalue(res, iRecord, 0));
	}
	else {
		sprintf(tmpstr, "{");
		for (j = 0; j < nFields - 1; j++) {
			sprintf(tmpstr, "%s'%s':'%s',", tmpstr, PQfname(res, j), PQgetvalue(res, iRecord, j));
		}
		sprintf(tmpstr, "%s'%s':'%s'}", tmpstr, PQfname(res, nFields - 1), PQgetvalue(res, iRecord, j));
	}
	strcpy(result, tmpstr); 
}

int check_id_or_modified_time_index(PGresult *res)
{
	int nFields;
	int i;
	int m_index = -1;
	int i_index = -1;

	nFields = PQnfields(res);
	for (i = 0; i < nFields; i++) {
		if (strcmp(PQfname(res, i), "modified_time") == 0) m_index = i;
		if (strcmp(PQfname(res, i), "id") == 0) i_index = i;
	}
	if (m_index >= 0) return(m_index + 1);
	if (i_index >= 0) return((i_index + 1) * 1000);
	return(-1);
}

bool verify_database_connection()
{
	int  tries = 0;
	bool db_status;

	db_status = CheckDatabaseConnection(postgresDB_master);
	while (db_status == false && tries < 10) {
		char database_init_str[200];
		sprintf(database_init_str, "host=%s port=5435 dbname=pms_db user=cp password=cp123", MDB_IP);
		postgresDB_master = ConnectDatabase(database_init_str);
		if (postgresDB_master == NULL) {
			usleep(100000);
			tries++;
			continue;
		}
		db_status = CheckDatabaseConnection(postgresDB_master);
		if (db_status == false) {
			usleep(100000);
			tries++;
			continue;
		}
		printf("verify_database_connection: Re-ConnectDatabase success (Master)\n");
	}
	if (db_status == false) printf("verify_database_connection: ConnectDatabase error (Master)\n");
	return db_status;
}
