#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QSerialPort>

class SerialComm : public QObject
{
    Q_OBJECT

public:
    explicit SerialComm(QObject *parent = nullptr);
    ~SerialComm();

    bool open(const QString &portName,
              int baudRate,
              QSerialPort::DataBits dataBits,
              QSerialPort::Parity parity,
              QSerialPort::StopBits stopBits);

    void close();
    bool isOpen() const;

    qint64 sendData(const QByteArray &data);

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);
    void stateChanged(bool opened);

private:
    QSerialPort *m_serial = nullptr;
};

#endif // SERIALCOMM_H