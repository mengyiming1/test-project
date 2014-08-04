#include <QCoreApplication>
#include "testsensorserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    new TestSensorServer(0);

    return a.exec();
}
