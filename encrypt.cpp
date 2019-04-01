#include "encrypt.h"
#include <QDebug>
#include <bitset>
#include <iostream>
EncryptionData encrypt(QString message) {
    srand(time(NULL));
    std::string _message = message.toStdString();

    std::vector<int> key(_message.size());
    std::vector<char> encryptedMessage;
    std::vector<char> encryptionKey;

    for (size_t i = 0; i < _message.size(); ++i) {
        key[i] = rand() % 26;

        encryptionKey.push_back((char)(key[i] + 65));

        if (_message[i] >= 65 && _message[i] <= 90)
            encryptedMessage.push_back((char) ((_message[i] - 65 + key[i]) % 26));

        else if (_message[i] >= 97 && _message[i] <= 122)
            encryptedMessage.push_back((char) ((_message[i] - 97 + key[i]) % 26));

        else
            encryptedMessage.push_back((char) _message[i]);
    }

    for (int i = 0; i < encryptedMessage.size(); ++i)
        encryptedMessage[i] += 65;

    return {encryptedMessage, encryptionKey};
}

std::vector<char> decrypt(QString message, QString key) {
    std::string _message = message.toStdString();
    std::string _key = key.toStdString();

    std::vector<char> decryptedMessage;

    for (size_t i = 0; i < _message.size(); ++i) {
        if ((_message[i] - _key[i]) < 0)
            decryptedMessage.push_back((char) (_message[i] - _key[i] + 26));

        else if ((_message[i] - _key[i]) >= 0)
            decryptedMessage.push_back((char) (_message[i] - _key[i]));

        else
            decryptedMessage.push_back((char) _message[i]);
    }

    for (int i = 0; i < decryptedMessage.size(); ++i)
        decryptedMessage[i] += 65;

    return decryptedMessage;
}
