#include "JCDemoRealTimeCurve.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JCDemoRealTimeCurve w;
    w.show();

    return a.exec();
}
