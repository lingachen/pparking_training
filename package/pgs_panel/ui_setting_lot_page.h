#ifndef UI_SETTING_LOT_PAGE_H
#define UI_SETTING_LOT_PAGE_H

#include "qt_inc.h"

class ui_setting_lot_page : public QWidget
{
    Q_OBJECT
public:
    explicit ui_setting_lot_page(QWidget *parent = nullptr);
    QGridLayout      *mainLayout;
    QLabel           *status;
    QLabel           *title_combo;
    QComboBox        *combo_level;
    QLabel           *title_combo2;
    QComboBox        *combo_type;
    QPushButton      *btn_add;
    QPushButton      *btn_del;
    QPushButton      *btn_upd;
    QPushButton      *btn_qry;
    QTableWidget     *info;
    QStringList      header[2];
    int              rid_selected;
    int              info_index_selected;

    QGraphicsView     *map;
    QGraphicsScene    *scene_carpark_setting = new QGraphicsScene();
    QGraphicsRectItem *carpark_setting_rectangle;
    QGraphicsTextItem *carpark_setting_text;

    void init_data();
    void show_floor_info();
    void show_lot_icon(char *lot_id, int x, int y, int w, int h);

signals:

public slots:
    void btn_add_clicked();
    void btn_del_clicked();
    void btn_upd_clicked();
    void btn_qry_clicked();
    void info_record_clicked(int row, int col);
    void combo_selected_level(int index);
    void combo_selected_type(int index);
    void mousePressEvent ( QMouseEvent * ev );
};

#endif // UI_SETTING_LOT_PAGE_H
