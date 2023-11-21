#include "register.h"

#include <QtQml/QtQml>

#include "sortedmodel.h"
#include "filesmanager.h"
#include "utils/filesutils.h"

inline void initialize_resources_within_namespace()
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
    Q_INIT_RESOURCE(fileDialogQml);
    Q_INIT_RESOURCE(fileDialogRc);
#endif
}


void FileDialog::register_module()
{
    initialize_resources_within_namespace();

    qRegisterMetaType<int64_t>("int64_t");
    qRegisterMetaType<uint64_t>("uint64_t");

    qmlRegisterModule("FileDialog", 1, 0);
    qmlRegisterType<FileDialog::FilesManager>("FileDialog.FilesManager", 1, 0, "FilesManager");
    qmlRegisterType<FileDialog::SortedModel>("FileDialog.FilesManager", 1, 0, "SortedModel");
    qmlRegisterType<Utils::Files>("FileDialog.FilesUtils", 1, 0, "FilesUtils");
    qmlRegisterType(QUrl("qrc:/FileDialogQml/FileDialog.qml"), "FileDialog", 1, 0, "FileDialog");
}
