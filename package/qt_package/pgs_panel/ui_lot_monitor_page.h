#ifndef UI_LOT_MONITOR_PAGE_H
#define UI_LOT_MONITOR_PAGE_H

#include "qt_inc.h"
#include "ui_display_block.h"
#include "ui_camera.h"

class ui_lot_monitor_page: public QWidget
{
    Q_OBJECT
public:    
    QGridLayout      *mainLayout;
    QLabel           *title_combo;
    QComboBox        *combo_monitor_mode;
    QLabel           *title_combo2;
    QComboBox        *combo_level;
    QLabel           *status;    
    QPushButton      *btn_page_prev;
    QPushButton      *btn_page_next;
    QLabel           *page_list;
    ui_display_block *display_block[9];
    ui_camera        *camera;
    int              total_pages;
    int              current_page;

    ui_lot_monitor_page();

    void init_data();
    void show_lot_image(int index, QString lot_id, QString platenum, QString update_time, QString image);
    void update_lot_monitor_images(int combo_index);

public slots:
    void camera_clicked();
    void combo_selected(int index);
    void combo_selected_level(int index);
    void page_prev_clicked();
    void page_next_clicked();
};

#endif // UI_LOT_MONITOR_PAGE_H
