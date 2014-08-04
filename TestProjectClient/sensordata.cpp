#include "sensordata.h"

//SensorData::SensorData()
//{
//
//}

static inline QByteArray shortToArray(qint16 source);
static inline QByteArray intToArray(qint32 source);
static inline QByteArray longToArray(qint64 source);

void SensorData::setVersion(QString version)
{
    metaData.version = version;
}

void SensorData::setType(unsigned char type)
{
    metaData.sensorType = type;
}

void SensorData::setLocation(unsigned char location)
{
    metaData.sensorLocation = location;
}

void SensorData::setTimeStamp(qint64 timestamp)
{
    bodyData.timeStamp = timestamp;
}

void SensorData::setDataFields(short numberOfFields, const QByteArray &dataField)
{
    metaData.numberOfDataFields = numberOfFields;
    metaData.dataFields.clear();
    metaData.dataFields = metaData.dataFields.append(dataField);
}

void SensorData::setSupplementaryData(const QByteArray &supData)
{
    bodyData.supplementaryData = (new QByteArray)->append(supData);
}

void SensorData::setDataLists(short numberOfData, const QByteArray &dataArray)
{
    bodyData.numberOfDataList = numberOfData;
    bodyData.dataArray.clear();
    bodyData.dataArray = bodyData.dataArray.append(dataArray);
}

QByteArray SensorData::packAllData()
{
    QByteArray dataBuffer;
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

    //Meta data
    dataBuffer.append(metaData.version);
    dataBuffer.append(metaData.sensorType);
    dataBuffer.append(metaData.sensorLocation);
    dataBuffer.append(shortToArray(metaData.numberOfDataFields));
    dataBuffer.append(metaData.dataFields);
    //Data body
    dataBuffer.append(intToArray(bodyData.lengthOfSupData));
    dataBuffer.append(bodyData.supplementaryData);
    dataBuffer.append(longToArray(bodyData.timeStamp));
    dataBuffer.append(intToArray(bodyData.numberOfDataList));
    dataBuffer.append(bodyData.dataArray);

    return dataBuffer;

}

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
