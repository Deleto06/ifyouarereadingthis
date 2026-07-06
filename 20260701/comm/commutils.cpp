#include "commutils.h"

QByteArray CommUtils::hexStringToByteArray(QString hex)
{
    hex.remove(" ");
    hex.remove("\r");
    hex.remove("\n");
    hex.remove("\t");

    return QByteArray::fromHex(hex.toLatin1());
}

QString CommUtils::byteArrayToHexString(const QByteArray &data)
{
    return data.toHex(' ').toUpper();
}