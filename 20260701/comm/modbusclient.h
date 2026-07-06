#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusRtuSerialClient>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusDevice>

#include <QSerialPort>

class ModbusClient : public QObject
{
    Q_OBJECT

public:
    explicit ModbusClient(QObject *parent = nullptr);
    ~ModbusClient();

    bool connectTcp(const QString &ip, int port);

    bool connectRtu(const QString &portName,
                    int baudRate,
                    int parity,
                    int dataBits,
                    int stopBits);

    void disconnectDevice();

    void readHoldingRegisters(int serverAddress, int startAddress, quint16 count);
    void writeSingleRegister(int serverAddress, int address, quint16 value);

signals:
    void connected();
    void disconnected();
    void readResult(QVector<quint16> values);
    void errorOccurred(QString error);

private:
    QModbusClient *m_client = nullptr;
};

#endif // MODBUSCLIENT_H