#include "modbusclient.h"

#include <QVariant>

ModbusClient::ModbusClient(QObject *parent)
    : QObject(parent)
{
}

ModbusClient::~ModbusClient()
{
    disconnectDevice();
}

bool ModbusClient::connectTcp(const QString &ip, int port)
{
    disconnectDevice();

    auto *client = new QModbusTcpClient(this);
    m_client = client;

    client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QVariant(ip));
    client->setConnectionParameter(QModbusDevice::NetworkPortParameter, QVariant(port));

    client->setTimeout(1000);
    client->setNumberOfRetries(3);

    connect(client, &QModbusClient::stateChanged, this,
            [=](QModbusDevice::State state) {
                if (state == QModbusDevice::ConnectedState) {
                    emit connected();
                } else if (state == QModbusDevice::UnconnectedState) {
                    emit disconnected();
                }
            });

    connect(client, &QModbusClient::errorOccurred, this,
            [=](QModbusDevice::Error) {
                emit errorOccurred(client->errorString());
            });

    return client->connectDevice();
}

bool ModbusClient::connectRtu(const QString &portName,
                              int baudRate,
                              int parity,
                              int dataBits,
                              int stopBits)
{
    disconnectDevice();

    auto *client = new QModbusRtuSerialClient(this);
    m_client = client;

    client->setConnectionParameter(QModbusDevice::SerialPortNameParameter, QVariant(portName));
    client->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QVariant(baudRate));
    client->setConnectionParameter(QModbusDevice::SerialParityParameter, QVariant(parity));
    client->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QVariant(dataBits));
    client->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QVariant(stopBits));

    client->setTimeout(1000);
    client->setNumberOfRetries(3);

    connect(client, &QModbusClient::stateChanged, this,
            [=](QModbusDevice::State state) {
                if (state == QModbusDevice::ConnectedState) {
                    emit connected();
                } else if (state == QModbusDevice::UnconnectedState) {
                    emit disconnected();
                }
            });

    connect(client, &QModbusClient::errorOccurred, this,
            [=](QModbusDevice::Error) {
                emit errorOccurred(client->errorString());
            });

    return client->connectDevice();
}

void ModbusClient::disconnectDevice()
{
    if (m_client) {
        m_client->disconnectDevice();
        m_client->deleteLater();
        m_client = nullptr;
    }
}

void ModbusClient::readHoldingRegisters(int serverAddress, int startAddress, quint16 count)
{
    if (!m_client) {
        emit errorOccurred("Modbus client is null");
        return;
    }

    if (m_client->state() != QModbusDevice::ConnectedState) {
        emit errorOccurred("Modbus client is not connected");
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters,
                         startAddress,
                         count);

    QModbusReply *reply = m_client->sendReadRequest(unit, serverAddress);

    if (!reply) {
        emit errorOccurred(m_client->errorString());
        return;
    }

    if (reply->isFinished()) {
        reply->deleteLater();
        return;
    }

    connect(reply, &QModbusReply::finished, this, [=]() {
        if (reply->error() == QModbusDevice::NoError) {
            QModbusDataUnit result = reply->result();

            QVector<quint16> values;
            values.reserve(int(result.valueCount()));

            for (uint i = 0; i < result.valueCount(); ++i) {
                values.append(result.value(i));
            }

            emit readResult(values);
        } else {
            emit errorOccurred(reply->errorString());
        }

        reply->deleteLater();
    });
}

void ModbusClient::writeSingleRegister(int serverAddress, int address, quint16 value)
{
    if (!m_client) {
        emit errorOccurred("Modbus client is null");
        return;
    }

    if (m_client->state() != QModbusDevice::ConnectedState) {
        emit errorOccurred("Modbus client is not connected");
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters,
                         address,
                         1);

    unit.setValue(0, value);

    QModbusReply *reply = m_client->sendWriteRequest(unit, serverAddress);

    if (!reply) {
        emit errorOccurred(m_client->errorString());
        return;
    }

    if (reply->isFinished()) {
        reply->deleteLater();
        return;
    }

    connect(reply, &QModbusReply::finished, this, [=]() {
        if (reply->error() != QModbusDevice::NoError) {
            emit errorOccurred(reply->errorString());
        }

        reply->deleteLater();
    });
}