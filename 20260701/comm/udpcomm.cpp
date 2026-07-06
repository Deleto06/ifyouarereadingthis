#include "udpcomm.h"

#include <QHostAddress>

UdpComm::UdpComm(QObject *parent)
    : QObject(parent)
{
    m_socket = new QUdpSocket(this);

    connect(m_socket, &QUdpSocket::readyRead, this, [=]() {
        while (m_socket->hasPendingDatagrams()) {
            QByteArray data;
            data.resize(static_cast<int>(m_socket->pendingDatagramSize()));

            QHostAddress sender;
            quint16 senderPort = 0;

            qint64 len = m_socket->readDatagram(
                data.data(),
                data.size(),
                &sender,
                &senderPort
                );

            if (len > 0) {
                emit dataReceived(sender.toString(), senderPort, data);
            }
        }
    });

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_socket, &QUdpSocket::errorOccurred,
            this,
            [=](QAbstractSocket::SocketError) {
                emit errorOccurred(m_socket->errorString());
            });
#else
    connect(m_socket,
            QOverload<QAbstractSocket::SocketError>::of(&QUdpSocket::error),
            this,
            [=](QAbstractSocket::SocketError) {
                emit errorOccurred(m_socket->errorString());
            });
#endif
}

UdpComm::~UdpComm()
{
    close();
}

bool UdpComm::bindPort(quint16 localPort)
{
    close();

    bool ok = m_socket->bind(QHostAddress::AnyIPv4, localPort);

    if (!ok) {
        emit errorOccurred(m_socket->errorString());
    }

    return ok;
}

void UdpComm::close()
{
    if (m_socket) {
        m_socket->close();
    }
}

qint64 UdpComm::sendData(const QString &ip, quint16 port, const QByteArray &data)
{
    if (!m_socket) {
        emit errorOccurred("UDP socket is null");
        return -1;
    }

    return m_socket->writeDatagram(data, QHostAddress(ip), port);
}