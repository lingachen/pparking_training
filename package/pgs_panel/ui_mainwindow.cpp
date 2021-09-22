#include "declaration.h"
#include "ui_mainwindow.h"

ui_mainwindow::ui_mainwindow()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_mainwindow"));

    this->setCentralWidget(new QWidget());

    init_data();

    main_tab_page = new ui_main_tab_page();
    main_tab_page->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH);
    proxy = new QGraphicsProxyWidget();
    proxy = scene->addWidget(main_tab_page);
    view  = new QGraphicsView(this->centralWidget());
    view->setScene(scene);
    view->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGTH);
    view->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->rotate(0);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->resize(SCREEN_WIDTH, SCREEN_HEIGTH);

} // setupUi

void ui_mainwindow::init_data()
{
    // init api
    int ret = minc_pgs_init_api();

    // init variables
    current_page_id = 0;
    memset((struct available_lot_info_rec *)&available_lot_info, 0, MAX_FLOORS*sizeof(struct available_lot_info_rec));
    memset((char *)prev_pgs_lot_state, 0, MAX_LOTS*30);

    // read database
    Total_floor_count               = minc_pgs_query_cfg_floorplan(&cfg_floor_info[0]);
    Total_floormap_count            = minc_pgs_query_cfg_floormap(&cfg_floor_lot[0]);
    Total_floormap_led_count        = minc_pgs_query_cfg_floormap_Total_LED("LED", &cfg_floor_led[0]);
    Total_lpr_data_count            = minc_pgs_query_data_lpr(&out_data_lpr_rec[0]);
    Total_enf_data_count            = minc_pgs_query_data_enf(&out_data_enf_rec[0]);
    Total_data_pgs_count            = minc_pgs_query_data_pgs(&out_data_pgs_rec[0]);

    // set variables
    for(int i=0; i<Total_lpr_data_count; i++) {
        int val = atoi(out_data_lpr_rec[i].pageindex);
        if(max_page_no[LPR_MODE][0] < val) max_page_no[LPR_MODE][0] = val;
    }
    for(int i=0; i<Total_data_pgs_count; i++) {
             if(strcmp(out_data_pgs_rec[i].status, "car") == 0)   strcpy(prev_pgs_lot_state[i], RESULT_PGS_CARS);
        else if(strcmp(out_data_pgs_rec[i].status, "empty") == 0) strcpy(prev_pgs_lot_state[i], RESULT_PGS_EMPTY);
        else                                                      strcpy(prev_pgs_lot_state[i], RESULT_PGS_BLOCK);
        int val = atoi(out_data_pgs_rec[i].pageindex);
        int n   = get_floor_index(out_data_pgs_rec[i].floor_id);
        available_lot_info[n].total_lots++;
        if(max_page_no[PGS_MODE][n] < val) max_page_no[PGS_MODE][n]= val;
        for(int k=0; k<Total_floormap_led_count; k++) {
            if(strstr(out_data_pgs_rec[i].led_id, cfg_floor_led[k].lot_id) != NULL) {
                available_lot_info[n].total_led[k]++;
                if(strcmp(out_data_pgs_rec[i].status, "car") == 0) {
                    available_lot_info[n].led_occupied[k]++;
                }
            }
        }
    }
    for(int i=0; i<Total_enf_data_count; i++) {
        int val = atoi(out_data_enf_rec[i].pageindex);
        if(max_page_no[ENF_MODE][0] < val) max_page_no[ENF_MODE][0] = val;
    }

    for(int i=0; i<Total_floormap_led_count; i++) {
        for(int k=0; k<Total_floor_count; k++) {
            current_led_display_count[k][i] = available_lot_info[k].total_led[i] - available_lot_info[k].led_occupied[i];
        }
    }

    init_udp();
}

void ui_mainwindow::init_udp()
{
    receiver = new QUdpSocket(this);
    receiver->bind(2010, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(udp_receiver_data()));
}

int ui_mainwindow::get_current_page_index()
{
    int n10000, n1000, n100, n1;

    n10000 = w->main_tab_page->maintab_widget->currentIndex();
    if(n10000 == PAGE_LOT_MONTIOR) n1000 = w->main_tab_page->lot_monitor_page->combo_monitor_mode->currentIndex();
    else                           n1000 = 0;

         if(n10000 == PAGE_LOT_MONTIOR)     n100 = atoi(w->main_tab_page->lot_monitor_page->combo_level->currentText().toStdString().c_str());
    else if(n10000 == PAGE_CARPARK_MONITOR) n100 = atoi(w->main_tab_page->carpark_monitor_page->combo_level->currentText().toStdString().c_str());
    else                                    n100 = 0;
    if(n10000 == PAGE_LOT_MONTIOR) n1 = w->main_tab_page->lot_monitor_page->current_page;
    else                           n1 = 0;
    return (n10000*10000+n1000*1000+n100*100+n1);
}

void ui_mainwindow::udp_receiver_data()
{
    QByteArray datagram;
    while(receiver->hasPendingDatagrams()) {
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size());
        QString information = QString::fromStdString(datagram.toStdString());

        QString json_format     = information;
        QJsonDocument d         = QJsonDocument::fromJson(json_format.toUtf8());
        QJsonObject json_obj    = d.object();

        QString Mode    = json_obj["Mode"].toString();
        QString PageID  = json_obj["PageID"].toString();

        current_page_id = get_current_page_index();

        // for led
        if (QString::compare(Mode.toStdString().data(), "LED", Qt::CaseInsensitive)==0) {
            QString Ledid      = json_obj["LedID"].toString();
            QString EmptyCount = json_obj["EmptyCount"].toString();
            char valstr[20];
            strcpy(valstr, Ledid.toStdString().c_str());
            int id = atoi(&valstr[3]);
            int fid = ((PageID.toInt())/100) % 10;
            strcpy(valstr, EmptyCount.toStdString().c_str());
            current_led_display_count[fid][id-1] = atoi(valstr);

            if(current_page_id == PageID.toInt()) {
                w->main_tab_page->carpark_monitor_page->show_led_icon(Ledid, EmptyCount);
            }
        }

        // normal process
        if(current_page_id == PageID.toInt()) {
             if (QString::compare(Mode.toStdString().data(), "PGS", Qt::CaseInsensitive)==0 ||
                 QString::compare(Mode.toStdString().data(), "LPR", Qt::CaseInsensitive)==0 ||
                 QString::compare(Mode.toStdString().data(), "ENF", Qt::CaseInsensitive)==0) {
                  QString Lotid     = json_obj["Lotid"].toString();
                  QString Platenum  = json_obj["VehiclePlateNo"].toString();
                  QString Imagefile = json_obj["CapturedImg"].toString();
                  QString Timeinfo  = json_obj["Time"].toString();

                 // get display index
                 int index = get_display_index((char *)Lotid.toStdString().c_str());
                 if(index >= 0) {
                    w->main_tab_page->lot_monitor_page->show_lot_image(index, Lotid, Platenum, Timeinfo, Imagefile);
                 }

                 // only for ENF
                 if(QString::compare(Mode.toStdString().data(), "ENF", Qt::CaseInsensitive)==0) {
                     int id = PageID.toInt() - 2000;
                     max_page_no[ENF_MODE][0] = id;
                 }
             }

             // for blacklist
             if (QString::compare(Mode.toStdString().data(),"BLC",Qt::CaseInsensitive)==0) {
                 QString Lotid          = json_obj["Lotid"].toString();
                 QString VehiclePlateNo = json_obj["VehiclePlateNo"].toString();

                  w->main_tab_page->carpark_monitor_page->status->setText("Lotid = "+ Lotid +" VehiclePlateNo = " + VehiclePlateNo);
                  w->main_tab_page->lot_monitor_page->status->setText("Lotid = "+ Lotid +" VehiclePlateNo = " + VehiclePlateNo);
             }
        }
        else {
            // only check PGS (for lot icon update)
            if (QString::compare(Mode.toStdString().data(), "PGS", Qt::CaseInsensitive)==0) {
                 QString Result = json_obj["ResultType"].toString();
                 QString Lotid  = json_obj["Lotid"].toString();
                 int lotid_index = get_pgs_lotid_index((char *)Lotid.toStdString().c_str());
                 int led_page_id = ((PageID.toInt())/100)*100 - 1000 + 10000; // 1402: 340
                 if(current_page_id == led_page_id) {                                        
                     // get display index
                     int index = get_floor_lot_index((char *)Lotid.toStdString().c_str());
                     if(index >= 0) {
                        w->main_tab_page->carpark_monitor_page->show_lot_icon(index, Lotid, Result);
                        // update available lots                        
                        if(strcmp(Result.toStdString().c_str(), RESULT_PGS_CARS) == 0 ||
                           strcmp(Result.toStdString().c_str(), RESULT_PGS_EMPTY) == 0) {
                            if(strcmp(prev_pgs_lot_state[lotid_index], Result.toStdString().c_str()) != 0) w->main_tab_page->carpark_monitor_page->update_available_lot(Result);
                        }
                     }
                }
                 if(strcmp(Result.toStdString().c_str(), RESULT_PGS_CARS) == 0 ||
                    strcmp(Result.toStdString().c_str(), RESULT_PGS_EMPTY) == 0) {
                    strcpy(prev_pgs_lot_state[lotid_index], Result.toStdString().c_str());
                 }
            }
        }
     }
    datagram.clear();
}
