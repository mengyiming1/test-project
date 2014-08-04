#ifndef SENSORDATAPARSER_H
#define SENSORDATAPARSER_H

#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QDateTime>

//defination of sensor type code
#define XRF_SENSOR 1
#define EMS_SENSOR 2
#define LIBS_SENSOR 3

//The following definations are just some examples.
//In real world, it should be different
//defination of sensor location code
#define SENSOR_LOCATION1 1
#define SENSOR_LOCATION2 2
#define SENSOR_LOCATION3 3
#define SENSOR_LOCATION4 4
#define SENSOR_LOCATION5 5
#define SENSOR_LOCATION6 6
//defination of data type code
#define DATA_TYPE_INT 1
#define DATA_TYPE_FLOAT 2
#define DATA_TYPE_UCHAR 3
#define DATA_TYPE_STRING 4
//defination of data units code
#define DATA_UNIT_NONE 0
#define DATA_UNIT_CENTIDEGREE 1
#define DATA_UNIT_FAHDEGREE 2
#define DATA_UNIT_PPM 3
#define DATA_UNIT_METER 4
#define DATA_UNIT_KMPERHOUR 5
#define DATA_UNIT_NUMBER 6
#define DATA_UNIT_NM 7
#define DATA_UNIT_MGRAM 8

static inline qint16 arrayToShort(QByteArray source);
static inline qint32 arrayToInt(QByteArray source);
static inline qint64 arrayToLong(QByteArray source);
static inline float arrayToFloat(QByteArray source);

qint16 arrayToShort(QByteArray source)
{
    qint16 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

qint32 arrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

qint64 arrayToLong(QByteArray source)
{
    qint64 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

float arrayToFloat(QByteArray source)
{
    float temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

struct ServerMetaInfo{
    QString         version;
    unsigned char   sensorType;
    unsigned char   sensorLocation;
    qint16          numberOfDataFields;
    QVector<QVector<qint16> > dataFields;
};

struct ServerDataBody{
    qint32          lengthOfSupData;
    QString         supplementaryData;
    qint64          timeStamp;
    qint32          numberOfDataList;
    QHash<int, QString> dataHash;
};

class SensorDataParser
{
public:
    SensorDataParser();
//    SensorDataParser(QByteArray*);

    int dataParser(QByteArray*);

private:
    int dataListParser(QByteArray*,int);
    int writeDataToFile();

    ServerMetaInfo    metaData;
    ServerDataBody    dataBody;

    QString     outFileName;
};

#endif // SENSORDATAPARSER_H
