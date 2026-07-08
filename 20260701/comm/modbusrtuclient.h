#ifndef MODBUSRTUCLIENT_H
#define MODBUSRTUCLIENT_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QVector>

class ModbusRtuClient : public QObject
{
    Q_OBJECT

public:
    explicit ModbusRtuClient(QObject *parent = nullptr);
    ~ModbusRtuClient();

    bool open(const QString &portName,
              qint32 baudRate,
              QSerialPort::DataBits dataBits,
              QSerialPort::Parity parity,
              QSerialPort::StopBits stopBits);

    void close();

    bool isOpen() const;

    void readHoldingRegisters(quint8 slaveId,
                              quint16 startAddress,
                              quint16 count);

    void writeSingleHoldingRegister(quint8 slaveId,
                                    quint16 address,
                                    quint16 value);

    void writeMultipleHoldingRegisters(quint8 slaveId,
                                       quint16 startAddress,
                                       const QVector<quint16> &values);

signals:
    void opened();
    void closed();
    void errorOccurred(const QString &error);
    void logMessage(const QString &message);

    void rawDataSent(const QByteArray &data);
    void rawDataReceived(const QByteArray &data);

    void holdingRegistersRead(quint8 slaveId,
                              quint16 startAddress,
                              QVector<quint16> values);

    void writeFinished(quint8 slaveId,
                       quint8 functionCode,
                       quint16 startAddress,
                       quint16 count);

private slots:
    void onReadyRead();
    void onFrameTimeout();

private:
    quint16 crc16(const QByteArray &data) const;
    void appendCrc(QByteArray &frame) const;
    bool checkCrc(const QByteArray &frame) const;

    QByteArray buildReadHoldingRegistersFrame(quint8 slaveId,
                                              quint16 startAddress,
                                              quint16 count) const;

    QByteArray buildWriteSingleRegisterFrame(quint8 slaveId,
                                             quint16 address,
                                             quint16 value) const;

    QByteArray buildWriteMultipleRegistersFrame(quint8 slaveId,
                                                quint16 startAddress,
                                                const QVector<quint16> &values) const;

    void sendFrame(const QByteArray &frame);

    void parseFrame(const QByteArray &frame);
    void parseReadHoldingRegistersResponse(const QByteArray &frame);
    void parseWriteSingleRegisterResponse(const QByteArray &frame);
    void parseWriteMultipleRegistersResponse(const QByteArray &frame);
    void parseExceptionResponse(const QByteArray &frame);

private:
    QSerialPort *m_serial = nullptr;
    QTimer *m_frameTimer = nullptr;
    QByteArray m_recvBuffer;

    quint8 m_lastSlaveId = 0;
    quint8 m_lastFunctionCode = 0;
    quint16 m_lastStartAddress = 0;
    quint16 m_lastCount = 0;
};

#endif // MODBUSRTUCLIENT_H