#include "ui_camera.h"

ui_camera::ui_camera(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_camera"));

    this->resize(640,480);
    this->setStyleSheet("background-color:white;color:black;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    camera_image = new QPushButton(this);
    camera_image->setStyleSheet("background-color:black;color:white;");
    camera_image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(camera_image);

    init_data();
}

void ui_camera::init_data()
{

}
