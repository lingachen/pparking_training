#ifndef UI_TAXNUM_PAGE_H
#define UI_TAXNUM_PAGE_H

#include "qt_inc.h"
#include "ui_keypad.h"

class ui_taxnum_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout *mainLayout;
    QLabel      *main_header;
    QLabel      *main_tailer;
    QLabel      *keypad_title;	
    QLabel      *status;
    QPushButton *back;
    ui_keypad   *input_keypad;
    QString		title_keypad_input;	
    QString		keypad_input_string;

    ui_taxnum_page();
    
    void init_data();
    void send_status(QString msg);

private:
    bool        confirm_clicked_flag;

public slots:
    void numbers_clicked();
    void clear_clicked();
    void confirm_clicked(); 
    void back_clicked();   
};

#endif // UI_this_H
