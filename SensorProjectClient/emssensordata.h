#ifndef EMSSENSORDATA_H
#define EMSSENSORDATA_H

#include "sensordata.h"

#define NUMBER_OF_EMS_FIELDS 6

struct EMSData{
    float   temprature1;
    float   temprature2;
    float   speed;
    qint16  status;
    qint16  alarmStation;
    QString alarmDescription;
};

class EMSSensorData : public SensorData
{
public:
    EMSSensorData();
    ~EMSSensorData();

    //This method allows other program to add a structed XRF Data
    void addData(const EMSData *dataLine);

    //This virtual method allows other program to add a splited raw data in strings
    virtual qint32 addData(QStringList *dataFields);

    QByteArray packAllData();

private:
    virtual void setDataFields();
    virtual void setSupplementaryData();

    const qint16 emsDataFields[NUMBER_OF_EMS_FIELDS][2]= {
           {DATA_TYPE_FLOAT,DATA_UNIT_CENTIDEGREE},
           {DATA_TYPE_FLOAT,DATA_UNIT_CENTIDEGREE},
           {DATA_TYPE_FLOAT,DATA_UNIT_KMPERHOUR},
           {DATA_TYPE_INT,DATA_UNIT_NONE},
           {DATA_TYPE_INT,DATA_UNIT_NONE},
           {DATA_TYPE_STRING,DATA_UNIT_NONE}
       };

    qint32      numberOfData;
    QByteArray  dataBuffer;

};


#endif // EMSSENSORDATA_H
