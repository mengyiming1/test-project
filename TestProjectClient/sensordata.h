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


struct DataField{
    qint16 dataType;
    qint16 dataUnit;
};

struct MetaInfo{
    QString         version;
    unsigned char   sensorType;
    unsigned char   sensorLocation;
    qint16          numberOfDataFields;
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

class SensorData
{

public:
    SensorData()
    {
        metaData.sensorType = 0;
        metaData.version = 0;
        metaData.sensorLocation = 0;
        metaData.numberOfDataFields = 0;
        metaData.dataFields = new QByteArray;

        bodyData.lengthOfSupData = 0;
        bodyData.supplementaryData = new QByteArray;
        bodyData.timeStamp = 0;
        bodyData.numberOfDataList = 0;
        bodyData.dataArray = new QByteArray;
    }

    ~SensorData()
    {
        delete metaData.dataFields;
        delete bodyData.dataList;
        delete bodyData.supplementaryData;
    }

    void setVersion(QString);
    void setType(unsigned char);
    void setLocation(unsigned char);
    void setTimeStamp(qint64);

    QByteArray packAllData();

    virtual int addData(QStringList& dataFields);


protected:
    void setDataFields(short numberOfFields, const QByteArray &dataField);
    void setSupplementaryData(const QByteArray &supData);
    void SensorData::setDataLists(short numberOfData, const QByteArray &dataArray); //May unnecessary

private:
    virtual void setDataFields();
    virtual void setSupplementaryData();
//    virtual qint16 setDataFields(QByteArray *dataField);
//    virtual qint16 setSupplementaryData(QByteArray *supData);
//    virtual qint16 setDataLists(QByteArray *dataArray);

    MetaInfo    metaData;
    DataBody    bodyData;

};

#endif // SENSORDATA_H
