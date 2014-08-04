#include "testsensorserver.h"
#include "sensordataparser.h"


TestSensorServer::TestSensorServer(QObject *parent) :
    QObject(parent)
{
    socketServer = new QTcpServer(this);

    connect(socketServer, SIGNAL(newConnection()), this, SLOT(newSocketConnection()));

    socketServer->listen(QHostAddress::Any, 1024 );


}

void TestSensorServer::newSocketConnection()
{
    while(socketServer->hasPendingConnections()){
        printf("Connecting\n");
        QTcpSocket *socket = socketServer->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
    }

}

void TestSensorServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
    printf("Disconnecting\n");

}

void TestSensorServer::readyRead(){

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = arrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                emit processDataReceived(&data);
            }
        }
    }
}

void TestSensorServer::processDataReceived(QByteArray *data)
{
    printf("Data Recieved");
    SensorDataParser *parser = new SensorDataParser();
    parser->dataParser(data);
}
