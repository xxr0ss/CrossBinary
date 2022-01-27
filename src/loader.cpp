#include "loader.h"
#include <iostream>
#include <QFile>
#include <QDebug>

BinaryLoader *BinaryLoader::_instance = nullptr;
std::mutex BinaryLoader::_mutex;

BinaryLoader *BinaryLoader::getBinaryLoader()
{
    if (!_instance)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_instance)
        {
            _instance = new BinaryLoader();
            return _instance;
        }
    }
    return _instance;
}

BinaryLoader::BinaryLoader() : binary(nullptr)
{
}

BinaryLoader::~BinaryLoader()
{
    if (this->binary)
    {
        delete this->binary;
        this->binary = nullptr;
    }
}

Binary::BinaryType detect_binary_type(QByteArray &header_bytes)
{
    // Detect binary file type
    const char ELF_header[] = {0x7f, 'E', 'L', 'F'};
    const char DOS_header[] = {'M', 'Z'};

    Binary::BinaryType type = Binary::BIN_TYPE_RAW;
    if (header_bytes.sliced(0, 4) == QByteArray(ELF_header, 4))
        type = Binary::BIN_TYPE_ELF;
    else if (header_bytes.sliced(0, 2) == QByteArray(DOS_header, 2))
        type = Binary::BIN_TYPE_PE;

    return type;
}

int BinaryLoader::load_binary(QString &fname, Binary::BinaryType type)
{
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly))
    {
        return -1;
    }

    Binary::BinaryType bin_type;
    if (type == Binary::BIN_TYPE_AUTO)
    {
        auto file_header_bytes = file.read(16);
        bin_type = detect_binary_type(file_header_bytes);
    }

    auto bytes = (uint8_t *)malloc(file.size());
    file.seek(0);
    file.read((char *)bytes, file.size());
    auto filename_stdstr = file.fileName().toStdString();

    if (this->binary)
    {
        delete this->binary;
        this->binary = nullptr;
    }

    switch (bin_type)
    {
    case Binary::BIN_TYPE_RAW:
        this->binary = new Binary(bin_type, filename_stdstr, bytes);
        break;
    case Binary::BIN_TYPE_PE:
    {
        PE_Binary *pe = new PE_Binary(filename_stdstr, bytes);
        this->binary = dynamic_cast<Binary *>(pe);
        break;
    }
    case Binary::BIN_TYPE_ELF:
    {
        ELF_Binary *elf = new ELF_Binary(filename_stdstr, bytes);
        this->binary = dynamic_cast<Binary *>(elf);
        break;
    }
    }

    return this->binary->parse_bytes();
}

void BinaryLoader::unload_binary()
{
    Section *sec;
    auto bin = this->binary;
    for (size_t i = 0; i < bin->sections.size(); i++)
    {
        sec = &bin->sections[i];
        if (sec->bytes)
        {
            free(sec->bytes);
        }
    }
}