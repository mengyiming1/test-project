#include "sensordataparser.h"

SensorDataParser::SensorDataParser()
{

    outFileName = "outsensordata.txt";

}

int SensorDataParser::dataParser(QByteArray *sourceData)
{
    qint32 ptr = 0;
    qint32 tmp = 0;

    tmp = arrayToInt(sourceData->mid(ptr,4)); //length of version string
    ptr += 4;
    metaData.version = sourceData->mid(ptr,tmp);//get version
    ptr += tmp;
    metaData.sensorType = arrayToShort(sourceData->mid(ptr,2)); //Sensor type
    ptr += 2;
    metaData.sensorLocation = arrayToShort(sourceData->mid(ptr,2));  //Sensor Location
    ptr += 2;
    metaData.numberOfDataFields = arrayToInt(sourceData->mid(ptr,4));  //Number of Data Fields
    ptr += 4;
    //metaData.dataFields = (qint16**)malloc(sizeof(qint16)*metaData.numberOfDataFields*2);
    for(int i = 0; i < metaData.numberOfDataFields; i++){
        QVector<qint16> rec;
        rec.push_back(arrayToShort(sourceData->mid(ptr,2)));
        //metaData.dataFields[i][0] = arrayToShort(sourceData->mid(ptr,2)); //Data type
        ptr += 2;
        rec.push_back(arrayToShort(sourceData->mid(ptr,2)));
        //metaData.dataFields[i][1] = arrayToShort(sourceData->mid(ptr,2)); //Data unit
        ptr += 2;
        metaData.dataFields.push_back(rec);
    }

    tmp = arrayToInt(sourceData->mid(ptr,4)); //length of supplementary data
    ptr += 4;
    dataBody.supplementaryData = sourceData->mid(ptr,tmp); //get supplementary data, include '\0'
    ptr += tmp;
    dataBody.timeStamp = arrayToLong(sourceData->mid(ptr,8));
    ptr += 8;
    dataBody.numberOfDataList = arrayToInt(sourceData->mid(ptr,4));
    ptr += 4;

//    dataBody.dataHash = sourceData->left(sourceData->length()-ptr);
    if(int ret = dataListParser(sourceData,ptr)!= 0){
        return ret;
    }

    return writeDataToFile();
}

int SensorDataParser::dataListParser(QByteArray* sourceData,int ptr)
{
    QString lineBuffer;
    int length;


    for (int i = 0; i < dataBody.numberOfDataList; i++){
        lineBuffer.clear();
        for(int j = 0; j < metaData.numberOfDataFields; j++){
            QString buffer;
            //data type
            switch (metaData.dataFields[j][0]){
                case DATA_TYPE_INT:
                    buffer.sprintf("%d",arrayToInt(sourceData->mid(ptr,4)));
                    ptr += 4;
                    break;
                case DATA_TYPE_FLOAT:
                    //print float in two decimals
                    buffer.sprintf("%.2f",arrayToFloat(sourceData->mid(ptr,8)));
                    ptr += 8;
                    break;
                case DATA_TYPE_STRING:
                    length = arrayToInt(sourceData->mid(ptr,4));
                    buffer.append(sourceData->mid(ptr+4,length));
                    ptr += length + 4;
                    break;
                default:
                    //unsupport data type
                    break;
            }
            //data unit
            switch (metaData.dataFields[j][1]){
                case DATA_UNIT_CENTIDEGREE:
                    buffer.append("C, ");
                    break;
                case DATA_UNIT_FAHDEGREE:
                    buffer.append("F, ");
                    break;
                case DATA_UNIT_PPM:
                    buffer.append("ppm, ");
                    break;
                case DATA_UNIT_METER:
                    buffer.append("m, ");
                    break;
                case DATA_UNIT_KMPERHOUR:
                    buffer.append("km/h, ");
                    break;
                case DATA_UNIT_NM:
                    buffer.append("nm, ");
                    break;
                case DATA_UNIT_MGRAM:
                    buffer.append("mg, ");
                    break;
                case DATA_UNIT_NONE:
                case DATA_UNIT_NUMBER:
                default:
                    buffer.append(", ");
                    break;

            }
            lineBuffer.append(buffer);
        }
        lineBuffer.append("\n");
        dataBody.dataHash[i] = lineBuffer;
    }

    return 0;
}

int SensorDataParser::writeDataToFile()
{
    QFile file("sensordata.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)){
        file.seek(file.size());

        QTextStream outText(&file);
        QString tmp;

        tmp.sprintf("Sensor Type:%d\n",metaData.sensorType);
        outText << tmp;
        tmp.clear();
        tmp.sprintf("Sensor Location:%d\n",metaData.sensorLocation);
        outText << tmp;
        tmp.clear();
        outText << "Version:"+ metaData.version+"\n";
        outText << "supplementary data:" + dataBody.supplementaryData + "\n";
        QDateTime::fromMSecsSinceEpoch(dataBody.timeStamp).toString();
        outText << "Time Stamp:" + QDateTime::fromMSecsSinceEpoch(dataBody.timeStamp).toString(Qt::SystemLocaleShortDate) + "\n";
        outText << "Data List:\n";
        for(int i = 0; i < dataBody.numberOfDataList; i++){
            outText << "\t";
            outText << dataBody.dataHash[i];
        }
        file.close();
        return 0;
    }else{
        return 1;
    }
}
