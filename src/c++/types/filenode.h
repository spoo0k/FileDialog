#ifndef FILENODE_H
#define FILENODE_H

#include <cstdint>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QFileDevice>

namespace Types{
    enum class FileType {
        Directory,
        File,
        Link
    };

    struct FileNode
    {
        QString name{};
        QString absolutePath{};
        FileType type{};
        uint64_t size{0};
        QDateTime createTime{};
        QDateTime updateTime{};
        QDateTime accessTime{};
        QFileDevice::Permissions permissions{};
        QString owner{};
    };
}

#endif // FILENODE_H
