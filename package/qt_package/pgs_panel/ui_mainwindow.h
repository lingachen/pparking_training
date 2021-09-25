#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "qt_inc.h"
#include "ui_main_tab_page.h"

class ui_mainwindow: public QMainWindow
{
    Q_OBJECT    
public:
    QGraphicsScene          *scene;  
    QGraphicsProxyWidget    *proxy;
    QGraphicsView           *view;    
    QUdpSocket              *receiver;
    ui_main_tab_page        *main_tab_page;

    ui_mainwindow();

    void init_data();
    void init_udp();
    int  get_current_page_index();

public slots:
     void udp_receiver_data();

};

#endif // UI_this_H
