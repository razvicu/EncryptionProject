#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include <QByteArray>
#include <vector>
#include <stdlib.h>

struct EncryptionData {
    std::vector<char> message;
    std::vector<char> key;
};

EncryptionData encrypt(QString message);
std::vector<char> decrypt(QString message, QString key);

#endif // ENCRYPT_H
