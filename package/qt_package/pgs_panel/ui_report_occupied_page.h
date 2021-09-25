#ifndef UI_REPORT_OCCUPIED_PAGE_H
#define UI_REPORT_OCCUPIED_PAGE_H

#include "qt_inc.h"
#include "ui_report_input.h"

class ui_report_occupied_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_report_occupied_page(QWidget *parent = nullptr);

    QGridLayout      *mainLayout;
    QLabel           *status;
    ui_report_input  *report_input;
    QTableWidget     *info;
    QPushButton      *car_image;
    QStringList      header;

    void init_data();

signals:

public slots:
    void btn_search_clicked();
    void btn_export_clicked();
    void info_record_clicked(int row, int col);
};

#endif // UI_REPORT_OCCUPIED_PAGE_H
