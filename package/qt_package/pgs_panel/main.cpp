#include "declaration.h"
#include "ui_mainwindow.h"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ui_mainwindow display;
    w = &display;
    display.show();
    return a.exec();
}
