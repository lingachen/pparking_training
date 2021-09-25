#ifndef UI_SERVICE_PAGE_H
#define UI_SERVICE_PAGE_H

#include "qt_inc.h"

class ui_service_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout *mainLayout;
    QPushButton *btn_hopper50;
    QPushButton *btn_hopper10;
    QPushButton *btn_back;
    QLabel      *main_header;
    QLabel      *main_tailer;
    QLabel      *title_engineering;
    QLabel      *hopper50_result;
    QLabel      *hopper10_result;
    QLabel      *status;
    QString		title_hopper50_result;
    QString		title_hopper10_result;

    ui_service_page();

    void init_data();
    void send_status(QString msg);
    void send_hopper50_result(int hopper50_count);
    void send_hopper10_result(int hopper10_count);
    
public slots:
    void hopper50_clicked();
    void hopper10_clicked();   
    void back_clicked(); 
};

#endif // UI_this_H
