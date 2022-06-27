import QtQuick
import QtQuick.Controls

    Rectangle {
        id: rectangle
        property string title: "Hello World!" //默认的消息框文字
        property alias closebtn: closebtn
        width: 200
        height: 45 //默认的组件宽高
        color: "#7447b9f0"
        radius: 5
        border.color: "#2cace5"
        border.width: 2
        Image {
            id: image
            x:20 //不知为什么设置anchors.leftMargin无效，改用x偏移20px
            width: 32
            height: 25
            source: "icons/logo.png"
            fillMode: Image.PreserveAspectFit
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            id: text1
            width: 264
            height: 25
            text: qsTr(title.toString())
            font.pixelSize: 16
            anchors.left: image.right
            anchors.verticalCenter: parent.verticalCenter
        }
        Button{
            id: closebtn
            width: 30
            height: 30
            icon.name:"window-close"
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: loadMessage.source=""
        }
    }
