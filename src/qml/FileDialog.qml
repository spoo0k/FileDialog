import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import FileDialog.FilesManager 1.0

Dialog {
    id: baseItem
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: parent.width * 2/3
    height: parent.height * 2/3
    title: "File Dialog"
    Overlay.modal: Rectangle { color:"#50000000" }
    closePolicy: Popup.NoAutoClose
    standardButtons: Dialog.NoButton
    modal: true
    background: Rectangle { radius: 4; color: __pallette.background; border.color: __pallette.white; border.width: 1 }
    header : Pane{
        implicitWidth: baseItem.implicitWidth
        background: Rectangle{border.color: __pallette.white; color: Qt.darker(__pallette.background, 2.0); radius: 4}
        RowLayout{
            anchors.fill: parent
            Item{Layout.fillWidth: true}
            Label {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 18
                font.bold: true
                color: __pallette.white
                text: baseItem.title
            }
            Label {
                visible: __filesManager.currentIndex !== -1
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 18
                font.bold: true
                color: __pallette.white
                text: ":  " + __filesManager.name(__filesManager.currentIndex);
            }
            Item{Layout.fillWidth: true}
        }
    }
    SortedModel {id: __sortedModel
        sourceModel: __filesManager
    }

    FilesManager { id: __filesManager }

    QtObject {
        id: __pallette
        property color frostDark: "#5E81AC"
        property color white: "#ffffff"
        property color black: "#000000"
        property color background: "#2f4f4f"
        property color transparent: "#00000000"
    }
    Item {id: __parentItem}


    component FileDialogHeader: Control {
        id: __fileLineHeader
        property string name;
        property string size;
        bottomPadding: 2
        background: Rectangle {color: __pallette.transparent}
        implicitHeight: __hName.implicitHeight * 1.4
        signal sortChanged(var newRole)

        RowLayout {
            anchors.fill: parent
            Button {
                enabled: false
                Layout.fillHeight: true
                Layout.preferredWidth: height
                palette.button: __pallette.transparent
                Material.background: __pallette.transparent
                flat: true
                hoverEnabled: false
            }
            Rectangle {visible: true; color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
            Button {
                id: __hName
                padding: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
                background: Rectangle{color: __pallette.black; opacity: parent.pressed ? 0.2 : 0}
                text: __fileLineHeader.name
                onClicked: {__fileLineHeader.sortChanged(FilesManager.Name); }
            }


            Rectangle {visible: true; color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
            Button {
                id: __hSize
                padding: 0
                Layout.fillHeight: true
//                Layout.fillWidth: true
                Layout.preferredWidth: baseItem.width / 4
                background: Rectangle{color: __pallette.black; opacity: parent.pressed ? 0.2 : 0}
                text: __fileLineHeader.name
                onClicked: __fileLineHeader.sortChanged(FilesManager.Size)
            }
        }
        Rectangle {width: parent.width; height: 1; y : parent.height}
    }

    component FileLineDelegate: Control {
        id: __fileLineDelegate
        property string name;
        property string newName;
        onNameChanged: { __name.text = name; }
        property string size;
        property string iconSource;
        property bool isHeader: false;
        property real mouseX: __fl_ma.mouseX
        property real mouseY: __fl_ma.mouseY
        property bool reneaming: false
        property bool enableReaname: false
        signal clicked(var mouse);
        signal pressed(var mouse);
        signal doubleClicked(var mouse);
        signal acceptRename();
        bottomPadding: 2
        background: Rectangle {color: __pallette.transparent}
        implicitHeight: __name.implicitHeight * 1.4

        RowLayout {
            anchors.fill: parent
            Button {
                enabled: false
                Layout.fillHeight: true
                Layout.preferredWidth: height
                palette.button: __pallette.transparent
                Material.background: __pallette.transparent
                flat: true
                hoverEnabled: false
                icon.source: __fileLineDelegate.iconSource
                icon.color: __pallette.white
            }
            Rectangle {visible: __fileLineDelegate.isHeader; color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
            TextInput {
                id: __name
                readOnly: !__fileLineDelegate.reneaming
                onReadOnlyChanged: {
                    if(!readOnly) {
                        forceActiveFocus()
                        selectAll();
                    }
                    else
                        __name.text = __fileLineDelegate.name;
                }
                Layout.fillHeight: true
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
                color: __pallette.white
                text: __fileLineDelegate.name
                onTextChanged: {if(text != __fileLineDelegate.name) __fileLineDelegate.newName = text;}
                Keys.onPressed: {
                    if(event.key === Qt.Key_Return) { __fileLineDelegate.acceptRename(); __fileLineDelegate.enableReaname = false;}
                    if(event.key === Qt.Key_Escape) { __fileLineDelegate.enableReaname = false;}
                }
            }
            Rectangle {visible: __fileLineDelegate.isHeader; color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
            Label {
                id: __size
                Layout.fillHeight: true
                Layout.preferredWidth: baseItem.width / 4
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: __pallette.white
                text: __fileLineDelegate.size
            }
        }
        MouseArea {
            id: __fl_ma
            enabled: __name.readOnly
            propagateComposedEvents: true
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            onClicked: __fileLineDelegate.clicked(mouse);
            onPressed: __fileLineDelegate.pressed(mouse);
            onDoubleClicked: __fileLineDelegate.doubleClicked(mouse);
        }
        Rectangle {width: parent.width; height: 1; y : parent.height}
    }

    component FileActionDialog: Popup {
        id: __faDialog
        background: Rectangle {color: Qt.darker(__pallette.background, 1.5); radius: 3; border.width: 1; border.color: __pallette.white}
        signal rename();
        signal remove();
        ColumnLayout {
            anchors.fill: parent
            spacing: 3
            Pane {
                hoverEnabled: true
                background: Rectangle {color: parent.hovered ? Qt.lighter(__pallette.background, 1.5) : __pallette.transparent}
                Layout.fillWidth: true
                padding: 0
                contentItem: Label{ verticalAlignment: Text.AlignVCenter; text: "Переименовать"; }
                MouseArea { anchors.fill: parent; onClicked: {__faDialog.rename(); close()}}
            }
            Pane {
                hoverEnabled: true
                background: Rectangle {color: parent.hovered ? Qt.lighter(__pallette.background, 1.5) : __pallette.transparent}
                Layout.fillWidth: true
                padding: 0
                contentItem: Label{ verticalAlignment: Text.AlignVCenter; text: "Удалить" ; }
                MouseArea { anchors.fill: parent; onClicked: {__faDialog.remove(); close()}}
            }
        }
    }

    component PopupAcceptRemove: Popup {
        id: __popupAcceptRemove
        padding: 20
        background: Rectangle {color: Qt.darker(__pallette.background, 1.5); radius: 3; border.width: 1; border.color: __pallette.white}
        Overlay.modal: Rectangle { color:"#50000000" }
        parent: __parentItem.parent
        anchors.centerIn: parent
        property string fname;
        signal accept();
        signal reject();
        modal: true
        ColumnLayout {
            Label{
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: __pallette.white
                text: "Вы Уверены что хотите удалить: "
            }
            Label{
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: __pallette.white
                text:__popupAcceptRemove.fname
            }
            RowLayout {
                width:parent.width
                Item{Layout.fillWidth: true}
                Button{
                    Layout.preferredWidth: parent.width * 4/9
                    Material.foreground: __pallette.white
                    Material.background: Qt.darker(__pallette.background, 1.2)
                    palette.buttonText: __pallette.white
                    palette.button: Qt.darker(__pallette.background, 1.2)
                    text: "Применить"
                    onClicked: {__popupAcceptRemove.accept(); __popupAcceptRemove.close()}
                }
                Item{Layout.fillWidth: true}
                Button{
                    Layout.preferredWidth: parent.width * 4/9
                    Material.foreground: __pallette.white
                    Material.background: Qt.darker(__pallette.background, 1.2)
                    palette.buttonText: __pallette.white
                    palette.button: Qt.darker(__pallette.background, 1.2)
                    text: "Отменить"
                    onClicked: {__popupAcceptRemove.reject(); __popupAcceptRemove.close()}
                }
                Item{Layout.fillWidth: true}
            }
        }
    }


    contentItem: ColumnLayout {
        Rectangle {
            id: contnet
            radius: 4
            color: Qt.lighter(__pallette.background, 1.5)
            Layout.fillWidth: true
            Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                FileDialogHeader {
                    Layout.fillWidth: true; name: "Имя"; size: "Размер";
                    onSortChanged: {
                        if(__sortedModel.sortRole !== newRole)
                            __sortedModel.sortRole = newRole;
                        else {
                            __sortedModel.changeSortOrder();
                        }
                    }
                }
                Control {background: Rectangle{color: __pallette.background;} Layout.fillWidth: true; Layout.preferredHeight: 2; Layout.leftMargin: 2; Layout.rightMargin: 2;}
                ListView {
                    id: __dataLv
                    property int accessedIndex: -1
                    clip: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 5
                    model: __sortedModel
                    spacing: 5
                    delegate: FileLineDelegate {
                        reneaming: __dataLv.accessedIndex === model.index && enableReaname
                        width: __dataLv.width;
                        name: model.name;
                        onAcceptRename: {__filesManager.rename(model.index, newName)}
                        size: model.size;
                        iconSource: "qrc:/file.svg"
                        hoverEnabled: true

                        background: Rectangle{color: model.index === __filesManager.currentIndex ? __pallette.frostDark :
                                                                                                   hovered ? Qt.lighter(__pallette.background, 1.8) :
                                                                                                             __pallette.transparent }
                        onClicked: (mouse) => {
                                       __dataLv.accessedIndex = model.index;
                                       if(mouse.button === Qt.LeftButton) { __filesManager.currentIndex = __filesManager.currentIndex === model.index ? -1 : model.index; }
                                       if(mouse.button === Qt.RightButton) { __fileActionDialog.open(); __filesManager.currentIndex = model.index; }
                                   }
                        ToolTip {id: __tooltip; visible: parent.hovered; x: 0; y: parent.height; text: model.path; delay: 2000 }
                        FileActionDialog{ id: __fileActionDialog; x: parent.mouseX; y: parent.height; onRemove: __rmDialog.open(); onRename: parent.enableReaname = true; }
                        PopupAcceptRemove{id:__rmDialog; fname: model.name; onAccept: __filesManager.remove(model.index)}
                        Connections{target: __dataLv;
                            function onContentYChanged() {__fileActionDialog.close(); enableReaname = false;}
                            function onAccessedIndexChanged(){if(__dataLv.accessedIndex !== model.index) enableReaname = false}
                        }
                    }
                }
            }
        }
        Control {
            Layout.fillWidth: true
            Layout.preferredHeight: __searchType.contentHeight * 2
            RowLayout {
                anchors.fill: parent
                Rectangle {
                    id: __searchMaskItem
                    Layout.fillHeight:  true
                    Layout.fillWidth: true
                    color:  Qt.lighter(__pallette.background, 1.5)
                    radius: 4
                    RowLayout{
                        anchors.fill: parent
                        anchors.leftMargin: 5
                        anchors.rightMargin: 5
                        Label {
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: "Имя файла"
                            color: __pallette.white
                        }
                        Rectangle {color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
                        Rectangle {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.topMargin: 3
                            Layout.bottomMargin: 3
                            Layout.rightMargin: -2
                            radius: 4
                            color: Qt.lighter(__pallette.background, 2.5)
                            TextInput {
                                anchors.fill: parent
                                anchors.leftMargin: 5
                                anchors.rightMargin: 5
                                verticalAlignment: Text.AlignVCenter
                                color: Qt.darker(__pallette.background, 1)
                                font.bold: true
                            }
                        }
                    }
                }
                Rectangle {
                    Layout.fillHeight: true
                    Layout.preferredWidth: rowLayout.width * 1.2
                    color:  Qt.lighter(__pallette.background, 1.5);
                    radius: 4
                    RowLayout{
                        id: rowLayout
                        anchors.centerIn: parent
                        height: parent.height
                        Label {
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: "Тип файла"
                            color: __pallette.white
                        }
                        Rectangle {color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
                        Label {
                            id: __searchType
                            width: contentWidth
                            height: contentHeight
                            text: ".json"
                            color: __pallette.white
                        }
                    }
                }
            }
        }
        Control {
            Layout.fillWidth: true
            Layout.preferredHeight: __btAccept.implicitHeight
            RowLayout {
                anchors.fill: parent
                Item {Layout.fillWidth: true;}
                Button{
                    id: __btAccept;
                    text: "Принять"
                    Material.foreground: __pallette.white
                    Material.background: Qt.darker(__pallette.background, 1.2)
                    palette.buttonText: __pallette.white
                    palette.button: Qt.darker(__pallette.background, 1.2)
                    onClicked: {
                        baseItem.accept()
                    }
                }
                Button{
                    id: __btCancle;
                    text: "Закрыть"
                    Material.foreground: __pallette.white
                    Material.background: Qt.darker(__pallette.background, 1.2)
                    palette.buttonText: __pallette.white
                    palette.button: Qt.darker(__pallette.background, 1.2)
                    onClicked: {
                        baseItem.reject()
                    }
                }
            }
        }
    }

    onOpened: {
        __filesManager.currentPath = "/home/spook/";
    }
}

