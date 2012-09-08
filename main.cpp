#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
try
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
catch (char const *exn)
{
    qDebug("error: %s", exn);
    return EXIT_FAILURE;
}
