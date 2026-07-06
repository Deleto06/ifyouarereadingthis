#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();

    bool start(quint16 port);
    void stop();

    bool isListening() const;
    qint64 sendDataToAll(const QByteArray &data);

signals:
    void clientConnected(const QString &peer);
    void clientDisconnected(const QString &peer);
    void dataReceived(const QString &peer, const QByteArray &data);
    void errorOccurred(const QString &error);

private:
    QTcpServer *m_server = nullptr;
    QList<QTcpSocket *> m_clients;
};

#endif // TCPSERVER_H