#include "declaration.h"
#include "utils.h"

void wait_ms(int timeval_ms)
{
    int step_val = timeval_ms / 10;
    if(step_val > 1000) step_val = 1000;
    QTime dieTime = QTime::currentTime().addMSecs(timeval_ms);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, step_val);
}

QString toQstring(char *inpstr)
{
    QString qstr = QString::fromStdString(inpstr);
    return qstr;
}

string toStdstring(QString *qstr)
{
    string str = qstr->toStdString();
    return str;
}

int toInt(QString qstr)
{
    int v = atoi(toStdstring(&qstr).c_str());
    return v;
}

QString get_currenttime()
{
    QDate dt_now = QDate::currentDate();
    QTime T1     = QTime::currentTime();
    QString yy,Month,dd,hh,mm,ss,tmp,time;
    tmp     = dt_now.toString("yyyy/MM/dd ").split("/").at(0);
    yy      = tmp.mid(0,4);
    Month   = dt_now.toString("yyyy/MM/dd ").split("/").at(1);
    dd      = dt_now.toString("yyyy/MM/dd ").split("/").at(2);
    hh      = QString("%1").arg(T1.hour(),2,'g',-1,'0');
    mm      = QString("%1").arg(T1.minute(),2,'g',-1,'0');//QString::number(T1.minute());
    ss      = QString("%1").arg(T1.second(),2,'g',-1,'0');//QString::number(T1.second());
    time = yy+"-"+Month+"-"+dd+hh+":"+mm+":"+ss;
    return time;
}

QString get_monthid()
{
    QDate dt_now  = QDate::currentDate();
    QString Month = dt_now.toString("yyyy/MM/dd ").split("/").at(1);
    int m = Month.toInt();
    char inp_months[100];
         if(m == 1  || m == 2)  strcpy(inp_months, "01-02");
    else if(m == 3  || m == 4)  strcpy(inp_months, "03-04");
    else if(m == 5  || m == 6)  strcpy(inp_months, "05-06");
    else if(m == 7  || m == 8)  strcpy(inp_months, "07-08");
    else if(m == 9  || m == 10) strcpy(inp_months, "09-10");
    else if(m == 11 || m == 12) strcpy(inp_months, "11-12");
    return toQstring(inp_months);
}

QString convert_time_format(char *time_bcd)
{
    char yy[10]; yy[2] = '\0';
    char mm[10]; mm[2] = '\0';
    char dd[10]; dd[2] = '\0';
    char hh[10]; hh[2] = '\0';
    char mi[10]; mi[2] = '\0';
    char ss[10]; ss[2] = '\0';

    strncpy(yy, &time_bcd[0], 2);
    strncpy(mm, &time_bcd[2], 2);
    strncpy(dd, &time_bcd[4], 2);
    strncpy(hh, &time_bcd[6], 2);
    strncpy(mi, &time_bcd[8], 2);
    strncpy(ss, &time_bcd[10], 2);

    char normal_time_format[100];
    sprintf(normal_time_format, "20%s-%s-%s %s:%s:%s", yy, mm, dd, hh, mi, ss);
    return toQstring(normal_time_format);
}

bool check_file_exist(char *FullPathFileName)
{
    bool status = false;
    struct stat filestatus;

    int exist = stat(FullPathFileName, &filestatus);
    if (exist == 0) status = true;
    return(status);
}

int get_pgs_lotid_index(char *lotid)
{
    for(int i=0; i<Total_data_pgs_count; i++) {
        if(strcmp(out_data_pgs_rec[i].lot_id, lotid) == 0) return i;
    }
    return -1;
}

int get_floor_index(char *floor_id)
{
    for(int i=0; i<Total_floor_count; i++) {
        if(strcmp(cfg_floor_info[i].floor_id, floor_id) == 0) return i;
    }
    return -1;
}

int get_floor_lot_index(char *lotid)
{
    for(int i=0; i<Total_floormap_count; i++) {
        if(strcmp(cfg_floor_lot[i].lot_id, lotid) == 0) return i;
    }
    return -1;
}

int get_display_index(char *lotid)
{
    for(int i=0; i<9; i++) {
        if(strcmp(display_list[i], lotid) == 0) return i;
    }
    return -1;
}
