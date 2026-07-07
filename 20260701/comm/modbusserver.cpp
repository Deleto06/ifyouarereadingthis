#include "modbusserver.h"

#include <QVariant>

ModbusServer::ModbusServer(QObject *parent)
    : QObject(parent)
{
}

ModbusServer::~ModbusServer()
{
    stop();
}

bool ModbusServer::startTcp(int port, int serverAddress)
{
    stop();

    auto *server = new QModbusTcpServer(this);
    m_server = server;

    server->setServerAddress(serverAddress);
    server->setConnectionParameter(QModbusDevice::NetworkPortParameter, QVariant(port));

    QModbusDataUnitMap map;

    map.insert(QModbusDataUnit::Coils,
               QModbusDataUnit(QModbusDataUnit::Coils, 0, 100));

    map.insert(QModbusDataUnit::DiscreteInputs,
               QModbusDataUnit(QModbusDataUnit::DiscreteInputs, 0, 100));

    map.insert(QModbusDataUnit::InputRegisters,
               QModbusDataUnit(QModbusDataUnit::InputRegisters, 0, 100));

    map.insert(QModbusDataUnit::HoldingRegisters,
               QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 100));

    server->setMap(map);

    connect(m_server, &QModbusServer::dataWritten,
            this,
            [this](QModbusDataUnit::RegisterType table, int address, int size)
            {
                if (table != QModbusDataUnit::HoldingRegisters) {
                    return;
                }

                for (int i = 0; i < size; ++i) {
                    quint16 value = 0;

                    bool ok = m_server->data(QModbusDataUnit::HoldingRegisters,
                                             address + i,
                                             &value);

                    if (ok) {
                        emit logMessage(QString("[Modbus TCP Server] client wrote HR[%1] = %2")
                                            .arg(address + i)
                                            .arg(value));

                        emit holdingRegisterChanged(address + i, value);
                    }
                }
            });

    connect(server, &QModbusServer::dataWritten,
            this, &ModbusServer::dataWritten);

    connect(server, &QModbusServer::errorOccurred,
            this,
            [=](QModbusDevice::Error) {
                emit errorOccurred(server->errorString());
            });

    bool ok = server->connectDevice();

    if (!ok) {
        emit errorOccurred(server->errorString());
    }

    return ok;
}

bool ModbusServer::startRtu(const QString &portName,
                            int baudRate,
                            int parity,
                            int dataBits,
                            int stopBits,
                            int serverAddress)
{
    stop();

    auto *server = new QModbusRtuSerialServer(this);
    m_server = server;

    server->setServerAddress(serverAddress);

    server->setConnectionParameter(QModbusDevice::SerialPortNameParameter, QVariant(portName));
    server->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QVariant(baudRate));
    server->setConnectionParameter(QModbusDevice::SerialParityParameter, QVariant(parity));
    server->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QVariant(dataBits));
    server->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QVariant(stopBits));

    QModbusDataUnitMap map;

    map.insert(QModbusDataUnit::Coils,
               QModbusDataUnit(QModbusDataUnit::Coils, 0, 100));

    map.insert(QModbusDataUnit::DiscreteInputs,
               QModbusDataUnit(QModbusDataUnit::DiscreteInputs, 0, 100));

    map.insert(QModbusDataUnit::InputRegisters,
               QModbusDataUnit(QModbusDataUnit::InputRegisters, 0, 100));

    map.insert(QModbusDataUnit::HoldingRegisters,
               QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 100));

    server->setMap(map);

    connect(server, &QModbusServer::dataWritten,
            this, &ModbusServer::dataWritten);

    connect(server, &QModbusServer::errorOccurred,
            this,
            [=](QModbusDevice::Error) {
                emit errorOccurred(server->errorString());
            });

    bool ok = server->connectDevice();

    if (!ok) {
        emit errorOccurred(server->errorString());
    }

    return ok;
}

void ModbusServer::stop()
{
    if (m_server) {
        m_server->disconnectDevice();
        m_server->deleteLater();
        m_server = nullptr;
    }
}

bool ModbusServer::setHoldingRegister(int address, quint16 value)
{
    if (!m_server) {
        return false;
    }

    return m_server->setData(QModbusDataUnit::HoldingRegisters, address, value);
}

quint16 ModbusServer::holdingRegister(int address) const
{
    if (!m_server) {
        return 0;
    }

    quint16 value = 0;
    m_server->data(QModbusDataUnit::HoldingRegisters, address, &value);

    return value;
}