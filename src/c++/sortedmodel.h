#ifndef SORTEDMODEL_H
#define SORTEDMODEL_H

#include <QtCore/QSortFilterProxyModel>
#include <filesmanager.h>

namespace FileDialog
{
    class SortedModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        explicit SortedModel(QObject *parent = nullptr);
        Q_INVOKABLE void changeSortOrder();

    protected:
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;


    private:
        Qt::SortOrder m_sOrder = Qt::AscendingOrder;
    };
}

#endif // SORTEDMODEL_H
