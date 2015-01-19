import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    property string base03: "#002b36"
    property string base02: "#073642"
    property string base01: "#586e75"
    property string base00: "#657b83"
    property string base0:  "#839496"
    property string base1:  "#93a1a1"
    property string base2:  "#eee8d5"
    property string base3:  "#fdf6e3"
    property string yellow: "#b58900"
    property string orange: "#cb4b16"
    property string red:    "#dc322f"
    property string magenta:"#d33682"
    property string violet: "#6c71c4"
    property string blue:   "#268bd2"
    property string cyan:   "#2aa198"
    property string green:  "#859900"
    property int defaultRadius: 5

    id: mainWindow
    width: 1280
    height: 720
    color: base02
    ColumnLayout {
        id: channelsLayout
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 300
        Rectangle {
            id: newChannel
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 50
            anchors.top: parent.top
            anchors.margins: 3
            color: mainWindow.color
            z: parent.z + 1
            Rectangle {
                id: enterTextLabel
                anchors.fill: parent
                color: base03
                border.color: base02
                radius: defaultRadius
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Add new url")
                    renderType: Text.NativeRendering
                    font.pixelSize: 18
                    font.bold: true
                    color: base01
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        enterTextLabel.visible = false
                        newFeedEditText.visible = true
                        newFeedInput.focus = true
                        newFeedInput.text = ""
                    }
                }
            }
            Rectangle {
                id: newFeedEditText
                color: base3
                anchors.fill: parent
                visible: false
                radius: defaultRadius
                TextInput  {
                    id: newFeedInput
                    color: base1
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    font.pixelSize: 20
                    readOnly: false
                    wrapMode: TextEdit.NoWrap
                    font.pointSize: 16
                    onAccepted: {
                        Provider.addNewUrl(text)
                        enterTextLabel.visible = true
                        newFeedEditText.visible = false
                    }
                }
            }
        }
        Rectangle {
            id: listOfChannels
            Layout.preferredWidth: parent.width
            anchors.top: newChannel.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 30
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            color: base02            
            ListView {
                id: channels
                spacing: 2
                anchors.fill: parent
                model: ChannelsModel
                focus: true
                clip: true
                header: Rectangle {
                    height: 20
                    width: listOfChannels.width
                    color: base02
                    Text {
                        text: qsTr("Feeds")
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: base1
                        renderType: Text.NativeRendering
                        font.bold: true
                        font.pixelSize: 16
                    }
                }
                delegate: RssChannelViewDelegate {
                    border.color: ListView.isCurrentItem ? base01 : base03
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            channels.currentIndex = index
                        }
                    }
                }
                onCountChanged: channels.currentIndex = channels.count -1
                onCurrentIndexChanged: channels.currentItem.showFeed()
                onMovementStarted: channelsScrollIndicator.opacity = 1
                onMovementEnded: channelsScrollIndicator.opacity = 0
                Behavior on contentY {
                    PropertyAnimation {
                        duration: 500
                        easing.type: Easing.OutQuad
                        onRunningChanged:  {
                            if (running) {
                                channelsScrollIndicator.opacity = 1
                            } else {
                                channelsScrollIndicator.opacity = 0
                            }
                        }
                    }
                }
            }
            ScrollIndicator {
                id: channelsScrollIndicator
                anchors.top: listOfChannels.top
                anchors.right: listOfChannels.right
                anchors.rightMargin: 5
                anchors.bottom: listOfChannels.bottom
                opacity: 0
                position: channels.visibleArea.yPosition
                pageSize: channels.visibleArea.heightRatio
            }
        }
    }
    Rectangle {
        id: verticalLine
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        anchors.left: channelsLayout.right
        width:1
        color: base01
    }
    Rectangle {
        id: listOfNews
        anchors.left: verticalLine.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: base02
        Rectangle {
            id: newsHeader
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20
            color: base02
            z: feed.z + 1
            Text {
                text: qsTr("News")
                anchors.horizontalCenter: parent.horizontalCenter
                color: base1
                renderType: Text.NativeRendering
                font.bold: true
                font.pixelSize: 16
            }
        }
        ListView {
            id: feed
            spacing: 2
            anchors.top: newsHeader.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            model: FeedModel
            focus: true
            clip: true
            delegate: RssItemViewDelegate {
                border.color: ListView.isCurrentItem ? base01 : base03
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        onClicked: Qt.openUrlExternally(model.link)
                        feed.currentIndex = index
                    }

                }
            }
            onCountChanged: currentIndex = -1
            onMovementStarted: feedScrollIndicator.opacity = 1
            onMovementEnded: feedScrollIndicator.opacity = 0
            Behavior on contentY {
                PropertyAnimation {
                    duration: 500
                    easing.type: Easing.OutQuad
                    onRunningChanged:  {
                        if (running) {
                            feedScrollIndicator.opacity = 1
                        } else {
                            feedScrollIndicator.opacity = 0
                        }
                    }
                }
            }
        }
        ScrollIndicator {
            id: feedScrollIndicator
            anchors.top: listOfNews.top
            anchors.right: listOfNews.right
            anchors.rightMargin: 5
            anchors.bottom: listOfNews.bottom
            opacity: 0
            position: feed.visibleArea.yPosition
            pageSize: feed.visibleArea.heightRatio
        }
    }

}
