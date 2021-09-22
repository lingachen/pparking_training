#ifndef UI_SELECTCAR_PAGE_H
#define UI_SELECTCAR_PAGE_H

#include "qt_inc.h"
#include "ui_image_select.h"

class ui_selectcar_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout 	*mainLayout;
    QPushButton 	*page_up;
    QPushButton 	*page_dn;
    QPushButton 	*back;
    QLabel      	*main_header;
    QLabel      	*main_tailer;
    QLabel          *status;
    ui_image_select *input_image_select;
    int             page_index;
    int             page_count;

    ui_selectcar_page();

    void init_data();
    void update_page();
    int  check_parking_fee(int movement_rid);
    void send_status(QString msg);
    
public slots:
    void page_up_clicked();
    void page_dn_clicked();
    void back_clicked();
    void images_clicked();
};

#endif // UI_this_H
