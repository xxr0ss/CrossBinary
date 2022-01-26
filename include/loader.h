#ifndef LOADER_H
#define LOADER_H

#include "binary.h"
#include <QObject>
#include <QString>
#include <mutex>

class BinaryLoader : public QObject
{
    Q_OBJECT

public:
    static BinaryLoader *getBinaryLoader();
    ~BinaryLoader();

private:
    BinaryLoader();
    static std::mutex _mutex;
    static BinaryLoader *_instance;

public:
    Binary *binary;

    int load_binary(QString &fname, Binary::BinaryType type);
    void unload_binary();
};

#endif /* LOADER_H */
