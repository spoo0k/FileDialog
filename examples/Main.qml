import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15


ApplicationWindow  {
    id: window_root;
    title: ""
//    Material.theme: Material.Dark

    Button{
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        path: "/home/user"
        fileFormat: ".json"
        selectNoExistFile: false
        onAccepted: {
            console.log(fileUrl)
        }
    }

    Shortcut {
        sequence: StandardKey.Quit;
        context: Qt.ApplicationShortcut;
        onActivated: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        window_root.x = Qt.application.screens[1 % Qt.application.screens.length].virtualX;
        window_root.y = Qt.application.screens[1 % Qt.application.screens.length].virtualY;
        window_root.visibility = Window.FullScreen;
        window_root.visible = true;
    }
}
