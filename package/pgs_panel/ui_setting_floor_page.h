#ifndef UI_SETTING_FLOOR_PAGE_H
#define UI_SETTING_FLOOR_PAGE_H

#include "qt_inc.h"

class ui_setting_floor_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_setting_floor_page(QWidget *parent = nullptr);
    QGridLayout      *mainLayout;
    QLabel           *status;
    QLabel           *floor_id;
    QLabel           *floor_name;
    QLabel           *floor_image;
    QLineEdit        *inp_floor_id;
    QLineEdit        *inp_floor_name;
    QLineEdit        *inp_floor_image;
    QPushButton      *btn_floor_image1;
    QPushButton      *btn_load;
    QPushButton      *btn_add;
    QPushButton      *btn_del;
    QPushButton      *btn_upd;
    QPushButton      *btn_qry;
    QTableWidget     *info;
    QPushButton      *btn_floor_image2;
    QStringList      header;
    int              rid_selected;

    void init_data();
    void show_floor_layout();

signals:

public slots:
    void btn_load_clicked();
    void btn_add_clicked();
    void btn_del_clicked();
    void btn_upd_clicked();
    void btn_qry_clicked();
    void info_record_clicked(int row, int col);
};

#endif // UI_SETTING_FLOOR_PAGE_H
