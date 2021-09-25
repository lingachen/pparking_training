#ifndef UI_REPORT_INPUT_H
#define UI_REPORT_INPUT_H

#include "qt_inc.h"

class ui_report_input : public QWidget
{
    Q_OBJECT
public:
    explicit ui_report_input(QWidget *parent = nullptr);

    QGridLayout      *mainLayout;
    QLabel           *platenum;
    QLabel           *stationid;
    QLabel           *starttime;
    QLabel           *endtime;
    QLineEdit        *inp_platenum;
    QLineEdit        *inp_stationid;
    QLineEdit        *inp_starttime;
    QLineEdit        *inp_endtime;
    QPushButton      *btn_search;
    QPushButton      *btn_export;    

    void init_data();

signals:

public slots:
};

#endif // UI_REPORT_INPUT_H
