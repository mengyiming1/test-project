#include "sensordata.h"

SensorData::SensorData(QObject *parent) :
    QObject(parent)
{
    metaData.sensorType = 0;
    metaData.version = "";
    metaData.sensorLocation = 0;
    metaData.numberOfDataFields = 0;
    metaData.dataFields.clear();

    bodyData.lengthOfSupData = 0;
    bodyData.supplementaryData.clear();
    bodyData.timeStamp = 0;
    bodyData.numberOfDataList = 0;
    bodyData.dataArray.clear();
}

//SensorData::~SensorData()
//{
    //delete metaData.dataFields;
    //delete bodyData.dataList;
    //delete bodyData.supplementaryData;
//}

void SensorData::setVersion(QString version)
{
    metaData.version = version;
}

void SensorData::setType(qint16 type)
{
    metaData.sensorType = type;
}

void SensorData::setLocation(qint16 location)
{
    metaData.sensorLocation = location;
}

void SensorData::setTimeStamp(qint64 timestamp)
{
    bodyData.timeStamp = timestamp;
}

void SensorData::setFields(qint16 numberOfFields, const QByteArray *dataField)
{
    metaData.numberOfDataFields = numberOfFields;
    metaData.dataFields.clear();
    metaData.dataFields = *dataField;
}

void SensorData::setSupplementary(const QByteArray *supData)
{
    bodyData.supplementaryData.clear();
    bodyData.supplementaryData = *supData;
    bodyData.lengthOfSupData = supData->length();
}

void SensorData::setDataLists(qint32 numberOfData, const QByteArray *dataArray)
{
    bodyData.numberOfDataList = numberOfData;
    bodyData.dataArray.clear();
    bodyData.dataArray = *dataArray;
}

QByteArray SensorData::packData()
{
    QByteArray dataBuffer;

    //Meta data
    dataBuffer.append(intToArray(metaData.version.length())); //tell server the length of version string
    dataBuffer.append(metaData.version);
    dataBuffer.append(shortToArray(metaData.sensorType));
    dataBuffer.append(shortToArray(metaData.sensorLocation));
    dataBuffer.append(intToArray(metaData.numberOfDataFields));
    dataBuffer.append(metaData.dataFields);
    //Data body
    dataBuffer.append(intToArray(bodyData.lengthOfSupData));
    dataBuffer.append(bodyData.supplementaryData);
    dataBuffer.append(longToArray(bodyData.timeStamp));
    dataBuffer.append(intToArray(bodyData.numberOfDataList));
    dataBuffer.append(bodyData.dataArray);

    return dataBuffer;

}

qint32 SensorData::addData(QStringList *dataFields){}
QByteArray  SensorData::packAllData(){}

void SensorData::setDataFields(){}
void SensorData::setSupplementaryData(){}

