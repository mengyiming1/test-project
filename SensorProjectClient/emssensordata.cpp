#include "emssensordata.h"

EMSSensorData::EMSSensorData()
{
    numberOfData = 0;
    setType(EMS_SENSOR);
    setDataFields();
    setSupplementaryData();
}

EMSSensorData::~EMSSensorData()
{
    dataBuffer.clear();
}

void EMSSensorData::setDataFields()
{
    QByteArray dataField;

    for(qint16 i = 0 ; i < NUMBER_OF_EMS_FIELDS; i++){
        dataField.append(shortToArray(emsDataFields[i][0]));
        dataField.append(shortToArray(emsDataFields[i][1]));
    }

    setFields(NUMBER_OF_EMS_FIELDS, &dataField);

}

void EMSSensorData::setSupplementaryData()
{
    QByteArray supData;
    supData.append("This is EMS Sensor");
    setSupplementary(&supData);

}


qint32 EMSSensorData::addData(QStringList *dataFields)
{
    bool ok = false;
    EMSData tmpData;


    if (dataFields->length()!= NUMBER_OF_EMS_FIELDS)
        return 6;  //wrong number of fields.
    tmpData.temprature1 = dataFields->at(0).toFloat(&ok);
    if(!ok)
        return 1; //temprature1 is not a float;
    tmpData.temprature2 = dataFields->at(1).toFloat(&ok);
    if(!ok)
        return 2; //temprature2 is not a float;
    tmpData.speed = dataFields->at(2).toFloat(&ok);
    if(!ok)
        return 3; //speed is not a float;
    tmpData.status = dataFields->at(3).toInt(&ok,10);
    if(!ok)
        return 4; //It is not a number;
    tmpData.alarmStation = dataFields->at(4).toInt(&ok,10);
    if(!ok)
        return 5; //It is not a number;
    tmpData.alarmDescription = dataFields->at(5);

    addData(&tmpData);
    return 0;
}

void EMSSensorData::addData(const EMSData *dataLine)
{
    dataBuffer.append(floatToArray(dataLine->temprature1));
    dataBuffer.append(floatToArray(dataLine->temprature2));
    dataBuffer.append(floatToArray(dataLine->speed));
    dataBuffer.append(intToArray(dataLine->status));
    dataBuffer.append(intToArray(dataLine->alarmStation));
    //add sensor description field
    //we need to add the length of string to tell server
    dataBuffer.append(intToArray(dataLine->alarmDescription.length()));
    dataBuffer.append(dataLine->alarmDescription);
    numberOfData++;
}

QByteArray EMSSensorData::packAllData()
{
    setDataLists(numberOfData,&dataBuffer);
    return packData();

}

