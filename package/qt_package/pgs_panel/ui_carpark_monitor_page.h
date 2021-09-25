#ifndef UI_CARPARK_MONITOR_PAGE_H
#define UI_CARPARK_MONITOR_PAGE_H

#include "qt_inc.h"

class ui_carpark_monitor_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_carpark_monitor_page(QWidget *parent = nullptr);
    QGridLayout     *mainLayout;
    QLabel          *title_combo;
    QComboBox       *combo_level;
    QLabel          *status;
    QLabel          *level;
    QLabel          *total_lots;
    QLabel          *available;
    QLabel          *occupied;

    QGraphicsView     *map;
    QGraphicsScene    *scene_carpark_setting = new QGraphicsScene();
    QGraphicsRectItem *carpark_setting_rectangle;
    QGraphicsTextItem *carpark_setting_text;

    void init_data();
    void show_carpark_floor_map(int floor_index);
    void show_led_icon(QString LED_ID, QString EmptyCount);
    void show_lot_icon(int index, QString lot_id, QString result);
    void show_available_lot(int total_lots_val, int total_available_lots, int total_occupied_lots);
    void update_available_lot(QString result);

signals:

public slots:
    void combo_selected_level(int index);
};

#endif // UI_CARPARK_MONITOR_PAGE_H
