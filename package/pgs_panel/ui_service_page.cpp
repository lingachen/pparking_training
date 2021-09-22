#include "declaration.h"
#include "ui_service_page.h"

ui_service_page::ui_service_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_service_page"));

    title_hopper50_result = "50元硬幣總數: ";
    title_hopper10_result = "10元硬幣總數: ";

    this->resize(1920,1080);
    this->setStyleSheet("background-color:black;color:white;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
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

    title_engineering = new QLabel(this);
    title_engineering->setText("工程模式");
    title_engineering->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_engineering->setFont(font50);
    mainLayout->addWidget(title_engineering, 1, 0, 2, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    btn_hopper50 = new QPushButton(this);
    btn_hopper50->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_hopper50->setText("退50元硬幣");
    btn_hopper50->setFont(font36);
    btn_hopper50->setStyleSheet("background-color:white;color:black;border:10px groove gray;margin: 20px 50px;");
    mainLayout->addWidget(btn_hopper50, 4, 2, 1, 3);   
    QObject::connect(btn_hopper50, SIGNAL(clicked()), this, SLOT(hopper50_clicked())); 

    hopper50_result = new QLabel(this);
    hopper50_result->setText(title_hopper50_result);
    hopper50_result->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    hopper50_result->setFont(font36);
    mainLayout->addWidget(hopper50_result, 4, 5, 1, 6, Qt::AlignLeft | Qt::AlignVCenter);

    btn_hopper10 = new QPushButton(this);
    btn_hopper10->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_hopper10->setText("退10元硬幣");
    btn_hopper10->setFont(font36);
    btn_hopper10->setStyleSheet("background-color:white;color:black;border:10px groove gray;margin: 20px 50px;");
    mainLayout->addWidget(btn_hopper10, 6, 2, 1, 3);   
    QObject::connect(btn_hopper10, SIGNAL(clicked()), this, SLOT(hopper10_clicked())); 

    hopper10_result = new QLabel(this);
    hopper10_result->setText(title_hopper10_result);
    hopper10_result->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    hopper10_result->setFont(font36);
    mainLayout->addWidget(hopper10_result, 6, 5, 1, 6, Qt::AlignLeft | Qt::AlignVCenter);

    btn_back = new QPushButton(this);
    btn_back->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_back->setText("返回");
    btn_back->setFont(font36);
    btn_back->setStyleSheet("background-color:white;color:black;border:10px groove gray;margin: 20px 50px;");
    mainLayout->addWidget(btn_back, 8, 2, 1, 3);   
    QObject::connect(btn_back, SIGNAL(clicked()), this, SLOT(back_clicked())); 

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

void ui_service_page::init_data()
{
    current_page_index = SERVICE_PAGE;
    watchdog_main_page_tick = 0;
    send_status("");
    hopper50_result->setText(title_hopper50_result);
    hopper10_result->setText(title_hopper10_result);
}

void ui_service_page::hopper50_clicked()
{
    watchdog_main_page_tick = 0;
    QString password = "506373168888";
    int actual_count = 0;
    int return_minc_return_all_changes_with_passwd = minc_return_all_changes_with_passwd((char *)toStdstring(&password).c_str(), &actual_count);
    send_hopper50_result(actual_count);
}

void ui_service_page::hopper10_clicked()
{
    watchdog_main_page_tick = 0;
    QString password = "106373168888";
    int actual_count = 0;
    int return_minc_return_all_changes_with_passwd = minc_return_all_changes_with_passwd((char *)toStdstring(&password).c_str(), &actual_count);
    send_hopper10_result(actual_count);
}

void ui_service_page::back_clicked()
{
    watchdog_main_page_tick = 0;
    w->change_page(MAIN_INPUT_PAGE);
}

void ui_service_page::send_status(QString msg)
{
    status->setText(msg);
    update();
    status->repaint();
    QWidget::repaint();
}

void ui_service_page::send_hopper50_result(int hopper50_count)
{
    hopper50_result->setText(title_hopper50_result+QString::number(hopper50_count));
    update();
    hopper50_result->repaint();
    QWidget::repaint();
}

void ui_service_page::send_hopper10_result(int hopper10_count)
{
    hopper10_result->setText(title_hopper10_result+QString::number(hopper10_count));
    update();
    hopper10_result->repaint();
    QWidget::repaint();
}