import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

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
    background: Rectangle {
        radius: 4
        color: __pallette.background
        border.color: __pallette.white
        border.width: 1
    }

    header : Pane{
        implicitWidth: baseItem.implicitWidth
        background: Rectangle{border.color: __pallette.white; color: Qt.darker(__pallette.background, 2.0); radius: 4}
        Label {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            font.bold: true
            text: baseItem.title
        }
    }

    QtObject {
        id: __pallette
        property color frostDark: "#5E81AC"
        property color white: "#ffffff"
        property color black: "#000000"
        property color background: "#2f4f4f"
    }




    contentItem: ColumnLayout {
        Rectangle {
            id: contnet
            radius: 4
            color: Qt.lighter(__pallette.background, 1.5)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Control {
            Layout.fillWidth: true
            Layout.preferredHeight: __searchType.contentHeight * 2
            //            background: Rectangle{
            //                radius: 4
            //                color: Qt.lighter(__pallette.background, 1.5)
            //            }
            RowLayout {
                anchors.fill: parent
                //                anchors.margins: 5
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
                        }
                        Rectangle {color: __pallette.background; Layout.fillHeight: true; Layout.preferredWidth: 2; Layout.topMargin: 2; Layout.bottomMargin: 2;}
                        Label {
                            id: __searchType
                            width: contentWidth
                            height: contentHeight
                            text: ".json"
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


    //    contentItem: ListView {
    //        id: __lv
    //        model: 50
    //        spacing: 15
    //        clip: true
    //        delegate: Button{
    //            width: __lv.width
    //        }
    //    }
}

