#ifndef FILESUTILS_H
#define FILESUTILS_H

#include <cstdint>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFileDevice>

namespace Utils
{
    class Files : public QObject {
        Q_OBJECT
    public:
        Files(QObject * parent = nullptr): QObject{parent}{}

        static bool removeFile(const QString &fName);
        static bool removeDir(const QString &dName);
        static bool removeDirRecursively(const QString &dName);
        static bool rename(const QString &oldName, const QString &newName);

        Q_INVOKABLE static QString formatFileSize(uint64_t size);
        Q_INVOKABLE static QString formatFilePermissis(QFileDevice::Permissions permissions);
    };
}

#endif // FILESUTILS_H
