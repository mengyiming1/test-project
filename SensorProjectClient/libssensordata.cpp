#include "libssensordata.h"


LIBSSensorData::LIBSSensorData()
{
    numberOfData = 0;
    setType(LIBS_SENSOR);
    dataBuffer.clear();
    setDataFields();
    setSupplementaryData();
}

LIBSSensorData::~LIBSSensorData()
{
    dataBuffer.clear();
}

void LIBSSensorData::setDataFields()
{
    QByteArray dataField;

    for(qint16 i = 0 ; i < NUMBER_OF_LIBS_FIELDS; i++ ){
        dataField.append(shortToArray(libsDataFields[i][0]));
        dataField.append(shortToArray(libsDataFields[i][1]));
    }

    setFields(NUMBER_OF_LIBS_FIELDS, &dataField);

}

void LIBSSensorData::setSupplementaryData()
{
    QByteArray supData;
    supData.append("This is LIBS Sensor");
    setSupplementary(&supData);

}

qint32 LIBSSensorData::addData(QStringList *dataFields)
{
    bool ok = false;
    LIBSData tmpData;


    if (dataFields->length()!= NUMBER_OF_LIBS_FIELDS)
        return 6;  //wrong number of fields.
    tmpData.temprature = dataFields->at(0).toFloat(&ok);
    if(!ok)
        return 1; //temprature1 is not a float;
    tmpData.width = dataFields->at(1).toFloat(&ok);
    if(!ok)
        return 2; //temprature2 is not a float;
    tmpData.length = dataFields->at(2).toFloat(&ok);
    if(!ok)
        return 3; //speed is not a float;
    tmpData.weight = dataFields->at(3).toFloat(&ok);
    if(!ok)
        return 4; //It is not a number;
    tmpData.numberOfElements = dataFields->at(4).toInt(&ok,10);
    if(!ok)
        return 5; //It is not a number;

    addData(&tmpData);
    return 0;
}

void LIBSSensorData::addData(const LIBSData *dataLine)
{
    dataBuffer.append(floatToArray(dataLine->temprature));
    dataBuffer.append(floatToArray(dataLine->width));
    dataBuffer.append(floatToArray(dataLine->length));
    dataBuffer.append(floatToArray(dataLine->weight));
    dataBuffer.append(intToArray(dataLine->numberOfElements));
    numberOfData++;
}

QByteArray LIBSSensorData::packAllData()
{
    setDataLists(numberOfData,&dataBuffer);
    return packData();

}
