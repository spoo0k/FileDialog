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
        Q_PROPERTY(QString targetPath READ targetPath WRITE setTargetPath NOTIFY targetPathChanged FINAL)
        Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged FINAL)
        Q_PROPERTY(QString filterName READ filterName WRITE setFilterName NOTIFY filterNameChanged FINAL)
        Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged FINAL)

    public:

        enum ModelRoles {
            Index = Qt::UserRole + 1,
            Name,
            Path,
            Size,
            CreateTime,
            UpdateTime,
            AccessTime,
            Owner,
            Permissions
        };
        Q_ENUM(ModelRoles)

    public:
        explicit FilesManager(QObject *parent = nullptr);
        int rowCount(const QModelIndex & = {}) const override;
        QVariant data (const QModelIndex &index, int role) const override;
        QHash<int, QByteArray> roleNames() const override;

        void refresh(const QString &dirPath);
        void clear();

        Q_INVOKABLE QString name(int index);
        Q_INVOKABLE QString currentName();
        Q_INVOKABLE void rename(int index, QString newName);
        Q_INVOKABLE void remove(int index);

        QString targetPath() const; void setTargetPath(const QString &newTargetPath);
        QString currentPath() const; void setCurrentPath(const QString &newCurrentPath);
        QString filterName() const; void setFilterName(const QString &newFilterName);
        int currentIndex() const; void setCurrentIndex(int newCurrentIndex);

    signals:
        void targetPathChanged();
        void currentPathChanged();
        void filterNameChanged();

        void currentIndexChanged();

    private:
        std::vector<Types::FileNode> m_data {};
        QString m_targetPath {};
        QString m_currentPath {};
        QString m_filterName;
        int m_currentIndex;
    };
}

#endif // FILESMANAGER_H
