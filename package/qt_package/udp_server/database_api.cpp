#include "declaration.h"
#include "database_api.h"

int database_read_fieldname(PGconn *postgresDB, char *tablename)
{
	char sqlcmd[200];
	struct datatable_template_rec datatable_template_data;

	sprintf(sqlcmd, "SELECT column_name,data_type FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='%s'", tablename);
	strcpy(datatable_template_data.tablename, tablename);
	PGresult *res;
	res = SendSql(postgresDB, sqlcmd);
	if (res == NULL) {
		PQclear(res);
		return RESULT_FAIL;
	}
	char rec_data[MAX_DATA_LEN];
	char dataitems[10][500];
	char tmpstr[500];
	char recname[100];
	char valname[100];
	int total_rec = PQntuples(res);
	for (int i = 0; i < total_rec; i++) {
		read_record_str(res, i, rec_data);
		int len = strlen(rec_data);
		int pno = splitstr(rec_data, len, ',', '{', ' ', '}', '\'', &dataitems[0][0], 500);
		struct field_data_rec field_data;
		memset((char *)&field_data, 0, sizeof(struct field_data_rec));
		for (int p = 0; p < pno; p++) {
			strcpy(tmpstr, dataitems[p]);
			char *ptr = strstr(tmpstr, ":");
			*ptr = '\0';
			strcpy(recname, tmpstr);
			strcpy(valname, ptr + 1);

			if (strcmp(recname, "column_name") == 0) {
				strcpy(field_data.fieldname, valname);
			}
			else if (strcmp(recname, "data_type") == 0) {
				strcpy(field_data.datatype, valname);
			}
			else {
			}
		} // end pno
		datatable_template_data.fields.push_back(field_data);
	}
	datatable_template.push_back(datatable_template_data);
	return RESULT_GOOD;
}

int database_extract_fieldname(char *tablename, char fieldname[][50])
{
	for (int k = 0; k < datatable_template.size(); k++) {
		if (strcmp(datatable_template[k].tablename, tablename) == 0) {
			for (int p = 0; p < datatable_template[k].fields.size(); p++) {
				strcpy(fieldname[p], datatable_template[k].fields[p].fieldname);
			}
			return datatable_template[k].fields.size();
		}
	}
	return -1;
}

int database_record_add(PGconn *postgresDB, char *tablename, struct datatable_record_rec *datatable_record_data)
{
	int  k;
	char *ptr;
	char tablename2[100];
	char header[4096];
	char dat[4096];
	char log_msg[4096];

	ptr = strstr(tablename, ".");
	if (ptr == NULL) strcpy(tablename2, tablename);
	else             strcpy(tablename2, ptr + 1);

	// prepare header data
	strcpy(header, "");
	char fieldname[100][50];
	int n = database_extract_fieldname(tablename2, fieldname);
	if (n < 0) return RESULT_FAIL;
	for (k = 1; k < n - 1; k++) {
		sprintf(header, "%s\"%s\",", header, fieldname[k]);
	}
	sprintf(header, "%s\"%s\"", header, fieldname[k]);

	// prepare value data
	strcpy(dat, "");
	for (k = 0; k < datatable_record_data->fields.size() - 1; k++) { // already skip id (k=0)
		if (strcmp(datatable_record_data->fields[k].datatype, "array") != 0) {
			sprintf(dat, "%s'%s',", dat, datatable_record_data->fields[k].value[0].c_str());
		}
		else {
			int q;
			sprintf(dat, "%s'{%s,", dat, datatable_record_data->fields[k].value[0].c_str());
			bool flag = false;
			for (q = 1; q < datatable_record_data->fields[k].value.size() - 1; q++) {
				sprintf(dat, "%s%s,", dat, datatable_record_data->fields[k].value[q].c_str());
				flag = true;
			}
			if (flag) {
				sprintf(dat, "%s%s}',", dat, datatable_record_data->fields[k].value[q].c_str());
			}
		}
	}
	sprintf(dat, "%s'%s'", dat, datatable_record_data->fields[k].value[0].c_str());

	// insert database
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = InsertDatabase(postgresDB, tablename, header, dat);
		usleep(10000);
		cnt++;
	}

	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int database_record_upd(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data)
{
	char set_str[1024];
	char query_str[1024];

	strcpy(set_str, "");
	int k;
	for (k = 0; k < datatable_record_data->fields.size() - 1; k++) {
		sprintf(set_str, "%s%s='%s',", set_str, datatable_record_data->fields[k].fieldname, datatable_record_data->fields[k].value[0].c_str());
	}
	sprintf(set_str, "%s%s='%s'", set_str, datatable_record_data->fields[k].fieldname, datatable_record_data->fields[k].value[0].c_str());

	char key_value2[50];
	if (strcmp(key_fieldname, "id") == 0) strcpy(key_value2, key_value);
	else								  sprintf(key_value2, "'%s'", key_value);
	if (strlen(key_fieldname) == 0 || strlen(key_value) == 0) strcpy(query_str, "");
	else													  sprintf(query_str, "%s=%s", key_fieldname, key_value2);

	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = UpdateDatabase(postgresDB, tablename, set_str, query_str);
		usleep(10000);
		cnt++;
	}

	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}

int database_record_qry(PGconn *postgresDB, char *tablename, int query_mode, char *key_fieldname, char *key_value, struct datatable_record_rec *datatable_record_data, vector<struct datatable_record_rec>*out_record_vecs)
{
	char *raw;
	char query_str[1024];
	char field_str[1024];
	char  tmpstr[4096];
	char  fieldname[500], valstr[4096];

	char key_value2[50];
	if (strcmp(key_fieldname, "id") == 0) strcpy(key_value2, key_value);
	else								  sprintf(key_value2, "'%s'", key_value);
	if (strlen(key_fieldname) == 0 || strlen(key_value) == 0) strcpy(query_str, "");
	else													  sprintf(query_str, "%s=%s", key_fieldname, key_value2);

	raw = (char *)malloc(MAX_RECORDS * MAX_DATA_LEN);

	int rec_no;
	if (datatable_record_data->fields.size() == 0) {
		rec_no = QueryDatabase(postgresDB, tablename, query_str, query_mode, raw);
	}
	else if (datatable_record_data->fields.size() == 1) {
		strcpy(field_str, datatable_record_data->fields[0].fieldname);
		rec_no = QueryDatabase(postgresDB, field_str, tablename, query_str, query_mode, raw);
	}
	else {
		strcpy(field_str, "");
		int k;
		for (k = 0; k < datatable_record_data->fields.size() - 1; k++) {
			sprintf(field_str, "%s%s,", field_str, datatable_record_data->fields[k].fieldname);
		}
		sprintf(field_str, "%s%s", field_str, datatable_record_data->fields[k].fieldname);
		rec_no = QueryDatabase(postgresDB, field_str, tablename, query_str, query_mode, raw);
	}
	if (rec_no == 0) {
		free(raw);
		return RESULT_FAIL;
	}
	char *ptr = (char *)malloc(200 * MAX_DATA_LEN);
	for (int i = 0; i < rec_no; i++) {
		struct datatable_record_rec tmp_datatable_record_data;
		int len = strlen(raw + i * MAX_DATA_LEN);
		int pno = splitstr(raw + i * MAX_DATA_LEN, len, ',', '{', ' ', '}', '=', ptr, MAX_DATA_LEN);
		for (int k = 0; k < pno; k++) {
			strcpy(tmpstr, &ptr[k * MAX_DATA_LEN]);
			char *ptr1 = strstr(tmpstr, ":");
			*ptr1 = '\0';
			strcpy(fieldname, tmpstr);
			strcpy(valstr, &ptr1[1]);
			struct field_data_rec field_data;
			strcpy(field_data.fieldname, fieldname);
			if (strstr(valstr, ",") == NULL) {
				strcpy(field_data.datatype, "string");
				string valstring = string(valstr);
				field_data.value.push_back(valstring);
			}
			else {
				char elements[256][200];
				int len2 = strlen(valstr);
				int pno2 = splitstr(valstr, len2, ',', '{', ' ', '}', '=', &elements[0][0], 200);
				if (pno2 > 1) {
					strcpy(field_data.datatype, "array");
					for (int m = 0; m < pno2; m++) {
						string valstring = string(elements[m]);
						field_data.value.push_back(valstring);
					}
				}
				else {
					strcpy(field_data.datatype, "string");
					string valstring = string(valstr);
					field_data.value.push_back(valstring);
				}
			}
			tmp_datatable_record_data.fields.push_back(field_data);
		} // end pno
		out_record_vecs->push_back(tmp_datatable_record_data);
	}
	free(ptr);
	free(raw);

	return RESULT_GOOD;
}

int database_record_del(PGconn *postgresDB, char *tablename, char *key_fieldname, char *key_value)
{
	char query_str[1024];

	char key_value2[50];
	if (strcmp(key_fieldname, "id") == 0) strcpy(key_value2, key_value);
	else								  sprintf(key_value2, "'%s'", key_value);
	if (strlen(key_fieldname) == 0 || strlen(key_value) == 0) return RESULT_FAIL;
	else													  sprintf(query_str, "%s=%s", key_fieldname, key_value2);

	// delete database
	int  cnt = 0;
	bool status = false;
	while (status == false && cnt < 10) {
		status = DeleteDatabase(postgresDB, tablename, query_str);
		usleep(10000);
		cnt++;
	}
	if (status == false) return RESULT_FAIL;
	else				 return RESULT_GOOD;
}