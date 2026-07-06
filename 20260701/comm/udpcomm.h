#ifndef UDPCOMM_H
#define UDPCOMM_H

#include <QObject>
#include <QUdpSocket>

class UdpComm : public QObject
{
    Q_OBJECT

public:
    explicit UdpComm(QObject *parent = nullptr);
    ~UdpComm();

    bool bindPort(quint16 localPort);
    void close();

    qint64 sendData(const QString &ip, quint16 port, const QByteArray &data);

signals:
    void dataReceived(const QString &ip, quint16 port, const QByteArray &data);
    void errorOccurred(const QString &error);

private:
    QUdpSocket *m_socket = nullptr;
};

#endif // UDPCOMM_H