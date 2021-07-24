#include "homescreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("Abhishek Bharti");
    a.setOrganizationDomain("https://www.github.com/ab28dev");
    a.setApplicationName("Basic Text Editor");
    a.setApplicationDisplayName("Basic Text Editor");
    a.setApplicationVersion("0.1.0 Beta");

    HomeScreen w;
    w.show();
    return a.exec();
}
