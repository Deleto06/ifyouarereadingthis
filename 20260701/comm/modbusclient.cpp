#include "modbusclient.h"
#include <QDebug>
#include <QTimer>
#include <QModbusReply>
#include <QVariant>

ModbusClient::ModbusClient(QObject *parent)
    : QObject(parent)
{
    m_client = new QModbusTcpClient(this);

    connect(m_client, &QModbusDevice::stateChanged,
            this,
            [this](QModbusDevice::State state)
            {
                QString stateText;

                switch (state) {
                case QModbusDevice::UnconnectedState:
                    stateText = "Unconnected";
                    emit disconnected();
                    break;

                case QModbusDevice::ConnectingState:
                    stateText = "Connecting";
                    break;

                case QModbusDevice::ConnectedState:
                    stateText = "Connected";
                    emit connected();
                    break;

                case QModbusDevice::ClosingState:
                    stateText = "Closing";
                    break;
                }

                QString msg = "[Modbus TCP Client] state changed: " + stateText;

                qDebug() << msg;
                emit logMessage(msg);
            });

    connect(m_client, &QModbusDevice::errorOccurred,
            this,
            [this](QModbusDevice::Error error)
            {
                if (error == QModbusDevice::NoError) {
                    return;
                }

                QString msg = "[Modbus TCP Client] error: " + m_client->errorString();

                qDebug() << msg;
                emit logMessage(msg);
                emit errorOccurred(m_client->errorString());
            });

    emit logMessage("[Modbus TCP Client] object created");
}

ModbusClient::~ModbusClient()
{
    if (m_client) {
        m_client->disconnectDevice();
    }
}


bool ModbusClient::connectToServer(const QString &ip, int port)
{
    if (!m_client) {
        emit errorOccurred("Modbus client is null");
        return false;
    }

    QModbusDevice::State state = m_client->state();

    emit logMessage(QString("[Modbus TCP Client] current state before connect: %1")
                        .arg(state));

    if (state == QModbusDevice::ConnectedState) {
        emit logMessage("[Modbus TCP Client] already connected");
        return true;
    }

    if (state == QModbusDevice::ConnectingState) {
        emit logMessage("[Modbus TCP Client] already connecting, wait next retry");
        return false;
    }

    if (state == QModbusDevice::ClosingState) {
        emit logMessage("[Modbus TCP Client] device is closing, wait next retry");
        return false;
    }

    /*
     * 走到这里，正常应该是 UnconnectedState
     * 自动重连时，每次都会重新设置 IP 和端口
     */
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, ip);
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);

    m_client->setTimeout(3000);
    m_client->setNumberOfRetries(3);

    emit logMessage(QString("[Modbus TCP Client] connecting to %1:%2")
                        .arg(ip)
                        .arg(port));

    bool ok = m_client->connectDevice();

    emit logMessage(QString("[Modbus TCP Client] connectDevice return: %1")
                        .arg(ok ? "true" : "false"));

    emit logMessage(QString("[Modbus TCP Client] state after connectDevice: %1")
                        .arg(m_client->state()));

    if (!ok) {
        QString err = m_client->errorString();
        if (err.isEmpty()) {
            err = "connectDevice failed";
        }

        emit logMessage("[Modbus TCP Client] connectDevice failed: " + err);
        emit errorOccurred(err);
        return false;
    }

    return true;
}

void ModbusClient::disconnectFromServer()
{
    if (!m_client) {
        return;
    }

    if (m_client->state() != QModbusDevice::UnconnectedState) {
        m_client->disconnectDevice();
    }
}

bool ModbusClient::isConnected() const
{
    if (!m_client) {
        return false;
    }

    return m_client->state() == QModbusDevice::ConnectedState;
}

void ModbusClient::readHoldingRegisters(int serverAddress, int startAddress, quint16 count)
{
    if (!isConnected()) {
        emit errorOccurred("Modbus TCP Client is not connected");
        return;
    }

    if (count == 0 || count > 125) {
        emit errorOccurred("Read count invalid, range is 1~125");
        return;
    }

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,
                             startAddress,
                             count);

    QModbusReply *reply = m_client->sendReadRequest(readUnit, serverAddress);

    if (!reply) {
        emit errorOccurred(m_client->errorString());
        return;
    }

    if (reply->isFinished()) {
        reply->deleteLater();
        return;
    }

    connect(reply, &QModbusReply::finished,
            this,
            [=]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit unit = reply->result();

                    QVector<quint16> values;
                    values.reserve(static_cast<int>(unit.valueCount()));

                    emit logMessage(QString("[Modbus TCP Client] read ok. start=%1, count=%2")
                                        .arg(startAddress)
                                        .arg(unit.valueCount()));

                    for (uint i = 0; i < unit.valueCount(); ++i) {
                        quint16 value = unit.value(i);
                        values.append(value);

                        emit logMessage(QString("[Modbus TCP Client] HR[%1] = %2")
                                            .arg(startAddress + static_cast<int>(i))
                                            .arg(value));
                    }

                    emit holdingRegistersRead(startAddress, values);
                } else {
                    emit errorOccurred(reply->errorString());
                }

                reply->deleteLater();
            });
}

void ModbusClient::writeSingleHoldingRegister(int serverAddress, int address, quint16 value)
{
    if (!isConnected()) {
        emit errorOccurred("Modbus TCP Client is not connected");
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters,
                              address,
                              1);

    writeUnit.setValue(0, value);

    QModbusReply *reply = m_client->sendWriteRequest(writeUnit, serverAddress);

    if (!reply) {
        emit errorOccurred(m_client->errorString());
        return;
    }

    if (reply->isFinished()) {
        reply->deleteLater();
        emit writeFinished(QString("Write single register ok. addr=%1, value=%2")
                               .arg(address)
                               .arg(value));
        return;
    }

    connect(reply, &QModbusReply::finished,
            this,
            [=]() {
                if (reply->error() == QModbusDevice::NoError) {
                    emit writeFinished(QString("Write single register ok. addr=%1, value=%2")
                                           .arg(address)
                                           .arg(value));
                } else {
                    emit errorOccurred(reply->errorString());
                }

                reply->deleteLater();
            });
}

void ModbusClient::writeMultipleHoldingRegisters(int serverAddress,
                                                 int startAddress,
                                                 const QVector<quint16> &values)
{
    if (!isConnected()) {
        emit errorOccurred("Modbus TCP Client is not connected");
        return;
    }

    if (values.isEmpty()) {
        emit errorOccurred("Write values is empty");
        return;
    }

    if (values.size() > 123) {
        emit errorOccurred("Write multiple count invalid, max is 123");
        return;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters,
                              startAddress,
                              values.size());

    for (int i = 0; i < values.size(); ++i) {
        writeUnit.setValue(i, values[i]);
    }

    QModbusReply *reply = m_client->sendWriteRequest(writeUnit, serverAddress);

    if (!reply) {
        emit errorOccurred(m_client->errorString());
        return;
    }

    if (reply->isFinished()) {
        reply->deleteLater();
        emit writeFinished(QString("Write multiple registers ok. start=%1, count=%2")
                               .arg(startAddress)
                               .arg(values.size()));
        return;
    }

    connect(reply, &QModbusReply::finished,
            this,
            [=]() {
                if (reply->error() == QModbusDevice::NoError) {
                    emit writeFinished(QString("Write multiple registers ok. start=%1, count=%2")
                                           .arg(startAddress)
                                           .arg(values.size()));
                } else {
                    emit errorOccurred(reply->errorString());
                }

                reply->deleteLater();
            });
}

void ModbusClient::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        emit connected();
    } else if (state == QModbusDevice::UnconnectedState) {
        emit disconnected();
    }
}

void ModbusClient::onErrorOccurred(QModbusDevice::Error error)
{
    if (error == QModbusDevice::NoError) {
        return;
    }

    if (!m_client) {
        emit errorOccurred("Modbus client error");
        return;
    }

    emit errorOccurred(m_client->errorString());
}