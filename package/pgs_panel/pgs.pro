#-------------------------------------------------
#
# Project created by QtCreator 2020-03-11T13:45:09
#
#-------------------------------------------------
QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pgs
TEMPLATE = app


SOURCES += main.cpp \
           ui_mainwindow.cpp \           
           ui_lot_monitor_page.cpp \
           ui_display_block.cpp \
           utils.cpp \
            ui_main_tab_page.cpp \
            ui_carpark_monitor_page.cpp \
            ui_report_tab_page.cpp \
            ui_setting_tab_page.cpp \
            ui_report_lpr_page.cpp \
            ui_report_pgs_page.cpp \
            ui_report_enf_page.cpp \
            ui_report_occupied_page.cpp \
            ui_setting_lot_page.cpp \
            ui_setting_floor_page.cpp \
            ui_report_all_page.cpp \
            ui_report_input.cpp \
    ui_camera.cpp

HEADERS  += declaration.h \
            qt_inc.h \
            defines.h \
            external_vars.h \
            external_func.h \
            main.h \
            ui_mainwindow.h \                     
            ui_lot_monitor_page.h \
            ui_display_block.h \
            utils.h \
            ui_main_tab_page.h \
            ui_carpark_monitor_page.h \
            ui_report_tab_page.h \
            ui_setting_tab_page.h \
            ui_report_lpr_page.h \
            ui_report_pgs_page.h \
            ui_report_enf_page.h \
            ui_report_occupied_page.h \
            ui_setting_lot_page.h \
            ui_setting_floor_page.h \
            ui_report_all_page.h \
            ui_report_input.h \
            main_api.h \
    ui_camera.h

LIBS += /usr/lib/libpgs_api.so



