#include "filesutils.h"

#include <cmath>
#include <QtCore/QDir>


namespace Utils::Files {
    bool removeFile(const QString &fName)
    {
        return QDir().remove(fName);
    }

    bool removeDir(const QString &dName)
    {
        return QDir().rmdir(dName);
    }

    bool removeDirRecursively(const QString &dName)
    {
        return QDir(dName).removeRecursively();
    }

    QString formatFileSize(uint64_t size)
    {
        static std::array<QString , 7> prefixes{ " bit", " B", " KB", " MB", " GB", " TB", " PB" };
        auto log1024 = [](auto &num) -> int{return static_cast<int>(std::log(num) / std::log(1024));};
        auto exp = size == 0 ? 0 : log1024(size);
        return QString::number(static_cast<float>(size) / std::pow(1024, exp), 'f', 2) + prefixes[exp + 1];

    }

    QString formatFilePermissis(QFileDevice::Permissions permissions)
    {
        QString result{};
        result += permissions & QFileDevice::Permission::ReadOwner  ? "r" : "_";
        result += permissions & QFileDevice::Permission::WriteOwner ? "w" : "_";
        result += permissions & QFileDevice::Permission::ExeOwner   ? "x" : "_";
        result += permissions & QFileDevice::Permission::ReadUser   ? "r" : "_";
        result += permissions & QFileDevice::Permission::WriteUser  ? "w" : "_";
        result += permissions & QFileDevice::Permission::ExeUser    ? "x" : "_";
        result += permissions & QFileDevice::Permission::ReadGroup  ? "r" : "_";
        result += permissions & QFileDevice::Permission::WriteGroup ? "w" : "_";
        result += permissions & QFileDevice::Permission::ExeGroup   ? "x" : "_";
        result += permissions & QFileDevice::Permission::ReadOther  ? "r" : "_";
        result += permissions & QFileDevice::Permission::WriteOther ? "w" : "_";
        result += permissions & QFileDevice::Permission::ExeOther   ? "x" : "_";
        return result;
    }
}
