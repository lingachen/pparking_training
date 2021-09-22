#include "declaration.h"
#include "ui_report_input.h"

ui_report_input::ui_report_input(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_report_input"));

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(20);

    platenum = new QLabel(this);
    platenum->setText("Plate No: ");
    platenum->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    platenum->setFont(font1);
    mainLayout->addWidget(platenum, 0, 1, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    inp_platenum = new QLineEdit(this);
    inp_platenum->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_platenum->setFont(font1);
    mainLayout->addWidget(inp_platenum, 0, 3, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    stationid = new QLabel(this);
    stationid->setText("ID: ");
    stationid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    stationid->setFont(font1);
    mainLayout->addWidget(stationid, 1, 1, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    inp_stationid = new QLineEdit(this);
    inp_stationid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_stationid->setFont(font1);
    mainLayout->addWidget(inp_stationid, 1, 3, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    starttime = new QLabel(this);
    starttime->setText("StartTime(yymmddhh): ");
    starttime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    starttime->setFont(font1);
    mainLayout->addWidget(starttime, 0, 6, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    inp_starttime = new QLineEdit(this);
    inp_starttime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_starttime->setFont(font1);
    mainLayout->addWidget(inp_starttime, 0, 8, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    endtime = new QLabel(this);
    endtime->setText("EndTime(yymmddhh): ");
    endtime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    endtime->setFont(font1);
    mainLayout->addWidget(endtime, 1, 6, 1, 2, Qt::AlignRight | Qt::AlignVCenter);

    inp_endtime = new QLineEdit(this);
    inp_endtime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_endtime->setFont(font1);
    mainLayout->addWidget(inp_endtime, 1, 8, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    btn_search = new QPushButton(this);
    btn_search->setStyleSheet("background-color:white;color:black;");
    btn_search->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_search->setFont(font1);
    btn_search->setText("Search");
    mainLayout->addWidget(btn_search, 0, 11, 2, 2);

    btn_export = new QPushButton(this);
    btn_export->setStyleSheet("background-color:white;color:black;");
    btn_export->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_export->setFont(font1);
    btn_export->setText("Export");
    mainLayout->addWidget(btn_export, 0, 13, 2, 2);

    init_data();
}

void ui_report_input::init_data()
{

}
