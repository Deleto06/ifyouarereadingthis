#include "tcpclient.h"
#include <QNetworkProxy>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    // 禁用代理
    m_socket->setProxy(QNetworkProxy::NoProxy);

    connect(m_socket, &QTcpSocket::connected,
            this, &TcpClient::connected);

    connect(m_socket, &QTcpSocket::disconnected,
            this, &TcpClient::disconnected);

    connect(m_socket, &QTcpSocket::readyRead,
            this, &TcpClient::onReadyRead);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_socket, &QTcpSocket::errorOccurred,
            this, &TcpClient::onErrorOccurred);
#else
    connect(m_socket,
            QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this,
            &TcpClient::onErrorOccurred);
#endif
}

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->abort();
    }

    m_socket->connectToHost(ip, port);
}

void TcpClient::disconnectFromServer()
{
    if (m_socket->state() == QAbstractSocket::UnconnectedState) {
        return;
    }

    m_socket->disconnectFromHost();
}

qint64 TcpClient::sendData(const QByteArray &data)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        emit errorOccurred("socket is not connected");
        return -1;
    }

    return m_socket->write(data);
}

bool TcpClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

void TcpClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();

    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);

    emit errorOccurred(m_socket->errorString());
}