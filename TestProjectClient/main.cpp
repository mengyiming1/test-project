#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include "xrfsensordata.h"
#include "sensorclient.h"

int main(int argc, char *argv[])
{
    QString hostName;
    QCoreApplication a(argc, argv);

    if (argc == 1)
        hostName = "127.0.0.1";
    else if(argc == 2)
        hostName = argv[1];
    else if(argc > 2)
        //wrong numbers of command parameters
        printf("Invalid command format. Use ./test [hostname] please!\n");

    testStart();

    return a.exec();
}

void testStart(QString hostName)
{
    xrfTest(hostName);
}

void xrfTest(QString hostName){
    //Test data file
    QString testDataFile = "xrftestdata.txt";
    SensorData* sensorData = createSensorData(XRF_SENSOR);
    int count = 0;

    QFile file(testDataFile);
    QTextStream in(&file);
    QString line = in.readLine();
    sensorData->setLocation(SENSOR_LOCATION1);
    sensorData->setVersion("1.0.0");
    sensorData->setTimeStamp(QDateTime::currentMSecsSinceEpoch());
    while(!in.atEnd()) {
        QStringList  fields = line.split(",");
        if (fields.size()<5)
            //invalid data, go next;
            continue;
        switch (sensorData->addData(fields)){
            case 0:
                count++;
                break;
            case 1:
                printf("Invalid data!\n");
                break;
            case 2:
                printf("Invalid data!\n");
                break;
            case 3:
                printf("Invalid data!\n");
                break;
            case 4:
                printf("Invalid data!\n");
                break;
            case 5:
                printf("Invalid data!\n");
                break;
            default:
        }
    }

    if(count>0){
        SensorClient *socketClient = new SensorClient(this);
        socketClient.connectToHost(hostName);
        socketClient.writeData(sensorData->packAllData());
        delete socketClient;
    }

    delete sensorData;
    file.close();
}

void addToSensorData(QStringList& fields)
{

}

//sensor data factory
SensorData* createSensorData(unsigned char sensorType )
{
    switch (sensorType){
        case XRF_SENSOR:
            return new XRFSensorData();
        case EMS_SENSOR:
            break;
        case LIBS_SENSOR:
            break;
        default:
        //unsupported type
    }
    return 0;
}
