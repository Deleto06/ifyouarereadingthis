#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <QObject>
#include <QVector>
#include <QModbusTcpClient>
#include <QModbusDevice>
#include <QModbusDataUnit>

class ModbusClient : public QObject
{
    Q_OBJECT

public:
    explicit ModbusClient(QObject *parent = nullptr);
    ~ModbusClient();

    bool connectToServer(const QString &ip, int port);
    void disconnectFromServer();

    bool isConnected() const;

    void readHoldingRegisters(int serverAddress, int startAddress, quint16 count);
    void writeSingleHoldingRegister(int serverAddress, int address, quint16 value);
    void writeMultipleHoldingRegisters(int serverAddress, int startAddress, const QVector<quint16> &values);

signals:
    void connected();
    void disconnected();
    void logMessage(const QString &msg);
    void errorOccurred(const QString &error);

    void holdingRegistersRead(int startAddress, QVector<quint16> values);
    void writeFinished(const QString &message);


private slots:
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);

private:
    QModbusTcpClient *m_client = nullptr;
};

#endif // MODBUSCLIENT_H