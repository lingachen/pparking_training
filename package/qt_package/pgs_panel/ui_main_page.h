#ifndef UI_MAIN_PAGE_H
#define UI_MAIN_PAGE_H

#include "qt_inc.h"
#include "ui_keypad.h"

class ui_main_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout *mainLayout;
    QLabel      *main_header;
    QLabel      *main_tailer;
    QLabel      *keypad_title;	
    QLabel      *status;
    ui_keypad   *input_keypad; 
    QString		title_keypad_input;	
    QString		keypad_input_string;

    ui_main_page();
    
    void init_data();
    void send_status(QString msg);

public slots:
    void numbers_clicked();
    void clear_clicked();
    void confirm_clicked();
};

#endif // UI_this_H
