#ifndef SORTEDMODEL_H
#define SORTEDMODEL_H

#include <QtCore/QSortFilterProxyModel>
#include <filesmanager.h>

namespace FileDialog
{
    class SortedModel : public QSortFilterProxyModel
    {
        Q_OBJECT
        Q_PROPERTY(QString fileFormat READ fileFormat WRITE setFileFormat NOTIFY fileFormatChanged FINAL)
    public:
        explicit SortedModel(QObject *parent = nullptr);
        Q_INVOKABLE void changeSortOrder();

        QString fileFormat() const;
        void setFileFormat(const QString &newFileFormat);

    signals:
        void fileFormatChanged();

    protected:
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
        bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;


    private:
        Qt::SortOrder m_sOrder = Qt::AscendingOrder;
        QString m_fileFormat;
    };
}

#endif // SORTEDMODEL_H
