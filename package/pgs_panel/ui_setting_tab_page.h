#ifndef UI_SETTING_TAB_PAGE_H
#define UI_SETTING_TAB_PAGE_H

#include "qt_inc.h"
#include "ui_setting_floor_page.h"
#include "ui_setting_lot_page.h"

class ui_setting_tab_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_setting_tab_page(QWidget *parent = nullptr);
    QGridLayout             *mainLayout;
    QTabWidget              *settingtab_widget;
    ui_setting_floor_page   *setting_floor_page;
    ui_setting_lot_page     *setting_lot_page;

    void init_data();

signals:

public slots:
    void tab_clicked(int index);
};

#endif // UI_SETTING_TAB_PAGE_H
