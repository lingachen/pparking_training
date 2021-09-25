#include "declaration.h"

ui_taxnum_page::ui_taxnum_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_taxnum_page"));

    title_keypad_input  = "請輸入統編號碼(8 碼): ";

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
    mainLayout->addWidget(keypad_title, 1, 3, 1, 8);

    input_keypad = new ui_keypad();
    input_keypad->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(input_keypad,3, 3, 6, 5);
    for(int i=0; i<12; i++) {
             if(i == 9 ) QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(clear_clicked()));  
        else if(i == 11) QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(confirm_clicked()));  
        else             QObject::connect(input_keypad->keypad[i], SIGNAL(clicked()), this, SLOT(numbers_clicked()));          
    }

    back = new QPushButton(this);
    back->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    back->setText("返回");
    back->setFont(font50);
    back->setStyleSheet("background-color:white;color:black;border:10px groove gray;margin: 0px 20px;");
    mainLayout->addWidget(back, 8, 8, 1, 2);   
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

void ui_taxnum_page::init_data()
{
    current_page_index = TAXNUM_INPUT_PAGE;
    watchdog_main_page_tick = 0;
    confirm_clicked_flag = false;
    keypad_title->setText(title_keypad_input);
    keypad_input_string = "";
    send_status("");
}

void ui_taxnum_page::send_status(QString msg)
{
    status->setText(msg);
    update();
    status->repaint();
    QWidget::repaint();
}

void ui_taxnum_page::numbers_clicked()
{
    watchdog_main_page_tick = 0;
    if(status->text().size() > 0) status->setText("");
    
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) {
        QString buttonText = pButton->text();
        keypad_title->setText(keypad_title->text()+buttonText);
        keypad_input_string += buttonText;
    }
}

void ui_taxnum_page::clear_clicked()
{
    init_data();
}

void ui_taxnum_page::confirm_clicked()
{
    watchdog_main_page_tick = 0;
    if(keypad_input_string.size() != 8) {
        send_status("輸入錯誤 !!");
        return;
    }

    if(confirm_clicked_flag == true) return;
    confirm_clicked_flag = true;

    send_status("發票列印中");

    int  receipt_rid;
    char invoice_receipt_number[100];
    QString monthid_str = get_monthid();
    int ret = minc_request_receipt_id((char *)toStdstring(&monthid_str).c_str(), invoice_receipt_number, &receipt_rid);
    if(ret >= 0) {
        // update receipt database and print receipt
        minc_update_receipt(receipt_rid,
                            invoice_receipt_number,
                            calc_parking_fee.paid_time,
                            calc_parking_fee.parkingfee,
                            (char *)toStdstring(&keypad_input_string).c_str(),
                            calc_parking_fee.entry_time);

        // update payment
        minc_update_payment_log(invoice_receipt_number,
                                find_hourly_cars[find_hourly_cars_select_index].platenum,
                                "hourly",
                                (dollars.coin_1000_count*1000)+(dollars.coin_500_count*500)+(dollars.coin_200_count*200)+(dollars.coin_100_count*100)+(dollars.coin_50_count*50)+(dollars.coin_10_count*10)-(dollars.hopper_50_count*50)-(dollars.hopper_10_count*10),
                                calc_parking_fee.paid_time,
                                calc_parking_fee.entry_time,
                                dollars.coin_1000_count,
                                dollars.coin_500_count,
                                dollars.coin_200_count,
                                dollars.coin_100_count,
                                dollars.coin_50_count,
                                dollars.coin_10_count,
                                dollars.coin_5_count,
                                dollars.hopper_50_count,
                                dollars.hopper_10_count,
                                dollars.hopper_5_count);

        // update movement
        minc_update_movement_record(&find_hourly_cars[find_hourly_cars_select_index],
                                    calc_parking_fee.paid_time,
                                    calc_parking_fee.parking_time_mins,
                                    calc_parking_fee.parkingfee,
                                    calc_parking_fee.paidfee);

        // update over_payment if have
        if(apm_return_changes_value > 0) {
                int received_fee = dollars.coin_100_count*100 + dollars.coin_50_count*50 + dollars.coin_10_count*10 + dollars.coin_5_count*5;
                minc_update_over_payment(invoice_receipt_number,
                                        find_hourly_cars[find_hourly_cars_select_index].platenum,
                                        "hourly",
                                        calc_parking_fee.parkingfee-calc_parking_fee.paidfee,
                                        received_fee,
                                        calc_parking_fee.paid_time,
                                        calc_parking_fee.entry_time,
                                        dollars.coin_1000_count,
                                        dollars.coin_500_count,
                                        dollars.coin_200_count,
                                        dollars.coin_100_count,
                                        dollars.coin_50_count,
                                        dollars.coin_10_count,
                                        dollars.coin_5_count,
                                        dollars.hopper_50_count,
                                        dollars.hopper_10_count,
                                        dollars.hopper_5_count);
        }

        // go back main windows
        w->change_page(MAIN_INPUT_PAGE);
    }
}

void ui_taxnum_page::back_clicked()
{
    watchdog_main_page_tick = 0;
    w->change_page(SELECT_RECEIPT_PAGE);
}