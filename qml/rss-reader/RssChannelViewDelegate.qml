import QtQuick 2.0

Rectangle {
    id: channelViewDelegate
    anchors.left: parent.left
    anchors.leftMargin: 2
    anchors.right: parent.right
    anchors.rightMargin: 2
    width: parent.width
    height: 50
    color: base03
    radius: defaultRadius    
    function showFeed() {
        Provider.showFeed(model.url)
    }
    Rectangle {
        id: channelImageRect
        anchors.left: parent.left
        anchors.leftMargin: 3
        anchors.verticalCenter: parent.verticalCenter
        width: height
        height: parent.height * 0.8
        color: base3
        radius: defaultRadius
        Image {
            id: channelImage
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: model.imageSource
            sourceSize.width: parent.width * 0.95
            sourceSize.height: parent.height * 0.95
            asynchronous: true
            visible: source == "" ? false : true
        }
    }
    Text {
        id: channelTitle
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: channelImageRect.right
        anchors.leftMargin: 10
        width: parent.width
        renderType: Text.NativeRendering
        text: model.title
        font.pixelSize: 14
        font.bold: true
        color: base1
    }
}
