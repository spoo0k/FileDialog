#include "sortedmodel.h"
#include <QtCore/QDebug>

#include "filesmanager.h"
#include "utils/filesutils.h"

using namespace FileDialog;

SortedModel::SortedModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setDynamicSortFilter(true);
    setFilterRole(FilesManager::ModelRoles::Name);
    connect(this, &QSortFilterProxyModel::sortRoleChanged, this, [this](auto role){sort(0, m_sOrder);});
    connect(this, &SortedModel::searchPatternChanged, this, &SortedModel::invalidateFilter);
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
    QVariant leftData = sourceModel()->data(left, sortRole());
    QVariant rightData = sourceModel()->data(right, sortRole());
    if(sortRole() == FilesManager::ModelRoles::Name) {
        return QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive);
    }
    else if(sortRole() == FilesManager::ModelRoles::Size) {
        return leftData.toULongLong() < rightData.toULongLong();
    }
    return true;
}

bool SortedModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    auto postfix = "." + index.data(FilesManager::ModelRoles::CompleteSuffix).toString();
    auto name = index.data(FilesManager::ModelRoles::Name).toString();
    return ((postfix) == fileFormat() || fileFormat().isEmpty()) && Utils::Files::removeFileNameFormat(name, postfix).contains(searchPattern());
}

QString SortedModel::fileFormat() const { return m_fileFormat; }
void SortedModel::setFileFormat(const QString &newFileFormat)
{
    if (m_fileFormat == newFileFormat)
        return;
    m_fileFormat.clear();
    if(newFileFormat.at(0) != ".") {
        m_fileFormat += ".";
    }
    m_fileFormat += newFileFormat;
    emit fileFormatChanged();
}

QString SortedModel::searchPattern() const { return m_searchPattern; }
void SortedModel::setSearchPattern(const QString &newSearchPattern)
{
    if (m_searchPattern == newSearchPattern)
        return;
    m_searchPattern = newSearchPattern;
    emit searchPatternChanged();
}
