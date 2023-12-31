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
        Q_INVOKABLE static bool fileExist(const QString &fName);

        Q_INVOKABLE static QString formatFileSize(uint64_t size);
        Q_INVOKABLE static QString formatFilePermissis(QFileDevice::Permissions permissions);
        Q_INVOKABLE static QString removeFileNameFormat(const QString &fName, const QString &fNameFormat);
        Q_INVOKABLE static QString addFileNameFormat(const QString &fName, const QString &fNameFormat);
    };
}

#endif // FILESUTILS_H
