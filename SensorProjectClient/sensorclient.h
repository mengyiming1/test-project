#ifndef SENSORCLIENT_H
#define SENSORCLIENT_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>

class SensorClient : public QObject
{
    Q_OBJECT
public:
    explicit SensorClient(QObject *parent = 0);


signals:

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);

private:
    QTcpSocket *socket;

};

#endif // SENSORCLIENT_H
