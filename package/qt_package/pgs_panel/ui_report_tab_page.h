#ifndef UI_REPORT_TAB_PAGE_H
#define UI_REPORT_TAB_PAGE_H

#include "qt_inc.h"
#include "ui_report_lpr_page.h"
#include "ui_report_pgs_page.h"
#include "ui_report_all_page.h"
#include "ui_report_enf_page.h"
#include "ui_report_occupied_page.h"

class ui_report_tab_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_report_tab_page(QWidget *parent = nullptr);
    QGridLayout             *mainLayout;
    QTabWidget              *reporttab_widget;
    ui_report_lpr_page      *report_lpr_page;
    ui_report_pgs_page      *report_pgs_page;
    ui_report_all_page      *report_all_page;
    ui_report_enf_page      *report_enf_page;
    ui_report_occupied_page *report_occupied_page;

    void init_data();

signals:

public slots:
    void tab_clicked(int index);
};

#endif // UI_REPORT_TAB_PAGE_H
