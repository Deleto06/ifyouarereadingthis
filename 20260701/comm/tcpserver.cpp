#include "tcpserver.h"

#include <QHostAddress>

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{
    m_server = new QTcpServer(this);

    connect(m_server, &QTcpServer::newConnection, this, [=]() {
        while (m_server->hasPendingConnections()) {
            QTcpSocket *client = m_server->nextPendingConnection();

            if (!client) {
                continue;
            }

            m_clients.append(client);

            QString peer = client->peerAddress().toString()
                           + ":"
                           + QString::number(client->peerPort());

            emit clientConnected(peer);

            connect(client, &QTcpSocket::readyRead, this, [=]() {
                QByteArray data = client->readAll();

                QString currentPeer = client->peerAddress().toString()
                                      + ":"
                                      + QString::number(client->peerPort());

                emit dataReceived(currentPeer, data);
            });

            connect(client, &QTcpSocket::disconnected, this, [=]() {
                QString currentPeer = client->peerAddress().toString()
                + ":"
                    + QString::number(client->peerPort());

                m_clients.removeAll(client);

                emit clientDisconnected(currentPeer);

                client->deleteLater();
            });

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
            connect(client, &QTcpSocket::errorOccurred,
                    this,
                    [=](QAbstractSocket::SocketError) {
                        emit errorOccurred(client->errorString());
                    });
#else
            connect(client,
                    QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
                    this,
                    [=](QAbstractSocket::SocketError) {
                        emit errorOccurred(client->errorString());
                    });
#endif
        }
    });
}

TcpServer::~TcpServer()
{
    stop();
}

bool TcpServer::start(quint16 port)
{
    stop();

    bool ok = m_server->listen(QHostAddress::AnyIPv4, port);

    if (!ok) {
        emit errorOccurred(m_server->errorString());
    }

    return ok;
}

void TcpServer::stop()
{
    for (QTcpSocket *client : m_clients) {
        if (!client) {
            continue;
        }

        client->disconnectFromHost();

        if (client->state() != QAbstractSocket::UnconnectedState) {
            client->waitForDisconnected(100);
        }

        client->deleteLater();
    }

    m_clients.clear();

    if (m_server && m_server->isListening()) {
        m_server->close();
    }
}

bool TcpServer::isListening() const
{
    return m_server && m_server->isListening();
}

qint64 TcpServer::sendDataToAll(const QByteArray &data)
{
    qint64 total = 0;

    for (QTcpSocket *client : m_clients) {
        if (!client) {
            continue;
        }

        if (client->state() == QAbstractSocket::ConnectedState) {
            total += client->write(data);
        }
    }

    return total;
}