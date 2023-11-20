#include "sortedmodel.h"
#include <QtCore/QDebug>

using namespace FileDialog;

SortedModel::SortedModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setDynamicSortFilter(true);
    connect(this, &QSortFilterProxyModel::sortRoleChanged, this, [this](auto role){sort(0, m_sOrder);});
}

void SortedModel::changeSortOrder()
{
    if(m_sOrder == Qt::AscendingOrder){
        m_sOrder = Qt::DescendingOrder;
    }
    else {
        m_sOrder = Qt::AscendingOrder;
    }
    sort(0, m_sOrder);
}

bool SortedModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, filterRole());
    QVariant rightData = sourceModel()->data(right, filterRole());
    qDebug() << "hello";
    if(filterRole() == FilesManager::ModelRoles::Name) {
        return QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive);
    }
    return true;
}
