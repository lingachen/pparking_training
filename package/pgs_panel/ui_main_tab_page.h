#ifndef UI_MAIN_TAB_PAGE_H
#define UI_MAIN_TAB_PAGE_H

#include "qt_inc.h"
#include "ui_lot_monitor_page.h"
#include "ui_carpark_monitor_page.h"
#include "ui_report_tab_page.h"
#include "ui_setting_tab_page.h"

class ui_main_tab_page: public QWidget
{
    Q_OBJECT
public:
    QGridLayout             *mainLayout;
    QTabWidget              *maintab_widget;
    ui_lot_monitor_page     *lot_monitor_page;
    ui_carpark_monitor_page *carpark_monitor_page;
    ui_report_tab_page      *report_tab_page;
    ui_setting_tab_page     *setting_tab_page;


    ui_main_tab_page();

    void init_data();

public slots:
    void tab_clicked(int index);
};

#endif // UI_MAIN_TAB_PAGE_H
