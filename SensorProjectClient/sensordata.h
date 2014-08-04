#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>

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

static inline QByteArray shortToArray(qint16 source);
static inline QByteArray intToArray(qint32 source);
static inline QByteArray longToArray(qint64 source);
static inline QByteArray floatToArray(float source);

QByteArray shortToArray(qint16 source) //Use qint16 to ensure that the number have 2 bytes
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

QByteArray intToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

QByteArray longToArray(qint64 source) //Use qint64 to ensure that the number have 8 bytes
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

QByteArray floatToArray(float source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

struct DataField{
    qint16 dataType;
    qint16 dataUnit;
};

struct MetaInfo{
    QString         version;
    qint16          sensorType;
    qint16          sensorLocation;
    qint32          numberOfDataFields;
    QByteArray      dataFields;
    //DataField       dataFields[];
};

struct DataBody{
    qint32          lengthOfSupData;
    QByteArray      supplementaryData;
    qint64          timeStamp;
    qint32          numberOfDataList;
    QByteArray      dataArray;
};

class SensorData : public QObject
{
public:
    explicit SensorData(QObject *parent = 0);

    void setVersion(QString);
    void setType(qint16);
    void setLocation(qint16);
    void setTimeStamp(qint64);

    virtual int addData(QStringList *dataFields);
    virtual QByteArray  packAllData();

protected:
    void setFields(qint16 numberOfFields, const QByteArray *dataField);
    void setSupplementary(const QByteArray *supData);
    void setDataLists(qint32 numberOfData, const QByteArray *dataArray);
    QByteArray packData();

    virtual void setDataFields();
    virtual void setSupplementaryData();
//    virtual qint16 setDataFields(QByteArray *dataField);
//    virtual qint16 setSupplementaryData(QByteArray *supData);
//    virtual qint16 setDataLists(QByteArray *dataArray);

private:

    MetaInfo    metaData;
    DataBody    bodyData;

};

#endif // SENSORDATA_H
