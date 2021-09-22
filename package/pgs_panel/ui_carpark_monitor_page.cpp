#include "declaration.h"
#include "ui_carpark_monitor_page.h"

ui_carpark_monitor_page::ui_carpark_monitor_page(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_carpark_monitor_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(20);

    title_combo = new QLabel(this);
    title_combo->setText("Select Levels:");
    title_combo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_combo->setFont(font1);
    mainLayout->addWidget(title_combo, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    combo_level = new QComboBox(this);
    combo_level->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    combo_level->setFont(font1);
    combo_level->clear();
    for(int i= 0 ; i<Total_floor_count ;i++) combo_level->addItem(QString(cfg_floor_info[i].floor_id));
    mainLayout->addWidget(combo_level, 0, 1, 1, 1);

    status = new QLabel(this);
    status->setText("HELLO");
    status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    status->setFont(font1);
    mainLayout->addWidget(status, 0, 4, 1, 8, Qt::AlignHCenter | Qt::AlignVCenter);

    total_lots = new QLabel(this);
    total_lots->setText("Lots: ");
    total_lots->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    total_lots->setFont(font1);
    mainLayout->addWidget(total_lots, 1, 1, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    available = new QLabel(this);
    available->setText("Available: ");
    available->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    available->setFont(font1);
    mainLayout->addWidget(available, 1, 3, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    occupied = new QLabel(this);
    occupied->setText("Occupied: ");
    occupied->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    occupied->setFont(font1);
    mainLayout->addWidget(occupied, 1, 5, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    QImage image(cfg_floor_info[combo_level->currentIndex()].Image);
    QGraphicsScene* scene = new QGraphicsScene();
    map = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    map->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    map->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGTH-250);
    mainLayout->addWidget(map, 2, 0, 15, 12, Qt::AlignLeft | Qt::AlignVCenter);

    init_data();

} // setupUi

void ui_carpark_monitor_page::init_data()
{
    show_carpark_floor_map(combo_level->currentIndex());
    connect(combo_level, SIGNAL (activated(int)), this, SLOT(combo_selected_level(int)));
}

void ui_carpark_monitor_page::combo_selected_level(int index)
{
    show_carpark_floor_map(index);
    status->setText(QString::number(w->get_current_page_index()));
}

void ui_carpark_monitor_page::show_carpark_floor_map(int floor_index)
{
    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush blueBrush(Qt::blue);
    QPen   outlinePen(Qt::black);
    outlinePen.setWidth(2);

    // show floor map
    scene_carpark_setting->clear();
    map->setStyleSheet("background-image:url("+QString(cfg_floor_info[floor_index].Image)+");background-repeat:repeat;");
    map->setSceneRect(0, 0, map->frameSize().width(),map->frameSize().height());
    map->setScene(scene_carpark_setting);

    // read database
    struct data_pgs_rec data_pgs_rec_local[MAX_LOTS];
    int total_occupancy = 0;
    int total_data_pgs_local_count = minc_pgs_query_data_pgs_by_floor_id((char *)combo_level->currentText().toStdString().c_str(), &data_pgs_rec_local[0]);

    // display lot icon
    for(int i=0; i<total_data_pgs_local_count; i++) {
        show_lot_icon(i+data_pgs_rec_local[0].id-1, data_pgs_rec_local[i].lot_id, data_pgs_rec_local[i].status);
        if(QString::compare(data_pgs_rec_local[i].status,"car",Qt::CaseInsensitive)==0) total_occupancy++;
    }

    // display led icon
    for(int i=0; i<Total_floormap_led_count; i++) {
        int id = combo_level->currentIndex();
        if(strcmp(cfg_floor_led[i].floor_id, cfg_floor_info[id].floor_id) == 0) show_led_icon(cfg_floor_led[i].lot_id, QString::number(current_led_display_count[id][i]));
    }

    // show available lots
    show_available_lot(total_data_pgs_local_count, total_data_pgs_local_count-total_occupancy, total_occupancy);
}

void ui_carpark_monitor_page::show_led_icon(QString LED_ID, QString EmptyCount)
{
    // initial graphic
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    // get roi
    struct ROI_rec ROI;
    for(int i =0; i<Total_floormap_led_count;i++){
        if(QString::compare( cfg_floor_led[i].lot_id, LED_ID, Qt::CaseInsensitive)==0){
            strcpy(ROI.location_x,cfg_floor_led[i].location_x);
            strcpy(ROI.location_y,cfg_floor_led[i].location_y);
            strcpy(ROI.block_w,cfg_floor_led[i].block_w);
            strcpy(ROI.block_h,cfg_floor_led[i].block_h);
            break;
        }
    }

     // display led block
    carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), atoi(ROI.block_w), atoi(ROI.block_h), outlinePen, yellowBrush);
    carpark_setting_text      = scene_carpark_setting->addText(LED_ID+"\n" + EmptyCount );
    carpark_setting_text->setFont(QFont("Microsoft YaHei", 8, 50));
    carpark_setting_text->setPos(atoi(ROI.location_x), atoi(ROI.location_y));
}

void ui_carpark_monitor_page::show_lot_icon(int index, QString lot_id, QString result)
{

    // initial graphic
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);

    outlinePen.setWidth(2);

    // get roi
    struct ROI_rec ROI;
    strcpy(ROI.location_x, cfg_floor_lot[index].location_x); //out_floormap_led
    strcpy(ROI.location_y, cfg_floor_lot[index].location_y);
    strcpy(ROI.block_w, cfg_floor_lot[index].block_w);
    strcpy(ROI.block_h, cfg_floor_lot[index].block_h);

    // display lot block
         if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_CARS) == 0)      carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, redBrush);
    else if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_BLOCK) == 0)     carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, blueBrush);
    else if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_EMPTY) == 0)     carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, greenBrush);
    else if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_FAIL) == 0)      carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, yellowBrush);
    else if(strcmp(result.toStdString().c_str(), (char *)"") == 0)                   carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, blueBrush);
    else if(strcmp(result.toStdString().c_str(), "car")   == 0) carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, redBrush);
    else if(strcmp(result.toStdString().c_str(), "block") == 0) carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, blueBrush);
    else if(strcmp(result.toStdString().c_str(), "empty") == 0) carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, greenBrush);
    else if(strcmp(result.toStdString().c_str(), "fail")  == 0) carpark_setting_rectangle = scene_carpark_setting->addRect(atoi(ROI.location_x),atoi(ROI.location_y), (QString(ROI.block_w)).toInt(), (QString(ROI.block_h)).toInt(), outlinePen, yellowBrush);

    carpark_setting_text = scene_carpark_setting->addText(lot_id);
    carpark_setting_text->setFont(QFont("Microsoft YaHei", 7, 50));
    carpark_setting_text->setPos(atoi(ROI.location_x), atoi(ROI.location_y));
}

void ui_carpark_monitor_page::show_available_lot(int total_lots_val, int total_available_lots, int total_occupied_lots)
{
    //show lot inforation
    total_lots->setText("Lots: " + QString::number(total_lots_val));

    //show available lot
    available->setText("Available: " + QString::number(total_available_lots));

    //show occupled lot
    occupied->setText("Occupied: " + QString::number(total_occupied_lots));
}

void ui_carpark_monitor_page::update_available_lot(QString result)
{
    char valstr[100];

    strcpy(valstr, total_lots->text().toStdString().c_str());
    int total_lot_val = atoi(&valstr[6]);
    strcpy(valstr, available->text().toStdString().c_str());
    int available_lot_val = atoi(&valstr[11]);

         if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_CARS) == 0)  available_lot_val--;
    else if(strcmp(result.toStdString().c_str(), (char *)RESULT_PGS_EMPTY) == 0) available_lot_val++;
    else if(strcmp(result.toStdString().c_str(), "car")   == 0)                  available_lot_val--;
    else if(strcmp(result.toStdString().c_str(), "empty") == 0)                  available_lot_val++;

    if(available_lot_val < 0) available_lot_val = 0;
    if(available_lot_val > total_lot_val) available_lot_val = total_lot_val;

    show_available_lot(total_lot_val, available_lot_val, total_lot_val-available_lot_val);
}
