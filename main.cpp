#include <iostream>

#include "mainwindow.h"
#include "build_number.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "vsplitter v0.1 (build " << BUILD << ")\n";

    QApplication app(argc, argv);

    // Qt sets the locale in the QApplication constructor, but libmpv requires
    // the LC_NUMERIC category to be set to "C", so change it back.
    std::setlocale(LC_NUMERIC, "C");

    MainWindow w;
    w.move(500,200);
    w.show();

    return app.exec();
}
