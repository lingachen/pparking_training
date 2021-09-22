#include "declaration.h"
#include "ui_lot_monitor_page.h"

ui_lot_monitor_page::ui_lot_monitor_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_lot_monitor_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(20);

    title_combo = new QLabel(this);
    title_combo->setText("Select Monitor Mode:");
    title_combo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_combo->setFont(font1);
    mainLayout->addWidget(title_combo, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    combo_monitor_mode = new QComboBox(this);
    combo_monitor_mode->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    combo_monitor_mode->setFont(font1);
    combo_monitor_mode->clear();
    combo_monitor_mode->addItem("LPR Mode");
    combo_monitor_mode->addItem("PGS Mode");
    combo_monitor_mode->addItem("ENF Mode");
    combo_monitor_mode->addItem("BLK Mode");
    mainLayout->addWidget(combo_monitor_mode, 0, 1, 1, 2);

    title_combo2 = new QLabel(this);
    title_combo2->setText("Select Levels:");
    title_combo2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_combo2->setFont(font1);
    mainLayout->addWidget(title_combo2, 0, 3, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    combo_level = new QComboBox(this);
    combo_level->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    combo_level->setFont(font1);
    combo_level->clear();
    for(int i= 0 ; i<Total_floor_count ;i++) combo_level->addItem(QString(cfg_floor_info[i].floor_id));
    mainLayout->addWidget(combo_level, 0, 4, 1, 1);

    status = new QLabel(this);
    status->setText("HELLO");
    status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    status->setFont(font1);
    mainLayout->addWidget(status, 0, 5, 1, 7, Qt::AlignHCenter | Qt::AlignVCenter);

    for(int i=0; i<9; i++) {
        display_block[i] = new ui_display_block();
        display_block[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        display_block[i]->setObjectName(QString::number(i));
        display_block[i]->btn_camera->setObjectName(QString::number(i));
        mainLayout->addWidget(display_block[i], (i/3)*5+1, (i%3)*4, 5, 4);
        QObject::connect(display_block[i]->btn_camera, SIGNAL(clicked()), this, SLOT(camera_clicked()));
    }

    total_pages  = max_page_no[combo_monitor_mode->currentIndex()][combo_level->currentIndex()] + 1;
    current_page = 0;

    btn_page_prev = new QPushButton(this);
    btn_page_prev->setStyleSheet("background-color:white;color:black;");
    btn_page_prev->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_page_prev->setFont(font1);
    btn_page_prev->setText("Prev");
    mainLayout->addWidget(btn_page_prev, 16, 5, 1, 1);
    QObject::connect(btn_page_prev, SIGNAL(clicked()), this, SLOT(page_prev_clicked()));

    page_list = new QLabel(this);
    page_list->setText(QString::number(current_page)+"/"+QString::number(total_pages));
    page_list->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    page_list->setFont(font1);
    mainLayout->addWidget(page_list, 16, 6, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    btn_page_next = new QPushButton(this);
    btn_page_next->setStyleSheet("background-color:white;color:black;");
    btn_page_next->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_page_next->setFont(font1);
    btn_page_next->setText("Next");
    mainLayout->addWidget(btn_page_next, 16, 7, 1, 1);
    QObject::connect(btn_page_next, SIGNAL(clicked()), this, SLOT(page_next_clicked()));

    title_combo2->hide();
    combo_level->hide();

    init_data();

} // setupUi

void ui_lot_monitor_page::init_data()
{
    connect(combo_monitor_mode, SIGNAL (activated(int)), this, SLOT(combo_selected(int)));
    connect(combo_level, SIGNAL (activated(int)), this, SLOT(combo_selected_level(int)));
    if(combo_monitor_mode->currentIndex() == PGS_MODE) {
        title_combo2->show();
        combo_level->show();
    }
    update_lot_monitor_images(combo_monitor_mode->currentIndex());
}

void ui_lot_monitor_page::camera_clicked()
{
    camera = new ui_camera();
    camera->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    camera->show();

    QPushButton* pCamera = qobject_cast<QPushButton*>(sender());
    if (pCamera) {
       QString cameraidx = pCamera->objectName();
       int idx = cameraidx.toInt();
       int pgs_index = get_pgs_lotid_index(display_list[idx]);
       QString image_path = "/tmp/PGS.jpg";
       int ret = minc_pgs_get_image(out_data_pgs_rec[pgs_index].camera_ip, "jvt","admin", "Pp990088");
       if(ret>=0) camera->camera_image->setStyleSheet("border-image: url("+image_path+")");
    }
}

void ui_lot_monitor_page::page_prev_clicked()
{
    current_page--;
    if(current_page < 0) current_page = 0;
    page_list->setText(QString::number(current_page)+"/"+QString::number(total_pages));
    status->setText(QString::number(w->get_current_page_index()));

    // update whole 9 images
    update_lot_monitor_images(combo_monitor_mode->currentIndex());
}

void ui_lot_monitor_page::page_next_clicked()
{
    current_page++;
    if(current_page > total_pages-1) current_page = total_pages-1;
    page_list->setText(QString::number(current_page)+"/"+QString::number(total_pages));
    status->setText(QString::number(w->get_current_page_index()));

    // update whole 9 images
    update_lot_monitor_images(combo_monitor_mode->currentIndex());
}

void ui_lot_monitor_page::combo_selected(int index)
{
    // calculate max_page & display page_list
    total_pages  = max_page_no[index][combo_level->currentIndex()] + 1;
    current_page = 0;
    page_list->setText(QString::number(current_page)+"/"+QString::number(total_pages));
    status->setText(QString::number(w->get_current_page_index()));

    // show floor level selected if PGS
    if(combo_monitor_mode->currentIndex() == PGS_MODE) {
        title_combo2->show();
        combo_level->show();
    }
    else {
        title_combo2->hide();
        combo_level->hide();
    }

    // update whole 9 images
    update_lot_monitor_images(index);

}

void ui_lot_monitor_page::combo_selected_level(int index)
{
    total_pages  = max_page_no[combo_monitor_mode->currentIndex()][index] + 1;
    current_page = 0;
    page_list->setText(QString::number(current_page)+"/"+QString::number(total_pages));
    status->setText(QString::number(w->get_current_page_index()));

    // update whole 9 images
    update_lot_monitor_images(combo_monitor_mode->currentIndex());
}

void ui_lot_monitor_page::show_lot_image(int index, QString lot_id, QString platenum, QString update_time, QString image)
{
    //show lot_id
    display_block[index]->lotid->setText(lot_id);

    //show platenum
    display_block[index]->platenum->setText(platenum);

    //show time
    display_block[index]->timev->setText(convert_time_format((char *)update_time.toStdString().c_str()));

    // show image
    display_block[index]->car_image->setStyleSheet("border-image: url("+image+")");
}


void ui_lot_monitor_page::update_lot_monitor_images(int combo_index)
{
    struct data_lpr_rec data_lpr_rec_local[MAX_STATIONS];
    struct data_pgs_rec data_pgs_rec_local[MAX_LOTS];
    struct data_enf_rec data_enf_rec_local[MAX_ENFORCEMENTS];
    int    total_display_count;
    char   pageindex[100];

    sprintf(pageindex, "%d", current_page);

         if(combo_index == LPR_MODE) total_display_count = minc_pgs_query_data_lpr_by_pageindex(pageindex ,&data_lpr_rec_local[0]);
    else if(combo_index == PGS_MODE) total_display_count = minc_pgs_query_data_pgs_by_pageindex(pageindex, cfg_floor_info[combo_level->currentIndex()].floor_id ,&data_pgs_rec_local[0]);
    else if(combo_index == ENF_MODE) total_display_count = minc_pgs_query_data_enf_by_pageindex(pageindex ,&data_enf_rec_local[0]);

    if(total_display_count > 9) total_display_count = 9;

    for(int i=0; i<total_display_count; i++) {
        display_block[i]->show();
        if(combo_index == LPR_MODE) {
            strcpy(display_list[i], data_lpr_rec_local[i].lot_id);
            show_lot_image(i, QString(data_lpr_rec_local[i].lot_id), QString(data_lpr_rec_local[i].plate_no), QString(data_lpr_rec_local[i].modified_time), QString(data_lpr_rec_local[i].image_path));
        }
        else if(combo_index == PGS_MODE) {
            strcpy(display_list[i], data_pgs_rec_local[i].lot_id);
            show_lot_image(i, QString(data_pgs_rec_local[i].lot_id), QString(data_pgs_rec_local[i].plate_no), QString(data_pgs_rec_local[i].modified_time), QString(data_pgs_rec_local[i].image_path));
        }
        else if(combo_index == ENF_MODE) {
            sprintf(display_list[i],"%d",data_enf_rec_local[i].id);
            show_lot_image(i, QString::number(data_enf_rec_local[i].id), QString(data_enf_rec_local[i].platenum), QString(data_enf_rec_local[i].modified_time), QString(data_enf_rec_local[i].car_image));
        }
    }

    if(total_display_count < 9) {
        for(int i=total_display_count; i<9; i++) {
            strcpy(display_list[i], "");
            display_block[i]->hide();
        }
    }
}
