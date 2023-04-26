//main.cpp
#include <QApplication>
#include "GiaoDienChuongTrinh.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GiaoDien giaoDien;
    giaoDien.show();




    return a.exec();
}
