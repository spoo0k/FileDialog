#include "filesmanager.h"

#include <cassert>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <utils/filesutils.h>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace FileDialog;

FilesManager::FilesManager(QObject *parent)
    : QAbstractListModel{parent}
    , m_filterName("*")
    ,m_currentIndex{-1}
{
    m_data.reserve(1024);
    connect(this, &FilesManager::currentPathChanged, this, [this](){refresh(currentPath());});
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
    case ModelRoles::CompleteSuffix:
        return m_data.at(index.row()).completeSuffix;
    case ModelRoles::Path:
        return m_data.at(index.row()).absolutePath;
    case ModelRoles::Size:
        return QVariant::fromValue(m_data.at(index.row()).size);
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
    roles[ModelRoles::CompleteSuffix] = "completeSuffix";
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
    beginInsertRows(QModelIndex(), 0 , d.entryInfoList().size() - 1);
    for (const auto &item : d.entryInfoList()) {
        m_data.push_back({.name = item.fileName(),
                          .absolutePath = item.absoluteFilePath(),
                          .completeSuffix = item.completeSuffix(),
                          .type = checkType(item),
                          .size = static_cast<uint64_t>(item.size()),
                          .createTime = item.birthTime(),
                          .updateTime = item.lastModified(),
                          .accessTime = item.lastRead(),
                          .permissions = item.permissions(),
                          .owner = item.owner()});
    }
    endInsertRows();
}

void FilesManager::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_data.clear();
    endRemoveRows();
}

QString FilesManager::path(int index)
{
    if(index < 0 || index >= m_data.size()) {
        return {};
    }
    return m_data.at(index).absolutePath;
}

QString FilesManager::name(int index)
{
    if(index < 0 || index >= m_data.size()) {
        return {};
    }
    return m_data.at(index).name;
}

QString FilesManager::currentName()
{
    return name(currentIndex());
}

void FilesManager::rename(int index, QString newName)
{
    if(index < 0 || index >= m_data.size() || m_data.at(index).name == newName) {
        return;
    }
    auto path = m_data.at(index).absolutePath.split('/');
    path[path.size() - 1] = newName;
    auto newPath = path.join("/");
    qDebug() << newPath;
    auto res = Utils::Files::rename(m_data.at(index).absolutePath, newPath);
    if(not res) {
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        qWarning() << "Error rename file from : " << m_data.at(index).absolutePath << ". To: " << newPath;
    }
    else{
        qInfo() << "Rename file from : " << m_data.at(index).absolutePath << ". To: " << newPath;
        m_data[index].absolutePath = newPath;
        m_data[index].name = newName;
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        emit currentIndexChanged();
    }
}

void FilesManager::remove(int index)
{
    if(index < 0 || index >= m_data.size()) {
        return;
    }
    if(Utils::Files::removeFile(m_data.at(index).absolutePath)) {
        beginRemoveRows(QModelIndex(), index, index);
        m_data.erase(m_data.cbegin() + index);
        endRemoveRows();
    }
    if(index == currentIndex()) {
        setCurrentIndex(-1);
    }
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
    if(m_currentPath.at(m_currentPath.size() - 1 ) != QDir::separator()) {
        m_currentPath += QDir::separator();
    }
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

int FilesManager::currentIndex() const { return m_currentIndex; }
void FilesManager::setCurrentIndex(int newCurrentIndex)
{
    if(m_currentIndex == newCurrentIndex) {
        return;
    }
    m_currentIndex = newCurrentIndex;
    emit currentIndexChanged();
}
