#ifndef SORTEDMODEL_H
#define SORTEDMODEL_H

#include <QtCore/QSortFilterProxyModel>

namespace FileDialog
{
    class SortedModel : public QSortFilterProxyModel
    {
        Q_OBJECT
        Q_PROPERTY(QString fileFormat READ fileFormat WRITE setFileFormat NOTIFY fileFormatChanged FINAL)
        Q_PROPERTY(QString searchPattern READ searchPattern WRITE setSearchPattern NOTIFY searchPatternChanged FINAL)
    public:
        explicit SortedModel(QObject *parent = nullptr);
        Q_INVOKABLE void changeSortOrder();

        QString fileFormat() const;
        void setFileFormat(const QString &newFileFormat);

        QString searchPattern() const;
        void setSearchPattern(const QString &newSearchPattern);

    signals:
        void fileFormatChanged();

        void searchPatternChanged();

    protected:
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
        bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;


    private:
        Qt::SortOrder m_sOrder = Qt::AscendingOrder;
        QString m_fileFormat;
        QString m_searchPattern;
    };
}

#endif // SORTEDMODEL_H
