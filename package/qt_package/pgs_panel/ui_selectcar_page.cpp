#include "declaration.h"
#include "ui_selectcar_page.h"

ui_selectcar_page::ui_selectcar_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_selectcar_page"));

    this->resize(1920,1080);
    this->setStyleSheet("background-color:black;color:white;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(20, 0, 20, 0); 
    
    QFont font50;
    font50.setPointSize(50);
    QFont font36;
    font36.setPointSize(36);
     
    main_header = new QLabel(this);
    main_header->setText("泊客智能停車管理系統");
    main_header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    main_header->setFont(font50);
    mainLayout->addWidget(main_header, 0, 0, 1, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    input_image_select = new ui_image_select();
    input_image_select->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(input_image_select, 1, 0, 9, 10);
    for(int i=0; i<4; i++) { 
        QObject::connect(input_image_select->image[i], SIGNAL(clicked()), this, SLOT(images_clicked()));          
    }

    page_up = new QPushButton(this);
    page_up->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    page_up->setText("上一頁");
    page_up->setFont(font36);
    page_up->setStyleSheet("background-color:white;color:black;border:6px groove gray;");
    mainLayout->addWidget(page_up, 4, 10, 1, 1);   
    QObject::connect(page_up, SIGNAL(clicked()), this, SLOT(page_up_clicked()));    

    page_dn = new QPushButton(this);
    page_dn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    page_dn->setText("下一頁");
    page_dn->setFont(font36);
    page_dn->setStyleSheet("background-color:white;color:black;border:6px groove gray;");
    mainLayout->addWidget(page_dn, 6, 10, 1, 1);   
    QObject::connect(page_dn, SIGNAL(clicked()), this, SLOT(page_dn_clicked())); 

    back = new QPushButton(this);
    back->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    back->setText("返回");
    back->setFont(font36);
    back->setStyleSheet("background-color:white;color:black;border:6px groove gray;");
    mainLayout->addWidget(back, 8, 10, 1, 1);   
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(back_clicked())); 

    status = new QLabel(this);
    status->setText("");
    status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    status->setFont(font36);
    mainLayout->addWidget(status, 10, 0, 1, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    main_tailer = new QLabel(this);
    main_tailer->setText("歡迎使用停車系統 , 需要客服請聯絡 0800-035181");
    main_tailer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    main_tailer->setFont(font36);
    mainLayout->addWidget(main_tailer, 11, 0, 1, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    init_data();
    
} // setupUi

void ui_selectcar_page::init_data()
{
    current_page_index = SELECT_CAR_PAGE;
    watchdog_main_page_tick = 0;
    page_index = 0;
    page_count = 0;
    page_up->hide();
    page_dn->hide(); 
    send_status("");
}

void ui_selectcar_page::update_page()
{ 
    if(minc_find_hourly_cars_no == 0)  page_count = 0; 
    else                               page_count = (minc_find_hourly_cars_no-1)/4 + 1;

    int index1 = page_index*4;
    int index2 = (page_index+1)*4 - 1;
    if(index2 > minc_find_hourly_cars_no-1) index2 = minc_find_hourly_cars_no-1;

    for(int i=index1; i<=index2; i++) {     
         QString qt_car_img_filename = toQstring(find_hourly_cars[i].img_filename);
         input_image_select->image[i%4]->setStyleSheet("border-image: url("+ qt_car_img_filename+")");
    }

    if(minc_find_hourly_cars_no <= 4) {
        page_up->hide();
        page_dn->hide();      
    }
    else {        
        if(page_index == 0) {
            page_up->hide();
            page_dn->show(); 
        }
        else if(page_index == page_count-1) {
            page_up->show();
            page_dn->hide();  
        }
        else {
            page_up->show();
            page_dn->show();  
        }
    }
    
}

int ui_selectcar_page::check_parking_fee(int movement_rid)
{
    int ret = minc_calc_parking_fee(movement_rid, &calc_parking_fee);
    if(ret == -1) {
        send_status("系統錯誤請重新輸入");
        wait_ms(2000);
        return -1;
    }
    else if(ret == 2) {
        send_status("已繳費請盡速離場");
        wait_ms(2000);
        return -1;
    }
    else if(ret == -2) {
        send_status("已超過離場時間15分鐘請重新繳費");
        wait_ms(2000);
    }
    return 0;
}

void ui_selectcar_page::send_status(QString msg)
{
    status->setText(msg);
    update();
    status->repaint();
    QWidget::repaint();
}

void ui_selectcar_page::page_up_clicked()
{
    watchdog_main_page_tick = 0;
    for(int i=0; i<4; i++) input_image_select->image[i]->setStyleSheet("");
    page_index--;
    if(page_index < 0) page_index = 0;
    update_page();
}

void ui_selectcar_page::page_dn_clicked()
{
    watchdog_main_page_tick = 0;
    for(int i=0; i<4; i++) input_image_select->image[i]->setStyleSheet("");
    page_index++;
    if(page_index > page_count) page_index = page_count;
    update_page();
}

void ui_selectcar_page::back_clicked()
{
    watchdog_main_page_tick = 0;
    for(int i=0; i<4; i++) input_image_select->image[i]->setStyleSheet("");
    w->change_page(MAIN_INPUT_PAGE);
}

void ui_selectcar_page::images_clicked()
{
    watchdog_main_page_tick = 0;
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) {
        QString buttonName = pButton->objectName(); 
        find_hourly_cars_select_index = page_index*4 + buttonName.toInt();  
        int rid = find_hourly_cars[find_hourly_cars_select_index].movement_rid;
        int ret = check_parking_fee(rid);
        if(ret == -1) {
            w->change_page(MAIN_INPUT_PAGE);
            return;
        }
        else {
            w->change_page(PAYMENT_PAGE);
            w->payment_page->update_page(find_hourly_cars_select_index);
            return;
        }   
    }
    w->change_page(MAIN_INPUT_PAGE);
}