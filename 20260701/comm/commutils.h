#ifndef COMMUTILS_H
#define COMMUTILS_H

#include <QString>
#include <QByteArray>

class CommUtils
{
public:
    static QByteArray hexStringToByteArray(QString hex);
    static QString byteArrayToHexString(const QByteArray &data);
};

#endif // COMMUTILS_H