#include "declaration.h"
#include "ui_alarm_tab_page.h"

ui_alarm_tab_page::ui_alarm_tab_page(QWidget *parent) : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_alarm_tab_page"));

    this->resize(SCREEN_WIDTH,SCREEN_HEIGTH);
    this->setStyleSheet("background-color:white;color:black;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font1;
    font1.setPointSize(14);

    status = new QLabel(this);
    status->setText("HELLO");
    status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    status->setFont(font1);
    mainLayout->addWidget(status, 0, 0, 1, 16, Qt::AlignHCenter | Qt::AlignVCenter);

    for(int i=0; i<Total_data_pgs_count; i++) {
        lot_status[i] = new ui_display_status();
        lot_status[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        lot_status[i]->lotid->setText(QString("LotID: ")+out_data_pgs_rec[i].lot_id);
        lot_status[i]->btn_status->setObjectName(QString::number(i));
        lot_status[i]->btn_status->setStyleSheet("background-color:red;color:black;");
        mainLayout->addWidget(lot_status[i], (i/16)+1, (i%16), 1, 1);
        QObject::connect(lot_status[i]->btn_status, SIGNAL(clicked()), this, SLOT(status_clicked()));
    }    
}

void ui_alarm_tab_page::status_clicked()
{
    camera = new ui_camera();
    camera->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    camera->show();

    QPushButton* pCamera = qobject_cast<QPushButton*>(sender());
    if (pCamera) {
       QString cameraidx = pCamera->objectName();
       int idx = cameraidx.toInt();
       int pgs_index = get_pgs_lotid_index(out_data_pgs_rec[idx].lot_id);
       QString image_path = "/tmp/PGS.jpg";
       int ret = minc_pgs_get_image(out_data_pgs_rec[pgs_index].camera_ip, "jvt","admin", "Pp990088");
       if(ret>=0) camera->camera_image->setStyleSheet("border-image: url("+image_path+")");
    }
}

void ui_alarm_tab_page::update_alarm()
{
    struct data_alarm_rec *data_alarm = (struct data_alarm_rec *)malloc(MAX_LOTS*sizeof(struct data_alarm_rec));
    int n = minc_pgs_read_alarm(data_alarm);
    if(n <= 0) {
        free(data_alarm);
        return;
    }
    time_t ct;
    time(&ct);
    for(int i=0; i<n; i++) {
        int wd_val = atoi(data_alarm[i].watchdog_time);
        if(wd_val == -1) continue;
        if(ct-wd_val > 200) strcpy(data_alarm[i].status, "Fail");
        else                strcpy(data_alarm[i].status, "Good");
        minc_pgs_update_alarm(false, (char *)data_alarm[i].lot_id, data_alarm[i].status);
        int p = get_pgs_lotid_index(data_alarm[i].lot_id);
        if(strcmp(data_alarm[i].status, "Fail") == 0)  lot_status[p]->btn_status->setStyleSheet("background-color:red;color:black;");
        else                                           lot_status[p]->btn_status->setStyleSheet("background-color:green;color:black;");
    }
    free(data_alarm);
}
