#include "declaration.h"
#include "ui_setting_tab_page.h"

ui_setting_tab_page::ui_setting_tab_page(QWidget *parent) : QWidget(parent)
{
    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    QFont font1;
    font1.setPointSize(20);

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    settingtab_widget = new QTabWidget();
    settingtab_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    settingtab_widget->setStyleSheet("QTabBar::tab { height: 70px; width: 300px; }");
    settingtab_widget->setFont(font1);

    setting_floor_page = new ui_setting_floor_page();
    setting_floor_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setting_lot_page = new ui_setting_lot_page();
    setting_lot_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    settingtab_widget->addTab(setting_floor_page, "Floor Layout");
    settingtab_widget->addTab(setting_lot_page, "Floor Lot");
    mainLayout->addWidget(settingtab_widget);

    init_data();
}

void ui_setting_tab_page::init_data()
{
    connect(settingtab_widget, SIGNAL(currentChanged(int)), this, SLOT(tab_clicked(int)));
}

void ui_setting_tab_page::tab_clicked(int index)
{
    if(index == PAGE_SETTING_LOT) {
        setting_lot_page->combo_selected_level(setting_lot_page->combo_level->currentIndex());
    }
}
