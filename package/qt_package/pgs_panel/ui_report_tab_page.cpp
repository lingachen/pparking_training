#include "declaration.h"
#include "ui_report_tab_page.h"

ui_report_tab_page::ui_report_tab_page(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_report_tab_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    QFont font1;
    font1.setPointSize(20);

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    reporttab_widget = new QTabWidget();
    reporttab_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    reporttab_widget->setStyleSheet("QTabBar::tab { height: 70px; width: 300px; }");
    reporttab_widget->setFont(font1);

    report_lpr_page = new ui_report_lpr_page();
    report_lpr_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    report_pgs_page = new ui_report_pgs_page();
    report_pgs_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    report_all_page = new ui_report_all_page();
    report_all_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    report_enf_page = new ui_report_enf_page();
    report_enf_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    report_occupied_page = new ui_report_occupied_page();
    report_occupied_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    reporttab_widget->addTab(report_lpr_page, "LPR Movement");
    reporttab_widget->addTab(report_pgs_page, "PGS Movement");
    reporttab_widget->addTab(report_all_page, "ALL Movement");
    reporttab_widget->addTab(report_enf_page, "Enforcement");
    reporttab_widget->addTab(report_occupied_page, "LOT Occupied");
    mainLayout->addWidget(reporttab_widget);

    init_data();
}

void ui_report_tab_page::init_data()
{
    connect(reporttab_widget, SIGNAL(currentChanged(int)), this, SLOT(tab_clicked(int)));
}

void ui_report_tab_page::tab_clicked(int index)
{

}
