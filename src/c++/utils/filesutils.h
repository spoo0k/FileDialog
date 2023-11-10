#ifndef FILESUTILS_H
#define FILESUTILS_H

#include <cstdint>
#include <QtCore/QString>
#include <QtCore/QFileDevice>

namespace Utils::Files
{
    bool removeFile(const QString &fName);
    bool removeDir(const QString &dName);
    bool removeDirRecursively(const QString &dName);

    QString formatFileSize(uint64_t size);
    QString formatFilePermissis(QFileDevice::Permissions permissions);
};

#endif // FILESUTILS_H
