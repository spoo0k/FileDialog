#include "filesmanager.h"

#include <cassert>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <utils/filesutils.h>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace FileDialog;

FilesManager::FilesManager(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data.reserve(1024);
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
    case ModelRoles::Path:
        return m_data.at(index.row()).absolutePath;
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
    roles[ModelRoles::Path] = "path";
    roles[ModelRoles::Size] = "size";
    roles[ModelRoles::CreateTime] = "createTime";
    roles[ModelRoles::UpdateTime] = "updateTime";
    roles[ModelRoles::AccessTime] = "accessTime";
    roles[ModelRoles::Owner] = "owner";
    roles[ModelRoles::Permissions] = "permissions";
    return roles;
}

void FilesManager::refresh(const QString &dirPath)
{
    QFileInfo f(dirPath);
    assertm(f.exists() and f.isDir() and f.isWritable(), "Can`t access target path");
    clear();
    auto d = QDir(dirPath, filterName(), QDir::SortFlags(QDir::SortFlag::Name | QDir::SortFlag::IgnoreCase), QDir::AllEntries | QDir::Hidden);
    auto checkType = [](QFileInfo info) -> Types::FileType {
        if(info.isDir()) return Types::FileType::Directory;
        if(info.isSymLink()) return Types::FileType::SymLink;
        if(info.isFile()) return Types::FileType::File;
        return Types::FileType::Unknown;
    };
    for (const auto &item : d.entryInfoList()) {
        m_data.push_back({.name = item.fileName(),
                          .absolutePath = item.absoluteFilePath(),
                          .type = checkType(item),
                          .size = static_cast<uint64_t>(item.size()),
                          .createTime = item.birthTime(),
                          .updateTime = item.lastModified(),
                          .accessTime = item.lastRead(),
                          .permissions = item.permissions(),
                          .owner = item.owner()});
    }
}

void FilesManager::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_data.clear();
    endRemoveRows();
}

QString FilesManager::targetPath() const { return m_targetPath; }
void FilesManager::setTargetPath(const QString &newTargetPath)
{
    if (m_targetPath == newTargetPath)
        return;
    m_targetPath = newTargetPath;
    emit targetPathChanged();
}

QString FilesManager::currentPath() const { return m_currentPath; }
void FilesManager::setCurrentPath(const QString &newCurrentPath)
{
    if (m_currentPath == newCurrentPath)
        return;
    m_currentPath = newCurrentPath;
    emit currentPathChanged();
}

QString FilesManager::filterName() const { return m_filterName; }
void FilesManager::setFilterName(const QString &newFilterName)
{
    if (m_filterName == newFilterName)
        return;
    m_filterName = newFilterName;
    emit filterNameChanged();
}
