#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include "sensordata.h"
#include "xrfsensordata.h"
#include "emssensordata.h"
#include "libssensordata.h"
#include "sensorclient.h"
//#include "../SensorProcessServer/sensordataparser.h"

void testStart();
void test(int);
SensorData* createSensorData(unsigned char);

QString applicationPath;
QString hostName;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    applicationPath = a.applicationDirPath();

    if (argc == 1)
        hostName = "127.0.0.1";
    else if(argc == 2)
        hostName = argv[1];
    else if(argc > 2)
        //wrong numbers of command parameters
        printf("Invalid command format. Use ./test [hostname] please!\n");

    testStart();

    return 0;

    //return a.exec();
}

void testStart()
{
    while(1){
    test(XRF_SENSOR);
    test(EMS_SENSOR);
    test(LIBS_SENSOR);
    }
}

void test(int sensorType){

    //Test data file
    QString testDataFile;
    int filedsSize;
    SensorData* sensorData = createSensorData(sensorType);
    int count = 0;

    switch (sensorType){
        case XRF_SENSOR:
            testDataFile = applicationPath + "/xrftestdata.txt";
//            testDataFile = "C:/Qt/Tools/QtCreator/bin/SensorProjectClient/xrftestdata.txt";
            filedsSize = 5;
            sensorData->setLocation(SENSOR_LOCATION1);
            sensorData->setVersion("1.0.0");
            break;
        case EMS_SENSOR:
            testDataFile = applicationPath + "/emstestdata.txt";
            //testDataFile = "C:/Qt/Tools/QtCreator/bin/SensorProjectClient/emstestdata.txt";
            filedsSize = 6;
            sensorData->setLocation(SENSOR_LOCATION2);
            sensorData->setVersion("1.0.0.1");
            break;
        case LIBS_SENSOR:
            testDataFile = applicationPath + "/libstestdata.txt";
            //testDataFile = "C:/Qt/Tools/QtCreator/bin/SensorProjectClient/libstestdata.txt";
            filedsSize = 5;
            sensorData->setLocation(SENSOR_LOCATION3);
            sensorData->setVersion("1.12.0.1");
            break;
        default:
            break;
    }

    QFile file(testDataFile);
    if(!file.open(QIODevice::ReadOnly)){
    }
    QTextStream in(&file);
    sensorData->setTimeStamp(QDateTime::currentMSecsSinceEpoch());
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList  fields = line.split(",");
        if (fields.size()<filedsSize)
            //invalid data, go next;
            continue;
        switch (sensorData->addData(&fields)){
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
                printf("Invalid data!\n");
                break;
        }
    }

    if(count>0){
        SensorClient *socketClient = new SensorClient(0);
        if(socketClient->connectToHost(hostName)){
            socketClient->writeData(sensorData->packAllData());
        }else{
            printf("Cannot find server!\n");
        }
        delete socketClient;

/*        //for local test only.
        SensorDataParser *serverParser = new SensorDataParser();
        QByteArray buffer = sensorData->packAllData();
        //buffer = buffer.mid(4,buffer.length());
        serverParser->dataParser(&buffer);*/
    }

    delete sensorData;
    file.close();
}

void emsTest(QString hostName){
}

//sensor data factory
SensorData* createSensorData(unsigned char sensorType )
{
    switch (sensorType){
        case XRF_SENSOR:
            return new XRFSensorData();
        case EMS_SENSOR:
            return new EMSSensorData();
            break;
        case LIBS_SENSOR:
            return new LIBSSensorData();
            break;
        default:
            break;
        //unsupported type
    }
    return 0;
}
