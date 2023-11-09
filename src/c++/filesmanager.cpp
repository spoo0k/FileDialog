#include "filesmanager.h"
#include <utils/filesutils.h>

using namespace FileDialog;

FilesManager::FilesManager(QObject *parent)
    : QAbstractListModel{parent}
{

}

int FilesManager::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

QVariant FilesManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return  {};
    }
    switch (role) {
    case ModelRoles::Index:
        return index.row();
    case ModelRoles::Name:
        return m_data.at(index.row()).name;
    case ModelRoles::Size:
        return Utils::Files::formatFileSize(m_data.at(index.row()).size);
    case ModelRoles::CreateTime:
        return m_data.at(index.row()).createTime.toString("dd.mm.yyyy");
    case ModelRoles::UpdateTime:
        return m_data.at(index.row()).updateTime.toString("dd.mm.yyyy");
    case ModelRoles::AccessTime:
        return m_data.at(index.row()).accessTime.toString("dd.mm.yyyy");
    case ModelRoles::Owner:
        return m_data.at(index.row()).owner;
    case ModelRoles::Permissions:
        return Utils::Files::formatFilePermissis(m_data.at(index.row()).permissions); // fromat
    default:
        return {};
    }
}

QHash<int, QByteArray> FilesManager::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[ModelRoles::Index] = "index";
    roles[ModelRoles::Name] = "name";
    roles[ModelRoles::Size] = "size";
    roles[ModelRoles::CreateTime] = "createTime";
    roles[ModelRoles::UpdateTime] = "updateTime";
    roles[ModelRoles::AccessTime] = "accessTime";
    roles[ModelRoles::Owner] = "owner";
    roles[ModelRoles::Permissions] = "permissions";
    return roles;
}
