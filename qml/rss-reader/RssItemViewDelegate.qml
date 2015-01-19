import QtQuick 2.0

Rectangle {
    anchors.left: parent.left
    anchors.leftMargin: 2
    anchors.right: parent.right
    anchors.rightMargin: 2
    height: 80
    color: base03
    radius: defaultRadius
    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        height: 20
        renderType: Text.NativeRendering
        text: model.title
        font.pixelSize: 14
        font.bold: true
        color: base1
    }
    Text {
        id: description
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        text: model.description
        maximumLineCount: 4
        wrapMode: Text.WordWrap
        renderType: Text.NativeRendering
        font.pixelSize: 14
        color: base1
    }
}
