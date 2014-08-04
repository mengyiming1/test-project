#include "xrfsensordata.h"

static inline QByteArray shortToArray(qint16 source);
static inline QByteArray intToArray(qint32 source);
static inline QByteArray longToArray(qint64 source);
static inline QByteArray floatToArray(float source);

//XRFSensorData::XRFSensorData()
//{
//}

qint16 XRFSensorData::setDataFields()
{
    QByteArray dataField;

    for(short i = 0 ; i++ ; i < NUMBER_OF_XRF_FIELDS){
        dataField.append(shortToArray(xrfDataFields[i].dataType));
        dataField.append(shortToArray(xrfDataFields[i].dataUnit));
    }

    setDataFields(NUMBER_OF_XRF_FIELDS,&dataField);

}

qint16 XRFSensorData::setSupplementaryData()
{
    QByteArray supData;
    supData.append("This is XRF Sensor");
    setSupplementaryData(&supData);

}

//qint16 XRFSensorData::setDataLists()
//{
//    dataArray.append(dataBuffer);
//    return numberOfData;
//}

int XRFSensorData::addData(QStringList& dataFields)
{
    bool ok = false;
    XRFData tmpData;

    if (dataFields.length()!= NUMBER_OF_XRF_FIELDS)
        return 5;  //wrong number of fields.
    tmpData.numberOfObject = dataFields.at(0).toInt(&ok,10);
    if(!ok)
        return 1; //It is not a number;
    tmpData.temprature = dataFields.at(1).toFloat(&ok);
    if(!ok)
        return 2; //temprature is not a float;
    tmpData.ppm = dataFields.at(2).toFloat(&ok);
    if(!ok)
        return 3; //ppm is not a float;
    tmpData.status = dataFields.at(3).toInt(&ok,10);
    if(!ok)
        return 4; //It is not a number;
    tmpData.sensorDescription = dataFields.at(4);

    addData(&tmpData);
    return 0;
}

viod XRFSensorData::addData(const XRFData &dataLine)
{
    dataBuffer.append(intToArray(dataLine.numberOfObject));
    dataBuffer.append(flocatToArray(dataLine.temprature));
    dataBuffer.append(flocatToArray(dataLine.ppm));
    dataBuffer.append(intToArray(dataLine.status));
    //add sensor description field
    //we need to add the length of string to tell server
    dataBuffer.append(intToArray(dataLine.sensorDescription.length()));
    dataBuffer.append(dataLine.sensorDescription);

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

QByteArray floatToArray(float source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
