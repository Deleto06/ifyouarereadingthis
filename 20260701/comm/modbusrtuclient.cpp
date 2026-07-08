#include "modbusrtuclient.h"
#include <QDebug>

ModbusRtuClient::ModbusRtuClient(QObject *parent)
    : QObject(parent)
{
    m_serial = new QSerialPort(this);

    m_frameTimer = new QTimer(this);
    m_frameTimer->setSingleShot(true);
    m_frameTimer->setInterval(30);

    connect(m_serial, &QSerialPort::readyRead,
            this, &ModbusRtuClient::onReadyRead);

    connect(m_frameTimer, &QTimer::timeout,
            this, &ModbusRtuClient::onFrameTimeout);

    connect(m_serial, &QSerialPort::errorOccurred,
            this,
            [=](QSerialPort::SerialPortError error) {
                if (error == QSerialPort::NoError) {
                    return;
                }

                emit errorOccurred(m_serial->errorString());
            });
}

ModbusRtuClient::~ModbusRtuClient()
{
    close();
}

bool ModbusRtuClient::open(const QString &portName,
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

    bool ok = m_serial->open(QIODevice::ReadWrite);

    if (!ok) {
        emit errorOccurred(m_serial->errorString());
        return false;
    }

    m_recvBuffer.clear();

    emit opened();
    emit logMessage(QString("[Modbus RTU Client] opened %1, baud=%2")
                        .arg(portName)
                        .arg(baudRate));

    return true;
}

void ModbusRtuClient::close()
{
    if (m_frameTimer) {
        m_frameTimer->stop();
    }

    m_recvBuffer.clear();

    if (m_serial && m_serial->isOpen()) {
        m_serial->close();
        emit closed();
        emit logMessage("[Modbus RTU Client] closed");
    }
}

bool ModbusRtuClient::isOpen() const
{
    return m_serial && m_serial->isOpen();
}

quint16 ModbusRtuClient::crc16(const QByteArray &data) const
{
    quint16 crc = 0xFFFF;

    for (unsigned char byte : data) {
        crc ^= byte;

        for (int i = 0; i < 8; ++i) {
            if (crc & 0x0001) {
                crc = static_cast<quint16>((crc >> 1) ^ 0xA001);
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

void ModbusRtuClient::appendCrc(QByteArray &frame) const
{
    quint16 crc = crc16(frame);

    frame.append(static_cast<char>(crc & 0xFF));
    frame.append(static_cast<char>((crc >> 8) & 0xFF));
}

bool ModbusRtuClient::checkCrc(const QByteArray &frame) const
{
    if (frame.size() < 4) {
        return false;
    }

    QByteArray data = frame.left(frame.size() - 2);

    quint16 calcCrc = crc16(data);

    quint8 crcLow = static_cast<quint8>(frame.at(frame.size() - 2));
    quint8 crcHigh = static_cast<quint8>(frame.at(frame.size() - 1));

    quint16 recvCrc = static_cast<quint16>(crcLow | (crcHigh << 8));

    return calcCrc == recvCrc;
}

QByteArray ModbusRtuClient::buildReadHoldingRegistersFrame(quint8 slaveId,
                                                           quint16 startAddress,
                                                           quint16 count) const
{
    QByteArray frame;

    frame.append(static_cast<char>(slaveId));
    frame.append(static_cast<char>(0x03));

    frame.append(static_cast<char>((startAddress >> 8) & 0xFF));
    frame.append(static_cast<char>(startAddress & 0xFF));

    frame.append(static_cast<char>((count >> 8) & 0xFF));
    frame.append(static_cast<char>(count & 0xFF));

    appendCrc(frame);

    return frame;
}

QByteArray ModbusRtuClient::buildWriteSingleRegisterFrame(quint8 slaveId,
                                                          quint16 address,
                                                          quint16 value) const
{
    QByteArray frame;

    frame.append(static_cast<char>(slaveId));
    frame.append(static_cast<char>(0x06));

    frame.append(static_cast<char>((address >> 8) & 0xFF));
    frame.append(static_cast<char>(address & 0xFF));

    frame.append(static_cast<char>((value >> 8) & 0xFF));
    frame.append(static_cast<char>(value & 0xFF));

    appendCrc(frame);

    return frame;
}

QByteArray ModbusRtuClient::buildWriteMultipleRegistersFrame(quint8 slaveId,
                                                             quint16 startAddress,
                                                             const QVector<quint16> &values) const
{
    QByteArray frame;

    quint16 count = static_cast<quint16>(values.size());
    quint8 byteCount = static_cast<quint8>(count * 2);

    frame.append(static_cast<char>(slaveId));
    frame.append(static_cast<char>(0x10));

    frame.append(static_cast<char>((startAddress >> 8) & 0xFF));
    frame.append(static_cast<char>(startAddress & 0xFF));

    frame.append(static_cast<char>((count >> 8) & 0xFF));
    frame.append(static_cast<char>(count & 0xFF));

    frame.append(static_cast<char>(byteCount));

    for (quint16 value : values) {
        frame.append(static_cast<char>((value >> 8) & 0xFF));
        frame.append(static_cast<char>(value & 0xFF));
    }

    appendCrc(frame);

    return frame;
}

void ModbusRtuClient::sendFrame(const QByteArray &frame)
{
    if (!isOpen()) {
        emit errorOccurred("[Modbus RTU Client] serial port is not open");
        return;
    }

    m_recvBuffer.clear();

    qint64 len = m_serial->write(frame);

    emit rawDataSent(frame);

    emit logMessage(QString("[Modbus RTU Send HEX] %1, bytes=%2")
                        .arg(QString::fromLatin1(frame.toHex(' ').toUpper()))
                        .arg(len));
}

void ModbusRtuClient::readHoldingRegisters(quint8 slaveId,
                                           quint16 startAddress,
                                           quint16 count)
{
    if (count == 0 || count > 125) {
        emit errorOccurred("[Modbus RTU Client] read count invalid, range: 1~125");
        return;
    }

    m_lastSlaveId = slaveId;
    m_lastFunctionCode = 0x03;
    m_lastStartAddress = startAddress;
    m_lastCount = count;

    QByteArray frame = buildReadHoldingRegistersFrame(slaveId, startAddress, count);

    sendFrame(frame);
}

void ModbusRtuClient::writeSingleHoldingRegister(quint8 slaveId,
                                                 quint16 address,
                                                 quint16 value)
{
    m_lastSlaveId = slaveId;
    m_lastFunctionCode = 0x06;
    m_lastStartAddress = address;
    m_lastCount = 1;

    QByteArray frame = buildWriteSingleRegisterFrame(slaveId, address, value);

    sendFrame(frame);
}

void ModbusRtuClient::writeMultipleHoldingRegisters(quint8 slaveId,
                                                    quint16 startAddress,
                                                    const QVector<quint16> &values)
{
    if (values.isEmpty() || values.size() > 123) {
        emit errorOccurred("[Modbus RTU Client] write multiple count invalid, range: 1~123");
        return;
    }

    m_lastSlaveId = slaveId;
    m_lastFunctionCode = 0x10;
    m_lastStartAddress = startAddress;
    m_lastCount = static_cast<quint16>(values.size());

    QByteArray frame = buildWriteMultipleRegistersFrame(slaveId, startAddress, values);

    sendFrame(frame);
}

void ModbusRtuClient::onReadyRead()
{
    QByteArray data = m_serial->readAll();

    if (data.isEmpty()) {
        return;
    }

    m_recvBuffer.append(data);

    emit rawDataReceived(data);

    emit logMessage(QString("[Modbus RTU Recv Part HEX] %1")
                        .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

    m_frameTimer->start();
}

void ModbusRtuClient::onFrameTimeout()
{
    if (m_recvBuffer.isEmpty()) {
        return;
    }

    QByteArray frame = m_recvBuffer;
    m_recvBuffer.clear();

    emit logMessage(QString("[Modbus RTU Recv Frame HEX] %1")
                        .arg(QString::fromLatin1(frame.toHex(' ').toUpper())));

    parseFrame(frame);
}

void ModbusRtuClient::parseFrame(const QByteArray &frame)
{
    if (frame.size() < 5) {
        emit errorOccurred("[Modbus RTU Client] response frame too short");
        return;
    }

    if (!checkCrc(frame)) {
        emit errorOccurred("[Modbus RTU Client] CRC check failed");
        return;
    }

    quint8 slaveId = static_cast<quint8>(frame.at(0));
    quint8 functionCode = static_cast<quint8>(frame.at(1));

    if (slaveId != m_lastSlaveId) {
        emit errorOccurred(QString("[Modbus RTU Client] slave id mismatch. recv=%1 expected=%2")
                               .arg(slaveId)
                               .arg(m_lastSlaveId));
        return;
    }

    if (functionCode & 0x80) {
        parseExceptionResponse(frame);
        return;
    }

    switch (functionCode) {
    case 0x03:
        parseReadHoldingRegistersResponse(frame);
        break;

    case 0x06:
        parseWriteSingleRegisterResponse(frame);
        break;

    case 0x10:
        parseWriteMultipleRegistersResponse(frame);
        break;

    default:
        emit errorOccurred(QString("[Modbus RTU Client] unsupported function code: 0x%1")
                               .arg(functionCode, 2, 16, QChar('0')).toUpper());
        break;
    }
}

void ModbusRtuClient::parseReadHoldingRegistersResponse(const QByteArray &frame)
{
    if (frame.size() < 5) {
        emit errorOccurred("[Modbus RTU Client] read response too short");
        return;
    }

    quint8 byteCount = static_cast<quint8>(frame.at(2));

    if (byteCount != m_lastCount * 2) {
        emit errorOccurred(QString("[Modbus RTU Client] byte count mismatch. recv=%1 expected=%2")
                               .arg(byteCount)
                               .arg(m_lastCount * 2));
        return;
    }

    if (frame.size() != byteCount + 5) {
        emit errorOccurred(QString("[Modbus RTU Client] frame length mismatch. size=%1 expected=%2")
                               .arg(frame.size())
                               .arg(byteCount + 5));
        return;
    }

    QVector<quint16> values;

    for (int i = 0; i < byteCount / 2; ++i) {
        quint8 high = static_cast<quint8>(frame.at(3 + i * 2));
        quint8 low = static_cast<quint8>(frame.at(4 + i * 2));

        quint16 value = static_cast<quint16>((high << 8) | low);
        values.append(value);
    }

    emit holdingRegistersRead(static_cast<quint8>(frame.at(0)),
                              m_lastStartAddress,
                              values);
}

void ModbusRtuClient::parseWriteSingleRegisterResponse(const QByteArray &frame)
{
    if (frame.size() != 8) {
        emit errorOccurred(QString("[Modbus RTU Client] write single response length invalid: %1")
                               .arg(frame.size()));
        return;
    }

    quint16 address = static_cast<quint16>(
        (static_cast<quint8>(frame.at(2)) << 8) |
        static_cast<quint8>(frame.at(3))
        );

    quint16 value = static_cast<quint16>(
        (static_cast<quint8>(frame.at(4)) << 8) |
        static_cast<quint8>(frame.at(5))
        );

    Q_UNUSED(value);

    emit writeFinished(static_cast<quint8>(frame.at(0)),
                       0x06,
                       address,
                       1);
}

void ModbusRtuClient::parseWriteMultipleRegistersResponse(const QByteArray &frame)
{
    if (frame.size() != 8) {
        emit errorOccurred(QString("[Modbus RTU Client] write multiple response length invalid: %1")
                               .arg(frame.size()));
        return;
    }

    quint16 startAddress = static_cast<quint16>(
        (static_cast<quint8>(frame.at(2)) << 8) |
        static_cast<quint8>(frame.at(3))
        );

    quint16 count = static_cast<quint16>(
        (static_cast<quint8>(frame.at(4)) << 8) |
        static_cast<quint8>(frame.at(5))
        );

    emit writeFinished(static_cast<quint8>(frame.at(0)),
                       0x10,
                       startAddress,
                       count);
}

void ModbusRtuClient::parseExceptionResponse(const QByteArray &frame)
{
    if (frame.size() != 5) {
        emit errorOccurred(QString("[Modbus RTU Client] exception response length invalid: %1")
                               .arg(frame.size()));
        return;
    }

    quint8 slaveId = static_cast<quint8>(frame.at(0));
    quint8 exceptionFunc = static_cast<quint8>(frame.at(1));
    quint8 exceptionCode = static_cast<quint8>(frame.at(2));

    emit errorOccurred(QString("[Modbus RTU Client] exception. slave=%1, function=0x%2, code=0x%3")
                           .arg(slaveId)
                           .arg(exceptionFunc, 2, 16, QChar('0'))
                           .arg(exceptionCode, 2, 16, QChar('0'))
                           .toUpper());
}