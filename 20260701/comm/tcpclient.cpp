#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::disconnected);

    connect(m_socket, &QTcpSocket::readyRead, this, [=]() {
        QByteArray data = m_socket->readAll();
        emit dataReceived(data);
    });

    connect(m_socket, &QTcpSocket::errorOccurred, this, [=](QAbstractSocket::SocketError) {
        emit errorOccurred(m_socket->errorString());
    });
}

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
    m_socket->connectToHost(ip, port);
}

void TcpClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

void TcpClient::sendData(const QByteArray &data)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(data);
    }
}