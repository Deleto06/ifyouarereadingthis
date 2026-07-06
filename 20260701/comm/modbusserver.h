#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QObject>
#include <QVariant>

#include <QModbusServer>
#include <QModbusTcpServer>
#include <QModbusRtuSerialServer>
#include <QModbusDataUnit>
#include <QModbusDevice>

class ModbusServer : public QObject
{
    Q_OBJECT

public:
    explicit ModbusServer(QObject *parent = nullptr);
    ~ModbusServer();

    bool startTcp(int port, int serverAddress);

    bool startRtu(const QString &portName,
                  int baudRate,
                  int parity,
                  int dataBits,
                  int stopBits,
                  int serverAddress);

    void stop();

    bool setHoldingRegister(int address, quint16 value);
    quint16 holdingRegister(int address) const;

signals:
    void errorOccurred(QString error);
    void dataWritten(QModbusDataUnit::RegisterType table, int address, int size);

private:
    QModbusServer *m_server = nullptr;
};

#endif // MODBUSSERVER_H