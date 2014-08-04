#ifndef TESTSENSORSERVER_H
#define TESTSENSORSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class TestSensorServer : public QObject
{
    Q_OBJECT
public:
    explicit TestSensorServer(QObject *parent = 0);

//signals:
    void processDataReceived(QByteArray*);

public slots:
    void newSocketConnection();
    void disconnected();
    void readyRead();

private:

    QTcpServer  *socketServer;
    QHash<QTcpSocket*, QByteArray*> buffers;    //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes;          //We need to store the size to verify if a block
};

#endif // TESTSENSORSERVER_H
