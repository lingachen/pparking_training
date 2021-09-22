#include "declaration.h"
#include "ui_selectreceipt_page.h"

ui_selectreceipt_page::ui_selectreceipt_page()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("ui_selectreceipt_page"));

    this->resize(1920,1080);
    this->setStyleSheet("background-color:black;color:white;");

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(30);
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

    title_completed = new QLabel(this);
    title_completed->setText("繳費完畢");
    title_completed->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_completed->setFont(font50);
    mainLayout->addWidget(title_completed, 1, 0, 2, 11, Qt::AlignHCenter | Qt::AlignVCenter);

    title_input_taxnum = new QLabel(this);
    title_input_taxnum->setText("請選擇發票列印方式: ");
    title_input_taxnum->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_input_taxnum->setFont(font36);
    mainLayout->addWidget(title_input_taxnum, 3, 2, 1, 11, Qt::AlignLeft | Qt::AlignVCenter);

    btn_taxnum_input = new QPushButton(this);
    btn_taxnum_input->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_taxnum_input->setText("輸入統編");
    btn_taxnum_input->setFont(font50);
    btn_taxnum_input->setStyleSheet("background-color:white;color:black;border:10px groove gray;");
    mainLayout->addWidget(btn_taxnum_input, 5, 2, 5, 4);   
    QObject::connect(btn_taxnum_input, SIGNAL(clicked()), this, SLOT(taxnum_input_clicked())); 

    btn_direct_print = new QPushButton(this);
    btn_direct_print->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btn_direct_print->setText("直接列印發票");
    btn_direct_print->setFont(font50);
    btn_direct_print->setStyleSheet("background-color:white;color:black;border:10px groove gray;");
    mainLayout->addWidget(btn_direct_print, 5, 6, 5, 4);   
    QObject::connect(btn_direct_print, SIGNAL(clicked()), this, SLOT(direct_print_clicked()));    

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

void ui_selectreceipt_page::init_data()
{
    current_page_index = SELECT_RECEIPT_PAGE;
    watchdog_main_page_tick = 0;
    send_status("");
    direct_print_clicked_flag = false;
    taxnum_input_clicked_flag = false;
}

void ui_selectreceipt_page::send_status(QString msg)
{
    status->setText(msg);
    update();
    status->repaint();
    QWidget::repaint();
}

void ui_selectreceipt_page::direct_print_clicked()
{
    watchdog_main_page_tick = 0;
    if(direct_print_clicked_flag == true) return;
    direct_print_clicked_flag = true;

    send_status("發票列印中");
   
    // request receipt id
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
                            "00000000",
                            calc_parking_fee.entry_time);

        // update printer counter
        minc_increase_printer_counter();

        // update payment log
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
                                        calc_parking_fee.parkingfee,
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
    else {
        send_status("發票號碼錯誤!!請聯繫管理中心");
        wait_ms(2000);
        w->change_page(MAIN_INPUT_PAGE);
    }
}

void ui_selectreceipt_page::taxnum_input_clicked()
{
    watchdog_main_page_tick = 0;
    if(direct_print_clicked_flag == true) return;
    taxnum_input_clicked_flag = true;
    w->change_page(TAXNUM_INPUT_PAGE);
}