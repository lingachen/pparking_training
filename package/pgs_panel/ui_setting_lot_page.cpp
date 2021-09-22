#include "declaration.h"
#include "ui_setting_lot_page.h"

ui_setting_lot_page::ui_setting_lot_page(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_setting_floor_page"));

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(20);
    QFont font2;
    font2.setPointSize(12);

    status = new QLabel(this);
    status->setText("HELLO");
    status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    status->setFont(font1);
    mainLayout->addWidget(status, 0, 0, 1, 15, Qt::AlignHCenter | Qt::AlignVCenter);

    title_combo = new QLabel(this);
    title_combo->setText("Select Levels:");
    title_combo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_combo->setFont(font1);
    mainLayout->addWidget(title_combo, 1, 0, 1, 2, Qt::AlignHCenter | Qt::AlignVCenter);

    combo_level = new QComboBox(this);
    combo_level->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    combo_level->setFont(font1);
    combo_level->clear();
    for(int i= 0 ; i<Total_floor_count ;i++) combo_level->addItem(QString(cfg_floor_info[i].floor_id));
    mainLayout->addWidget(combo_level, 1, 2, 1, 1);
    connect(combo_level, SIGNAL (activated(int)), this, SLOT(combo_selected_level(int)));

    title_combo2 = new QLabel(this);
    title_combo2->setText("Data Type:");
    title_combo2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_combo2->setFont(font1);
    mainLayout->addWidget(title_combo2, 2, 0, 1, 2, Qt::AlignHCenter | Qt::AlignVCenter);

    combo_type = new QComboBox(this);
    combo_type->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    combo_type->setFont(font1);
    combo_type->clear();
    combo_type->addItem(QString("Floor Lot Loc"));
    combo_type->addItem(QString("Floor Lot Param"));
    mainLayout->addWidget(combo_type, 2, 2, 1, 2);
    connect(combo_type, SIGNAL (activated(int)), this, SLOT(combo_selected_type(int)));

    btn_add = new QPushButton(this);
    btn_add->setStyleSheet("background-color:white;color:black;");
    btn_add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_add->setFont(font1);
    btn_add->setText("Add");
    mainLayout->addWidget(btn_add, 3, 1, 1, 1);
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(btn_add_clicked()));

    btn_del = new QPushButton(this);
    btn_del->setStyleSheet("background-color:white;color:black;");
    btn_del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_del->setFont(font1);
    btn_del->setText("Del");
    mainLayout->addWidget(btn_del, 3, 2, 1, 1);
    QObject::connect(btn_del, SIGNAL(clicked()), this, SLOT(btn_del_clicked()));

    btn_upd = new QPushButton(this);
    btn_upd->setStyleSheet("background-color:white;color:black;");
    btn_upd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_upd->setFont(font1);
    btn_upd->setText("Update");
    mainLayout->addWidget(btn_upd, 3, 3, 1, 1);
    QObject::connect(btn_upd, SIGNAL(clicked()), this, SLOT(btn_upd_clicked()));

    btn_qry = new QPushButton(this);
    btn_qry->setStyleSheet("background-color:white;color:black;");
    btn_qry->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_qry->setFont(font1);
    btn_qry->setText("Query");
    mainLayout->addWidget(btn_qry, 3, 4, 1, 1);
    QObject::connect(btn_qry, SIGNAL(clicked()), this, SLOT(btn_qry_clicked()));

    init_data();

    int type_selected = combo_type->currentIndex();
    info = new QTableWidget(50, header[type_selected].size(), this);
    QFont font = info->horizontalHeader()->font();
    font.setPointSize( 14 );
    info->horizontalHeader()->setFont( font );
    for(int i=0; i<header[type_selected].size(); i++) info->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    info->setFont( font2 );
    info->setHorizontalHeaderLabels( header[type_selected] );
    info->setStyleSheet("background-color:white;color:black;");
    info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(info, 4, 0, 11, 5);
    connect(info, SIGNAL(cellClicked(int, int)), this, SLOT(info_record_clicked(int, int)));

    int floor_selected = combo_level->currentIndex();
    QImage image(cfg_floor_info[floor_selected].Image);
    QGraphicsScene *scene = new QGraphicsScene();
    map = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    map->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(map, 1, 5, 14, 10);
}

void ui_setting_lot_page::init_data()
{
    rid_selected = -1;
    info_index_selected = -1;
    header[0] << "id" << "Lot ID" << "Block X" << "Block Y" << "Block W" << "Block H" << "Comments";
    header[1] << "id" << "Floor ID" << "Lot ID" << "Platenum" << "Camera IP" << "LED ID" << "Controller IP" << "Page Index" << "Status" << "Car Image" << "Comments";
}

void ui_setting_lot_page::btn_add_clicked()
{
    if(combo_type->currentIndex() == PAGE_SETTING_FLOOR) {
        struct cfg_floormap_rec inp_floormap;
        strcpy(inp_floormap.lot_id, "000");
        strcpy(inp_floormap.floor_id, combo_level->currentText().toStdString().c_str());
        strcpy(inp_floormap.location_x, "000");
        strcpy(inp_floormap.location_y, "000");
        strcpy(inp_floormap.block_w, "000");
        strcpy(inp_floormap.block_h, "000");
        strcpy(inp_floormap.comments, "");
        int ret = minc_pgs_add_floormap(&inp_floormap);
    }
    else if(combo_type->currentIndex() == PAGE_SETTING_LOT) {

    }
    show_floor_info();
}

void ui_setting_lot_page::btn_del_clicked()
{
    if(rid_selected != -1) {
        if(combo_type->currentIndex() == PAGE_SETTING_FLOOR) {
            int ret = minc_pgs_del_floormap(rid_selected);
        }
        else if(combo_type->currentIndex() == PAGE_SETTING_LOT) {

        }
        show_floor_info();
    }
}

void ui_setting_lot_page::btn_upd_clicked()
{
    if(combo_type->currentIndex() == PAGE_SETTING_FLOOR) {
        struct cfg_floormap_rec inp_floormap;
        inp_floormap.id = info->item(info_index_selected,0)->text().toInt();
        strcpy(inp_floormap.lot_id, (char *)info->item(info_index_selected,1)->text().toStdString().c_str());
        strcpy(inp_floormap.floor_id, combo_level->currentText().toStdString().c_str());
        strcpy(inp_floormap.location_x, (char *)info->item(info_index_selected,2)->text().toStdString().c_str());
        strcpy(inp_floormap.location_y, (char *)info->item(info_index_selected,3)->text().toStdString().c_str());
        strcpy(inp_floormap.block_w, (char *)info->item(info_index_selected,4)->text().toStdString().c_str());
        strcpy(inp_floormap.block_h, (char *)info->item(info_index_selected,5)->text().toStdString().c_str());
        strcpy(inp_floormap.comments, (char *)info->item(info_index_selected,6)->text().toStdString().c_str());
        int ret = minc_pgs_upd_floormap(&inp_floormap);
    }
    else if(combo_type->currentIndex() == PAGE_SETTING_LOT) {

    }
    show_floor_info();
}

void ui_setting_lot_page::btn_qry_clicked()
{
    show_floor_info();
}

void ui_setting_lot_page::info_record_clicked(int row, int col)
{
    rid_selected = info->item(row,0)->text().toInt();
    info_index_selected = row;
    status->setText("ID: " + QString::number(rid_selected));
}

void ui_setting_lot_page::combo_selected_level(int index)
{
    scene_carpark_setting->clear();
    map->setStyleSheet("background-image:url("+QString(cfg_floor_info[index].Image)+");background-repeat:repeat;");
    map->setSceneRect(0,0,map->frameSize().width(),map->frameSize().height());
    map->setScene(scene_carpark_setting);

    show_floor_info();
}

void ui_setting_lot_page::combo_selected_type(int index)
{
    info->clear();
    info->setColumnCount(header[index].size());
    info->setRowCount(50);
    info->setHorizontalHeaderLabels( header[index] );
    for(int i=0; i<header[index].size(); i++) info->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

    show_floor_info();
}

void ui_setting_lot_page::show_floor_info()
{
    info->clear();
    info->setColumnCount(header[combo_type->currentIndex()].size());
    info->setRowCount(50);
    info->setHorizontalHeaderLabels( header[combo_type->currentIndex()] );

    if(combo_type->currentIndex() == SETTING_TYPE_FLOOR_LOC) {
        struct cfg_floormap_rec *out_cfg_floormap = (struct cfg_floormap_rec *) malloc(MAX_LOTS*sizeof(struct cfg_floormap_rec));
        int pgs_count = minc_pgs_query_cfg_floormap_by_floor_id(cfg_floor_info[combo_level->currentIndex()].floor_id, out_cfg_floormap);
        if(pgs_count > 0) {
            info->setRowCount(pgs_count+1);
            for(int i=0; i<pgs_count; i++) {
                info->setItem(i, 0,new QTableWidgetItem(QString(QString::number(out_cfg_floormap[i].id))));
                info->setItem(i, 1,new QTableWidgetItem(QString(out_cfg_floormap[i].lot_id)));      //lot_id
                info->setItem(i, 2,new QTableWidgetItem(QString(out_cfg_floormap[i].location_x)));  //location_x
                info->setItem(i, 3,new QTableWidgetItem(QString(out_cfg_floormap[i].location_y)));  //location_y
                info->setItem(i, 4,new QTableWidgetItem(QString(out_cfg_floormap[i].block_w)));     //block_w
                info->setItem(i, 5,new QTableWidgetItem(QString(out_cfg_floormap[i].block_h)));     //block_h
                info->setItem(i, 6,new QTableWidgetItem(QString(out_cfg_floormap[i].comments)));    //comments
                info->resizeColumnsToContents();
                show_lot_icon(out_cfg_floormap[i].lot_id, atoi(out_cfg_floormap[i].location_x), atoi(out_cfg_floormap[i].location_y), atoi(out_cfg_floormap[i].block_w), atoi(out_cfg_floormap[i].block_h));
            }
        }
        free(out_cfg_floormap);
    }
    else if(combo_type->currentIndex() == SETTING_TYPE_FLOOR_PARAM) {
        struct data_pgs_rec *out_data_pgs_rec = (struct data_pgs_rec *) malloc(MAX_LOTS*sizeof(struct data_pgs_rec));
        int pgs_count = minc_pgs_query_data_pgs_by_floor_id(cfg_floor_info[combo_level->currentIndex()].floor_id, out_data_pgs_rec);
        if(pgs_count > 0) {
            info->setRowCount(pgs_count+1);
            for(int i=0; i<pgs_count; i++) {
                info->setItem(i, 0,new QTableWidgetItem(QString(QString::number(out_data_pgs_rec[i].id))));
                info->setItem(i, 1,new QTableWidgetItem(QString(out_data_pgs_rec[i].floor_id)));        //floor_id
                info->setItem(i, 2,new QTableWidgetItem(QString(out_data_pgs_rec[i].lot_id)));          //lot_id
                info->setItem(i, 3,new QTableWidgetItem(QString(out_data_pgs_rec[i].plate_no)));        //plate_no
                info->setItem(i, 4,new QTableWidgetItem(QString(out_data_pgs_rec[i].camera_ip)));       //camera_ip
                info->setItem(i, 5,new QTableWidgetItem(QString(out_data_pgs_rec[i].led_id)));          //led_id
                info->setItem(i, 6,new QTableWidgetItem(QString(out_data_pgs_rec[i].controller_ip)));   //controller_ip
                info->setItem(i, 7,new QTableWidgetItem(QString(out_data_pgs_rec[i].pageindex)));       //pageindex
                info->setItem(i, 8,new QTableWidgetItem(QString(out_data_pgs_rec[i].status)));          //status
                info->setItem(i, 9,new QTableWidgetItem(QString(out_data_pgs_rec[i].image_path)));      //car image
                info->setItem(i, 10,new QTableWidgetItem(QString(out_data_pgs_rec[i].comments)));        //comments
                info->resizeColumnsToContents();
            }
        }
        free(out_data_pgs_rec);
    }
}

void ui_setting_lot_page::show_lot_icon(char *lot_id, int x, int y, int w, int h)
{
    // initial graphic
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);

    outlinePen.setWidth(2);

    if(strstr(lot_id, "LED") != 0) carpark_setting_rectangle = scene_carpark_setting->addRect(x, y, w, h, outlinePen, yellowBrush);
    else                           carpark_setting_rectangle = scene_carpark_setting->addRect(x, y, w, h, outlinePen, greenBrush);

    carpark_setting_text = scene_carpark_setting->addText(lot_id);
    carpark_setting_text->setFont(QFont("Microsoft YaHei", 7, 50));
    carpark_setting_text->setPos(x, y);
}

void ui_setting_lot_page::mousePressEvent (QMouseEvent * event )
{
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());

    QPoint origin = map->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = map->mapToScene(origin);
    status->setText(QString::number(origin.x())+","+QString::number(origin.y()));

}
