#include "xrfsensordata.h"


XRFSensorData::XRFSensorData()
{
    numberOfData = 0;
    setType(XRF_SENSOR);
    dataBuffer.clear();
    setDataFields();
    setSupplementaryData();
}

XRFSensorData::~XRFSensorData()
{
    dataBuffer.clear();
}

void XRFSensorData::setDataFields()
{
    QByteArray dataField;

    for(qint16 i = 0 ; i < NUMBER_OF_XRF_FIELDS ; i++){
        dataField.append(shortToArray(xrfDataFields[i][0]));
        dataField.append(shortToArray(xrfDataFields[i][1]));
    }

    setFields(NUMBER_OF_XRF_FIELDS,&dataField);

}

void XRFSensorData::setSupplementaryData()
{
    QByteArray supData;
    supData.append("This is XRF Sensor");
    setSupplementary(&supData);

}


qint32 XRFSensorData::addData(QStringList *dataFields)
{
    bool ok = false;
    XRFData tmpData;

    if (dataFields->length()!= NUMBER_OF_XRF_FIELDS)
        return 5;  //wrong number of fields.
    tmpData.numberOfObject = dataFields->at(0).toInt(&ok,10);
    if(!ok)
        return 1; //It is not a number;
    tmpData.temprature = dataFields->at(1).toFloat(&ok);
    if(!ok)
        return 2; //temprature is not a float;
    tmpData.ppm = dataFields->at(2).toFloat(&ok);
    if(!ok)
        return 3; //ppm is not a float;
    tmpData.status = dataFields->at(3).toInt(&ok,10);
    if(!ok)
        return 4; //It is not a number;
    tmpData.sensorDescription = dataFields->at(4);

    addData(&tmpData);
    return 0;
}

void XRFSensorData::addData(const XRFData *dataLine)
{
    dataBuffer.append(intToArray(dataLine->numberOfObject));
    dataBuffer.append(floatToArray(dataLine->temprature));
    dataBuffer.append(floatToArray(dataLine->ppm));
    dataBuffer.append(intToArray(dataLine->status));
    //add sensor description field
    //we need to add the length of string to tell server
    dataBuffer.append(intToArray(dataLine->sensorDescription.length()));
    dataBuffer.append(dataLine->sensorDescription);
    numberOfData++;
}

QByteArray XRFSensorData::packAllData()
{
    setDataLists(numberOfData,&dataBuffer);
    return packData();
}

