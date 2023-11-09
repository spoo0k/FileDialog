#ifndef FILESMANAGER_H
#define FILESMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>

#include <types/filenode.h>


namespace FileDialog
{
    class FilesManager : public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum ModelRoles {
            Index = Qt::UserRole + 1,
            Name,
            Size,
            CreateTime,
            UpdateTime,
            AccessTime,
            Owner,
            Permissions
        };
    public:
        explicit FilesManager(QObject *parent = nullptr);
        int rowCount(const QModelIndex &) const override;
        QVariant data (const QModelIndex &index, int role) const override;
        QHash<int, QByteArray> roleNames() const override;

    private:
        std::vector<Types::FileNode> m_data;
    };
}

#endif // FILESMANAGER_H
