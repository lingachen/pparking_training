#include "declaration.h"
#include "ui_display_block.h"

ui_display_block::ui_display_block()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_display_block"));

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(14);

    lbl_lotid = new QLabel(this);
    lbl_lotid->setText("LotID:");
    lbl_lotid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lbl_lotid->setFont(font1);
    mainLayout->addWidget(lbl_lotid, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    lotid = new QLabel(this);
    lotid->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lotid->setFixedWidth(3*14);
    lotid->setText("");
    lotid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lotid->setFont(font1);
    mainLayout->addWidget(lotid, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    lbl_platenum = new QLabel(this);
    lbl_platenum->setText("Plate:");
    lbl_platenum->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lbl_platenum->setFont(font1);
    mainLayout->addWidget(lbl_platenum, 0, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    platenum = new QLabel(this);
    platenum->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    platenum->setFixedWidth(8*14);
    platenum->setText("");
    platenum->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    platenum->setFont(font1);
    mainLayout->addWidget(platenum, 0, 3, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    lbl_timev = new QLabel(this);
    lbl_timev->setText("Time:");
    lbl_timev->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lbl_timev->setFont(font1);
    mainLayout->addWidget(lbl_timev, 0, 5, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    timev = new QLabel(this);
    timev->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timev->setFixedWidth(18*14);
    timev->setText("");
    timev->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    timev->setFont(font1);
    mainLayout->addWidget(timev, 0, 6, 1, 4, Qt::AlignLeft | Qt::AlignVCenter);

    btn_camera = new QPushButton(this);
    btn_camera->setStyleSheet("background-color:blue;color:black;margin:10px 5px 15px 0px;");
    btn_camera->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_camera->setFont(font1);
    btn_camera->setText("camera");
    mainLayout->addWidget(btn_camera, 0, 10, 1, 1);

    car_image = new QPushButton(this);
    car_image->setStyleSheet("background-color:black;color:white;");
    car_image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(car_image, 1, 0, 4, 11);
} // setupUi
