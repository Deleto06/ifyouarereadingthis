#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent)
    : QObject(parent)
{
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::readyRead, this, [=]() {
        QByteArray data = m_serial->readAll();
        emit dataReceived(data);
    });

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_serial, &QSerialPort::errorOccurred,
            this,
            [=](QSerialPort::SerialPortError error) {
                if (error == QSerialPort::NoError) {
                    return;
                }

                emit errorOccurred(m_serial->errorString());
            });
#else
    connect(m_serial,
            QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),
            this,
            [=](QSerialPort::SerialPortError error) {
                if (error == QSerialPort::NoError) {
                    return;
                }

                emit errorOccurred(m_serial->errorString());
            });
#endif
}

SerialComm::~SerialComm()
{
    close();
}

bool SerialComm::open(const QString &portName,
                      int baudRate,
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

    bool ok = m_serial->open(QIODevice::ReadWrite);

    emit stateChanged(ok);

    if (!ok) {
        emit errorOccurred(m_serial->errorString());
    }

    return ok;
}

void SerialComm::close()
{
    if (m_serial && m_serial->isOpen()) {
        m_serial->close();
    }

    emit stateChanged(false);
}

bool SerialComm::isOpen() const
{
    return m_serial && m_serial->isOpen();
}

qint64 SerialComm::sendData(const QByteArray &data)
{
    if (!isOpen()) {
        emit errorOccurred("Serial port is not open");
        return -1;
    }

    return m_serial->write(data);
}