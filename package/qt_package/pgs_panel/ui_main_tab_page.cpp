#include "declaration.h"
#include "ui_main_tab_page.h"

ui_main_tab_page::ui_main_tab_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_main_tab_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    QFont font1;
    font1.setPointSize(20);

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    maintab_widget = new QTabWidget();
    maintab_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    maintab_widget->setStyleSheet("QTabBar::tab { height: 70px; width: 300px; }");
    maintab_widget->setFont(font1);

    lot_monitor_page = new ui_lot_monitor_page();
    lot_monitor_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    carpark_monitor_page = new ui_carpark_monitor_page();
    carpark_monitor_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    report_tab_page = new ui_report_tab_page();
    report_tab_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setting_tab_page = new ui_setting_tab_page();
    setting_tab_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    alarm_tab_page = new ui_alarm_tab_page();
    alarm_tab_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


    maintab_widget->addTab(lot_monitor_page, "Lot Monitor");
    maintab_widget->addTab(carpark_monitor_page, "Carpark Monitor");
    maintab_widget->addTab(report_tab_page, "Report");
    maintab_widget->addTab(setting_tab_page, "Setting");
    maintab_widget->addTab(alarm_tab_page, "Alarm");
    mainLayout->addWidget(maintab_widget);

    init_data();

} // setupUi

void ui_main_tab_page::init_data()
{
    connect(maintab_widget, SIGNAL(currentChanged(int)), this, SLOT(tab_clicked(int)));
}

void ui_main_tab_page::tab_clicked(int index)
{
         if(index == PAGE_LOT_MONTIOR) lot_monitor_page->status->setText(QString::number(w->get_current_page_index()));
    else if(index == PAGE_CARPARK_MONITOR) carpark_monitor_page->status->setText(QString::number(w->get_current_page_index()));
    else if(index == PAGE_ALARM) alarm_tab_page->update_alarm();
}
