import QtQuick 2.0

Item {
     id: scrollIndicator

     property real position
     property real pageSize

     Behavior on opacity { PropertyAnimation {  duration: 200 } }

     Rectangle {
         anchors.left: parent.left
         anchors.top: parent.top
         anchors.topMargin: scrollIndicator.position * scrollIndicator.height + 1 < 0 ? 0 : scrollIndicator.position * scrollIndicator.height + 1
         anchors.bottom: parent.bottom
         anchors.bottomMargin: {
             if (scrollIndicator.height - scrollIndicator.position * scrollIndicator.height + 1 - scrollIndicator.pageSize * scrollIndicator.height < 0)
                 0
             else
                 scrollIndicator.height - scrollIndicator.position * scrollIndicator.height + 1 - scrollIndicator.pageSize * scrollIndicator.height
         }
         x: 1
         width: 3
         radius: width / 2
         color: base2
         opacity: 0.6
         border.color: base3
         border.width: 5
     }
 }
