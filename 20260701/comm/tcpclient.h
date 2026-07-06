#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);

    void connectToServer(const QString &ip, quint16 port);
    void disconnectFromServer();
    void sendData(const QByteArray &data);

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);

private:
    QTcpSocket *m_socket = nullptr;
};