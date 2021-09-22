#ifndef UI_SELECTRECEIPT_PAGE_H
#define UI_SELECTRECEIPT_PAGE_H

#include "qt_inc.h"

class ui_selectreceipt_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout 	*mainLayout;
    QPushButton 	*btn_direct_print;
    QPushButton 	*btn_taxnum_input;
    QLabel      	*main_header;
    QLabel      	*main_tailer;
    QLabel          *status;
    QLabel          *title_completed;
    QLabel          *title_input_taxnum;

    ui_selectreceipt_page();
   
    void init_data();
    void send_status(QString msg);

private:
    bool            direct_print_clicked_flag;
    bool            taxnum_input_clicked_flag;

public slots:
    void direct_print_clicked();
    void taxnum_input_clicked();
};

#endif // UI_this_H
