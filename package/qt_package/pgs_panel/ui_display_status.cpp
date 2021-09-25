#include "declaration.h"
#include "ui_display_status.h"

ui_display_status::ui_display_status(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_display_status"));

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(14);

    lotid = new QLabel(this);
    lotid->setText("  ");
    lotid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lotid->setFont(font1);
    mainLayout->addWidget(lotid, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    btn_status = new QPushButton(this);
    btn_status->setStyleSheet("background-color:black;color:white;");
    btn_status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(btn_status, 1, 0, 1, 1);
}
