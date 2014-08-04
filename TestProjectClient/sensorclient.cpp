#include "sensorclient.h"

static inline QByteArray intToArray(qint32 source);

SensorClient::SensorClient(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
}

bool SensorClient::connectToHost(QString host)
{
    socket->connectToHost(host, 1024);
    return socket->waitForConnected();
}

bool SensorClient::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(intToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

QByteArray intToArray(qint32 source)
{
    //Avoid use of cast
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
