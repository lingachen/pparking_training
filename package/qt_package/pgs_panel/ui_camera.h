#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include "qt_inc.h"

class ui_camera : public QWidget
{
    Q_OBJECT
public:
    explicit ui_camera(QWidget *parent = nullptr);
    QGridLayout *mainLayout;
    QPushButton *camera_image;

    void init_data();

signals:

public slots:
};

#endif // UI_CAMERA_H
