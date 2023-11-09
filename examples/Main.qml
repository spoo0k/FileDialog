import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15


ApplicationWindow  {
    id: window_root;
    title: ""
    Material.theme: Material.Dark






    Shortcut {
        sequence: StandardKey.Quit;
        context: Qt.ApplicationShortcut;
        onActivated: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        window_root.x = Qt.application.screens[1].virtualX;
        window_root.y = Qt.application.screens[1].virtualY;
        window_root.visibility = Window.FullScreen;
        window_root.visible = true;
    }
}
