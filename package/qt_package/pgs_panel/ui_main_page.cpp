#include "declaration.h"
#include "ui_main_page.h"

ui_main_page::ui_main_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_main_page"));

    title_keypad_input = "請輸入車牌號碼(數字 3 or 4 碼): ";

    this->resize(1920,1080);
    this->setStyleSheet("background-color:black;color:white;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    
    QFont font50;
    font50.setPointSize(50);
    QFont font36;
    font36.setPointSize(36);
     
    main_header = new QLabel(this);
    main_header->setText("泊客智能停車管理系統");
    main_header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    main_header->setFont(font50);
    mainLayout->addWidget(main_header, 0, 0, 1, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    keypad_title = new QLabel(this);
    keypad_title->setText(title_keypad_input);
    keypad_title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    keypad_title->setFont(font36);
    mainLayout->addWidget(keypad_title, 1, 1, 1, 10);

    input_keypad = new ui_keypad();
    input_keypad->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(input_keypad,2, 1, 8, 9); 
    for(int i=0; i<12; i++) {
             if(i == 9 ) QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(clear_clicked()));  
        else if(i == 11) QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(confirm_clicked()));  
        else             QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(numbers_clicked()));          
    }

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

void ui_main_page::init_data()
{
    current_page_index = MAIN_INPUT_PAGE;
    keypad_title->setText(title_keypad_input);
    keypad_input_string = "";
    status->setText("");
}

void ui_main_page::send_status(QString msg)
{
    status->setText(msg);
    update();
    status->repaint();
    QWidget::repaint();
}

void ui_main_page::numbers_clicked()
{
    if(status->text().size() > 0) status->setText("");

    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) {
        QString buttonText = pButton->text();
        keypad_title->setText(keypad_title->text()+buttonText);
        keypad_input_string += buttonText;
    }
}

void ui_main_page::clear_clicked()
{
    init_data();
}

void ui_main_page::confirm_clicked()
{
    printf("plate=%s\n", (char *)toStdstring(&keypad_input_string).c_str());

    if(keypad_input_string.size() < 3 || keypad_input_string.size() > 4) {
        send_status("輸入錯誤 !!");
        return;
    }
    else if(keypad_input_string.size() > 10) {
        int return_minc_check_passwd =  minc_check_passwd((char *)(toStdstring(&keypad_input_string).c_str()));
        if(return_minc_check_passwd == 0) {
            w->change_page(SERVICE_PAGE);
        }
        return;
    }
    else {
        minc_find_hourly_cars_no = minc_find_hourly_cars((char *)(toStdstring(&keypad_input_string).c_str()), &find_hourly_cars[0]);
        keypad_input_string = "";
         if(minc_find_hourly_cars_no < 1) {
            send_status("找不到車號 , 請再輸入一次");
            keypad_title->setText(title_keypad_input);
         }
         else {
            if(apm_return_changes_ready_flag == false) send_status("本系統可繳費但無法找零，如需找零請聯絡管理中心");            
            w->change_page(SELECT_CAR_PAGE);
            w->selectcar_page->update_page();
         }        
    }
}