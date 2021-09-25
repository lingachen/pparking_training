#ifndef UI_IPCAM_TAB_PAGE_H
#define UI_IPCAM_TAB_PAGE_H

#include "qt_inc.h"
#include "ui_display_status.h"
#include "ui_camera.h"

class ui_alarm_tab_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_alarm_tab_page(QWidget *parent = nullptr);

     QGridLayout        *mainLayout;
     QLabel             *status;
     ui_display_status  *lot_status[192];
     ui_camera          *camera;

     void update_alarm();

signals:

public slots:
     void status_clicked();
};

#endif // UI_IPCAM_TAB_PAGE_H
