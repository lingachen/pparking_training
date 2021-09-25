#include "declaration.h"
#include "ui_setting_floor_page.h"

ui_setting_floor_page::ui_setting_floor_page(QWidget *parent) : QWidget(parent)
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

    floor_id = new QLabel(this);
    floor_id->setText("Floor ID: ");
    floor_id->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    floor_id->setFont(font1);
    mainLayout->addWidget(floor_id, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

    inp_floor_id = new QLineEdit(this);
    inp_floor_id->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_floor_id->setFont(font1);
    mainLayout->addWidget(inp_floor_id, 1, 1, 1, 3, Qt::AlignLeft | Qt::AlignVCenter);

    floor_name = new QLabel(this);
    floor_name->setText("Floor Name: ");
    floor_name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    floor_name->setFont(font1);
    mainLayout->addWidget(floor_name, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

    inp_floor_name = new QLineEdit(this);
    inp_floor_name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_floor_name->setFont(font1);
    mainLayout->addWidget(inp_floor_name, 2, 1, 1, 3, Qt::AlignLeft | Qt::AlignVCenter);

    floor_image = new QLabel(this);
    floor_image->setText("Floor Image: ");
    floor_image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    floor_image->setFont(font1);
    mainLayout->addWidget(floor_image, 3, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

    inp_floor_image = new QLineEdit(this);
    inp_floor_image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inp_floor_image->setFont(font1);
    mainLayout->addWidget(inp_floor_image, 3, 1, 1, 3, Qt::AlignLeft | Qt::AlignVCenter);

    btn_load = new QPushButton(this);
    btn_load->setStyleSheet("background-color:white;color:black;");
    btn_load->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_load->setFont(font1);
    btn_load->setText("Load");
    mainLayout->addWidget(btn_load, 4, 0, 1, 1);
    QObject::connect(btn_load, SIGNAL(clicked()), this, SLOT(btn_load_clicked()));

    btn_floor_image1 = new QPushButton(this);
    btn_floor_image1->setStyleSheet("background-color:black;color:white;");
    btn_floor_image1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(btn_floor_image1, 1, 5, 4, 10);

    btn_add = new QPushButton(this);
    btn_add->setStyleSheet("background-color:white;color:black;");
    btn_add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_add->setFont(font1);
    btn_add->setText("Add");
    mainLayout->addWidget(btn_add, 4, 1, 1, 1);
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(btn_add_clicked()));

    btn_del = new QPushButton(this);
    btn_del->setStyleSheet("background-color:white;color:black;");
    btn_del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_del->setFont(font1);
    btn_del->setText("Del");
    mainLayout->addWidget(btn_del, 4, 2, 1, 1);
    QObject::connect(btn_del, SIGNAL(clicked()), this, SLOT(btn_del_clicked()));

    btn_upd = new QPushButton(this);
    btn_upd->setStyleSheet("background-color:white;color:black;");
    btn_upd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_upd->setFont(font1);
    btn_upd->setText("Update");
    mainLayout->addWidget(btn_upd, 4, 3, 1, 1);
    QObject::connect(btn_upd, SIGNAL(clicked()), this, SLOT(btn_upd_clicked()));

    btn_qry = new QPushButton(this);
    btn_qry->setStyleSheet("background-color:white;color:black;");
    btn_qry->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_qry->setFont(font1);
    btn_qry->setText("Query");
    mainLayout->addWidget(btn_qry, 4, 4, 1, 1);
    QObject::connect(btn_qry, SIGNAL(clicked()), this, SLOT(btn_qry_clicked()));

    init_data();

    info = new QTableWidget(50, header.size(), this);
    QFont font = info->horizontalHeader()->font();
    font.setPointSize( 14 );
    info->horizontalHeader()->setFont( font );
    for(int i=0; i<4; i++) info->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    info->setFont( font2 );
    info->setHorizontalHeaderLabels( header );
    info->setStyleSheet("background-color:white;color:black;");
    info->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(info, 5, 0, 10, 5);
    connect(info, SIGNAL(cellClicked(int, int)), this, SLOT(info_record_clicked(int, int)));

    btn_floor_image2 = new QPushButton(this);
    btn_floor_image2->setStyleSheet("background-color:black;color:white;");
    btn_floor_image2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(btn_floor_image2, 5, 5, 10, 10);

    show_floor_layout();
}

void ui_setting_floor_page::init_data()
{
    header << "Floor ID" << "Floor Name" << "Floor Image" << "RID";
    rid_selected = -1;
}

void ui_setting_floor_page::btn_load_clicked()
{
    QString image = inp_floor_image->text();
    btn_floor_image1->setStyleSheet("border-image: url("+image+")");
}

void ui_setting_floor_page::btn_add_clicked()
{
    struct cfg_floorplan_rec inp_floorplan;
    strcpy(inp_floorplan.floor_id, inp_floor_id->text().toStdString().c_str());
    strcpy(inp_floorplan.floor_name, inp_floor_name->text().toStdString().c_str());
    strcpy(inp_floorplan.Image, inp_floor_image->text().toStdString().c_str());
    strcpy(inp_floorplan.comments, "");
    int ret = minc_pgs_add_floorplan(&inp_floorplan);
}

void ui_setting_floor_page::btn_del_clicked()
{
    if(rid_selected != -1) {
        int ret = minc_pgs_del_floorplan(rid_selected);
    }
}

void ui_setting_floor_page::btn_upd_clicked()
{
    struct cfg_floorplan_rec inp_floorplan;
    strcpy(inp_floorplan.floor_id, inp_floor_id->text().toStdString().c_str());
    strcpy(inp_floorplan.floor_name, inp_floor_name->text().toStdString().c_str());
    strcpy(inp_floorplan.Image, inp_floor_image->text().toStdString().c_str());
    int ret = minc_pgs_upd_floorplan(&inp_floorplan);
}

void ui_setting_floor_page::btn_qry_clicked()
{
    struct cfg_floorplan_rec inp_floorplan;
    if(rid_selected != -1) {
        int ret = minc_pgs_query_cfg_floorplan2(rid_selected, &inp_floorplan);
        if( ret > 0) {
            inp_floor_id->setText(QString(inp_floorplan.floor_id));
            inp_floor_name->setText(QString(inp_floorplan.floor_name));
            inp_floor_image->setText(QString(inp_floorplan.Image));
        }
    }
    show_floor_layout();
}

void ui_setting_floor_page::info_record_clicked(int row, int col)
{
    QString image = info->item(row,2)->text();
    btn_floor_image2->setStyleSheet("border-image: url("+image+")");
    rid_selected = info->item(row,3)->text().toInt();
}

void ui_setting_floor_page::show_floor_layout()
{
    struct cfg_floorplan_rec out_floorplan_data[MAX_FLOORS];

    //get floorpalne table
    int floor_count = minc_pgs_query_cfg_floorplan(&out_floorplan_data[0]);

    //load data into table
    if(floor_count >= 0) {
        info->clear();
        info->setColumnCount(header.size());
        info->setRowCount(floor_count+1);
        info->setHorizontalHeaderLabels( header );
        for(int i=0; i<floor_count; i++) {
            info->setItem(i,0,new QTableWidgetItem(out_floorplan_data[i].floor_id));    //floor_id
            info->setItem(i,1,new QTableWidgetItem(out_floorplan_data[i].floor_name));  //floor_name
            info->setItem(i,2,new QTableWidgetItem(out_floorplan_data[i].Image));       //floor_image
            info->setItem(i,3,new QTableWidgetItem(QString::number(out_floorplan_data[i].id))); //rid
        }
        info->resizeColumnsToContents();
    }
}
