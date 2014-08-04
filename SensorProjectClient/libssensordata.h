#ifndef LIBSSENSORDATA_H
#define LIBSSENSORDATA_H

#include "sensordata.h"

#define NUMBER_OF_LIBS_FIELDS 5

struct LIBSData{
    float   temprature;
    float   width;
    float   length;
    float   weight;
    qint16  numberOfElements;
};

class LIBSSensorData : public SensorData
{
public:
    LIBSSensorData();
    ~LIBSSensorData();

    //This method allows other program to add a structed XRF Data
    void addData(const LIBSData *dataLine);

    //This virtual method allows other program to add a splited raw data in strings
    virtual qint32 addData(QStringList *dataFields);

    QByteArray packAllData();

private:
    virtual void setDataFields();
    virtual void setSupplementaryData();

    const qint16 libsDataFields[NUMBER_OF_LIBS_FIELDS][2]= {
           {DATA_TYPE_FLOAT,DATA_UNIT_CENTIDEGREE},
           {DATA_TYPE_FLOAT,DATA_UNIT_NM},
           {DATA_TYPE_FLOAT,DATA_UNIT_NM},
           {DATA_TYPE_FLOAT,DATA_UNIT_MGRAM},
           {DATA_TYPE_INT,DATA_UNIT_NUMBER}
       };

    qint32      numberOfData;
    QByteArray  dataBuffer;

};

#endif // LIBSSENSORDATA_H
