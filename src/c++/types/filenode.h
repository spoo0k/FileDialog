#ifndef FILENODE_H
#define FILENODE_H

#include <cstdint>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QFileDevice>

namespace Types{
    enum class FileType {
        Unknown,
        Directory,
        File,
        SymLink
    };

    struct FileNode
    {
        QString name{};
        QString absolutePath{};
        QString completeSuffix{};
        FileType type{FileType::Unknown};
        uint64_t size{0};
        QDateTime createTime{};
        QDateTime updateTime{};
        QDateTime accessTime{};
        QFileDevice::Permissions permissions{};
        QString owner{};
    };
}

#endif // FILENODE_H
