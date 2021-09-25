#ifndef UI_DISPLAY_STATUS_H
#define UI_DISPLAY_STATUS_H

#include "qt_inc.h"

class ui_display_status : public QWidget
{
    Q_OBJECT
public:
    explicit ui_display_status(QWidget *parent = nullptr);

    QGridLayout *mainLayout;
    QLabel      *lotid;
    QPushButton *btn_status;

signals:

public slots:
};

#endif // UI_DISPLAY_STATUS_H
