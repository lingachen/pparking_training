#include "declaration.h"
#include "ui_report_pgs_page.h"

ui_report_pgs_page::ui_report_pgs_page(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_report_pgs_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

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

    report_input = new ui_report_input();
    report_input->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(report_input, 2, 0, 3, 15);
    QObject::connect(report_input->btn_search, SIGNAL(clicked()), this, SLOT(btn_search_clicked()));
    QObject::connect(report_input->btn_export, SIGNAL(clicked()), this, SLOT(btn_export_clicked()));

    init_data();

    info = new QTableWidget(50, header.size(), this);
    QFont font = info->horizontalHeader()->font();
    font.setPointSize( 14 );
    info->horizontalHeader()->setFont( font );
    for(int i=0; i<7; i++) info->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    info->setFont( font2 );
    info->setHorizontalHeaderLabels( header );
    info->setStyleSheet("background-color:white;color:black;");
    info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(info, 5, 0, 10, 10);
    connect(info, SIGNAL(cellClicked(int, int)), this, SLOT(info_record_clicked(int, int)));

    car_image = new QPushButton(this);
    car_image->setStyleSheet("background-color:black;color:white;");
    car_image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(car_image, 5, 10, 10, 5);
}

void ui_report_pgs_page::init_data()
{
    header << "Modified_time" << "Lot_id" << "Platenum" << "Ptype" << "Movement_time" << "Car_image" << "Comments";
}

void ui_report_pgs_page::btn_search_clicked()
{
    char inp_datetime_yymmddhh_start[100];
    char inp_datetime_yymmddhh_stop[100];
    char inp_platenum[100];
    char lot_id[100];

    strcpy(inp_datetime_yymmddhh_start, report_input->inp_starttime->text().toStdString().c_str());
    strcpy(inp_datetime_yymmddhh_stop, report_input->inp_endtime->text().toStdString().c_str());
    strcpy(inp_platenum, report_input->inp_platenum->text().toStdString().c_str());
    strcpy(lot_id, report_input->inp_stationid->text().toStdString().c_str());

    info->clear();
    info->setColumnCount(0);
    info->setRowCount(0);

    struct log_pgs_movement_rec *report_page_log_pgs_movement = (struct log_pgs_movement_rec *)malloc(30000*sizeof(struct log_pgs_movement_rec));
    int ret_lpr_movement = minc_pgs_query_log_pgs_movement_by_report(inp_datetime_yymmddhh_start, inp_datetime_yymmddhh_stop, inp_platenum, lot_id, &report_page_log_pgs_movement[0]);
    info->setColumnCount(7);
    info->setRowCount(ret_lpr_movement+1);
    info->setHorizontalHeaderLabels( header );
    for(int i=0; i<ret_lpr_movement; i++) {
        info->setItem(i,0,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].modified_time)));   //modified_time
        info->setItem(i,1,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].lot_id)));      //station_id
        info->setItem(i,2,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].platenum)));        //platenum
        info->setItem(i,3,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].ptype)));           //ptype
        info->setItem(i,4,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].movement_time)));   //movement_time
        info->setItem(i,5,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].car_image)));       //car_image
        info->setItem(i,6,new QTableWidgetItem(QString(report_page_log_pgs_movement[i].comments)));        //comments
        info->resizeColumnsToContents();
    }
    free(report_page_log_pgs_movement);
}

void ui_report_pgs_page::btn_export_clicked()
{

}

void ui_report_pgs_page::info_record_clicked(int row, int col)
{
    QString image = info->item(row,5)->text();
    car_image->setStyleSheet("border-image: url("+image+")");
}
