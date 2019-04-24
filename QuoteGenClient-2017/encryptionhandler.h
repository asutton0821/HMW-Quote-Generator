#ifndef ENCRYPTIONHANDLER_H
#define ENCRYPTIONHANDLER_H

#include <QString>
#include <QChar>
#include <QDebug>

class encryptionHandler
{
public:
    encryptionHandler();
    QString encryptString(QString string);
    QString decryptString(QString string);
};

#endif // ENCRYPTIONHANDLER_H
