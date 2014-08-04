#ifndef XRFSENSORDATA_H
#define XRFSENSORDATA_H

#include "sensordata.h"

#define NUMBER_OF_XRF_FIELDS 5

struct XRFData{
    qint32  numberOfObject;
    float   temprature;
    float   ppm;
    qint32  status;
    QString sensorDescription;
};

class XRFSensorData : public SensorData
{
public:
    //XRFSensorData();
    XRFSensorData()
    {
        numberOfData = 0;
        setType(XRF_SENSOR);
        dataBuffer = new QByteArray;
        setDataFields();
        setSupplementaryData();
    }

    ~XRFSensorData()
    {
        delete dataBuffer;
    }

    //This method allows other program to add a structed XRF Data
    void addData(const XRFData &dataLine);
    //This virtual method allows other program to add a splited raw data in strings
    virtual int addData(QStringList& dataFields);

private:
    virtual qint16 setDataFields();
    virtual qint16 setSupplementaryData();
//    virtual qint16 setDataLists();

    const qint16 xrfDataFields[NUMBER_OF_XRF_FIELDS][2]= {
           {DATA_TYPE_INT,DATA_UNIT_NUMBER},
           {DATA_TYPE_FLOAT,DATA_UNIT_CENTIDEGREE},
           {DATA_TYPE_FLOAT,DATA_UNIT_PPM},
           {DATA_TYPE_INT,DATA_UNIT_NONE},
           {DATA_TYPE_STRING,DATA_UNIT_NONE}
       };

    int         numberOfData;
    QByteArray  dataBuffer;

};

#endif // XRFSENSORDATA_H
