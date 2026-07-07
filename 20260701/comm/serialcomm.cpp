#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent)
    : QObject(parent)
{
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::readyRead,
            this, &SerialComm::onReadyRead);

    connect(m_serial, &QSerialPort::errorOccurred,
            this, &SerialComm::onErrorOccurred);
}

bool SerialComm::open(const QString &portName,
                      qint32 baudRate,
                      QSerialPort::DataBits dataBits,
                      QSerialPort::Parity parity,
                      QSerialPort::StopBits stopBits)
{
    if (m_serial->isOpen()) {
        m_serial->close();
    }

    m_serial->setPortName(portName);
    m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(dataBits);
    m_serial->setParity(parity);
    m_serial->setStopBits(stopBits);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serial->open(QIODevice::ReadWrite)) {
        emit errorOccurred(m_serial->errorString());
        return false;
    }

    emit opened();
    return true;
}

void SerialComm::close()
{
    if (m_serial->isOpen()) {
        m_serial->close();
        emit closed();
    }
}

qint64 SerialComm::sendData(const QByteArray &data)
{
    if (!m_serial->isOpen()) {
        emit errorOccurred("serial port is not open");
        return -1;
    }

    return m_serial->write(data);
}

bool SerialComm::isOpen() const
{
    return m_serial->isOpen();
}

void SerialComm::onReadyRead()
{
    QByteArray data = m_serial->readAll();

    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

void SerialComm::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    emit errorOccurred(m_serial->errorString());
}