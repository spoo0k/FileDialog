#include <iostream>

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>
#include <QtWidgets/QApplication>

#include <filesmanager.h>
#include <sortedmodel.h>
#include <utils/filesutils.h>




#if defined(Q_OS_WIN)
#include <windows.h>
#endif


int main(int argc, char* argv[]) {

#if defined(Q_OS_WIN)
    FreeConsole();
#endif

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setOrganizationName(PROJECT_COMPANY);

#if defined QT_OS_WINDOWS
    app.setWindowIcon(QIcon(":/icon.ico"));
#else
    QApplication::setWindowIcon(QIcon(":/icon.png"));
#endif

    qInfo().noquote() << QCoreApplication::applicationName() << "version" << QCoreApplication::applicationVersion();

    const QUrl qml_entry(QStringLiteral("qrc:/Main.qml"));
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    QQuickStyle::setStyle("Fusion");

    QQmlEngine engine;
    QObject::connect(&engine, &QQmlEngine::quit, qApp, &QCoreApplication::quit);

    qmlRegisterType<FileDialog::FilesManager>("FileDialog.FilesManager", 1, 0, "FilesManager");
    qmlRegisterType<FileDialog::SortedModel>("FileDialog.FilesManager", 1, 0, "SortedModel");
    qmlRegisterType<Utils::Files>("FileDialog.FilesUtils", 1, 0, "FilesUtils");
    qRegisterMetaType<int64_t>("int64_t");
    qRegisterMetaType<uint64_t>("uint64_t");

    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    component.loadUrl(qml_entry);
    if(component.isReady())
    {
        component.create();
    }
    else
    {
        qInstallMessageHandler(nullptr);
        qCritical() << "[QML ERROR]" << component.errorString();
    }
    return QApplication::exec();

}
